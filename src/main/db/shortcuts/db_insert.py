"""
Module for INSERT commands shortcuts.
"""

from ..database import (update_table_entry, value_exists_in_table,
                        insert_data_in_table)
from .db_query import exists_listened_channel
from .fetch_db import get_default_prefix


def update_guild(guild_id: int, guild_name: str) -> bool:
    """
    Registers the guild in the DB. 
    
    Returns 'True' if the guild is
    already present, else returns 'False'.
    
    """

    if value_exists_in_table(table="guilds", id=guild_id):
        update_table_entry(table="guilds",
                                 col_name="name",
                                 value=guild_name)
        return True

    insert_data_in_table(table="guilds",
                            default_primary_key=False,
                            values=(guild_id, guild_name))
    update_prefix(get_default_prefix(), guild_id)
    return False


def update_prefix(new_prefix: str, guild_id: int) -> bool:
    """
    Updates the prefix of a specific guild. 
    
    Returns 'True' if the prefix is already present, else returns 'False'.
    """

    if value_exists_in_table(table="prefixes", id_guild=guild_id):
        update_table_entry(table="prefixes",
                                 col_name="prefix",
                                 value=new_prefix)
        return True

    insert_data_in_table(table="prefixes",
                            default_primary_key=True,
                            values=(guild_id, new_prefix))
    return False


def update_listened_channel(channel_id: int, channel_name: str, id_guild: int) -> bool:
    """
    Updates the listened channels data. 
    
    Returns 'True' if the channel is already present, else returns 'False'.
    """

    if exists_listened_channel(id_channel=channel_id):
        update_table_entry(table="listenable_channels",
                                    col_name="nombre",
                                    value=channel_name,
                                    # conditions
                                    id=channel_id)
        return True

    insert_data_in_table(table="listenable_channels",
                            default_primary_key=False,
                            values=(channel_id, id_guild, channel_name))
    return False

def register_authorised_user(name: str,
                                 discriminator: str,
                                 id_user: int) -> bool:
    """
    Registers an authorised user. 
    If the user is not repeated, returns 'True', else returns 'False'.
    """

    if value_exists_in_table(table="authorised_users",
                            id=id_user):
        return False

    insert_data_in_table(table="authorised_users",
                            default_primary_key=False,
                            values=(id_user, name, discriminator))
    return True