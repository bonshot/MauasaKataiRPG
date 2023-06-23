"""
Module dedicated to implement the logic that overloads the
'discord.ext.commands.Bot'.
"""

from asyncio import set_event_loop_policy
from platform import system
from typing import TYPE_CHECKING, Callable

from discord import Intents, Message
from discord.ext.commands import Bot
from discord.utils import utcnow

from ..files import buscar_archivos
from ..auxiliars import get_prefijo
from ..db.atajos import (actualizar_guild, existe_usuario_autorizado,
                         get_botshot_id, get_cogs_path)
from ..logger import BotLogger

if TYPE_CHECKING:
    from datetime import datetime, timedelta

# Para que no tire error en Windows al cerrar el Bot.

try:
    from asyncio import \
        WindowsSelectorEventLoopPolicy  # pylint: disable=ungrouped-imports
    if system() == "Windows":
        set_event_loop_policy(WindowsSelectorEventLoopPolicy())
except ImportError:
    BotLogger().warning("No se pudo importar 'WindowsSelectorEventLoopPolicy' al iniciar " +
                        "el Bot, probablemente porque esto no es Windows.")


PrefixCallable = Callable[["BotShot", Message], str]


# pylint: disable=abstract-method
class MauasaKataiRPG(Bot):
    """
    Class that overload the Bot class of discord.
    """

    @staticmethod
    def intents_botshot() -> Intents:
        """
        Returns the specific intents for MauasaKataiRPG.
        """

        return Intents.all()


    def __init__(self,
                 cmd_prefix: PrefixCallable=get_prefix,
                 **options) -> None:
        """
        Initializes an instance of 'MauasaKataiRPG'.
        """
        super().__init__(cmd_prefix,
                         intents=MauasaKataiRPG.intents_botshot(),
                         application_id=get_botshot_id(),
                         options=options)

        self.log: BotLogger = BotLogger()
        self.awake_since: "datetime" = utcnow()


    async def setup_hook(self) -> None:
        """
        Does the initial actions the bot requires.
        """

        await self.load_cogs()


    async def load_cogs(self) -> None:
        """
        Search and load recursively all the cogs for the bot.
        """

        ext = "py"

        for path_cog in search_files(pattern=f"*.{ext}",
                                        path_name=get_cogs_path(),
                                        ignore_patterns=("__init__.*", "*_abc.*")):

            self.log.info(f"[COG] Loading cog {path_cog!r}")
            await self.load_extension(path_cog.removesuffix(f".{ext}").replace("/", "."))

        self.log.info("Synchronizing commands tree...")
        await self.tree.sync()


    def update_db(self) -> None:
        """
        Updates de db if necessary.
        """

        self.log.info("[DB] Updating guilds...")
        for guild in self.guilds:
            update_guild(guild.id, guild.name)


    @property
    def uptime(self) -> "timedelta":
        """
        Shows Botarius' uptime.
        """

        return utcnow() - self.awake_since


    def is_admin(self, user_id: int) -> bool:
        """
        Verifies if the user_id is an authorized one to
        use bot high privilegies.
        """

        return (user_id == self.owner_id
                or exists_authorized_user(user_id))