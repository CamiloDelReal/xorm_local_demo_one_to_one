import QtQuick 2.14
import QtQuick.Controls 2.14

import "qrc:/qml"

XPane {
    id: departmentsView
    padding: 0

    property alias navController: departmentNavController

    function back() {
        if(departmentNavController.depth > 1) {
            departmentNavController.goBack()
            return true
        }
        return false
    }

    XViewNavController {
        id: departmentNavController
        anchors.fill: parent

        initialView: DepartmentListingView {}

        property int departmentEditionViewIndex: 0
        property int departmentDetailsViewIndex: 1
        viewNavigationModel: [
            { view: "views/DepartmentEditionView.qml", stacked: true },
            { view: "views/DepartmentDetailsView.qml", stacked: true }
        ]
    }
}
