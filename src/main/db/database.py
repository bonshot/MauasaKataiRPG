"""
Module for database.
"""

from os import PathLike
from sqlite3 import connect
from typing import Any, Dict, List, Literal, Optional, Tuple, TypeAlias, Union

DictConds: TypeAlias = Dict[str, Any]
ResolutionValues: TypeAlias = Literal["ABORT", "FAIL", "IGNORE", "REPLACE", "ROLLBACK"]
_SingularResult: TypeAlias = Tuple[Union[None, int, str]]
FetchResult: TypeAlias = Union[List[_SingularResult], _SingularResult]

DEFAULT_DB: PathLike = "src/main/db/db.sqlite3"
RESOLUTIONS: Tuple[str, ...] = "ABORT", "FAIL", "IGNORE", "REPLACE", "IGNORE"


def create_new_db(db_path: PathLike[str]="") -> None:
    """
    Creates a new db from a template.
    This WON'T be the db that MauasaKataiRPG uses unless it's\
    the DEFAULT_DB.
    """

    db_path = db_path or DEFAULT_DB

    with connect(db_path) as con:
        cur = con.cursor()
        cur.executescript("""--sql
        
        CREATE TABLE properties (
            prop_id INTEGER PRIMARY KEY,
            name TEXT,
            value TEXT
        ) STRICT;

        CREATE TABLE guilds (
            id INTEGER PRIMARY KEY,
            name TEXT
        ) STRICT;

        CREATE TABLE prefixes (
            id INTEGER PRIMARY KEY,
            id_guild INTEGER,
            prefix TEXT,
            FOREIGN KEY(id_guild) REFERENCES guilds(id)
        ) STRICT;

        CREATE TABLE paths (
            id_path INTEGER PRIMARY KEY,
            path_name TEXT,
            fpath TEXT
        ) STRICT;

        CREATE TABLE listenable_channels (
            id INTEGER PRIMARY KEY,
            guild_id INTEGER,
            name TEXT,
            FOREIGN KEY(guild_id) REFERENCES guilds(id)
        ) STRICT;

        CREATE TABLE authorised_users (
            id INTEGER PRIMARY KEY,
            name TEXT,
            discriminator INTEGER
        ) STRICT;
        """)


def execute_command(command: str, is_script: bool, db_path: PathLike[str]="") -> None:
    """
    Executes an arbitrary command, passing it as it is to
    sqlite to parse.
    """

    with connect(db_path) as con:
        cur = con.cursor()

        if is_script:
            cur.executescript(command)
        else:
            cur.execute(command)


def execute_line(command: str, db_path: PathLike[str]="") -> None:
    """
    Executes a SQL command that doesn't require to fetch data.
    """

    execute_command(command, False, db_path or DEFAULT_DB)


def execute_script(command: str, db_path: PathLike[str]="") -> None:
    """
    Executes a SQL command that requires to fetch data.
    """

    execute_command(command, True, db_path or DEFAULT_DB)


def _where_conditions(**conditions: DictConds) -> str:
    "Creates an SQL WHERE clause from a dictionary of conditions."

    extra = None

    try:
        extra = conditions.pop("where")
        if not isinstance(extra, tuple):
            raise TypeError("extra conditions of 'where' parameter should be a strings tuple.")
    except KeyError:
        extra = tuple()

    conds = " AND ".join([f"{k}={v!r}" for k, v in conditions.items()] + list(extra))
    return ('' if not conds else f" WHERE {conds}")


def _resolution_protocol(resolution: Optional[ResolutionValues]=None) -> str:
    "Parses an option to define a protocol in case an operation fails."

    if resolution is None:
        res_protocol = ''
    elif resolution.upper() not in RESOLUTIONS:
        raise ValueError(f"Type of resolution must be one of {RESOLUTIONS}")
    else:
        res_protocol = f" OR {resolution} "

    return res_protocol


def fetch_table_data(table: str,
                         fetch_one: bool=False,
                         **conditions: DictConds) -> FetchResult:
    "Fetch data from a database."

    res = None
    conds = _where_conditions(**conditions)

    with connect(DEFAULT_DB) as con:
        cur = con.cursor()
        cur.execute(f"SELECT * FROM {table}{conds};")
        res = (cur.fetchone() if fetch_one else cur.fetchall())

    return res


def delete_table_data(table: str,
                          **conditions: DictConds) -> None:
    """
    Deletes data from a database.

    * Does not include a LIMIT option.
    """

    conds = _where_conditions(**conditions)

    with connect(DEFAULT_DB) as con:
        cur = con.cursor()
        cur.execute(f"DELETE FROM {table}{conds};")


def insert_data_in_table(table: str,
                            resolution: Optional[ResolutionValues]=None,
                            *,
                            default_primary_key: bool=True,
                            values=Tuple[Any, ...]) -> None:
    "Tries to insert data in a table."

    res_protocol = _resolution_protocol(resolution)
    wrapped_values = [f"{v!r}" for v in values]
    final_values = f"({'?, ' if default_primary_key else ''}{', '.join(wrapped_values)})"

    with connect(DEFAULT_DB) as con:
        cur = con.cursor()
        cur.executescript(f"INSERT{res_protocol} INTO {table} VALUES{final_values};")


def update_table_entry(table: str,
                              resolution: Optional[ResolutionValues]=None,
                              *,
                              col_name: str,
                              value: Any,
                              **conditions: DictConds) -> None:
    "Updates an existing entry in the table."

    if not isinstance(col_name, str):
        raise TypeError("The type of the column must be string.")

    conds = _where_conditions(**conditions)
    res_protocol = _resolution_protocol(resolution)

    with connect(DEFAULT_DB) as con:
        cur = con.cursor()
        cur.execute(f"UPDATE{res_protocol} {table} SET {col_name}={value!r} {conds};")


def value_exists_in_table(table: str,
                         **conditions: DictConds) -> bool:
    "Checks if there is a value in the table."

    return bool(fetch_table_data(table, **conditions))