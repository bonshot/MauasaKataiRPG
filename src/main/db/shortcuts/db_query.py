"""
Module for database queries.
"""

from ..database import value_exists_in_table
from .db_fetch import get_authorised_users


def exists_listened_channel(id_channel: int) -> bool:
    """
    Verifies if the channel is in the listened ones.
    """

    return value_exists_in_table(table="canales_escuchables",
                                id=id_channel)


def exists_authorised_user(id_user: int) -> bool:
    """
    Verifies if the user is authorised with the
    specified id.
    """

    for id_u, _, _ in get_authorised_users():
        if id_user == id_u:
            return True

    return False