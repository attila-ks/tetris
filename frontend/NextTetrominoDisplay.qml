import QtQuick
import QtQuick.Controls

Item {
    width: 80
    height: 80

    Rectangle {
        id: rect
        color: "#0e001f"
        opacity: 0.9
        anchors.fill: parent
    }

    Rectangle {
        id: titleBar
        width: parent.width
        height: 20
        color: "#d93ed7"
        opacity: 0.7
    }

    Text {
        id: title
        text: "NEXT"
        color: "#16faff"
        x: 6
        anchors.verticalCenter: titleBar.verticalCenter
    }

    Line {
        id: topLine
        width: parent.width
        height: 2
        color: "#d971de"
        anchors.bottom: titleBar.bottom
    }

    Image {
        id: nextTetromino
        anchors.centerIn: parent
        anchors.verticalCenterOffset: titleBar.height / 2

        Connections {
            target: tetrion
            function onNextTetrominoChanged(nextTetrominoImageUrl) {
                nextTetromino.source = nextTetrominoImageUrl
            }
        }
    }

    Line {
        id: bottomLine
        width: parent.width
        height: 2
        color: "#d971de"
        anchors.bottom: rect.bottom
    }
}
