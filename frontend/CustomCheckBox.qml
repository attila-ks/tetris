import QtQuick
import QtQuick.Controls
import Qt5Compat.GraphicalEffects

CheckBox {
    id: control
    property string borderColor
    property string fillColor
    property string checkMarkColor
    property string textColor

    indicator: Rectangle {
        implicitWidth: 20
        implicitHeight: 20
        x: control.leftPadding
        y: control.height / 2 - height / 2
        radius: 3
        border.color: control.borderColor
        color: control.fillColor

        Image {
            id: icon
            width: 17
            height: 15
            source: "../resources/icons/done_black_24dp.svg"
            visible: control.checked
            anchors.centerIn: parent
        }

        ColorOverlay {
            anchors.fill: icon
            source: icon
            color: control.checkMarkColor
            visible: icon.visible
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.textColor
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
