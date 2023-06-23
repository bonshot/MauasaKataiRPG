"""
Main module, wrapper for all the other files.
To run the Bot itself.
"""

from os import getenv

from dotenv import load_dotenv

from .MauasaKataiRPG import MauasaKataiRPG

load_dotenv()


def main() -> int:
    """
    Principal function.
    """

    MauasaKataiRPG().run(getenv('TOKEN'))
    return 0


if __name__ == '__main__':
    main()