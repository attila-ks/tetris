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
            tetrisBoard.visible = true
            level.visible = true
            tetrion.startGame()
        }

        onQuitButtonClicked: {
            Qt.quit()
        }
    }

    TetrisBoard {
        id: tetrisBoard
        visible: false
        anchors.centerIn: parent
    }

    Level {
        id: level
        visible: false
        anchors.right: tetrisBoard.left
        anchors.rightMargin: 17
        anchors.bottom: tetrisBoard.bottom
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
            tetrisBoard.visible = false
            level.visible = false
            gameOverMenu.visible = true
        }
    }
}
