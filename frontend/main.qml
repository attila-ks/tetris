import QtQuick 2.13
import QtQuick.Controls 2.12

ApplicationWindow {
    id: root
    width: 400
    height: 560
    minimumWidth: 400
    maximumWidth: 400
    minimumHeight: 560
    maximumHeight: 560
    title: "Tetris"
    flags: Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint
    visible: true
    background: Rectangle {
        gradient: Gradient {
            GradientStop { position: 0.3; color: "#1866ce" }
            GradientStop { position: 1; color: "#330867" }
        }
    }

    Component.onCompleted: tetrion.start()

    Playfield {
        anchors.centerIn: parent
    }

    Item {
        id: inputHandler
        focus: true
        anchors.fill: parent
        // This should be done in the Tetrion class.
        // Cannot pass the event itself for distinguish the key pressing and
        // releasing, that's why a second argument is needed.
        Keys.onPressed: {
            if (event.key === Qt.Key_Escape) {
                pauseMenu.visible = !pauseMenu.visible
                pauseMenu.visible ? tetrion.pause() : tetrion.resume()
            }
            else {
                tetrion.process_input(event.key, true)
            }
        }

        Keys.onReleased: tetrion.process_input(event.key, false)
    }

    Connections {
        target: tetrion

        function onGame_over() { gameOverDialog.visible = true }
    }

    Rectangle {
        color: "black"
        opacity: 0.3
        visible: pauseMenu.visible || optionsWindow.visible ||
                 gameOverDialog.visible
        anchors.fill: parent
    }

    PauseMenu {
        id: pauseMenu
        width: root.width / 2
        height: root.height / 2
        visible: false
        anchors.centerIn: parent

        quitButton.onPressed: Qt.quit()
        resumeButton.onPressed: {
            visible = false
            tetrion.resume()
            inputHandler.focus = true
        }
        newGameButton.onPressed: {
            visible = false
            tetrion.restart()
            inputHandler.focus = true
        }
        optionsButton.onPressed: {
            visible = false
            optionsWindow.visible = true
        }
    }

    OptionsWindow {
        id: optionsWindow
        width: root.width / 2
        height: root.height / 1.7
        visible: false
        anchors.centerIn: parent

        showGhostTetrominoCheckbox.onCheckedChanged: {
            tetrion.show_ghost_tetromino(showGhostTetrominoCheckbox.checked)
        }
        doneButton.onPressed: {
            visible = false
            pauseMenu.visible = true
            inputHandler.focus = true
        }
    }

    GameOverDialog {
        id: gameOverDialog
        width: root.width / 2
        height: root.height / 2.6
        visible: false
        anchors.centerIn: parent

        quitButton.onPressed: Qt.quit()
        newGameButton.onPressed: {
            visible = false
            tetrion.restart()
            inputHandler.focus = true
        }
    }
}
