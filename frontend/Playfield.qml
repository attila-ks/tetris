import QtQuick 2.13
import QtQuick.Controls 2.12

Frame {
    implicitWidth: playfieldBackground.width + 4
    implicitHeight: playfieldBackground.height + 4
    background: Rectangle {
        color: "transparent"
        border.color: "#2177cf"
        border.width: 4
    }

    Rectangle {
        id: playfieldBackground
        width: playfield.width
        height: playfield.height - 17
        color: "#1e3c72"
        clip: true
        anchors.centerIn: parent

        TableView {
            id: playfield
            width: childrenRect.width
            height: childrenRect.height
            rowSpacing: 1
            columnSpacing: 1
            anchors.bottom: playfieldBackground.bottom
            model: tetrion.playfield // FIXME: Sometimes throws TypeError.
            delegate: Rectangle {
                id: cell
                implicitWidth: 20
                implicitHeight: 20
                color: model.cellColor
                border.color: model.cellBorderColor
            }
        }
    }
}
