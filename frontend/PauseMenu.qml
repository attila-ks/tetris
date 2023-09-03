import QtQuick

Item {
    width: 450
    height: 560

    signal resumeGameButtonClicked
    signal mainMenuButtonClicked
    signal settingsButtonClicked
    signal quitButtonClicked

    Text {
        id: title
        text: "Pause"
        font.family: fontLoader.font.family
        font.pixelSize: 72
        font.letterSpacing: 8
        color: "#16faff"
        anchors.horizontalCenter: parent.horizontalCenter
        y: 60
    }

    TextButton {
        id: resumeGameButton
        text: "Resume"
        font.family: fontLoader.font.family
        font.pixelSize: 24
        font.letterSpacing: 8
        anchors.horizontalCenter: parent.horizontalCenter
        y: 202

        onClicked: parent.resumeGameButtonClicked()
    }

    TextButton {
        id: mainMenuButton
        text: "Main Menu"
        font.family: fontLoader.font.family
        font.pixelSize: 24
        font.letterSpacing: 8
        anchors.horizontalCenter: parent.horizontalCenter
        y: resumeGameButton.y + 48

        onClicked: parent.mainMenuButtonClicked()
    }

    TextButton {
        id: settingsButton
        text: "Settings"
        font.family: fontLoader.font.family
        font.pixelSize: 24
        font.letterSpacing: 8
        anchors.horizontalCenter: parent.horizontalCenter
        y: mainMenuButton.y + 48

        onClicked: parent.settingsButtonClicked()
    }

    TextButton {
        id: quitButton
        text: "Quit"
        font.family: fontLoader.font.family
        font.pixelSize: 24
        font.letterSpacing: 8
        anchors.horizontalCenter: parent.horizontalCenter
        y: settingsButton.y + 48

        onClicked: {
            parent.quitButtonClicked()
        }
    }
}
