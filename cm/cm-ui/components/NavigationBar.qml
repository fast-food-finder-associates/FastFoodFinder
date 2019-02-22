import QtQuick 2.9
import assets 1.0

Item {
    property bool isCollapsed: true

    anchors {
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }
    width: isCollapsed ? Style.widthNavigationBarCollapsed : Style.heightNavigationBarExpanded

    Rectangle {
        anchors.fill: parent
        color: Style.colourNavigationBarBackground

        Column {
            width: parent.width

            NavigationButton {
                iconCharacter: "\uf0c9"
                description: ""
                hoverColour: "#993333"
                onNavigationButtonClicked: isCollapsed = !isCollapsed
            }
            NavigationButton {
                iconCharacter: "\uf2bd"
                description: "Dashboard"
                hoverColour: "#dc8a00"
                onNavigationButtonClicked: masterController.ui_navigationController.goDashboardView();
            }
            NavigationButton {
                iconCharacter: "\uf0f5"
                description: "Plan A Trip"
                hoverColour: "#dccd00"
                onNavigationButtonClicked: masterController.ui_navigationController.goCreateClientView();
            }
            NavigationButton {
                iconCharacter: "\uf002"
                description: "Look Up\nRestaurants"
                hoverColour: "#8aef63"
                onNavigationButtonClicked: masterController.ui_navigationController.goFindClientView();
            }
            NavigationButton {
                iconCharacter: "\uf1c0"
                description: "Inventory\nManagment"
                hoverColour: "#ffa500"
                onNavigationButtonClicked: masterController.ui_navigationController.goCreateClientView();

            }
        }
    }
}
