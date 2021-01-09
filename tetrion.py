# This Python file uses the following encoding: utf-8

from PySide2.QtCore import Property, QObject, QTimer, Slot
from tetromino import Tetromino
from playfield import Playfield
from random import choice


class Tetrion(QObject):
    def __init__(self, parent=None):
        QObject.__init__(self, parent)
        self._playfield = Playfield(21, 10)
        self._playfield.tetromino_landed.connect(self._spawn_tetromino)
        self._bag = []
        self._timer = QTimer()
        self._timer.setInterval(1000)
        self._timer.timeout.connect(self._playfield.move_tetromino_down)

    def playfield(self):
        return self._playfield

    @Slot()
    def start(self):
        self._spawn_tetromino()
        self._timer.start()

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
