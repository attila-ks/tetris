from enum import Enum


class Color(Enum):
    BLUE = (0, "#11213c")
    CYAN = (1, "#00b8d4")
    INDIGO = (2, "#304ffe")
    ORANGE = (3, "#ff6d00")
    YELLOW = (4, "#ffd600")
    GREEN = (5, "#00c853")
    PURPLE = (6, "#aa00ff")
    RED = (7, "#d50000")

    def __new__(cls, value, html_code):
        obj = object.__new__(cls)
        obj._value_ = value
        obj.html_code = html_code
        return obj
