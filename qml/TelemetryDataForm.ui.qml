import QtQuick 2.4

Item {
    width: 340
    height: 260

    property string dataName: "Battery Pack Voltage"
    property double dataValue: 0
    property string dataUnit: "VDC"

    property alias dataMax: gradient_bar.max
    property alias dataMin: gradient_bar.min

    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: "#232635"

        Text {
            id: data_name_text
            text: dataName
            font.pixelSize: 34
            horizontalAlignment: Text.AlignHCenter
            lineHeight: 1.4
            wrapMode: Text.WordWrap
            font.weight: Font.Light
            font.family: "Tahoma"
            textFormat: Text.PlainText
            fontSizeMode: Text.HorizontalFit
            anchors.horizontalCenter: parent.horizontalCenter
            anchors {
                top: parent.top
            }
            color: "white"
        }

        Text {
            id: data_value_text
            color: "#ffffff"
            text: dataValue
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            font.weight: Font.Light
            font.family: "Tahoma"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: data_name_text.bottom
        }

        Text {
            id: data_unit_text
            color: "#ffffff"
            text: dataUnit
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
            font.weight: Font.Light
            font.family: "Tahoma"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: data_value_text.bottom
        }

        GradientBar {
            id: gradient_bar
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 42
            value: dataValue
        }
    }
}
