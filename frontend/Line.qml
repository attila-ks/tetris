import QtQuick

// FIXME: It's not the proper way for line drawing!
Item {
    property color color;

    Rectangle {
        width: parent.width
        height: parent.height
        color: parent.color
    }
}
