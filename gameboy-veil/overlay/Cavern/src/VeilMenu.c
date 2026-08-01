#include "VeilMenu.h"

struct VeilMenuState veil_menu;

static const char* const veil_menu_labels[VEIL_MENU_ITEM_COUNT] = {
    "MAP",
    "INVENTORY",
    "COMPANION",
    "JOURNAL",
    "CONTROLS",
    "SAVE"
};

void VeilMenu_Init(void) {
    veil_menu.is_open = 0U;
    veil_menu.cursor = 0U;
    veil_menu.page = VEIL_MENU_MAP;
    veil_menu.dirty = 1U;
}

void VeilMenu_Open(void) {
    veil_menu.is_open = 1U;
    veil_menu.cursor = veil_menu.page;
    veil_menu.dirty = 1U;
}

void VeilMenu_Close(void) {
    veil_menu.is_open = 0U;
    veil_menu.dirty = 1U;
}

void VeilMenu_Move(INT8 direction) {
    if (!veil_menu.is_open || direction == 0) return;

    if (direction > 0) {
        veil_menu.cursor++;
        if (veil_menu.cursor >= VEIL_MENU_ITEM_COUNT) veil_menu.cursor = 0U;
    } else {
        if (veil_menu.cursor == 0U) veil_menu.cursor = VEIL_MENU_ITEM_COUNT - 1U;
        else veil_menu.cursor--;
    }
    veil_menu.dirty = 1U;
}

UINT8 VeilMenu_Select(void) {
    if (!veil_menu.is_open) return 0xFFU;
    veil_menu.page = veil_menu.cursor;
    veil_menu.dirty = 1U;
    return veil_menu.page;
}

const char* VeilMenu_Label(UINT8 item) {
    if (item >= VEIL_MENU_ITEM_COUNT) return "";
    return veil_menu_labels[item];
}
