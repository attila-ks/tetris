import QtQuick

Text {
    color: "#16faff"
    opacity: 0.65

    signal clicked

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent

        onEntered: parent.opacity = 1.0
        onExited: parent.opacity = 0.65
        onClicked: parent.clicked()
    }
}
