import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.3
import QtGraphicalEffects 1.0

Rectangle {

    width: 700
    height: 500

    Connections {
        target: mainCtrl
        onAddEntry: {
            var milliseconds = duration % 1000
            var seconds = parseInt((duration / 1000) % 60)
            var minutes = parseInt((duration / 1000 / 60) % 60)

            var millisecondsStr = ""
            var secondsStr = ""
            var minutesStr = ""

            if(milliseconds < 10) {
                millisecondsStr = "00" + milliseconds
            } else if (milliseconds < 100) {
                millisecondsStr = "0" + milliseconds
            } else {
                millisecondsStr = milliseconds
            }

            if(seconds < 10) {
                secondsStr = "0" + seconds
            } else {
                secondsStr = seconds
            }

            if(minutes < 10) {
                minutesStr = "0" + minutes
            } else {
                minutesStr = minutes
            }

            var durationStr = minutesStr + ":" + secondsStr + "." + millisecondsStr

            // ----

            var newEntry = {"duration": duration,
                "durationStr": durationStr,
                "name": name,
                "mistakeCount": mistakeCount,
                "avatarId": avatarId}

            var i
            var idx = -1
            for(i = 0; i < leaderboard.count; i++) {
                var entry = leaderboard.get(i)
                if(duration < entry.duration) {
                    //print(duration + "<" + entry.duration)
                    leaderboard.insert(i, newEntry)
                    idx = i
                    break
                }
            }
            if(idx < 0) {
                leaderboard.append(newEntry)
            }

            // only show the best 100
            if(leaderboard.count > 100) {
                leaderboard.remove(100, leaderboard.count - 100)
            }
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

        ListModel {
            id: leaderboard
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

                                Image {
                                    id: avatar
                                    width: 80
                                    height: 80
                                    source: "avatars/" + model.avatarId + ".png"
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                }

                                Text {
                                    id: nameField
                                    text: model.name
                                    anchors.verticalCenter: parent.verticalCenter
                                    font.bold: true
                                    font.pointSize: 16
                                    anchors.leftMargin: 5
                                    anchors.left: avatar.right
                                    anchors.right: timeField.left
                                }

                                Text {
                                    id: mistakeCountField
                                    text: model.mistakeCount
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.right: timeField.left
                                    anchors.rightMargin: 45
                                    font.pointSize: 16
                                }

                                Text {
                                    id: timeField
                                    text: model.durationStr
                                    anchors.verticalCenter: parent.verticalCenter
                                    //anchors.left: nameField.Right
                                    anchors.right: parent.right
                                    anchors.rightMargin: 5
                                    font.pointSize: 16
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

            add: Transition {
                NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 400 }
                NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 400 }
            }

            displaced: Transition {
                NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
                NumberAnimation { properties: "gradient"; duration: 400; easing.type: Easing.OutCubic }
            }
        }


    }
}
