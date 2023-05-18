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
            nextTetrominoDisplay.visible = true
            scoreDisplay.visible = true
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

    NextTetrominoDisplay {
        id: nextTetrominoDisplay
        visible: false
        anchors.left: playfield.right
        anchors.leftMargin: 17
        anchors.top: playfield.top
    }

    InfoDisplay {
        id: scoreDisplay
        height: 50
        text: "SCORE"
        visible: false
        anchors.left: playfield.right
        anchors.leftMargin: 17
        y: 380

        // TODO: Use property alias instead!
        property int score

        Text {
            id: score
            text: parent.score
            color: "#16faff"
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 10
        }
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
            nextTetrominoDisplay.visible = false
            scoreDisplay.visible = false
            gameOverMenu.visible = true
        }

        function onScoreChanged(score) {
            scoreDisplay.score = score
        }
    }
}
