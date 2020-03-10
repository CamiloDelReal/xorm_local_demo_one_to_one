import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "qrc:/qml"

import XApps.XOrmDemoOneToOne 1.0

XPane {
    id: departmentEditionView

    property var listingListener: sharedData

    DepartmentEditionViewModel {
        id: viewModel

        onDepartmentCreated: {
            departmentNavController.goBack()
            listingListener.update()
        }
    }

    XScrollView {
        id: scrollview
        anchors.fill: parent
        ScrollIndicator.vertical: ScrollIndicator {}

        ColumnLayout {
            id: layout
            width: scrollview.contentView.availableWidth
            spacing: 12

            XHeadlineLabel {
                Layout.fillWidth: true
                text: qsTr("New department")
            }

            XFormTextField {
                id: txfName
                placeholderText: qsTr("Name")
                font.pixelSize: 18
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XFormTextArea {
                id: txfDescription
                placeholderText: qsTr("Description")
                wrapMode: TextArea.Wrap
                font.pixelSize: 14
                Layout.fillWidth: true
            }
        }
    }

    XPane {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 16
        radius: height / 2
        Material.elevation: 3
        padding: 2
        visible: opacity > 0
        opacity: viewModel.isWorking ? 1 : 0
        Behavior on opacity { NumberAnimation {} }

        BusyIndicator {
            anchors.centerIn: parent
            implicitWidth: 32
            implicitHeight: 32
        }
    }

    XToast {
        id: toast
    }

    XRoundButton {
        id: btnNew
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        icon.source: "qrc:/img/icons/check.svg"
        onClicked: {
            if(txfName.text.length > 0) {
                viewModel.createDepartment(txfName.text, txfDescription.text)
            } else {
                toast.showText(qsTr("There are empty fields"))
            }
        }
    }
}
