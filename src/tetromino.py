# This Python file uses the following encoding: utf-8

from enum import IntEnum
from color import Color


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
        self._type = type
        self._row = row
        self._column = column
        self._color = Color(type)
        self._matrix = ROTATIONS[type][0]
        self._rows = len(self._matrix)
        self._columns = len(self._matrix[0])
        self._rotation_index = 0

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

    def rotate_left(self):
        self._rotation_index -= 1

        if self._rotation_index == -1:
            self._rotation_index = len(ROTATIONS[self._type]) - 1

        self._matrix = ROTATIONS[self._type][self._rotation_index]

    def rotate_right(self):
        self._rotation_index += 1

        if self._rotation_index == len(ROTATIONS[self._type]):
            self._rotation_index = 0

        self._matrix = ROTATIONS[self._type][self._rotation_index]


ROTATIONS = {
    Tetromino.Type.I:
    ([[0, 0, 0, 0],
      [1, 1, 1, 1],
      [0, 0, 0, 0],
      [0, 0, 0, 0]],

     [[0, 0, 1, 0],
      [0, 0, 1, 0],
      [0, 0, 1, 0],
      [0, 0, 1, 0]],

     [[0, 0, 0, 0],
      [0, 0, 0, 0],
      [1, 1, 1, 1],
      [0, 0, 0, 0]],

     [[0, 1, 0, 0],
      [0, 1, 0, 0],
      [0, 1, 0, 0],
      [0, 1, 0, 0]]),

    Tetromino.Type.J:
    ([[1, 0, 0],
      [1, 1, 1],
      [0, 0, 0]],

     [[0, 1, 1],
      [0, 1, 0],
      [0, 1, 0]],

     [[0, 0, 0],
      [1, 1, 1],
      [0, 0, 1]],

     [[0, 1, 0],
      [0, 1, 0],
      [1, 1, 0]]),

    Tetromino.Type.L:
    ([[0, 0, 1],
      [1, 1, 1],
      [0, 0, 0]],

     [[0, 1, 0],
      [0, 1, 0],
      [0, 1, 1]],

     [[0, 0, 0],
      [1, 1, 1],
      [1, 0, 0]],

     [[1, 1, 0],
      [0, 1, 0],
      [0, 1, 0]]),

    Tetromino.Type.O:
    ([[1, 1],
      [1, 1]],),

    Tetromino.Type.S:
    ([[0, 1, 1],
      [1, 1, 0],
      [0, 0, 0]],

     [[0, 1, 0],
      [0, 1, 1],
      [0, 0, 1]],

     [[0, 0, 0],
      [0, 1, 1],
      [1, 1, 0]],

     [[1, 0, 0],
      [1, 1, 0],
      [0, 1, 0]]),

    Tetromino.Type.T:
    ([[0, 1, 0],
      [1, 1, 1],
      [0, 0, 0]],

     [[0, 1, 0],
      [0, 1, 1],
      [0, 1, 0]],

     [[0, 0, 0],
      [1, 1, 1],
      [0, 1, 0]],

     [[0, 1, 0],
      [1, 1, 0],
      [0, 1, 0]]),

    Tetromino.Type.Z:
    ([[1, 1, 0],
      [0, 1, 1],
      [0, 0, 0]],

     [[0, 0, 1],
      [0, 1, 1],
      [0, 1, 0]],

     [[0, 0, 0],
      [1, 1, 0],
      [0, 1, 1]],

     [[0, 1, 0],
      [1, 1, 0],
      [1, 0, 0]]),
}
