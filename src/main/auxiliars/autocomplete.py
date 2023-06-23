"""
Module for autocomplete function.
"""

from typing import Optional, TYPE_CHECKING

from discord import ChannelType, Interaction
from discord.app_commands import Choice

from ..files import search_files, split_path
from ..db.shortcuts import (get_listened_channels, get_authorised_users)

if TYPE_CHECKING:

    from os import PathLike


async def channels_autocomplete(interaction: Interaction,
                                 current: str,
                                 channels_types: Optional[tuple[ChannelType, ...]]=None) -> list[Choice[str]]:
    """
    Returns all the channels from the guilds that matches the types and
    current search.
    """
    canales = interaction.guild.channels

    return [Choice(name=canal.name, value=str(canal.id)) for canal in canales
            if ((current.lower() in canal.name.lower())
            and (canal.type in channels_types if channels_types is not None else True))][:25]
    


async def all_channels_autocomplete(interaction: Interaction,
                                       current: str) -> list[Choice[str]]:
    """
    Returns all the channels from the guilds that matches the current search.
    """
    return await channels_autocomplete(interaction =interaction,
                                        current=current)


async def text_channels_autocomplete(interaction: Interaction,
                                       current: str) -> list[Choice[str]]:
    """
    Returns all the channels from the guild that are text channels.
    """
    return await channels_autocomplete(interaction=interaction,
                                        current=current,
                                        channels_types=(ChannelType.text, ))

async def listened_channels_autocomplete(_interaction: Interaction,
                                            current: str) -> list[Choice[str]]:
    """
    Returns all the listened channels by the bot.
    """

    choices_list = []

    for lista_ch in get_listened_channels().values():
        for id_ch, name_ch in lista_ch:
            if current.lower() in name_ch.lower():
                choices_list.append(Choice(name=name_ch, value=str(id_ch)))

    return choices_list[:25]

async def guild_members_autocomplete(interaction: Interaction,
                                        current: str) -> list[Choice[str]]:
    """
    Returns all the users from the current guild.
    """

    return [Choice(name=member.display_name, value=str(member.id))
            for member in interaction.guild.members
            if (current.lower() in member.name.lower()
                or (current.lower() in member.nick.lower()
                    if member.nick is not None else False))
    ][:25]


async def authorised_users_autocomplete(_interaction: Interaction,
                                              current: str) -> list[Choice[str]]:
    """
    Returns all the authorised users.
    """

    return [Choice(name=f"{name}#{discriminator}", value=str(id_user))
            for (id_user, name, discriminator) in get_authorised_users()
            if current.lower() in name.lower()
    ][:25]


async def path_autocomplete(_interaction: Interaction,
                              current: str,
                              current_path: "PathLike") -> list[Choice[str]]:
    """
    Returns all the files of a path.
    """

    return [
        Choice(name=split_path(path)[1], value=path)
        for path in search_files(path_name=current_path)
        if current.lower() in path.lower()
    ][:25]