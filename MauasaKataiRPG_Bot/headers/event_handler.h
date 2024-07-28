#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

/*
* Function that handles the bot events for better organization
* @param dpp::slashcommand_t event: The event that is being handled
* @param dpp::cluster& bot: The bot that is being used
*/
void bot_on_event_handler(const dpp::slashcommand_t& event, dpp::cluster& bot);

#endif