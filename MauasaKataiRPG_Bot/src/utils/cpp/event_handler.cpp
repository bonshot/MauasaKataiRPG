#include <dpp/dpp.h>
#include <string>
#include "../event_handler.h"
#include "../register.h"

void bot_on_event_handler(const dpp::slashcommand_t& event, dpp::cluster& bot) {
    std::string command_name = event.command.get_command_name();

    if (command_name == "register") {
        bot_on_event_register(event, bot);
    }

    if (command_name == "beep") {
        event.reply("Boop!");
    }

    
}