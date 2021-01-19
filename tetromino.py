# This Python file uses the following encoding: utf-8

from enum import IntEnum
from color import Color


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

    def __init__(self, type, row, column):
        self._row = row
        self._column = column
        self._color = Color(type)
        # Tetromino.Type starts from value 1.
        self._matrix = TETROMINO_MATRICES[type - 1]
        self._rows = len(self._matrix)
        self._columns = len(self._matrix[0])

    def row(self):
        return self._row

    def set_row(self, row):
        self._row = row

    def column(self):
        return self._column

    def set_column(self, column):
        self._column = column

    def color(self):
        return self._color

    def matrix(self):
        return self._matrix

    def rows(self):
        return self._rows

    def columns(self):
        return self._columns
