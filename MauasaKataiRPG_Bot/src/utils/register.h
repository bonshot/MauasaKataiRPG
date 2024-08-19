#include <dpp/dpp.h>
#include <string>
#include <vector>
#include <map>
#include <string>

#ifndef __REGISTER_H__
#define __REGISTER_H__

const std::string REGISTER_URL = "http://mauasakatairpg_api:5000/api/add_user";
const std::string RACES_URL = "http://mauasakatairpg_api:5000/api/races";

/**
* @brief Function that converts an std::map to JSON
* @param data: a pair of key value strings to be converted to JSON -> map<string, string>
* @return string: The JSON in a string
**/
std::string map_to_json(const std::map<std::string, std::string>& data);

/**
 * @brief Function that creates a default embed
* @param title: The title of the embed -> string
* @param description: The description of the embed -> string
* @return dpp::embed: The embed created
**/
std::string get_register_description(std::string class_selected, std::string race_selected);

/**
 * @brief Function that creates a default embed
 * @param title: The title of the embed -> string
 * @param description: The description of the embed -> string
 * @return dpp::embed: The embed created
**/
dpp::embed create_default_embed(std::string title, std::string description);

/**
 * @brief Function that creates the message for the register command with the components
 * @param event: The event that triggered the function -> const dpp::slashcommand_t&
 * @param class_selected: The class selected by the user -> string
 * @param race_selected: The race selected by the user -> string
 * @return dpp::message: The message created
**/
dpp::message get_register_message(const dpp::slashcommand_t& event, std::string class_selected, std::string race_selected);

/**
* Function that registers the user to the game
* @param event: the event that triggered the function -> const dpp::slashcommand_t&
* @param bot: The bot cluster already initialized on main -> dpp::cluster&
**/
void bot_on_event_register(const dpp::slashcommand_t& event, dpp::cluster& bot);
dpp::component create_default_selector_component(std::string placeholder, std::string custom_id, std::array<std::string, 9> options);
dpp::component create_default_button_component(std::string label, std::string custom_id, dpp::component_style style);
#endif