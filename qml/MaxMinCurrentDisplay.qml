import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: root
    property real min: 0
    property real max: 100
    property real current: 50
    property string units: "V"
    property string label: "BatPack Voltage"

    Rectangle {
        id: currentContainer
        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }
        width: 0.6*parent.width
        border {
            color: primaryYellow
        }
        color: secondaryBlue
        MouseArea {
            id: currentValueMouseArea
            anchors.fill: parent
            acceptedButtons:Qt.NoButton
            hoverEnabled: true

            Text {
                id: currentText
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                    topMargin: parent.height/4
                }
                horizontalAlignment: Text.AlignHCenter

                text: current + units
                font.pointSize: 14
                color: primaryYellow

                ToolTip.visible: currentValueMouseArea.containsMouse
                ToolTip.text: "Current Value"
            }
            Text {
                id: labelText
                text: label
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors {
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                    top: currentText.bottom
                }
                font.pointSize: 10
                color: primaryYellow
                wrapMode: Text.WordWrap
            }
        }
    }
    Rectangle {
        id: maxMinContainer
        anchors {
            top: parent.top
            left: currentContainer.right
            bottom: parent.bottom
            right: parent.right
        }

        Rectangle {
            id: maxContainer
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            border {
                color: primaryYellow
            }
            color: secondaryBlue
            height: 0.5*parent.height
            MouseArea{
                id: maxValueMouseArea
                anchors.fill: parent
                acceptedButtons:Qt.NoButton
                hoverEnabled: true

                Text {
                    anchors.centerIn: parent
                    text: max + units
                    font.pointSize: 12
                    color: primaryYellow

                    ToolTip.visible: maxValueMouseArea.containsMouse
                    ToolTip.text: "Max Value"
                }
            }

        }
        Rectangle {
            id: minContainer
            border {
                color: primaryYellow
            }
            color: secondaryBlue
            anchors {
                top: maxContainer.bottom
                left: parent.left
                bottom: parent.bottom
                right: parent.right
            }
            MouseArea {
                id: minValueMouseArea
                anchors.fill: parent
                acceptedButtons:Qt.NoButton
                hoverEnabled: true

                Text {
                    anchors.centerIn: parent
                    text: min + units
                    font.pointSize: 12
                    color: primaryYellow
                }
            }
        }
    }
}
