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
            anchors {
                top: parent.top
                topMargin: 8
                leftMargin: 8
                left: parent.left
                rightMargin: 8
                right: parent.right
            }
            color: "white"
        }

        Text {
            id: data_value_text
            color: "#ffffff"
            text: dataValue.toFixed(4)
            font.pixelSize: 60
            horizontalAlignment: Text.AlignHCenter
            font.weight: Font.Light
            font.family: "Tahoma"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors {
                top: parent.top
                topMargin: 50
                bottom: parent.bottom
                bottomMargin: 50
            }
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
            anchors.top: data_value_text.top
            anchors.topMargin: 70
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
