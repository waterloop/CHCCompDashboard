import QtQuick 2.15

Rectangle {
    width: 400
    height: 400
    color: 'grey'
    property alias delegateSelector: delegateSelector
    property alias dashboardOptionsModel: grid.model

    GridView {
        id: grid
        visible: true
        cellWidth: 84
        cellHeight: 84
        anchors.fill: parent

        model: ListModel {
            ListElement {
                fieldName: 'Battery Voltage'
                selected: false
            }
            ListElement {
                fieldName: 'Battery Current'
                selected: true
            }
            ListElement {
                fieldName: 'Torchic 1'
                selected: true
            }
        }

        delegate: Rectangle {
            id: delegate_root
            width: grid.cellWidth - 4
            height: grid.cellHeight - 4
            color: 'white'

            border.color: 'black'

            Rectangle {
                anchors.top: delegate_root.top
                anchors.right: delegate_root.right
                anchors.topMargin: 8
                anchors.rightMargin: 8

                height: 8
                width: 8
                border.color: 'black'
                border.width: 2

                Image {
                    source: 'qrc:/assets/checkmark.svg'
                }
            }

            Text {
                text: fieldName
                font.family: "Tahoma"
                color: 'black'
                anchors.centerIn: parent
            }
            TapHandler {
                id: delegateSelector
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/

