import QtQuick 2.15

Item {
    id: root
    width: 700
    height: 80

    property alias resting_state_button: resting_state_button
    property alias lv_state_button: lv_state_button
    property alias hv_state_button: hv_state_button
    property alias autopilot_state_button: autopilot_state_button
    property alias braking_state_button: braking_state_button

    Rectangle {
        id: resting_state_container
        height: parent.height
        width: parent.width / 5
        color: "#232635"
        anchors.left: parent.left

        TapHandler {
            id: resting_state_button
        }

        Text {
            id: resting_state
            color: "#ffffff"
            text: "Resting"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
        }
    }
    Rectangle {
        id: lowv_state_container
        height: parent.height
        width: parent.width / 5
        color: "#232635"
        anchors.left: resting_state_container.right

        TapHandler {
            id: lv_state_button
        }

        Text {
            id: lowv_state
            color: "#ffffff"
            text: "LV Ready"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
        }
    }
    Rectangle {
        id: highv_state_container
        height: parent.height
        width: parent.width / 5
        color: "#232635"
        anchors.left: lowv_state_container.right

        TapHandler {
            id: hv_state_button
        }

        Text {
            id: highv_state
            color: "#ffffff"
            text: "HV Ready"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
        }
    }
    Rectangle {
        id: autopilot_state_container
        height: parent.height
        width: parent.width / 5
        color: "#232635"
        anchors.left: highv_state_container.right

        TapHandler {
            id: autopilot_state_button
        }

        Text {
            id: autopilot_state
            color: "#ffffff"
            text: "Autopilot"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
        }
    }
    Rectangle {
        id: braking_state_container
        height: parent.height
        width: parent.width / 5
        color: "#232635"
        anchors.left: autopilot_state_container.right

        TapHandler {
            id: braking_state_button
        }

        Text {
            id: braking_state
            color: "#ffffff"
            text: "Brake"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.fill: parent
        }
    }
    states: [
        State {
            name: "RestingState"

            PropertyChanges {
                target: resting_state
                color: "#fed138"
            }
        },
        State {
            name: "LvReadyState"

            PropertyChanges {
                target: lowv_state
                color: "#fed138"
            }
        },
        State {
            name: "HvReadyState"
            PropertyChanges {
                target: lowv_state
                color: "#ffffff"
            }

            PropertyChanges {
                target: highv_state
                color: "#fed138"
                text: "HV Ready"
            }
        },
        State {
            name: "AutopilotState"

            PropertyChanges {
                target: autopilot_state
                color: "#fed138"
            }
        },
        State {
            name: "BrakingState"

            PropertyChanges {
                target: braking_state
                color: "#fed138"
            }
        }
    ]
}
