import QtQuick 2.15

Item {
    id: item1
    width: 300
    height: 400
    property alias connect_button_logic: connect_button_logic
    property alias connect_button_text: connect_button_text.text
    property alias background_color: background.color
    property alias change_dashboard_button_logic: change_dashboard_button_logic

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#31325d"
    }

    Rectangle {
        id: connect_button
        height: 50
        color: "#7071c5"
        radius: 4
        anchors {
            left: parent.left
            right: parent.right
            leftMargin: 8
            rightMargin: 8
            top: parent.top
            topMargin: 8
        }
        TapHandler {
            id: connect_button_logic
        }

        Text {
            id: connect_button_text
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.underline: false
            font.bold: false
            font.family: "Tahoma"
            anchors.centerIn: parent
            text: "Connect"
            font.letterSpacing: 0.6
            font.pixelSize: 24
        }
    }

    Rectangle {
        id: change_dashboard_button
        height: 50
        color: "#7071c5"
        radius: 4
        anchors {
            left: parent.left
            right: parent.right
            leftMargin: 8
            rightMargin: 8
            top: connect_button.bottom
            topMargin: 8
        }
        TapHandler {
            id: change_dashboard_button_logic
        }

        Text {
            id: change_dashboard_button_text
            color: "#ffffff"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            style: Text.Normal
            font.underline: false
            font.bold: false
            font.family: "Tahoma"
            anchors.centerIn: parent
            text: "Edit Dashboard"
            font.letterSpacing: 0.6
            font.pixelSize: 24
        }
    }
}
