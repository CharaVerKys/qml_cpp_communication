import QtQuick
import QtQuick.Controls

Button{
    width: 390
    height: 125
    x: 200
    y: 50
    text: "Start Application"
    onClicked: frontendConnectionSide.sendStartApplication()
}