import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.3
import QtGraphicalEffects 1.0

Rectangle {

    width: 700
    height: 500

    ListModel {
        id: modelMatches

        ListElement {
            name: "Grey"
            colorCode: "grey"
            time: "01:24.127"
        }

        ListElement {
            name: "Red"
            colorCode: "red"
            time: "01:24.127"
        }

        ListElement {
            name: "Blue"
            colorCode: "blue"
            time: "01:24.127"
        }

        ListElement {
            name: "Green"
            colorCode: "green"
            time: "01:24.127"
        }
    }

    Gradient {
        id: gold

        GradientStop {
            position: 0
            color: "#fceabb"
        }
        GradientStop {
            position: 0.5
            color: "#fccd4d"
        }
        GradientStop {
            position: 0.51
            color: "#f8b500"
        }
        GradientStop {
            position: 1
            color: "#fbdf93"
        }
    }

    Gradient {
        id: silver

        GradientStop {
            position: 0
            color: "#f2f6f8"
        }
        GradientStop {
            position: 0.5
            color: "#d8e1e7"
        }
        GradientStop {
            position: 0.51
            color: "#b5c6d0"
        }
        GradientStop {
            position: 1
            color: "#e0eff9"
        }
    }

    Gradient {
        id: bronze

        GradientStop {
            position: 0
            color: "#feccb1"
        }
        GradientStop {
            position: 0.5
            color: "#f17432"
        }
        GradientStop {
            position: 0.51
            color: "#ea5507"
        }
        GradientStop {
            position: 1
            color: "#fb955e"
        }
    }

    Gradient {
        id: white

        GradientStop {
            position: 1
            color: "#ffffff"
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Rectangle {
        id: columnMain
        anchors.fill: parent



        Rectangle {
            id: rowCurrentGame
            height: parent.height / 100 * 20
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.top: parent.top

            /*Image {
                id: imageAvatar
                width: height
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                source: "qrc:/qtquickplugin/images/template_image.png"
            }

            TextField {
                id: textInputName
                text: currMatch.name
                anchors.bottomMargin: 10
                anchors.topMargin: 10
                placeholderText: "Mr. Unbekannt"
                anchors.rightMargin: 10
                anchors.left: imageAvatar.right
                anchors.right: textTime.left
                //anchors.bottom: parent.bottom
                //anchors.top: parent.top
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: 10
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
            }*/

            Text {
                id: textMistakeCount
                //width: 200
                text: currMatch.mistakeCount
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                font.pointSize: 100
                wrapMode: Text.NoWrap
                //horizontalAlignment: Text.AlignHCenter
                anchors.left: parent.left
                anchors.top: parent.top
                fontSizeMode: Text.Fit
                verticalAlignment: Text.AlignVCenter
            }

            Text {
                id: textTime
                //width: 200
                text: currMatch.durationStr
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                font.pointSize: 100
                wrapMode: Text.NoWrap
                horizontalAlignment: Text.AlignRight
                anchors.right: parent.right
                anchors.top: parent.top
                fontSizeMode: Text.Fit
                verticalAlignment: Text.AlignVCenter
            }
        }

        ListView {
            id: listLeaderboard
            anchors.top: rowCurrentGame.bottom
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: 0
            clip: true
            delegate: Item {
                x: 5
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10

                height: 60

                Rectangle {
                    anchors.fill: parent;
                    anchors.topMargin: 4
                    anchors.bottomMargin: 4

                    Rectangle {
                        id: rect
                        anchors.fill: parent
                        border.width: 1
                        gradient: index==0 ? gold : (index==1 ? silver : (index==2 ? bronze : white))

                        Rectangle {
                            color: "#00000000";
                            anchors.fill: parent
                            anchors.margins: 2
                            anchors.leftMargin: 5

                            Rectangle {
                                color: "#00000000";
                                anchors.fill: parent

                                anchors.verticalCenter: parent.verticalCenter

                                Rectangle {
                                    id: avatar
                                    width: 40
                                    height: 40
                                    color: colorCode
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                }

                                Text {
                                    id: nameField
                                    text: model.modelData.name
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                    font.pointSize: 12
                                    anchors.leftMargin: 5
                                    anchors.left: avatar.right
                                    anchors.right: timeField.left
                                }

                                Text {
                                    id: timeField
                                    text: model.modelData.durationStr
                                    anchors.verticalCenter: parent.verticalCenter
                                    //anchors.left: nameField.Right
                                    anchors.right: parent.right
                                    anchors.rightMargin: 5
                                    font.pointSize: 12
                                }
                            }
                        }

                        layer.enabled: true
                        layer.effect: DropShadow {
                            anchors.fill: parent
                            horizontalOffset: 3
                            verticalOffset: 3
                            radius: 4.0
                            samples: 17
                            color: "#80000000"
                            source: rect
                            transparentBorder: true
                        }
                    }
                }
            }


            model: leaderboard
        }


    }
}
