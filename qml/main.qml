import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4
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

//    Rectangle {
//        id: side_bar
//        width: 300
//        anchors.left: parent.left
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        color: waterloo_dark

//        Text {
//            text: "Connect"
//            color: "white"
//            horizontalAlignment: Text.AlignHCenter
//            verticalAlignment: Text.Center
//        }

//        MouseArea {
//            anchors.fill: parent
//            onClicked: network.connectToRelayBoard()
//        }
//    }
    SideBar {
        id: side_bar
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }

        connect_button_text: {
            if (network.relayBoardConnected) {
                "Disconnect"
            } else {
                "Connect"
            }
        }

        onConnectionButtonPressed: {
            if (network.relayBoardConnected) {
                network.disconnectFromRelayBoard()
            } else {
                network.connectToRelayBoard()
            }
        }

        onEditDashboardPressed: {
            gui.cycleCurrentPage(display_container.count);
        }
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

    TabView {
        id: display_container
        anchors {
            top: header.bottom
            left: side_bar.right
            right: parent.right
            bottom: parent.bottom
//            topMargin: 225
            bottomMargin: 80
            rightMargin: 80
        }
        currentIndex: gui.currentPage
        tabsVisible: false
        frameVisible: false

        Tab {
            title: 'main_screen'
            Rectangle {
                color: waterloo_light
                anchors.top: parent.top
                anchors.topMargin: 100

                PodStateViewer {
                    id: pod_state_viewer
                    anchors {
                        bottom: distance_tracker.top
                        bottomMargin: 8
                        left: data_grid.left
                        right: speedometer.left
                    }

                    state: {
                        if (!network.relayBoardConnected) return "";
                        switch (pod.currentState) {
                        case PodStates.LowVoltage:
                            return "LvReadyState"
                        case PodStates.Armed:
                            return "HvReadyState"
                        case PodStates.AutoPilot:
                            return "AutopilotState"
                        case PodStates.Braking:
                            return "BrakingState"
                        case PodStates.Resting:
                        default:
                            return "RestingState"
                        }
                    }
                    onStateSelected: {
                        console.log("State Selected")
                        console.log(newState)
                        if (!network.relayBoardConnected) return; // Don't try to change states if the relay board isn't connected
                        switch (newState) {
                        case "LvReadyState":
                            pod.requestedState = PodStates.LowVoltage;
                            break;
                        case "HvReadyState":
                            pod.requestedState = PodStates.Armed;
                            break;
                        case "AutopilotState":
                            pod.requestedState = PodStates.Autopilot;
                            break;
                        case "BrakingState":
                            pod.requestedState = PodStates.Braking;
                            break;
                        case "RestingState":
                        default:
                            console.log("State: ", newState, "Not implimented")
                        }
                    }
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

        Tab {
            title: "sensor_screen"
            anchors.fill:parent
            Rectangle {
                color: waterloo_light
                anchors.fill: parent

                GridView {
                    model: liveData
                    onCountChanged: {
                        console.log(count)
                    }
                    anchors.fill:parent
                    cellWidth: 340
                    cellHeight: 260
                    delegate: TelemetryDataForm {
                        id: sensor_screen_list_item
                        dataName: display
                        dataValue: reading
                        dataUnit: unit

                        dataMax: max_value
                        dataMin: min_value

                    }
                }
            }
        }

    }
}
