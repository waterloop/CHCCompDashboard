import QtQuick 2.15
import "."
SideBarForm {
    id: root
    signal connectionButtonPressed()
    signal editDashboardPressed()
    property alias connect_button_text: root.connect_button_text

    connect_button_logic {
        onTapped: connectionButtonPressed()
    }

    change_dashboard_button_logic {
        onTapped: editDashboardPressed()
    }

    background_color: waterloo_dark
}
