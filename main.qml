import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    ListView {
        id: listView1
        anchors.fill: parent
        delegate: Item {
            x: 5
            anchors.right: parent.right
            anchors.left: parent.left
            height: 50
            Row {
                id: row1
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    anchors.verticalCenter: parent.verticalCenter
                    font.bold: true
                }
                Text {
                    text: time
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.Right
                }

                spacing: 10
            }
        }
        model: ListModel {
            ListElement {
                name: "Karl"
                colorCode: "grey"
                time: "12:34.342"
            }

            ListElement {
                name: "Marx"
                colorCode: "red"
                time: "12:34.342"
            }

            ListElement {
                name: "Lars"
                colorCode: "blue"
                time: "12:34.342"
            }

            ListElement {
                name: "Steffi"
                colorCode: "green"
                time: "12:34.342"
            }
        }


    }
}
