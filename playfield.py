# This Python file uses the following encoding: utf-8

from enum import Enum
from PySide2.QtCore import QAbstractTableModel, Qt


class Playfield(QAbstractTableModel):
    class CellColor(Enum):
        DEFAULT = (0, "#11213c")

        def __new__(cls, value, color_code):
            obj = object.__new__(cls)
            obj._value_ = value
            obj.color_code = color_code
            return obj

    def __init__(self, rows, columns, parent=None):
        QAbstractTableModel.__init__(self, parent)
        self._rows = rows
        self._columns = columns
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
