import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 1080 / 2
    height: 720 / 2
    visible: true
    title: qsTr("CuteGallery")
    color: "#333333"

    Item {
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        clip: true

        GridView {
            id: grid
            anchors.fill: parent
            cellHeight: 190
            cellWidth: 250
            model: ListModel {}
            delegate: Rectangle {
                id: box
                color: "#0099ff"
                width: 240
                height: 180
                Image {
                    id: image
                    anchors.left: box.left
                    anchors.right: box.right
                    anchors.top: box.top
                    height: 160
                    fillMode: Image.PreserveAspectFit
                    source: "image://file/" + path
                }
                Text {
                    anchors.left: box.left
                    anchors.right: box.right
                    anchors.bottom: box.bottom
                    color: "#111111"
                    text: "Bild"
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }
    }

    Timer {
        interval: 10
        running: true
        repeat: false
        onTriggered: {
            controller.deferredInit()
            grid.model = model
        }
    }
}
