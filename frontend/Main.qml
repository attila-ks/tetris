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

    FontLoader {
        id: fontLoader
        source: "../resources/fonts/Streamster.ttf"
    }

    Image {
        id: background
        source: "../resources/images/background.jpg"
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        clip: true
    }

    // Do components use resources when their `visible` attribute is set to false?

    MainMenu {
        id: mainMenu

        onNewGameButtonClicked: {
            visible = false
            playfield.visible = true
            levelDisplay.visible = true
            nextTetrominoDisplay.visible = true
            scoreDisplay.visible = true
            highScoreDisplay.visible = true
            tetrion.startGame()
        }

        onLoadGameButtonClicked: {
            visible = false
            playfield.visible = true
            levelDisplay.visible = true
            nextTetrominoDisplay.visible = true
            scoreDisplay.visible = true
            highScoreDisplay.visible = true
            tetrion.loadGame()
        }

        onSettingsButtonClicked: {
            visible = false
            settingsMenu.visible = true
            settingsMenuCalledFromThis = true
        }

        onQuitButtonClicked: {
            Qt.quit()
        }
    }

    PauseMenu {
        id: pauseMenu
        visible: false

        onResumeGameButtonClicked: {
            visible = false
            playfield.visible = true
            levelDisplay.visible = true
            nextTetrominoDisplay.visible = true
            scoreDisplay.visible = true
            highScoreDisplay.visible = true
            tetrion.resumeGame()
        }

        onMainMenuButtonClicked: {
            visible = false
            playfield.visible = false
            levelDisplay.visible = false
            nextTetrominoDisplay.visible = false
            scoreDisplay.visible = false
            highScoreDisplay.visible = false
            mainMenu.visible = true
        }

        onSettingsButtonClicked: {
            visible = false
            settingsMenu.visible = true
        }

        onQuitButtonClicked: {
            Qt.quit()
        }
    }

    SettingsMenu {
        id: settingsMenu
        visible: false
        anchors.centerIn: parent

        onBackButtonClicked: {
            visible = false
            if (mainMenu.settingsMenuCalledFromThis) {
                mainMenu.settingsMenuCalledFromThis = false
                mainMenu.visible = true
            } else {
                pauseMenu.visible = true
            }
        }
    }

    Playfield {
        id: playfield
        visible: false
        anchors.centerIn: parent
    }

    InfoDisplay {
        id: levelDisplay
        text: "LEVEL"
        visible: false
        anchors.right: playfield.left
        anchors.rightMargin: 17
        anchors.bottom: playfield.bottom

        property alias progressBarValue: progressBar.value
        property alias level: level.text

        CircularProgressBar {
            id: progressBar
            size: 43
            lineWidth: 3
            primaryColor: "#16faff"
            secondaryColor: "#d93ed7"
            value: tetrion.getLevelProgress()
            anchors.horizontalCenter: parent.horizontalCenter
            y: 27
        }

        Text {
            id: level
            text: tetrion.getLevel()
            color: "#16faff"
            anchors.centerIn: progressBar
        }

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
        anchors.bottom: highScoreDisplay.top
        anchors.bottomMargin: 17

        property alias score: score.text

        Text {
            id: score
            text: tetrion.getScore()
            color: "#16faff"
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 10
        }
    }

    InfoDisplay {
        id: highScoreDisplay
        height: 50
        text: "BEST"
        visible: false
        anchors.left: playfield.right
        anchors.leftMargin: 17
        anchors.bottom: playfield.bottom

        property alias highScore: highScore.text

        Text {
            id: highScore
            text: tetrion.getHighScore()
            color: "#16faff"
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 10
        }
    }

    GameOverMenu {
        id: gameOverMenu
        visible: false

        onNewGameButtonClicked: {
            visible = false
            mainMenu.newGameButtonClicked()
        }

        onLoadGameButtonClicked: {
            visible = false
            mainMenu.loadGameButtonClicked()
        }

        onQuitButtonClicked: {
            Qt.quit()
        }
    }

    Connections {
        target: tetrion
        function onGameOver() {
            playfield.visible = false
            levelDisplay.visible = false
            nextTetrominoDisplay.visible = false
            scoreDisplay.visible = false
            highScoreDisplay.visible = false
            gameOverMenu.visible = true
        }

        function onGamePaused() {
            playfield.visible = false
            levelDisplay.visible = false
            nextTetrominoDisplay.visible = false
            scoreDisplay.visible = false
            highScoreDisplay.visible = false
            pauseMenu.visible = true
        }

        function onLevelIncreased(level) {
            levelDisplay.level = level;
        }

        function onLevelProgressed(levelProgress) {
            levelDisplay.progressBarValue = levelProgress;
        }

        function onScoreChanged(score) {
            scoreDisplay.score = score
        }

        function onHighScoreChanged(highScore) {
            highScoreDisplay.highScore = highScore
        }
    }
}
