"""
Module for auxiliar functions.
"""

from typing import TYPE_CHECKING

from discord import Message

from ..db.shortcuts import get_prefix_guild

if TYPE_CHECKING:

    from ..MauasaKataiRPG import MauasaKataiRPG


def get_prefix(_bot: "MauasaKataiRPG", mensaje: Message) -> str:
    """
    It looks in the prefix dictionary and returns the one
    that corresponds to the server from where the command is called.
    """

    return get_prefix_guild(guild_id=mensaje.guild.id)