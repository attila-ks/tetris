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

    Rectangle {
        id: playfieldBackground
        width: playfield.width
        height: playfield.height - 17
        color: "#1e3c72"
        clip: true
        anchors.centerIn: parent

        TableView {
            id: playfield
            width: childrenRect.width
            height: childrenRect.height
            rowSpacing: 1
            columnSpacing: 1
            anchors.bottom: playfieldBackground.bottom
            model: tetrion.playfield // FIXME: Sometimes throws TypeError.
            delegate: Rectangle {
                id: cell
                implicitWidth: 20
                implicitHeight: 20
                color: model.cellColor
            }
        }
    }

    Item {
        focus: true
        anchors.fill: parent
        // This should be done in the Tetrion class.
        // Cannot pass the event itself for distinguish the key pressing and
        // releasing, that's why a second argument is needed.
        Keys.onPressed: tetrion.process_input(event.key, true)
        Keys.onReleased: tetrion.process_input(event.key, false)
    }
}
