import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "qrc:/qml"

import XApps.XOrmDemoOneToOne 1.0

XPane {
    id: memberEditionView

    property var listingListener: sharedData

    MemberEditionViewModel {
        id: viewModel

        onMemberCreated: {
            memberNavController.goBack()
            listingListener.update()
        }
    }

    DepartmentListingViewModel {
        id: departmentViewModel
    }

    Component.onCompleted: {
        departmentViewModel.readDepartments()
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
                text: qsTr("New member")
            }

            XFormTextField {
                id: txfName
                placeholderText: qsTr("Full Name")
                font.pixelSize: 18
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XFormTextField {
                id: txfJob
                placeholderText: qsTr("Job")
                wrapMode: TextField.Wrap
                font.pixelSize: 14
                Layout.fillWidth: true
            }

            XCaptionLabel {
                text: qsTr("Department")
                color: memberEditionView.Material.secondaryTextColor
                Layout.fillWidth: true
                Layout.topMargin: 18
            }

            ComboBox {
                id: cbxDepartments
                Layout.fillWidth: true
                displayText: (currentIndex == -1 ? qsTr("Select a Department") : currentText)
                visible: departmentViewModel.departmentModel.count > 0
                model: departmentViewModel.departmentModel
                textRole: "name"
            }

            XBodyLabel1 {
                text: qsTr("No department defined, please create a new one")
                horizontalAlignment: Label.AlignHCenter
                color: Material.color(Material.Red)
                Layout.fillWidth: true
                visible: departmentViewModel.departmentModel.count === 0
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
            if(txfName.text.length > 0 && txfJob.text.length > 0 && cbxDepartments.currentIndex != -1) {
                viewModel.createMember(txfName.text, txfJob.text,
                                       departmentViewModel.departmentModel.departmentGuid(cbxDepartments.currentIndex))
            } else {
                toast.showText(qsTr("There are empty fields"))
            }
        }
    }
}
