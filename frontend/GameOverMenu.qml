import QtQuick

Item {
    width: 450
    height: 560

    signal newGameButtonClicked
    signal quitButtonClicked

    // TODO: Investigate whether using multiple FontLoaders affects performance,
    // and if so, how to load just one and use it everywhere it needed? Because
    // there are multiple FontLoader now.
    FontLoader {
        id: fontLoader
        source: "../resources/fonts/Streamster.ttf"
    }

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
