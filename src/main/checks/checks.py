"""
Módulo que contiene funciones que verifican
condiciones.
"""

from discord import Message

from ..db.shortcuts import exists_listened_channel


def is_listened_channel(message: Message) -> bool:
    """
    Returns 'True' if the channel is listened.
    If not, returns 'False'.
    """
    if message.guild is None: # If it's a slash command, for example
        return False

    return exists_listened_channel(id_channel=message.channel.id)