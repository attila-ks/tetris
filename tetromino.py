# This Python file uses the following encoding: utf-8

from enum import IntEnum


TETROMINO_MATRICES = (
    [[0, 0, 0, 0],
     [1, 1, 1, 1],
     [0, 0, 0, 0],
     [0, 0, 0, 0]],

    [[1, 0, 0],
     [1, 1, 1],
     [0, 0, 0]],

    [[0, 0, 1],
     [1, 1, 1],
     [0, 0, 0]],

    [[0, 1, 1],
     [0, 1, 1]],

    [[0, 1, 1],
     [1, 1, 0],
     [0, 0, 0]],

    [[0, 1, 0],
     [1, 1, 1],
     [0, 0, 0]],

    [[1, 1, 0],
     [0, 1, 1],
     [0, 0, 0]]
)


class Tetromino:
    class Type(IntEnum):
        I = 1
        J = 2
        L = 3
        O = 4
        S = 5
        T = 6
        Z = 7

    def __init__(self, type, x, y):
        self._type = type
        self._x = x
        self._y = y
        # Tetromino.Type starts from value 1.
        self._matrix = TETROMINO_MATRICES[type - 1]

    def type(self):
        return self._type

    def x(self):
        return self._x

    def set_x(self, x):
        self._x = x

    def y(self):
        return self._y

    def set_y(self, y):
        self._y = y

    def matrix(self):
        return self._matrix
