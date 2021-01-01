# This Python file uses the following encoding: utf-8

from PySide2.QtCore import Property, QObject
from playfield import Playfield


class Game(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self._playfield = Playfield(21, 10)

    def playfield(self):
        return self._playfield

    playfield = Property(QObject, playfield, constant=True)
