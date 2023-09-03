import QtQuick

Item {
    width: 450
    height: 560

    signal newGameButtonClicked
    signal loadGameButtonClicked
    signal quitButtonClicked

    // TODO: Add drop shadow.
    Text {
        id: title
        text: "Game Over"
        font.family: fontLoader.font.family
        font.pixelSize: 70
        font.letterSpacing: 8
        color: "#16faff"
        anchors.horizontalCenter: parent.horizontalCenter
        y: 60
    }

    // TODO: Add drop shadow to the hovered and/or selected button.

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
        id: quitButton
        text: "Quit"
        font.family: fontLoader.font.family
        font.pixelSize: 24
        font.letterSpacing: 8
        anchors.horizontalCenter: parent.horizontalCenter
        y: loadGameButton.y + 48

        onClicked: parent.quitButtonClicked()
    }
}
