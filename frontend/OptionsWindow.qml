import QtQuick 2.13
import QtQuick.Controls 2.12

Rectangle {
    border.color: "#2d58ac"
    gradient: Gradient {
        GradientStop { position: 0; color: "#173d89" }
        GradientStop { position: 1; color: "#072052" }
    }

    property alias doneButton: doneButton
    property alias showGhostTetrominoCheckbox: showGhostTetrominoCheckbox

    Text {
        id: label
        text: "OPTIONS"
        color: "white"
        font.bold: true
        font.pointSize: Qt.application.font.pointSize + 5
        anchors.horizontalCenter: parent.horizontalCenter
        y: 15
    }

    Column {
        id: optionsColumn
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: label.bottom
        anchors.topMargin: 25
        spacing: 10

        Text {
            text: "MOVE LEFT         ←"
            color: "white"
        }

        Text {
            text: "MOVE RIGHT       →"
            color: "white"
        }

        Text {
            text: "SOFT DROP        ↓"
            color: "white"
        }

        Text {
            text: "HARD DROP        SPACE"
            color: "white"
        }

        Text {
            text: "ROTATE LEFT      Z"
            color: "white"
        }

        Text {
            text: "ROTATE RIGHT   ↑"
            color: "white"
        }

        CheckBox {
            id: showGhostTetrominoCheckbox
            // The text should be 'SHOW GHOST TETROMINO', but it's too long.
            text: "SHOW GHOST PIECE"
            palette.windowText: "white"
            leftPadding: 0
        }
    }

    RoundButton {
        id: doneButton
        width: implicitWidth + 15
        height: implicitHeight - 5
        text: "DONE"
        radius: 3
        palette.button: "#0072ff"
        palette.buttonText: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: optionsColumn.bottom
        anchors.topMargin: 15
    }
}
