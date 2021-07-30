import QtQuick 2.0
import QtQuick.Controls 2.15
// Controls
Rectangle {

    function handleGoControlClicked() {
        if (state == "running") {
            state = "stoped"
        } else {
            state = "running"
        }
    }

    state: "stoped"

    states: [
        State {
            name: "running"
            PropertyChanges {
                target: buttonText
                text: "STOP"
            }PropertyChanges {
                target: buttonBackground
                color: red
            }
        },
        State {
            name: "stoped"
            PropertyChanges {
                target: buttonText
                text: "START"
            }
            PropertyChanges {
                target: buttonBackground
                color: green
            }
        }

    ]

    border {
        color: primaryYellow
        width: 4
    }
    color: primaryBlue
    radius: 9

    Button {
        id: goControl
        width: parent.width / 4;
        height: parent.height / 3;
        anchors.centerIn: parent;
        background: Rectangle {
            id: buttonBackground
            color: green
            anchors.fill: parent
            radius: 18
            Text {
                id: buttonText
                anchors.centerIn: parent
                font.pointSize: 18
                color: "#FAFAFA"
            }
        }

        onClicked: handleGoControlClicked()
    }
}
