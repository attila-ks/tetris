# This Python file uses the following encoding: utf-8
import sys
import os

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine
from game import Game


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)

    game = Game()

    engine = QQmlApplicationEngine()
    engine.rootContext().setContextProperty("game", game)
    engine.load(os.path.join(os.path.dirname(__file__), "main.qml"))

    if not engine.rootObjects():
        sys.exit(-1)
    sys.exit(app.exec_())
