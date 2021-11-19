import QtQuick 2.4

Item {
    width: 400
    height: 400
    property alias speed: speed_value.text

    Text {
        id: unit
        text: "M / S"
        font.pixelSize: 14
        horizontalAlignment: Text.AlignHCenter
        font.family: "Tahoma"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        color: "white"
    }

    Text {
        id: speed_value
        font.pixelSize: 60
        anchors.top: unit.bottom
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        font.family: "Tahoma"
        anchors.horizontalCenter: parent.horizontalCenter
        text: "0"
    }
}
