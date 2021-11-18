import QtQuick 2.0
import QtQuick.Window 2.15
import "."
import waterloop.common 1.0

Window {
    width: 1024
    height: 576
    visible: true
    title: qsTr("CHC Competition Dashboard")

    property string waterloo_dark: "#232635"
    property string waterloo_light: "#31325D"

    Rectangle {
        id: background
        color: waterloo_light
        anchors.fill: parent
    }

    Rectangle {
        id: side_bar
        width: 300
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: footer.bottom
        color: waterloo_dark
    }

    Rectangle {
        id: header
        height: 60
        anchors {
            left: side_bar.right
            right: parent.right
            top: parent.top
        }
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#232635"
            }
            GradientStop {
                position: 1
                color: "transparent"
            }
        }
    }

    Rectangle {
        id: footer
        height: 80
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: waterloo_dark
    }

    Rectangle {
        id: display_container
        anchors {
            top: header.top
            left: side_bar.right
            right: parent.right
            topMargin: 225
            bottomMargin: 80
            leftMargin: 80
            rightMargin: 80
        }
    }
}
