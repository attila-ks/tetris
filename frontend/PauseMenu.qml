import QtQuick 2.13
import QtQuick.Controls 2.12

Item {
    id: root

    property alias resumeButton: resumeButton
    property alias newGameButton: newGameButton
    property alias optionsButton: optionsButton
    property alias quitButton: quitButton

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
            text: "PAUSED"
            color: "white"
            font.bold: true
            font.pointSize: Qt.application.font.pointSize + 5
            anchors.horizontalCenter: menuBackground.horizontalCenter
            y: 15
        }

        Column {
            width: newGameButton.width
            height: childrenRect.height
            anchors.horizontalCenter: menuBackground.horizontalCenter
            anchors.top: label.bottom
            anchors.topMargin: 25
            spacing: 10

            RoundButton {
                id: resumeButton
                width: newGameButton.width
                text: "RESUME"
                radius: 3
                palette.button: "#0072ff"
                palette.buttonText: "white"
            }

            RoundButton {
                id: newGameButton
                width: implicitWidth + 15
                text: "NEW GAME"
                radius: 3
                palette.button: "#0072ff"
                palette.buttonText: "white"
            }

            RoundButton {
                id: optionsButton
                width: newGameButton.width
                text: "OPTIONS"
                radius: 3
                palette.button: "#0072ff"
                palette.buttonText: "white"
            }

            RoundButton {
                id: quitButton
                width: newGameButton.width
                text: "QUIT"
                radius: 3
                palette.button: "#0072ff"
                palette.buttonText: "white"
            }
        }
    }
}
