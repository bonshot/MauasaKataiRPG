"""
Module for decorator checks.
"""

from discord import Interaction
from discord.app_commands import check

from ...db.shortcuts import exists_authorised_user


def is_authorised_user():
    """
    Verifies if the user is authorised to use admin commands.
    """

    def predicate(interaction: Interaction) -> bool:
        """
        Verifies if the user is in.
        """

        return exists_authorised_user(interaction.user.id)

    return check(predicate)