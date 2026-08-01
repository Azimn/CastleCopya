#include "VeilRuntime.h"
#include "VeilMenu.h"
#include "VeilCampaign.h"
#include "Keys.h"

void VeilRuntime_Init(void) {
    VeilMenu_Init();
    if (!VeilCampaign_IsValid()) {
        VeilCampaign_NewGame();
    }
}

UINT8 VeilRuntime_Update(void) {
    if (KEY_TICKED(J_START)) {
        if (veil_menu.is_open) {
            VeilMenu_Close();
        } else {
            VeilMenu_Open();
        }
        return veil_menu.is_open;
    }

    if (!veil_menu.is_open) {
        return 0U;
    }

    if (KEY_TICKED(J_UP)) {
        VeilMenu_Move(-1);
    }
    if (KEY_TICKED(J_DOWN)) {
        VeilMenu_Move(1);
    }
    if (KEY_TICKED(J_A)) {
        VeilMenu_Select();
    }
    if (KEY_TICKED(J_B)) {
        VeilMenu_Close();
    }

    return veil_menu.is_open;
}
