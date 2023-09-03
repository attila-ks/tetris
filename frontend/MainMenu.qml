import QtQuick

Item {
    width: 450
    height: 560
    property bool settingsMenuCalledFromThis: false

    signal newGameButtonClicked
    signal loadGameButtonClicked
    signal settingsButtonClicked
    signal quitButtonClicked

    Text {
        id: title
        text: "Tetris"
        font.family: fontLoader.font.family
        font.pixelSize: 72
        font.letterSpacing: 8
        color: "#16faff"
        anchors.horizontalCenter: parent.horizontalCenter
        y: 60
    }

    TextButton {
        id: newGameButton
        text: "New Game"
        font.family: fontLoader.font.family
        font.pixelSize: 24
        font.letterSpacing: 8
        anchors.horizontalCenter: parent.horizontalCenter
        y: 202

        onClicked: parent.newGameButtonClicked()
    }

    TextButton {
        id: loadGameButton
        text: "Load Game"
        font.family: fontLoader.font.family
        font.pixelSize: 24
        font.letterSpacing: 8
        anchors.horizontalCenter: parent.horizontalCenter
        y: newGameButton.y + 48

        onClicked: parent.loadGameButtonClicked()
    }

    TextButton {
        id: settingsButton
        text: "Settings"
        font.family: fontLoader.font.family
        font.pixelSize: 24
        font.letterSpacing: 8
        anchors.horizontalCenter: parent.horizontalCenter
        y: loadGameButton.y + 48

        onClicked: parent.settingsButtonClicked()
    }

    TextButton {
        id: quitButton
        text: "Quit"
        font.family: fontLoader.font.family
        font.pixelSize: 24
        font.letterSpacing: 8
        anchors.horizontalCenter: parent.horizontalCenter
        y: settingsButton.y + 48

        onClicked: {
            parent.quitButtonClicked()
        }
    }
}
