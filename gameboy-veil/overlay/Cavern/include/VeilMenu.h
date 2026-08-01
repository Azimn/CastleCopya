#ifndef VEIL_MENU_H
#define VEIL_MENU_H

#include <asm/gbz80/types.h>

#define VEIL_MENU_ITEM_COUNT 6U

#define VEIL_MENU_MAP       0U
#define VEIL_MENU_INVENTORY 1U
#define VEIL_MENU_COMPANION 2U
#define VEIL_MENU_JOURNAL   3U
#define VEIL_MENU_CONTROLS  4U
#define VEIL_MENU_SAVE      5U

struct VeilMenuState {
    UINT8 is_open;
    UINT8 cursor;
    UINT8 page;
    UINT8 dirty;
};

extern struct VeilMenuState veil_menu;

void VeilMenu_Init(void);
void VeilMenu_Open(void);
void VeilMenu_Close(void);
void VeilMenu_Move(INT8 direction);
UINT8 VeilMenu_Select(void);
const char* VeilMenu_Label(UINT8 item);

#endif
