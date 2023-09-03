import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    width: 450
    height: 560

    signal backButtonClicked

    Text {
        id: title
        text: "Settings"
        font.family: fontLoader.font.family
        font.pixelSize: 72
        font.letterSpacing: 8
        color: "#16faff"
        anchors.horizontalCenter: parent.horizontalCenter
        y: 60
    }

    ColumnLayout {
        id: checkBoxLayout
        anchors.horizontalCenter: parent.horizontalCenter
        y: 202

        CustomCheckBox {
            text: "Sound"
            checked: tetrion.isSoundEnabled()
            borderColor: "#16faff"
            fillColor: "transparent"
            checkMarkColor: "#16faff"
            textColor: "#16faff"
            font.family: fontLoader.font.family
            font.pixelSize: 17
            font.letterSpacing: 5

            onCheckStateChanged: {
                if (checked) {
                    tetrion.enableSound()
                } else {
                    tetrion.disableSound()
                }
            }
        }

        CustomCheckBox {
            text: "Display Ghost Tetromino"
            checked: tetrion.isGhostTetrominoVisible()
            borderColor: "#16faff"
            fillColor: "transparent"
            checkMarkColor: "#16faff"
            textColor: "#16faff"
            font.family: fontLoader.font.family
            font.pixelSize: 17
            font.letterSpacing: 5

            onCheckStateChanged: {
                if (checked) {
                    tetrion.showGhostTetromino()
                } else {
                    tetrion.hideGhostTetromino()
                }
            }
        }

        CustomCheckBox {
            text: "Display Grid"
            checked: tetrion.isPlayfieldGridVisible()
            borderColor: "#16faff"
            fillColor: "transparent"
            checkMarkColor: "#16faff"
            textColor: "#16faff"
            font.family: fontLoader.font.family
            font.pixelSize: 17
            font.letterSpacing: 5

            onCheckStateChanged: {
                if (checked) {
                    tetrion.showPlayfieldGrid()
                } else {
                    tetrion.hidePlayfieldGrid()
                }
            }
        }

    }

    TextButton {
        id: keyBindingsButton
        text: "Key Bindings"
        font.family: fontLoader.font.family
        font.pixelSize: 17
        font.letterSpacing: 5
        anchors.top: checkBoxLayout.bottom
        anchors.topMargin: 10
        anchors.left: checkBoxLayout.left
        anchors.leftMargin: 3
    }

    TextButton {
        id: backButton
        text: "Back"
        font.family: fontLoader.font.family
        font.pixelSize: 17
        font.letterSpacing: 5
        anchors.top: keyBindingsButton.bottom
        anchors.topMargin: 10
        anchors.left: keyBindingsButton.left
        anchors.leftMargin: 3

        onClicked: parent.backButtonClicked()
    }
}
