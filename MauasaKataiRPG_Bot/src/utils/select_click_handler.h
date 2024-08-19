#include <dpp/dpp.h>

#ifndef __SELECT_CLICK_HANDLER_H__
#define __SELECT_CLICK_HANDLER_H__

/**
 * @brief Function that handles the select click event
 * @param event: the event that triggered the function -> const dpp::select_click_t&
 * @param bot: The bot cluster already initialized on main -> dpp::cluster&
**/
void bot_on_select_click_handler(const dpp::select_click_t& event, dpp::cluster& bot);
#endif