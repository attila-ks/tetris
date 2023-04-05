import QtQuick

Item {
    width: 80
    height: 80

    Rectangle {
        id: rect
        color: "#0e001f"
        opacity: 0.9
        anchors.fill: parent
    }

    Rectangle {
        id: titleBar
        width: parent.width
        height: 20
        color: "#d93ed7"
        opacity: 0.7
    }

    Text {
        id: title
        text: "LEVEL"
        color: "#16faff"
        x: 6
        anchors.verticalCenter: titleBar.verticalCenter
    }

    Line {
        width: 80
        height: 2
        color: "#d971de"
        anchors.bottom: title.bottom
    }

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

    Line {
        width: 80
        height: 2
        color: "#d971de"
        anchors.bottom: rect.bottom
    }

    Connections {
        target: tetrion

        function onLevelIncreased() {
            level.text = tetrion.getLevel();
        }

        function onLevelProgressed() {
            progressBar.value = tetrion.getLevelProgress();
        }
    }
}
