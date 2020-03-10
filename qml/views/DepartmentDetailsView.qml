import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import XApps.XOrmDemoOneToOne 1.0

import "qrc:/qml"

XPane {
    id: departmentDetailsView

    property var departmentGuid: sharedData

    Component.onCompleted: {
        viewModel.readDepartment(departmentGuid)
    }

    DepartmentDetailsViewModel {
        id: viewModel
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
                text: qsTr("Department")
            }

            XCaptionLabel {
                text: qsTr("Name")
                color: departmentDetailsView.Material.secondaryTextColor
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XSubheadingLabel {
                Layout.fillWidth: true
                text: viewModel.currentDepartment !== null
                      ? viewModel.currentDepartment.name
                      : "--"
            }

            XCaptionLabel {
                text: qsTr("Description")
                color: departmentDetailsView.Material.secondaryTextColor
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XSubheadingLabel {
                Layout.fillWidth: true
                text: viewModel.currentDepartment !== null
                      ? viewModel.currentDepartment.description
                      : "--"
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
        Behavior on opacity { NumberAnimation { duration: 100 } }

        BusyIndicator {
            anchors.centerIn: parent
            implicitWidth: 32
            implicitHeight: 32
        }
    }
}
