import QtQuick 2.13
import QtQuick.Controls 2.12

ApplicationWindow {
    width: 400
    height: 560
    minimumWidth: 400
    maximumWidth: 400
    minimumHeight: 560
    maximumHeight: 560
    title: "Tetris"
    flags: Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint
    visible: true
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
        Keys.onPressed: tetrion.process_input(event.key, true)
        Keys.onReleased: tetrion.process_input(event.key, false)
    }

    Connections {
        target: tetrion

        function onGame_over() { gameOverDialog.visible = true }
    }

    GameOverDialog {
        id: gameOverDialog
        visible: false
        anchors.fill: parent

        exitButton.onPressed: Qt.quit()
        newGameButton.onPressed: {
            visible = false
            tetrion.restart()
            inputHandler.focus = true
        }
    }
}
