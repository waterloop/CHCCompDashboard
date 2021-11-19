import QtQuick 2.15

PodStateViewerForm {
    signal stateSelected(string newState)
    resting_state_button {
        onPressedChanged: stateSelected("RestingState")
    }
    lv_state_button {
        onPressedChanged: stateSelected("LvReadyState")
    }
    hv_state_button {
        onPressedChanged: stateSelected("HvReadyState")
    }
    autopilot_state_button {
        onPressedChanged: stateSelected("AutopilotState")
    }
    braking_state_button {
        onPressedChanged: stateSelected("BrakingState")
    }
}
