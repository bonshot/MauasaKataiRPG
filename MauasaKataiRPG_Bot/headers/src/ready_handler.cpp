#include <dpp/dpp.h>

#include "../ready_handler.h"

void bot_on_ready_handler(dpp::cluster& bot){
    bot.global_command_create(dpp::slashcommand("beep", "Beep Boop!", bot.me.id));
    bot.global_command_create(dpp::slashcommand("register", "Register with the RPG system", bot.me.id));
}