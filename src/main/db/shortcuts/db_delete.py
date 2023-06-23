"""
Module for DELETE commands shortcuts.
"""

from ..database import delete_table_data


def delete_listened_channel(channel_id: int) -> None:
    """
    Deletes a listened channel.
    """

    delete_table_data(table="listenable_channels",
                          id=channel_id)

def delete_authorised_user(id_user: int) -> None:
    """
    Deletes a user authorisation from the DB.
    """

    delete_table_data(table="authorised_users",
                          id=id_user)