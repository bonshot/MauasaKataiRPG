"""
General cog for hierarchy purposes
"""

from sys import exc_info
from traceback import format_exc
from typing import TYPE_CHECKING, Any, Optional, TypeAlias, Union

from discord import Interaction
from discord.app_commands import AppCommandError, Group
from discord.ext.commands import Cog, Context
from discord.utils import MISSING

if TYPE_CHECKING:

    from discord import Permissions
    from discord.app_commands import locale_str

    from ..MauasaKataiRPG import MauasaKataiRPG


class _GroupABC(Group):
    """
    General group for hierarchy purposes.
    """

    def __init__(self,
                 bot: "MauasaKataiRPG",
                 *,
                 name: Union[str, "locale_str"] = MISSING,
                 description: Union[str, "locale_str"] = MISSING,
                 parent: Optional[Group] = None,
                 guild_ids: Optional[list[int]] = None,
                 guild_only: bool = MISSING,
                 auto_locale_strings: bool = True,
                 default_permissions: Optional["Permissions"] = MISSING,
                 extras: dict[Any, Any] = MISSING) -> None:
        """
        Initializes an instance of '_GroupABC', or a child.
        """

        super().__init__(name=name,
                         description=description,
                         parent=parent,
                         guild_ids=guild_ids,
                         guild_only=guild_only,
                         auto_locale_strings=auto_locale_strings,
                         default_permissions=default_permissions,
                         extras=extras)
        self.bot: "MauasaKataiRPG" = bot


GroupsList: TypeAlias = list[type[_GroupABC]]


class _CogABC(Cog):
    """
    General cog for hierarchy purposes.
    """


    def __init__(self, bot: "MauasaKataiRPG") -> None:
        """
        Initializes an instance of '_CogABC', or a child.
        """
        self.bot: "MauasaKataiRPG" = bot
        self._load_groups()


    def _load_groups(self) -> None:
        """
        Loads all the groups that the cog has registered.
        """

        for group_class in self.grupos():
            self.bot.tree.add_command(group_class(self.bot))


    @classmethod
    def groups(cls) -> GroupsList:
        """
        Returns the list of groups associated with this Cog.
        """

        return []


    async def cog_app_command_error(self,
                                    interaction: Interaction,
                                    _error: AppCommandError) -> None:
        """
        Handles an error by default for all cogs.
        """

        await interaction.response.send_message(f"**[ERROR]** Seems that there was an error.",
                                                ephemeral=True)
        beautiful_error = "\n\t|\t".join(f"Exception in app_commands:\n{format_exc()}".split("\n"))
        self.bot.log.error(beautiful_error)


    async def cog_before_invoke(self, ctx: Context) -> None:
        """
        Registers in the log the command being processed.
        """

        there_is_guild = ("" if ctx.guild is None else f" in {ctx.guild.name!r}")
        there_is_message = ("a message without content" if not ctx.message.content else f"the message {ctx.message.content!r}")
        self.bot.log.info((f"[CMD] {ctx.author.name!r} is trying to execute command " +
                           f"{ctx.command.name!r}{there_is_guild}, mediante {there_is_message}."))


    async def cog_after_invoke(self, ctx: Context) -> None:
        """
        Registers in the log the command processed.
        """

        there_is_guild = ("" if ctx.guild is None else f" in {ctx.guild.name!r}")
        there_is_message = ("a message without content" if not ctx.message.content else f"the message {ctx.message.content!r}")
        self.bot.log.info((f"[CMD] {ctx.author.name!r} executed " +
                           f"{ctx.command.name!r}{there_is_guild}, mediante {there_is_message}."))


async def setup(bot: "MauasaKataiRPG"):
    """
    This is just for compatibility purposes. It does nothing. Just bullshit.
    """
    ...