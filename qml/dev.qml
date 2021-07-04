import QtQuick 2.0
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    height: 600;
    width: 800;
    title: qsTr("Development Portal")
    visible: true

    Button {
        id: testNetwork
        anchors.centerIn: parent
        height: parent.height/2
        width: parent.width/2
        background: Rectangle {
            id: buttonBackground
            color: "black"
            anchors.centerIn: parent
            anchors.fill: parent
            Text {
                id: buttonText
                anchors.centerIn: parent
                font.pointSize: 18
                color: "#FAFAFA"
                text: "Connect to Relayboard"
            }
        }
        onClicked: {
            network.connectToRelayBoard()
        }

    }
}
