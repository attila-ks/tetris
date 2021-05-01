import QtQuick 2.13

Item {
    id: root
    implicitWidth: childrenRect.width
    implicitHeight: childrenRect.height

    Rectangle {
        id: header
        width: panelBackground.width
        height: 20
        color: "#173d89"

        Text {
            text: "NEXT"
            color: "white"
            x: 2
            anchors.verticalCenter: header.verticalCenter
        }
    }

    Line {
        id: line
        length: panelBackground.width
        width: 2
        anchors.top: header.bottom
        color: "#2177cf"
    }

    Rectangle {
        id: panelBackground
        // FIX: The width and height attributes are depend on rows and columns
        // of the matrix of the next tetromino, which means these attributes has
        // to be adjusted when the size of the matrix is changed.
        width: 95
        height: 105
        color: "#11213c" // It should not be hardcoded.
        anchors.top: line.bottom
        // panelBackground hides line without the following code.
        anchors.topMargin: line.width

        Grid {
            id: grid
            spacing: 1
            anchors.centerIn: panelBackground

            Repeater {
                id: repeater

                Rectangle {
                    id: cell
                    implicitWidth: 20
                    implicitHeight: 20
                    color: modelData
                }
            }

            Connections {
                target: tetrion
                // TODO: Give more expressive names for the parameters.
                function onNext_tetromino_changed(rows, columns) {
                    grid.rows = rows;
                    grid.columns = columns;
                    repeater.model = tetrion.next_tetromino();
                }
            }
        }
    }

    Line {
        length: panelBackground.width
        width: 2
        anchors.bottom: root.bottom
        color: "#2177cf"
    }
}
