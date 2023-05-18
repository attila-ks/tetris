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
            levelDisplay.visible = true
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

    InfoDisplay {
        id: levelDisplay
        text: "LEVEL"
        visible: false
        anchors.right: playfield.left
        anchors.rightMargin: 17
        anchors.bottom: playfield.bottom

        // TODO: Use property alias instead!
        property double progressBarValue
        // TODO: Use property alias instead!
        // TODO: The initial value should come from the `tetrion` too!
        property int level: 1

        CircularProgressBar {
            id: progressBar
            size: 43
            lineWidth: 3
            primaryColor: "#16faff"
            secondaryColor: "#d93ed7"
            value: parent.progressBarValue
            anchors.horizontalCenter: parent.horizontalCenter
            y: 27
        }

        Text {
            id: level
            text: parent.level
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
            levelDisplay.visible = false
            nextTetrominoDisplay.visible = false
            scoreDisplay.visible = false
            gameOverMenu.visible = true
        }

        function onLevelIncreased() {
            levelDisplay.level = tetrion.getLevel();
        }

        function onLevelProgressed() {
            levelDisplay.progressBarValue = tetrion.getLevelProgress();
        }

        function onScoreChanged(score) {
            scoreDisplay.score = score
        }
    }
}
