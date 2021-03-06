import QtQuick 2.15
import QtQuick.Window 2.15
import "."
import waterloop.common 1.0

Window {
    width: 1024
    height: 576
    visible: true
    title: qsTr("CHC Competition Dashboard")
    color: primaryBlue

    property string primaryBlue: "#232635"
    property string secondaryBlue: "#373E5A"
    property string primaryYellow: "#FED138"
    property string green: "#1FDD8C"
    property string red: "#F2466F"
    property string blue3: "#556697"
    property real maxMinCurDisplayHeight: 96
    property real maxMinCurDisplayWidth: 170

    function getUnitString(unit) {
        switch(unit) {
        case Common.VOLT:
            return 'V'
        case Common.AMP:
            return 'A'
        case Common.PERCENTAGE:
            return '%'
        case Common.CELCIUS:
            return 'C'
        }
    }

    Controls{
        id: controls
        height: 0.2*parent.height
        width: 0.6*parent.width
        anchors {
            bottom: parent.bottom
            left: parent.left
            leftMargin: Math.min(parent.width*0.2, 30)
            bottomMargin: Math.min(parent.width*0.2, 30)
        }
    }

    Item {
        id: listRow
        clip: true
        anchors {
            top: parent.top
            left: parent.left
            topMargin: Math.min(parent.width*0.2, 30)
            leftMargin: Math.min(parent.width*0.2, 30)
            rightMargin: Math.min(parent.width*0.2, 30)
            bottom: controls.top
            right: sensors.left
            horizontalCenter: parent
        }


        GridView {
            model: liveData

            interactive: contentHeight > parent.height

            anchors.fill: parent

            cellWidth: maxMinCurDisplayWidth + 10
            cellHeight: maxMinCurDisplayHeight + 10

            Component.onCompleted: console.log(currentItem)

            onCurrentItemChanged: console.log(currentItem)

            delegate: MaxMinCurrentDisplay {
                max: max_value
                min: min_value
                current: reading
                label: display
                height: maxMinCurDisplayHeight
                width: maxMinCurDisplayWidth
                units: getUnitString(unit)
            }
        }
    }

    Rectangle {
        id: sensors
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            rightMargin: 30
            topMargin: 30
            bottomMargin: 30
        }
        width: 280
    }
}
