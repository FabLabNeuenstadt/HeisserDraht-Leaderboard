import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Rectangle {
    width: 320
    height: 140

    ColumnLayout {
        id: columnLayoutMain
        anchors.fill: parent


        RowLayout {
            id: rowLayoutMatch
            width: 100
            height: 100
            Layout.fillWidth: true


            Image {
                id: imageAvatar
                width: 80
                height: 80
                Layout.maximumHeight: 128
                Layout.maximumWidth: 128
                Layout.minimumHeight: 32
                Layout.minimumWidth: 32
                Layout.preferredHeight: 80
                Layout.preferredWidth: 80
                source: "qrc:/qtquickplugin/images/template_image.png"
            }
            ColumnLayout {
                id: columnLayoutValues
                width: 100
                height: 100
                Layout.fillWidth: true

                TextField {
                    id: textFieldName
                    width: 198
                    height: 26
                    Layout.fillWidth: true
                    placeholderText: qsTr("Name")
                }

                Label {
                    id: labelMistakes
                    text: qsTr("Fehler: 0")
                    font.pointSize: 16
                }

                Label {
                    id: labelDuration
                    text: qsTr("Zeit: 00:00.000")
                    font.pointSize: 16
                }


            }
        }

        RowLayout {
            id: rowLayoutButtons
            width: 100
            height: 100
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            Button {
                id: buttonCancel
                text: qsTr("Abbrechen")
            }

            Button {
                id: buttonAdd
                text: qsTr("Eintragen")
                isDefault: true
            }

        }

    }

}
