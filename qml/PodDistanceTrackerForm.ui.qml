import QtQuick 2.4

Item {
    property double distanceTraveled: 0 // in meters
    property double tripDistance: 100 // in meters
    width: 300
    height: 80

    Image {
        id: pod_icon
        source: "../assets/pod.svg"
        height: 20
        width: 100
        anchors.bottom: base_bar.top
        anchors.bottomMargin: 6
        sourceSize.width: 100
        sourceSize.height: 20
    }

    Rectangle {
        id: base_bar
        color: "black"
        height: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.left: parent.left
        anchors.right: distance_text_container.left
        radius: 10
    }

    Rectangle {
        id: progress_bar
        color: "#FED138"
        height: 8
        width: (base_bar.width - 50) * (distanceTraveled / tripDistance) + 50
        anchors {
            left: base_bar.left
            top: base_bar.top
            bottom: base_bar.bottom
        }
        radius: 10
    }
    Rectangle {
        id: distance_text_container
        anchors {
            top: parent.top
            bottom: progress_bar.bottom
            right: parent.right
        }
        width: parent.width * 1 / 8
        color: "transparent"

        Text {
            id: distance_text_value
            text: distanceTraveled
            font.family: "Tahoma"
            font.pointSize: 34
            minimumPixelSize: 6
            color: "#FED138"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
        }
        Text {
            text: "M"
            font.family: "Tahoma"
            font.pointSize: 14
            minimumPixelSize: 6
            color: "#FED138"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: distance_text_value.bottom
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:2}
}
##^##*/

