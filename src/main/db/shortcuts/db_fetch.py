"""
Module for FETCH commands shortcuts.
"""

from os import PathLike
from typing import TYPE_CHECKING, Tuple

from ..database import fetch_table_data

if TYPE_CHECKING:
    from ..database import FetchResult


def get_property(propiedad: str) -> "FetchResult":
    "Consigue alguna propiedad de BotShot."

    return fetch_table_data("properties",
                                sacar_uno=True,
                                nombre=propiedad)[2]


def get_version() -> str:
    "Gets the version of the bot."

    return get_property("version")


def get_bot_id() -> int:
    "Gets the bot ID."

    return int(get_property("bot_id"))


def get_default_prefix() -> str:
    "Gets the default bot prefix."

    return get_property("default_prefix")


def get_backup_limit_db() -> int:
    "Gets the limit of backups of dbs."

    return int(get_property("db_backup_limit"))


def get_db_path(path_name: str) -> PathLike:
    "Gets a path of the DB."

    res = fetch_table_data("paths",
                               fetch_one=True,
                               path_name=path_name)

    # The value will always be the third column
    return res[2]


def get_db_paths(path_name: str) -> Tuple[PathLike, ...]:
    "Gets more than one path of the DB."

    res = fetch_table_data("paths",
                               fetch_one=False,
                               path_name=path_name)

    # The values will always be in the third column
    return tuple(col[2] for col in res)


def get_images_path() -> PathLike:
    "Gets the path of the dir 'images'."

    return get_db_path("images")


def get_cogs_path() -> PathLike:
    "Gets the cogs path."

    return get_db_path("cogs")


def get_log_path() -> PathLike:
    "Gets the log path."

    return get_db_path("log")


def get_backup_path() -> PathLike:
    "Gets backups path."

    return get_db_path("backup")

def get_guild_prefix(guild_id: int) -> str:
    "Returns a prefix for the given guild id."

    res = fetch_table_data("prefixes",
                               fetch_one=True,
                               id_guild=guild_id)

    if not res:
        return get_default_prefix()

    return res[2]


def get_listened_channels() -> dict[int, tuple[tuple[int, str], ...]]:
    """
    Returns a dict in which the keys are guild ids, and the values
    a tuple in which its elements are other subtuples. 
    
    These subtuples have the id and the name of the channels belonging to that guild.
    """

    data = fetch_table_data(table="listenable_channels")
    final_dict = {}

    for channel_id, id_guild, channel_name in data:
        if id_guild not in final_dict:
            final_dict[id_guild] = []
        
        final_dict[id_guild].append((channel_id, channel_name))


    # To make the dict immutable
    for ch_list in final_dict.values():
        for ch_data in ch_list:
            ch_data = tuple(ch_data)
        ch_list = tuple(ch_list)

    return final_dict

def get_authorised_users() -> list[Tuple[int, str, int]]:
    """
    Returns the data of authorised users.
    """

    return fetch_table_data(table="authorised_users",
                                fetch_one=False)