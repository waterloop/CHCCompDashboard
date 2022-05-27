import QtQuick 2.4
import QtGraphicalEffects 1.12

Item {
    width: 300
    height: 58
    visible: true
    property double value: 27
    property double max: 70
    property double min: 0

    Rectangle {
        id: gradient_bar
        x: 146
        y: -126
        width: 8
        radius: 10
        border.color: "#ffffff"
        border.width: 1
        height: 300
        rotation: 270
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#31325D"
            }
            GradientStop {
                position: 0.33
                color: "#25CB55"
            }
            GradientStop {
                position: 0.66
                color: "#FED138"
            }
            GradientStop {
                position: 1.0
                color: "#E82127"
            }
        }
    }

    Rectangle {
        id: left_line
        height: 28
        width: 1
        color: "white"
        x: value * 298 / 28 // 298/28 => number of pixels per division
        y: 0
    }

    Rectangle {
        id: tick_1
        height: 12
        width: 1
        y: left_line.height + 4
        x: 1
    }

    Text {
        text: ((max - min) / 14) * 0 + min
        anchors.top: tick_1.bottom
        color: "white"
    }

    Rectangle {
        id: tick_2
        height: 6
        width: 1
        y: left_line.height + 4
        x: 1 * 298 / 28
    }
    Rectangle {
        id: tick_3
        height: 8
        width: 1
        y: left_line.height + 4
        x: 2 * 298 / 28
    }

    Text {
        text: Math.round(((max - min) / 14) * 1)+ min
        anchors.top: tick_3.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_3.horizontalCenter
        color: "white"
    }

    Rectangle {
        id: tick_4
        height: 6
        width: 1
        y: left_line.height + 4
        x: (300 / 28) * 3
    }
    Rectangle {
        id: tick_5
        height: 12
        width: 1
        y: left_line.height + 4
        x: (300 / 28) * 4
    }
    Text {
        text: Math.round(((max - min) / 14) * 2)+ min
        anchors.top: tick_5.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_5.horizontalCenter
        color: "white"
    }

    Rectangle {
        id: tick_6
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 5
    }
    Rectangle {
        id: tick_7
        height: 8
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 6
    }
    Text {
        text: Math.round(((max - min) / 14) * 3)+ min
        anchors.top: tick_7.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_7.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_8
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 7
    }
    Rectangle {
        id: tick_9
        height: 12
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 8
    }
    Text {
        text: Math.round(((max - min) / 14) * 4)+ min
        anchors.top: tick_9.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_9.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_10
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 9
    }
    Rectangle {
        id: tick_11
        height: 8
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 10
    }
    Text {
        text: Math.round(((max - min) / 14) * 5)+ min
        anchors.top: tick_11.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_11.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_12
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 11
    }
    Rectangle {
        id: tick_13
        height: 12
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 12
    }
    Text {
        text: Math.round(((max - min) / 14) * 6)+ min
        anchors.top: tick_13.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_13.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_14
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 13
    }
    Rectangle {
        id: tick_15
        height: 8
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 14
    }
    Text {
        text: Math.round(((max - min) / 14) * 7)+ min
        anchors.top: tick_15.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_15.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_16
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 15
    }
    Rectangle {
        id: tick_17
        height: 12
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 16
    }
    Text {
        text: Math.round(((max - min) / 14) * 8)+ min
        anchors.top: tick_17.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_17.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_18
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 17
    }
    Rectangle {
        id: tick_19
        height: 8
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 18
    }
    Text {
        text: Math.round(((max - min) / 14) * 9)+ min
        anchors.top: tick_19.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_19.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_20
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 19
    }
    Rectangle {
        id: tick_21
        height: 12
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 20
    }
    Text {
        text: Math.round(((max - min) / 14) * 10)+ min
        anchors.top: tick_21.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_21.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_22
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 21
    }
    Rectangle {
        id: tick_23
        height: 8
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 22
    }
    Text {
        text: Math.round(((max - min) / 14) * 11)+ min
        anchors.top: tick_23.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_23.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_24
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 23
    }
    Rectangle {
        id: tick_25
        height: 12
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 24
    }
    Text {
        text: Math.round(((max - min) / 14) * 12)+ min
        anchors.top: tick_25.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_25.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_26
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 25
    }
    Rectangle {
        id: tick_27
        height: 8
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 26
    }
    Text {
        text: Math.round(((max - min) / 14) * 13)+ min
        anchors.top: tick_27.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_27.horizontalCenter
        color: "white"
    }
    Rectangle {
        id: tick_28
        height: 6
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 27
    }
    Rectangle {
        id: tick_29
        height: 8
        width: 1
        y: left_line.height + 4
        x: (298 / 28) * 28
    }
    Text {
        text: Math.round(((max - min) / 14) * 14)+ min
        anchors.top: tick_29.bottom
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: tick_29.horizontalCenter
        color: "white"
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}
}
##^##*/

