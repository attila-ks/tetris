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
        self._ghost_tetromino = None
        self._ghost_tetromino_visible = False
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

        # Return the ghost tetromino's color if param index matches with one
        # of the block position of the ghost tetromino.
        # Is there a nicer way to check?

        # Would be great to check only the '_ghost_tetromino_visible' member.
        if self._ghost_tetromino_visible and self._ghost_tetromino and \
           index.row() >= self._ghost_tetromino.row() and \
           index.row() < \
           self._ghost_tetromino.row() + self._ghost_tetromino.rows() and \
           index.column() >= self._ghost_tetromino.column() and \
           index.column() < \
           self._ghost_tetromino.column() + self._ghost_tetromino.columns():
            ROW = index.row() - self._ghost_tetromino.row()
            COL = index.column() - self._ghost_tetromino.column()
            if self._ghost_tetromino.matrix()[ROW][COL] == 1:
                roleName = self.roleNames()[role].decode()
                # Maybe it's not the best way if role names used here
                # explicitly.
                if roleName == "cellColor":
                    pass
                elif roleName == "cellBorderColor":
                    return self._ghost_tetromino.color().html_code

        CELL_VALUE = self._playfield[index.row()][index.column()]
        return Color(CELL_VALUE).html_code

    def roleNames(self):
        roles = dict()
        roles[hash(Qt.UserRole + 1)] = "cellColor".encode()
        roles[hash(Qt.UserRole + 2)] = "cellBorderColor".encode()
        return roles

    def add_tetromino(self, tetromino):
        """Returns true if tetromino has been added successfully,
           otherwise returns false."""
        self._tetromino = tetromino

        if not self._does_tetromino_fit(tetromino):
            return False

        # Add the tetromino only to the frontend-side of the playfield.
        for i, row in enumerate(tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = tetromino.row() + i
                    COL = tetromino.column() + j
                    INDEX = self.createIndex(ROW, COL)
                    self.dataChanged.emit(INDEX, INDEX)

        if self._ghost_tetromino_visible:
            self._add_ghost_tetromino()

        return True

    # FIXME: Causes lagging.
    def move_tetromino_down(self):
        """This method is used for both automatic and soft drop."""
        if self._is_tetromino_landed(self._tetromino):
            self._lock_tetromino()
            self._tetromino = None
            self._ghost_tetromino = None
            self._clear_filled_rows()
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
        while not self._is_tetromino_landed(self._tetromino):
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

        self._tetromino = None
        self._ghost_tetromino = None
        self._clear_filled_rows()
        self.tetromino_landed.emit()

    def _is_tetromino_landed(self, tetromino):
        """It can be used for both tetromino and ghost tetromino."""
        for i, row in enumerate(tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = tetromino.row() + i
                    COL = tetromino.column() + j
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

        self._fit_ghost_tetromino()

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

        self._fit_ghost_tetromino()

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

        self._fit_ghost_tetromino()

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

        self._fit_ghost_tetromino()

    def clear(self):
        self._tetromino = None

        for i in range(self._rows):
            for j in range(self._columns):
                # Would be great to clear only the not empty cells.
                self._playfield[i][j] = 0
                INDEX = self.createIndex(i, j)
                self.dataChanged.emit(INDEX, INDEX)

    def show_ghost_tetromino(self, show):
        if show:
            self._ghost_tetromino_visible = True
            self._add_ghost_tetromino()
        else:
            self._ghost_tetromino_visible = False
            self._remove_ghost_tetromino()
            self._ghost_tetromino = None

    def _add_ghost_tetromino(self):
        """Create and add a ghost tetromino to the playfield."""
        self._ghost_tetromino = copy(self._tetromino)

        new_row = 0
        while not self._is_tetromino_landed(self._ghost_tetromino):
            new_row += 1
            self._ghost_tetromino.set_row(new_row)

        for i, row in enumerate(self._ghost_tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._ghost_tetromino.row() + i
                    COL = self._ghost_tetromino.column() + j
                    index = self.createIndex(ROW, COL)
                    self.dataChanged.emit(index, index)

    def _remove_ghost_tetromino(self):
        """Remove the ghost tetromino from the playfield, but does not
        destroy it."""
        for i, row in enumerate(self._ghost_tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = self._ghost_tetromino.row() + i
                    COL = self._ghost_tetromino.column() + j
                    self._playfield[ROW][COL] = 0
                    INDEX = self.createIndex(ROW, COL)
                    self.dataChanged.emit(INDEX, INDEX)

    def _fit_ghost_tetromino(self):
        if not self._ghost_tetromino_visible:
            return

        # Playing around with the '_ghost_tetromino_visible' member is needed
        # because of the method 'data'. Without it, previous blocks of the
        # ghost tetromino wouldn't be removed from the playfield.
        self._ghost_tetromino_visible = False
        self._remove_ghost_tetromino()
        self._ghost_tetromino_visible = True
        self._ghost_tetromino = copy(self._tetromino)
        self._add_ghost_tetromino()

    def _clear_filled_rows(self):
        i = self._rows - 1
        while i >= 0:
            if (self._is_row_filled(i)):
                self._clear_filled_row(i)
                self._move_blocks_down(i - 1)
            else:
                i -= 1

    def _is_row_filled(self, row_index):
        for col in self._playfield[row_index]:
            if col == 0:
                return False
        return True

    def _clear_filled_row(self, row_index):
        for col_index in range(self._columns):
            if self._playfield[row_index][col_index] != 0:
                self._playfield[row_index][col_index] = 0
                INDEX = self.createIndex(row_index, col_index)
                self.dataChanged.emit(INDEX, INDEX)

    def _move_blocks_down(self, row_index):
        for i in range(row_index, -1, -1):
            for j in range(self._columns):
                if self._playfield[i][j] != 0:
                    self._playfield[i + 1][j] = self._playfield[i][j]
                    self._playfield[i][j] = 0
                    index = self.createIndex(i, j)
                    self.dataChanged.emit(index, index)
                    index = self.createIndex(i + 1, j)
                    self.dataChanged.emit(index, index)

    def _does_tetromino_fit(self, tetromino):
        for i, row in enumerate(tetromino.matrix()):
            for j, col in enumerate(row):
                if col == 1:
                    ROW = tetromino.row() + i
                    COL = tetromino.column() + j
                    if self._playfield[ROW][COL] != 0:
                        return False
        return True

    tetromino_landed = Signal()
