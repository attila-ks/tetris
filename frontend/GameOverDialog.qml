import QtQuick 2.13
import QtQuick.Controls 2.12

Item {
    id: root

    property alias newGameButton: newGameButton
    property alias exitButton: exitButton

    Rectangle {
        id: menuBackground
        border.color: "#2d58ac"
        anchors.fill: parent
        anchors.verticalCenterOffset: -10
        gradient: Gradient {
            GradientStop { position: 0; color: "#173d89" }
            GradientStop { position: 1; color: "#072052" }
        }

        Text {
            id: label
            text: "GAME OVER"
            color: "white"
            font.bold: true
            font.pointSize: Qt.application.font.pointSize + 5
            anchors.horizontalCenter: menuBackground.horizontalCenter
            y: 15
        }

        RoundButton {
            id: newGameButton
            text: "NEW GAME"
            radius: 3
            palette.button: "#0072ff"
            palette.buttonText: "white"
            anchors.horizontalCenter: menuBackground.horizontalCenter
            anchors.top: label.bottom
            anchors.topMargin: 25
        }

        RoundButton {
            id: exitButton
            text: "EXIT"
            width: newGameButton.width
            radius: 3
            palette.button: "#0072ff"
            palette.buttonText: "white"
            anchors.horizontalCenter: menuBackground.horizontalCenter
            anchors.top: newGameButton.bottom
            anchors.topMargin: 10
        }
    }
}
