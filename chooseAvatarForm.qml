import QtQuick 2.0

Item {
    width: 370 // 5*2(Border) + 4*10(Spacing) + 4*80(AvatarImage)
    height: 370
    //color: "white"
    signal avatarChosen(int avatarId)

    Grid {
        x: 5
        y: 5
        rows: 4
        columns: 4
        spacing: 10

        Repeater {
            model: 16
            Image {
                id: avatar
                width: 80
                height: 80
                source: "avatars/" + (index+1) + ".png"

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        avatarChosen(index+1)
                    }
                }
            }
        }
    }
}
