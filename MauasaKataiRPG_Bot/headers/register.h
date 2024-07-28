#ifndef __REGISTER_H__
#define __REGISTER_H__

const std::string register_url = "http://mauasakatairpg_api:5000/api/add_user";

// Temporal
const std::vector<std::pair<std::string, std::string>> CLASSES = {
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

// Temporal
const std::vector<std::pair<std::string, std::string>> RACES = {
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

/*
* @brief Function that converts an std::map to JSON
* @param std::map<std::string, std::string>: A pair of key value strings to be converted to JSON
* @return string: The JSON in a string
*/
std::string map_to_json(const std::map<std::string, std::string>& data);

/*
* Function that registers the user to the game
* @param const dpp::slashcommand_t&: The event that triggered the function
* @param dpp::cluster&: The bot cluster already initialized on main
*/
void bot_on_event_register(const dpp::slashcommand_t& event, dpp::cluster& bot);

#endif