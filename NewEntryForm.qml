import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
//import QtQuick.Dialogs 1.2

Item {
    id: dialog
    width: 320
    height: 140

    property string name
    property int duration
    property int mistakeCount

    signal buttonCancelClicked()
    signal buttonAddClicked(string name, int duration, int mistakeCount)

    Connections {
        target: currMatch
        onStopped: {
            dialog.duration = duration
            dialog.mistakeCount = mistakeCount
            //dialog.show()
        }
    }

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
                    text: qsTr("Fehler: " +  mistakeCount)
                    font.pointSize: 16
                }

                Label {
                    id: labelDuration
                    text: qsTr("Zeit: 00:00.000" + duration)
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
                onClicked: dialog.buttonCancelClicked()
            }

            Button {
                id: buttonAdd
                text: qsTr("Eintragen")
                isDefault: true
                onClicked: dialog.buttonAddClicked(name, duration, mistakeCount)
            }

        }

    }

}
