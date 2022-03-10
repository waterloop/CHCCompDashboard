import QtQuick 2.15

PodStateViewerForm {
    signal stateSelected(string newState)
    resting_state_button {
        onTapped: stateSelected("RestingState")
    }
    lv_state_button {
        onTapped: stateSelected("LvReadyState")
    }
    hv_state_button {
        onTapped: stateSelected("HvReadyState")
    }
    autopilot_state_button {
        onTapped: stateSelected("AutopilotState")
    }
    braking_state_button {
        onTapped: stateSelected("BrakingState")
    }
}
