#include <dpp/dpp.h>
#include <sstream>
#include <unordered_map>

#include "../register.h"
#include "../utils.h"

using namespace std;

#define IMG_URL "https://i.ibb.co/cFkKzbj/imagen-2024-07-19-042212883.png"
#define DOCS_URL "https://mauasakatairpg.bonzzard.com.ar/docs"
#define CLASSES_URL "https://mauasakatairpg.bonzzard.com.ar/api/classes/"
#define RACES_URL "https://mauasakatairpg.bonzzard.com.ar/api/races/"
#define COLOR 16711783
#define WHITESPACE " "

const array<string, 9> CLASSES = {"Warrior", "Rogue", "Mage", "Cleric", "Paladin", "Bard", "Priest", "Warlock", "Ranger"};
const array<string, 9> RACES = {"Human", "Elf", "Dark elf", "Dwarf", "Orc", "Giant", "Goblin", "Undead", "Gnome"};

string get_whitespace(string value, int line, bool left) {
    const int lsize[8] = {11, 11, 8, 7, 3, 4, 11, 12}; // Default left space for each line
    const int rsize[8] = {15, 8, 10, 4, 7, 9, 12, 11};
    string result = "";
    int size = (left)? lsize[line] - value.size() : rsize[line] - value.size();
    for (int i = 0; i < size; i++)
        result += WHITESPACE;
    return result;
}

array<string, 8> get_stats(string url, string name, bool is_class) {
    array<string, 8> stats;
    array<string, 8> left_stats = {"class", "extra_vigor", "extra_strength", "extra_dexterity", "extra_concentration", "extra_intelligence", "extra_faith", "extra_luck"};
    array<string, 8> right_stats = {"race", "extra_health", "extra_mana", "extra_conviction", "extra_stamina", "extra_armor", "extra_magic_resistance", "location"};
    stats = (is_class)?
        array<string, 8>{"TBD", "0", "0", "0", "0", "0", "0", "0"}:
        array<string, 8>{"TBD", "0", "0", "0", "0", "0", "0", "1"};
    
    if(name != "") {
        std::string full_url = (name == "Dark elf")? url + "Dark_elf" : url + name;
        string response = http_get_request(full_url);
        if(is_class){
            for(int i = 0; i < 8; i ++){
                stats[i] = 
                    (left_stats[i] == "class")? name:
                    json_value_finder(response, left_stats[i]);
            }
        }

        if(!is_class) {
            for(int i = 0; i < 8; i++){
                stats[i] = 
                    (right_stats[i] == "race")? name :
                    (right_stats[i] == "location")? "1" :
                    json_value_finder(response, right_stats[i]);
            }
        }
    } 
    return stats;
}

string get_register_description(string class_selected, string race_selected) {
    array<string, 8> lv = get_stats(CLASSES_URL, class_selected, true);
    array<string, 8> rv = get_stats(RACES_URL, race_selected, false);
    ostringstream result;

    result  << "Welcome to **MauasaKataiRPG**! Let's set up your character.\n"
            << "Please select your **class** and your **race**.\n"
            << "With that information we can set up your stats.\n"
            << "```css\n"
            << "┏━━━━━━━━━━━━━━━━━━━┰━━━━━━━━━━━━━━━━━━━━━━┓\n"
            << "┃ Class: "          << lv[0] << get_whitespace(lv[0], 0, true) << "┃ Race: "             << rv[0] << get_whitespace(rv[0], 0, false) << "┃\n"
            << "┃ Vigor: "          << lv[1] << get_whitespace(lv[1], 1, true) << "┃ Base Health: "      << rv[1] << get_whitespace(rv[1], 1, false) << "┃\n"
            << "┃ Strength: "       << lv[2] << get_whitespace(lv[2], 2, true) << "┃ Base Mana: "        << rv[2] << get_whitespace(rv[2], 2, false) << "┃\n"
            << "┃ Dexterity: "      << lv[3] << get_whitespace(lv[3], 3, true) << "┃ Base Conviction: "  << rv[3] << get_whitespace(rv[3], 3, false) << "┃\n"
            << "┃ Concentration: "  << lv[4] << get_whitespace(lv[4], 4, true) << "┃ Base Stamina: "     << rv[4] << get_whitespace(rv[4], 4, false) << "┃\n"
            << "┃ Intelligence: "   << lv[5] << get_whitespace(lv[5], 5, true) << "┃ Base Armor: "       << rv[5] << get_whitespace(rv[5], 5, false) << "┃\n"
            << "┃ Faith: "          << lv[6] << get_whitespace(lv[6], 6, true) << "┃ Base MR: "          << rv[6] << get_whitespace(rv[6], 6, false) << "┃\n"
            << "┃ Luck: "           << lv[7] << get_whitespace(lv[7], 7, true) << "┃ Location: "         << rv[7] << get_whitespace(rv[7], 7, false) << "┃\n"
            << "┗━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━┛\n"
            << "```";
        
    return result.str();
}

dpp::embed create_default_embed(string title, string description){
    return dpp::embed()
        .set_color(COLOR)
        .set_title(title)
        .set_thumbnail(IMG_URL)
        .set_description(description);
}

dpp::component create_default_selector_component(string placeholder, string custom_id, array<string, 9> options){
    dpp::component selector = dpp::component()
        .set_type(dpp::cot_selectmenu)
        .set_placeholder(placeholder)
        .set_id(custom_id);

    for(const auto& option : options){
        selector.add_select_option(dpp::select_option(option.c_str(), option.c_str()));
    }

    return selector;
}

dpp::component create_default_button_component(string label, string custom_id, dpp::component_style style){
    return dpp::component()
        .set_type(dpp::cot_button)
        .set_label(label)
        .set_style(style)
        .set_id(custom_id);
}


void bot_on_event_register(const dpp::slashcommand_t& event, dpp::cluster& bot) {
    string class_selected = "";
    string race_selected = "";

    dpp::embed register_embed = create_default_embed("Setting up your character", get_register_description(class_selected, race_selected));

    unordered_map<string, string> commands{
        {"class_select", "class_select_" + to_string(event.command.id)},
        {"race_select", "race_select_" + to_string(event.command.id)},
        {"confirm_button", "confirm_button_" + to_string(event.command.id)},
        {"cancel_button", "cancel_button_" + to_string(event.command.id)}
    };

    dpp::component class_menu = create_default_selector_component("Select your class", commands["class_select"], CLASSES);
    dpp::component race_menu = create_default_selector_component("Select your race", commands["race_select"], RACES);    
    dpp::component cancel_button = create_default_button_component("Cancel", commands["cancel_button"], dpp::cos_danger);
    dpp::component confirm_button = create_default_button_component("Register", commands["confirm_button"], dpp::cos_success);

    dpp::message msg(event.command.channel_id, register_embed);

    msg.add_component(dpp::component().add_component(class_menu))
       .add_component(dpp::component().add_component(race_menu)) 
       .add_component(dpp::component().add_component(confirm_button)
       .add_component(cancel_button));

    event.reply(msg);
}