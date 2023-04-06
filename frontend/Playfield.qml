import QtQuick
import QtQuick.Controls

// TODO: Add drop shadow.
Frame {
    width: background.width + padding * 2
    height: 422
    padding: 2
    background: Rectangle {
        color: "transparent"
        border.color: "#16faff"
        border.width: 2
    }

    Item {
        width: background.width
        height: 418
        clip: true

        Rectangle {
            id: background
            width: grid.width
            height: grid.height
            color: "#1f4d4f"
            opacity: 0.8
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
        }

        TableView {
            id: grid
            width: childrenRect.width
            height: childrenRect.height
            rowSpacing: 0.5
            columnSpacing: 0.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: background.bottom
            model: tetrion.playfield
            delegate: Rectangle {
                id: cell
                implicitWidth: 20
                implicitHeight: 20
                color: model.display
                opacity: 0.9
            }
        }
    }
}
