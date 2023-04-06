import QtQuick

Window {
    width: 450
    height: 560
    // TODO: Check if there is an easier way to fix the window size.
    minimumWidth: width
    minimumHeight: height
    maximumWidth: width
    maximumHeight: height
    visible: true
    title: "Tetris"

    Image {
        id: background
        source: "../resources/images/background.jpg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        clip: true
    }

    // Do components use resources when their `visible` attribute is set to false?

    MainMenu {
        onNewGameButtonClicked: {
            visible = false
            playfield.visible = true
            level.visible = true
            tetrion.startGame()
        }

        onQuitButtonClicked: {
            Qt.quit()
        }
    }

    Playfield {
        id: playfield
        visible: false
        anchors.centerIn: parent
    }

    Level {
        id: level
        visible: false
        anchors.right: playfield.left
        anchors.rightMargin: 17
        anchors.bottom: playfield.bottom
    }

    GameOverMenu {
        id: gameOverMenu
        visible: false

        onQuitButtonClicked: {
            Qt.quit()
        }
    }

    Connections {
        target: tetrion
        function onGameOver() {
            playfield.visible = false
            level.visible = false
            gameOverMenu.visible = true
        }
    }
}
