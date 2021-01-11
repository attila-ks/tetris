# This Python file uses the following encoding: utf-8

from enum import Enum
from PySide2.QtCore import QAbstractTableModel, Qt, Signal


class Playfield(QAbstractTableModel):
    class CellColor(Enum):
        DEFAULT = (0, "#11213c")
        CYAN = (1, "#00b8d4")
        BLUE = (2, "#2962ff")
        ORANGE = (3, "#ff6d00")
        YELLOW = (4, "#ffd600")
        GREEN = (5, "#00c853")
        PURPLE = (6, "#aa00ff")
        RED = (7, "#d50000")

        def __new__(cls, value, color_code):
            obj = object.__new__(cls)
            obj._value_ = value
            obj.color_code = color_code
            return obj

    def __init__(self, rows, columns, parent=None):
        QAbstractTableModel.__init__(self, parent)
        self._rows = rows
        self._columns = columns
        self._tetromino = None
        self._playfield = [[0 for _ in range(columns)] for _ in range(rows)]

    def rowCount(self, parent):
        return self._rows

    def columnCount(self, parent):
        return self._columns

    def data(self, index, role):
        if role < Qt.UserRole:
            return super().data(self, index, role)

        CELL_VALUE = self._playfield[index.row()][index.column()]
        return self.CellColor(CELL_VALUE).color_code

    def roleNames(self):
        return {hash(Qt.UserRole): "cellColor".encode()}

    def add_tetromino(self, tetromino):
        for i, row in enumerate(tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    X = tetromino.x() + j
                    Y = tetromino.y() + i
                    self._playfield[Y][X] = tetromino.type().value
                    INDEX = self.createIndex(Y, X)
                    self.dataChanged.emit(INDEX, INDEX)

        self._tetromino = tetromino

    # FIXME: Causes lagging.
    def move_tetromino_down(self):
        """This method is used for both automatic and soft drop."""
        if self._is_tetromino_landed():
            self.tetromino_landed.emit()
            return

        i = len(self._tetromino.matrix()) - 1
        for row in reversed(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    X = self._tetromino.x() + j
                    Y = self._tetromino.y() + i
                    self._playfield[Y][X] = 0
                    self._playfield[Y + 1][X] = self._tetromino.type().value
                    index = self.createIndex(Y, X)
                    self.dataChanged.emit(index, index)
                    index = self.createIndex(Y + 1, X)
                    self.dataChanged.emit(index, index)
            i -= 1

        self._tetromino.set_y(self._tetromino.y() + 1)

    def hard_drop_tetromino(self):
        OLD_Y = self._tetromino.y()
        new_y = OLD_Y
        while not self._is_tetromino_landed():
            new_y += 1
            self._tetromino.set_y(new_y)

        i = len(self._tetromino.matrix()) - 1
        for row in reversed(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    X = self._tetromino.x() + j
                    Y = self._tetromino.y() + i
                    self._playfield[OLD_Y + i][X] = 0
                    self._playfield[Y][X] = self._tetromino.type().value
                    index = self.createIndex(OLD_Y + i, X)
                    self.dataChanged.emit(index, index)
                    index = self.createIndex(Y, X)
                    self.dataChanged.emit(index, index)
            i -= 1

        self.tetromino_landed.emit()

    def _is_tetromino_landed(self):
        # Find and check only the last row in the tetromino matrix which
        # contains at leas one tetromino block.
        i = len(self._tetromino.matrix()) - 1
        for row in reversed(self._tetromino.matrix()):
            block_found = False
            for j, col in enumerate(row):
                if col == 1:
                    X = self._tetromino.x() + j
                    Y = self._tetromino.y() + i
                    if Y + 1 == self._rows or self._playfield[Y + 1][X] != 0:
                        return True
                    block_found = True
            if block_found:
                return False
            i -= 1

    tetromino_landed = Signal()
