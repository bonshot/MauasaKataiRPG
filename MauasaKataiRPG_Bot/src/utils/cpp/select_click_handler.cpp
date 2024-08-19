#include <dpp/dpp.h>
#include <string>

#include "../register.h"
#include "../select_click_handler.h"



void bot_on_select_click_handler(const dpp::select_click_t& event, dpp::cluster& bot) {
    std::string custom_id = event.custom_id;
    dpp::message old_msg = event.command.msg;
    std::string class_selected = "";
    std::string race_selected = "";

    if(custom_id.find("class_select") != std::string::npos){
        class_selected = event.values[0];
        race_selected = (old_msg.components[1].components[0].placeholder != "Select your race") ? old_msg.components[1].components[0].placeholder : "";
        old_msg.components[0].components[0].placeholder = class_selected;
        old_msg.components[1].components[0].placeholder = old_msg.components[1].components[0].placeholder;
    } else if(custom_id.find("race_select") != std::string::npos){
        class_selected = (old_msg.components[0].components[0].placeholder != "Select your class") ? old_msg.components[0].components[0].placeholder : "";
        race_selected = event.values[0];
        old_msg.components[0].components[0].placeholder = old_msg.components[0].components[0].placeholder;
        old_msg.components[1].components[0].placeholder = race_selected;
    }

    dpp::embed register_embed = create_default_embed("Setting up your character", get_register_description(class_selected, race_selected));
    old_msg.embeds[0] = register_embed;

    event.reply(dpp::ir_update_message, old_msg);
}