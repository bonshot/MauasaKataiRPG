#include <dpp/dpp.h>
#include <unordered_map>

#include "../register.h"

#define IMG_URL "https://i.ibb.co/cFkKzbj/imagen-2024-07-19-042212883.png"

void bot_on_event_register(const dpp::slashcommand_t& event, dpp::cluster& bot) {
    dpp::embed register_embed = dpp::embed()
        .set_color(dpp::colors::light_blue)
        .set_title("Register your account")
        .set_thumbnail(IMG_URL);

    std::unordered_map<std::string, std::string> commands{
        {"class_select", "class_select_" + std::to_string(event.command.id)},
        {"race_select", "race_select_" + std::to_string(event.command.id)},
        {"confirm_button", "confirm_button_" + std::to_string(event.command.id)},
        {"cancel_button", "cancel_button_" + std::to_string(event.command.id)}
    };

    dpp::component class_menu = dpp::component()
        .set_type(dpp::cot_selectmenu)
        .set_placeholder("Select your class")
        .set_id(commands["class_select"]);

    for (const auto& cls : CLASSES) {
        class_menu.add_select_option(dpp::select_option(cls.first, cls.second, "Desc"));
    }

    dpp::component race_menu = dpp::component()
        .set_type(dpp::cot_selectmenu)
        .set_placeholder("Select your race")
        .set_id(commands["race_select"]);

    for (const auto& race : RACES) {
        race_menu.add_select_option(dpp::select_option(race.first, race.second, "Desc"));
    }

    dpp::message msg(event.command.channel_id, register_embed);

    msg.add_component(dpp::component().add_component(class_menu))
       .add_component(dpp::component().add_component(race_menu))
       .add_component(dpp::component().add_component(
            dpp::component()
                .set_type(dpp::cot_button)
                .set_label("Confirm")
                .set_style(dpp::cos_primary)
                .set_id(commands["confirm_button"])
        )
    ).add_component(dpp::component().add_component(
            dpp::component()
                .set_type(dpp::cot_button)
                .set_label("Cancel")
                .set_style(dpp::cos_danger)
                .set_id(commands["cancel_button"])
        )
    );

    event.reply(msg);
}