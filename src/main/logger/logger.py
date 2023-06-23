"""
Module with the logger constructor.
"""

from logging import INFO, FileHandler, Formatter, Logger, StreamHandler

from ..db.shortcuts import get_log_path


class BotLogger:
    """
    Logger for the bot.
    """

    def __init__(self,
                 *,
                 log_name: str='MauasaKataiRPG',
                 log_level: int=INFO,
                 format='%(asctime)s - %(levelname)s - %(message)s',
                 date_format='%d-%m-%Y %H:%M:%S') -> None:
        """
        Initializes an instance for 'BotLogger'.
        """

        super().__init__()

        self._format: str = format
        self._date_format: str = date_format

        self._formatter: Formatter = Formatter(fmt=self.format, datefmt=self.date_format)

        self.handler_files: FileHandler = FileHandler(filename=get_log_path(), encoding='utf-8')
        self.handler_console: StreamHandler = StreamHandler()
        self.update_formatter()

        self.logger = Logger(name=log_name)
        self.logger.setLevel(log_level)
        self.logger.addHandler(self.handler_files)
        self.logger.addHandler(self.handler_console)


    def update_formatter(self) -> None:
        """
        Updates the logger's formatter.
        """

        self.handler_files.setFormatter(self.formatter)
        self.handler_console.setFormatter(self.formatter)


    @property
    def formatter(self) -> Formatter:
        """
        Returns the logger's formatter.
        """

        return self._formatter

    @formatter.setter
    def formatter(self, new_formatter: Formatter) -> None:
        """
        Replaces the current formatter with a new one, and
        updates all the handlers.
        """

        self._formatter = new_formatter
        self.update_formatter()


    @property
    def format(self) -> str:
        """
        Returns the logger's format.
        """

        return self._format


    @format.setter
    def format(self, new_format: str) -> None:
        """
        Updates the logger's format.
        """

        self._format = new_format
        self.formatter = Formatter(fmt=self.format, datefmt=self.date_format)


    @property
    def date_format(self) -> str:
        """
        Returns the logger's date format.
        """

        return self._date_format


    @date_format.setter
    def date_format(self, new_date_format: str) -> None:
        """
        Updates the date format of the logger.
        """

        self._date_format = new_date_format
        self.formatter = Formatter(fmt=self.format, datefmt=self.date_format)


    def debug(self, message: str, *args, **kwargs) -> None:
        """
        Registers an event of DEBUG level.
        """

        self.logger.debug(message, *args, **kwargs)


    def info(self, message: str, *args, **kwargs) -> None:
        """
        Registers an event of INFO level.
        """

        self.logger.info(message, *args, **kwargs)


    def warning(self, message: str, *args, **kwargs) -> None:
        """
        Registers an event of WARNING level.
        """

        self.logger.warning(message, *args, **kwargs)


    def error(self, message: str, *args, **kwargs) -> None:
        """
        Registers an event of ERROR level.
        """

        self.logger.error(message, *args, **kwargs)


    def critical(self, message: str, *args, **kwargs) -> None:
        """
        Registers an event of CRITICAL level.
        """

        self.logger.critical(message, *args, **kwargs)