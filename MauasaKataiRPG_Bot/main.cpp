#include <dpp/dpp.h>

#include "headers/env_loader.h"
#include "headers/event_handler.h"
#include "headers/ready_handler.h"

using namespace std;

unordered_map<string, string> ENV = load_env_file(".env");

int main() {
    string bot_token = ENV.at("BOT_TOKEN");
    dpp::cluster bot(bot_token);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        bot_on_event_handler(event, bot);
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot_on_ready_handler(bot);
        }
    });

    bot.start(dpp::st_wait);
}