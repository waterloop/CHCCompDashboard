import QtQuick 2.0
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "."
import waterloop.common 1.0

Window {
    width: 1440
    height: 800
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
        anchors.bottom: parent.bottom
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
        id: display_container
        anchors {
            top: header.bottom
            left: side_bar.right
            right: parent.right
            bottom: parent.bottom
            topMargin: 225
            bottomMargin: 80
            rightMargin: 80
        }
        color: waterloo_light

        PodStateViewer {
            id: pod_state_viewer
            anchors {
                bottom: distance_tracker.top
                bottomMargin: 8
                left: data_grid.left
                right: speedometer.left
            }
            state: "RestingState"
            onStateSelected: pod_state_viewer.state = newState
        }

        Speedometer {
            id: speedometer
            width: 80
            speed: pod.motorController.podSpeed
            anchors {
                right: data_grid.right
                bottom: pod_state_viewer.bottom
                top: pod_state_viewer.top
            }
        }

        PodDistanceTracker {
            id: distance_tracker
            anchors {
                bottom: data_grid.top
                left: data_grid.left
                right: data_grid.right
                bottomMargin: 8
            }
        }

        GridLayout {
            id: data_grid
            columns: 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            TelemetryDataForm {

            }
            TelemetryDataForm {

            }
            TelemetryDataForm {

            }
            TelemetryDataForm {

            }
        }
    }
}
