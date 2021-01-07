# This Python file uses the following encoding: utf-8

from PySide2.QtCore import Property, QObject, Slot
from tetromino import Tetromino
from playfield import Playfield
from random import choice


class Game(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self._playfield = Playfield(21, 10)
        self._bag = []

    def playfield(self):
        return self._playfield

    @Slot()
    def start(self):
        self._spawn_tetromino()

    def _spawn_tetromino(self):
        TETR = self._select_tetromino()
        self._playfield.add_tetromino(TETR)

    def _select_tetromino(self):
        if len(self._bag) == 0:
            self._fill_bag()

        TETR = choice(self._bag)
        self._bag.remove(TETR)
        return TETR

    def _fill_bag(self):
        self._bag = [Tetromino(type, 3, 0) for type in Tetromino.Type]

    playfield = Property(QObject, playfield, constant=True)
