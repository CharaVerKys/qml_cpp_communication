import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
    modal: true
    closePolicy: Popup.NoAutoClose
    title: "Single Application"
    standardButtons: Dialog.Ok 

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: parent.width/3
    height: parent.height/3

    header: Label {
        text: "Single Application"
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        width: parent.width
        padding: 8
    }

    contentItem: 
        Label {
            //anchors.centerIn: parent
            width: parent.width 
            text: "Нельзя запускать\nбольше одного экземпляра."
            horizontalAlignment: Text.AlignHCenter
        }
    footer: 
    // simple without layout, i not know qml enough :(
    // Rectangle {
    //     height: button.implicitHeight+2
    //     width: parent.width
    //     color: parent.color

    //     Button {
    //         id: button
    //         text: "Centered Button"
    //         anchors.centerIn: parent
    //     }
    // }
    RowLayout {
        // class just list items as first lvl children
        // width: parent.width // ? not required in normal row layout
        height: button.implicitHeight + 8 // ? padding 4 

        // this still looks wrong, because not explicit this.center
        // but its work fine and not rectangle + button
        Item { Layout.fillWidth: true }  // spacer
        Button {
            id: button
            text: "OK"
            onClicked: {console.log("call qt.quit() in single application"); Qt.quit();}
        }
        Item { Layout.fillWidth: true }  // spacer
    }
}