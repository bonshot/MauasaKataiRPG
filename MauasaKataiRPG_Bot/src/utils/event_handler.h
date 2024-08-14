#include <dpp/dpp.h>

#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

/**
* Function that handles the bot events for better organization
* @param event: The event that is being handled -> const dpp::slashcommand_t&
* @param bot: The bot that is being used -> dpp::cluster&
**/
void bot_on_event_handler(const dpp::slashcommand_t& event, dpp::cluster& bot);

#endif