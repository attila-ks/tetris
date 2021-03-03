# This Python file uses the following encoding: utf-8

from PySide2.QtCore import QAbstractTableModel, Qt, Signal
from color import Color
from copy import copy


class Playfield(QAbstractTableModel):
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

        # Return the current tetromino's color if param index matches with one
        # of the block position of the current tetromino.
        # Is there a nicer way to check?
        if self._tetromino and \
           index.row() >= self._tetromino.row() and \
           index.row() < self._tetromino.row() + self._tetromino.rows() and \
           index.column() >= self._tetromino.column() and \
           index.column() < self._tetromino.column() + self._tetromino.columns():
            ROW = index.row() - self._tetromino.row()
            COL = index.column() - self._tetromino.column()
            if self._tetromino.matrix()[ROW][COL] == 1:
                return self._tetromino.color().html_code

        CELL_VALUE = self._playfield[index.row()][index.column()]
        return Color(CELL_VALUE).html_code

    def roleNames(self):
        return {hash(Qt.UserRole): "cellColor".encode()}

    def add_tetromino(self, tetromino):
        self._tetromino = tetromino
        # Add the tetromino only to the frontend-side of the playfield.
        for i, row in enumerate(tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = tetromino.row() + i
                    COL = tetromino.column() + j
                    INDEX = self.createIndex(ROW, COL)
                    self.dataChanged.emit(INDEX, INDEX)

    # FIXME: Causes lagging.
    def move_tetromino_down(self):
        """This method is used for both automatic and soft drop."""
        if self._is_tetromino_landed():
            self._lock_tetromino()
            self.tetromino_landed.emit()
            return

        self._tetromino.set_row(self._tetromino.row() + 1)

        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._tetromino.row() + i
                    COL = self._tetromino.column() + j
                    index = self.createIndex(ROW - 1, COL)
                    self.dataChanged.emit(index, index)
                    index = self.createIndex(ROW, COL)
                    self.dataChanged.emit(index, index)

    def hard_drop_tetromino(self):
        OLD_ROW = self._tetromino.row()
        new_row = OLD_ROW
        while not self._is_tetromino_landed():
            new_row += 1
            self._tetromino.set_row(new_row)
        # It'd be great to use method _lock_tetromino for this.
        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._tetromino.row() + i
                    COL = self._tetromino.column() + j
                    self._playfield[OLD_ROW + i][COL] = 0
                    self._playfield[ROW][COL] = self._tetromino.color().value
                    index = self.createIndex(OLD_ROW + i, COL)
                    self.dataChanged.emit(index, index)
                    index = self.createIndex(ROW, COL)
                    self.dataChanged.emit(index, index)

        self.tetromino_landed.emit()

    def _is_tetromino_landed(self):
        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._tetromino.row() + i
                    COL = self._tetromino.column() + j
                    if ROW + 1 == self._rows or \
                       self._playfield[ROW + 1][COL] != 0:
                        return True
        return False

    def _lock_tetromino(self):
        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._tetromino.row() + i
                    COL = self._tetromino.column() + j
                    self._playfield[ROW][COL] = self._tetromino.color().value

    def move_tetromino_left(self):
        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._tetromino.row() + i
                    COL = self._tetromino.column() + j
                    if COL == 0 or self._playfield[ROW][COL - 1] != 0:
                        return

        self._tetromino.set_column(self._tetromino.column() - 1)

        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._tetromino.row() + i
                    COL = self._tetromino.column() + j
                    index = self.createIndex(ROW, COL + 1)
                    self.dataChanged.emit(index, index)
                    index = self.createIndex(ROW, COL)
                    self.dataChanged.emit(index, index)

    def move_tetromino_right(self):
        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._tetromino.row() + i
                    COL = self._tetromino.column() + j
                    if COL + 1 == self._columns or \
                       self._playfield[ROW][COL + 1] != 0:
                        return

        self._tetromino.set_column(self._tetromino.column() + 1)

        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._tetromino.row() + i
                    COL = self._tetromino.column() + j
                    index = self.createIndex(ROW, COL - 1)
                    self.dataChanged.emit(index, index)
                    index = self.createIndex(ROW, COL)
                    self.dataChanged.emit(index, index)

    def rotate_tetromino_left(self):
        temp_tetromino = copy(self._tetromino)
        temp_tetromino.rotate_left()

        for i, row in enumerate(temp_tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = temp_tetromino.row() + i
                    COL = temp_tetromino.column() + j
                    if ROW < 0 or ROW >= self._rows or COL < 0 or \
                        COL >= self._columns or self._playfield[ROW][COL] != 0:
                        return

        self._tetromino.rotate_left()

        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                ROW = self._tetromino.row() + i
                COL = self._tetromino.column() + j
                INDEX = self.createIndex(ROW, COL)
                self.dataChanged.emit(INDEX, INDEX)

    def rotate_tetromino_right(self):
        temp_tetromino = copy(self._tetromino)
        temp_tetromino.rotate_right()

        for i, row in enumerate(temp_tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = temp_tetromino.row() + i
                    COL = temp_tetromino.column() + j
                    if ROW < 0 or ROW >= self._rows or COL < 0 or \
                        COL >= self._columns or self._playfield[ROW][COL] != 0:
                        return

        self._tetromino.rotate_right()

        for i, row in enumerate(self._tetromino.matrix()):
            for j, col in enumerate(row):
                ROW = self._tetromino.row() + i
                COL = self._tetromino.column() + j
                INDEX = self.createIndex(ROW, COL)
                self.dataChanged.emit(INDEX, INDEX)

    tetromino_landed = Signal()
