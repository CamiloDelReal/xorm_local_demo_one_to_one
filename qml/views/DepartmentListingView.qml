import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.impl 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "qrc:/qml"
import "qrc:/qml/delegates"
import "qrc:/qml/listeners"

import XApps.XOrmDemoOneToOne 1.0

XPane {
    id: departmentListingView
    title: qsTr("Department List")

    Component.onCompleted: {
        viewModel.readDepartments()
    }

    DepartmentListingViewModel {
        id: viewModel
    }

    DepartmentListingListener {
        id: listener

        function update() {
            viewModel.readDepartments()
        }
    }

    ListView {
        id: departmentListView
        anchors.fill: parent
        ScrollIndicator.vertical: ScrollIndicator {}
        model: viewModel.departmentModel
        delegate: DepartmentDelegate {}
    }

    Rectangle {
        anchors.fill: parent
        color: departmentListView.Material.background
        visible: opacity > 0
        opacity: viewModel.departmentModel.count === 0 ? 1 : 0
        Behavior on opacity { NumberAnimation { duration: 150 } }

        ColumnLayout {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right

            IconLabel {
                Layout.alignment: Qt.AlignHCenter
                icon.source: "qrc:/img/icons/home-alert.svg"
                icon.color: departmentListView.Material.secondaryTextColor
                icon.width: 50
                icon.height: 50
            }

            XCaptionLabel {
                Layout.alignment: Qt.AlignHCenter
                Layout.leftMargin: 50
                Layout.rightMargin: 50
                Layout.fillWidth: true
                text: qsTr("No departments inserted, please touch the plus button to insert a new one")
                horizontalAlignment: Label.AlignHCenter
                wrapMode: Label.WordWrap
                color: departmentListView.Material.secondaryTextColor
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

    XRoundButton {
        id: btnNew
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        icon.source: "qrc:/img/icons/plus.svg"
        onClicked: departmentNavController.gotoView(departmentNavController.departmentEditionViewIndex, listener)
    }
}
