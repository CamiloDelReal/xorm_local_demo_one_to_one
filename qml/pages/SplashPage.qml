import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

import "qrc:/qml"

XPage {
    id: splashPage
    padding: 0

    XSplashPane {
        anchors.fill: parent
        Material.background: Material.color(ApplicationSettingsObj.primaryColor, Material.Shade500)
        logo.source: "qrc:/img/app/logo_foreground.svg"
    }
}


