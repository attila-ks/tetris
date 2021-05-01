import QtQuick 2.13

Item {
    id: root
    property alias length: rect.width
    property alias color: rect.color

    Rectangle {
        id: rect
        height: root.width
    }
}
