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
    Component.onCompleted: game.start()

    Rectangle {
        id: playfieldBackground
        width: playfield.width
        height: playfield.height - 17
        clip: true
        anchors.centerIn: parent
        gradient: Gradient {
            GradientStop { position: 0; color: "#1e3c72" }
            GradientStop { position: 1; color: "#2a5298" }
        }

        TableView {
            id: playfield
            width: childrenRect.width
            height: childrenRect.height
            rowSpacing: 1
            columnSpacing: 1
            anchors.bottom: playfieldBackground.bottom
            model: game.playfield // FIXME: Sometimes throws TypeError.
            delegate: Rectangle {
                id: cell
                implicitWidth: 20
                implicitHeight: 20
                color: model.cellColor
            }
        }
    }
}
