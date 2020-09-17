import QtQuick 2.3
import evo.views 1.0

EView {
    id: home_root
    objectName: "home_root"
    width: 100
    height: 100

    Rectangle {
        id: home_container
        objectName: "home_container"
        width: 100
        height: 100
        color: "black"

        Text {
            id: home_text
            objectName: "home_text"
            anchors.centerIn: parent
            text: qsTr("QmlDemo")
            color: "white"
        }
    }
}
