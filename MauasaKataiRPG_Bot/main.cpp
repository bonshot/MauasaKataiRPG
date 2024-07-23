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

#define IMG_URL "https://i.ibb.co/cFkKzbj/imagen-2024-07-19-042212883.png"

std::string map_to_json(const std::map<std::string, std::string>& data) {
    std::string json = "{";
    bool first = true;
    for (const auto& pair : data) {
        if (!first) {
            json += ",";
        }
        json += "\"" + pair.first + "\":\"" + pair.second + "\"";
        first = false;
    }
    json += "}";
    return json;
}

std::unordered_map<std::string, std::string> load_env_file(const std::string& fileName) {
    std::unordered_map<std::string, std::string> variables;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Cannot open env file " << fileName << std::endl;
        return variables;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            variables[key] = value;
        }
    }
    file.close();
    return variables;
}

const std::unordered_map<std::string, std::string> ENV = load_env_file(".env");
const std::string register_url = "http://mauasakatairpg_api:5000/api/add_user";

void event_register(const dpp::slashcommand_t& event, dpp::cluster& bot) {
    dpp::embed register_embed = dpp::embed()
        .set_color(dpp::colors::light_blue)
        .set_title("Register your account")
        .set_thumbnail(IMG_URL);

    dpp::message msg(event.command.channel_id, register_embed);

    std::string class_select_id = "class_select_" + std::to_string(event.command.id);
    std::string race_select_id = "race_select_" + std::to_string(event.command.id);
    std::string confirm_button_id = "confirm_button_" + std::to_string(event.command.id);
    std::string cancel_button_id = "cancel_button_" + std::to_string(event.command.id);

    std::vector<std::pair<std::string, std::string>> classes = {
        {"Warrior", "Warrior"},
        {"Rogue", "Rogue"},
        {"Mage", "Mage"},
        {"Cleric", "Cleric"},
        {"Paladin", "Paladin"},
        {"Bard", "Bard"},
        {"Priest", "Priest"},
        {"Warlock", "Warlock"},
        {"Ranger", "Ranger"}
    };

    std::vector<std::pair<std::string, std::string>> races = {
        {"Human", "Human"},
        {"Elf", "Elf"},
        {"Dark Elf", "Dark Elf"},
        {"Dwarf", "Dwarf"},
        {"Orc", "Orc"},
        {"Giant", "Giant"},
        {"Goblin", "Goblin"},
        {"Undead", "Undead"},
        {"Gnome", "Gnome"}
    };

    dpp::component class_menu = dpp::component()
        .set_type(dpp::cot_selectmenu)
        .set_placeholder("Select your class")
        .set_id(class_select_id);
    
    for (const auto& cls : classes) {
        class_menu.add_select_option(dpp::select_option(cls.first, cls.second, "Desc"));
    }

    dpp::component race_menu = dpp::component()
        .set_type(dpp::cot_selectmenu)
        .set_placeholder("Select your race")
        .set_id(race_select_id);
    
    for (const auto& race : races) {
        race_menu.add_select_option(dpp::select_option(race.first, race.second, "Desc"));
    }

    msg.add_component(
        dpp::component().add_component(class_menu)
    ).add_component(
        dpp::component().add_component(race_menu)
    ).add_component(
        dpp::component().add_component(
            dpp::component()
                .set_type(dpp::cot_button)
                .set_label("Confirm")
                .set_style(dpp::cos_primary)
                .set_id(confirm_button_id)
        )
    ).add_component(
        dpp::component().add_component(
            dpp::component()
                .set_type(dpp::cot_button)
                .set_label("Cancel")
                .set_style(dpp::cos_danger)
                .set_id(cancel_button_id)
        )
    );

    event.reply(msg);
}

int main() {
    std::string bot_token = ENV.at("BOT_TOKEN");
    dpp::cluster bot(bot_token);
    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        std::string command_name = event.command.get_command_name();

        if(command_name == "register"){
            event_register(event, bot);
        }

        if(command_name == "beep"){
            event.reply("Boop!");
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("beep", "Beep Boop!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("register", "Register with the RPG system", bot.me.id));
        }
    });

    bot.start(dpp::st_wait);
}
