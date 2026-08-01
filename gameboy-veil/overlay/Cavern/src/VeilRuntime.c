#include "VeilRuntime.h"
#include "VeilMenu.h"
#include "VeilMenuView.h"
#include "VeilCampaign.h"
#include "VeilInteraction.h"
#include "Keys.h"

void VeilRuntime_Init(void) {
    VeilMenu_Init();
    VeilMenuView_Init();
    VeilInteraction_Init();
    if (!VeilCampaign_IsValid()) {
        VeilCampaign_NewGame();
    }
}

UINT8 VeilRuntime_Update(void) {
    if (!veil_menu.is_open && VeilInteraction_Update()) {
        return 1U;
    }

    if (KEY_TICKED(J_START)) {
        if (veil_menu.is_open) {
            VeilMenu_Close();
            VeilMenuView_Hide();
        } else {
            VeilMenu_Open();
            VeilMenuView_Show();
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
        VeilMenuView_Hide();
        return 0U;
    }

    if (veil_menu.dirty) {
        VeilMenuView_Render();
    }

    return veil_menu.is_open;
}
