import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// * i not want to care about resizing while work with one device and fixed max window size
// * so everything is in pixels, its fine

// also language server not work on this version of qt (minimum 6.7 for auto ini)
// so write everything by hands

ApplicationWindow
{


    visible: true

    // our device window is 1024, 768
    //
    width: 780

    height: 520

    title: qsTr("*your*Launcher")

    SingleApplicationDialog{
        id: singleApplication_dialog
    }

    StartApplicationButton{}

    Connections {
        target: frontendConnectionSide
        function onReceiveShowSingleApplicationDialog(){ singleApplication_dialog.open()}
    }
}
