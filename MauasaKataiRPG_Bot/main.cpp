#include <dpp/dpp.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

std::unordered_map<std::string, std::string> load_env_file(const std::string& fileName) {
    std::unordered_map<std::string, std::string> variables;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Cannot open env file " << fileName << std::endl;
        return variables;
    }

    std::string linea;
    while (std::getline(file, linea)) {
        std::istringstream iss(linea);
        std::string clave, valor;
        if (std::getline(iss, clave, '=') && std::getline(iss, valor)) {
            variables[clave] = valor;
        }
    }

    file.close();
    return variables;
}

void process_curl(CURL* curl, const std::string& url, const std::string& data) {
    CURLcode res;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    curl_slist_free_all(headers);
}

void send_post_request(const std::string& url, const std::string& data) {
    CURL* curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        process_curl(curl, url, data);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void event_register(const dpp::slashcommand_t& event) {
    std::string url = "http://mauasakatairpg_api:5000/api/add_user";
    std::string username = event.command.usr.username;
    std::string password = event.command.usr.username;
    std::string email = std::get<std::string>(event.get_parameter("email"));
    std::string data = "{\"username\": \"" + username + "\", \"password\": \"" + password + "\", \"email\": \"" + email + "\"}";
    send_post_request(url, data);
    event.reply("You have been registered!");
}

int main() {
    std::string envfile = ".env";
    std::unordered_map<std::string, std::string> env = load_env_file(envfile);
    std::string bot_token = env["BOT_TOKEN"];
    std::cout << "Bot token: " << env["BOT_TOKEN"] << std::endl;

    dpp::cluster bot(bot_token);
    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        std::string command_name = event.command.get_command_name();
        (command_name == "register") ? event_register(event) :
        (command_name == "beep") ? event.reply("Boop!") :
        event.reply("Command not found!");
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("beep", "Beep Boop!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("register", "Register with the RPG system", bot.me.id)
                .add_option(dpp::command_option(dpp::co_string, "email", "Your email address", true))
            );
        }
    });

    bot.start(dpp::st_wait);
}
