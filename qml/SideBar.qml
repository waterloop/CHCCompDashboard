import QtQuick 2.15
import "."
SideBarForm {
    id: root
    signal connectionButtonPressed()
    signal editDashboardPressed()
    signal triggerSystemFault()
    property alias connect_button_text: root.connect_button_text

    connect_button_logic {
        onTapped: connectionButtonPressed()
    }

    change_dashboard_button_logic {
        onTapped: editDashboardPressed()
    }

    e_break_button_logic {
        onTapped: triggerSystemFault()
    }

    background_color: waterloo_dark
}
