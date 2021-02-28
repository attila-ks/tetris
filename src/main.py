# This Python file uses the following encoding: utf-8
import sys
import os

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine
from tetrion import Tetrion


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)

    tetrion = Tetrion()

    engine = QQmlApplicationEngine()
    engine.rootContext().setContextProperty("tetrion", tetrion)
    engine.load(os.path.join(os.path.dirname(
        __file__), "../frontend/main.qml"))

    if not engine.rootObjects():
        sys.exit(-1)
    sys.exit(app.exec_())
