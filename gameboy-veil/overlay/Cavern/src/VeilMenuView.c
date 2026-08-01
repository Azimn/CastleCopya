#include "VeilMenuView.h"
#include "VeilMenu.h"
#include "VeilCampaign.h"
#include <gb/gb.h>

#define VEIL_MENU_W 20U
#define VEIL_MENU_H 18U

static const unsigned char blank_tile = 0U;
static UINT8 visible = 0U;

static void clear_window(void) {
    UINT8 y;
    UINT8 x;
    for (y = 0U; y != VEIL_MENU_H; ++y) {
        for (x = 0U; x != VEIL_MENU_W; ++x) {
            set_win_tiles(x, y, 1U, 1U, &blank_tile);
        }
    }
}

static void draw_text(UINT8 x, UINT8 y, const char* text) {
    while (*text && x < VEIL_MENU_W) {
        unsigned char tile = (unsigned char)(*text);
        set_win_tiles(x, y, 1U, 1U, &tile);
        ++text;
        ++x;
    }
}

static void draw_menu_list(void) {
    UINT8 i;
    for (i = 0U; i != VEIL_MENU_ITEM_COUNT; ++i) {
        draw_text(2U, (UINT8)(3U + i * 2U), VeilMenu_Label(i));
        if (i == veil_menu.cursor) draw_text(0U, (UINT8)(3U + i * 2U), ">");
    }
}

static void draw_page(void) {
    char buffer[3];
    clear_window();
    draw_text(1U, 0U, "VEIL OF NEVERWINTER");

    switch (veil_menu.page) {
        case VEIL_MENU_MAP:
            draw_text(1U, 3U, "MAP");
            if (VeilCampaign_HasFlag(VEIL_FLAG_M01_COMPLETE)) {
                draw_text(1U, 5U, "BLACKLAKE CLEARED");
                draw_text(1U, 7U, "TEMPLE QUARTER OPEN");
            } else {
                draw_text(1U, 5U, "BLACKLAKE DISTRICT");
                if (VeilCampaign_HasFlag(VEIL_FLAG_BLACKLAKE_CELL))
                    draw_text(1U, 7U, "CULT CELL MARKED");
                else
                    draw_text(1U, 7U, "SEARCH EAST BLOCK");
            }
            break;
        case VEIL_MENU_INVENTORY:
            draw_text(1U, 3U, "INVENTORY");
            draw_text(1U, 5U, "WEAPON: IRON BLADE");
            draw_text(1U, 7U, "RELICS: NONE");
            break;
        case VEIL_MENU_COMPANION:
            draw_text(1U, 3U, "COMPANION");
            draw_text(1U, 5U, "VAELITH");
            draw_text(1U, 7U, "TRUST:");
            buffer[0] = (char)('0' + (veil_campaign.companion_trust[0] / 10U));
            buffer[1] = (char)('0' + (veil_campaign.companion_trust[0] % 10U));
            buffer[2] = '\0';
            draw_text(8U, 7U, buffer);
            if (VeilCampaign_HasFlag(VEIL_FLAG_VAELITH_RESOLVED)) {
                draw_text(1U, 9U, VeilCampaign_HasFlag(VEIL_FLAG_VAELITH_PUBLIC) ? "STATUS: PUBLIC" : "STATUS: HIDDEN");
            } else {
                draw_text(1U, 9U, "STATUS: UNDECIDED");
            }
            break;
        case VEIL_MENU_JOURNAL:
            draw_text(1U, 3U, "JOURNAL");
            if (VeilCampaign_HasFlag(VEIL_FLAG_M01_COMPLETE)) {
                draw_text(1U, 5U, "M02 THE WARNING");
                draw_text(1U, 7U, "GO TO TEMPLE QUARTER");
                draw_text(1U, 9U, "M01 COMPLETE");
            } else {
                draw_text(1U, 5U, "ASHES IN BLACKLAKE");
                if (!VeilCampaign_HasFlag(VEIL_FLAG_BLACKLAKE_CELL)) {
                    draw_text(1U, 7U, "FIND THE CULT CELL");
                } else if (!VeilCampaign_HasFlag(VEIL_FLAG_VAELITH_RESOLVED)) {
                    draw_text(1U, 7U, "SPEAK WITH VAELITH");
                } else {
                    draw_text(1U, 7U, "RETURN TO WEST GATE");
                }
            }
            break;
        case VEIL_MENU_CONTROLS:
            draw_text(1U, 3U, "CONTROLS");
            draw_text(1U, 5U, "A JUMP / CONFIRM");
            draw_text(1U, 7U, "B ATTACK / BACK");
            draw_text(1U, 9U, "START MENU");
            break;
        case VEIL_MENU_SAVE:
            draw_text(1U, 3U, "SAVE");
            draw_text(1U, 5U, "USE A SAVE SHRINE");
            break;
        default:
            draw_menu_list();
            break;
    }

    draw_text(1U, 16U, "B BACK");
}

void VeilMenuView_Init(void) {
    visible = 0U;
}

void VeilMenuView_Show(void) {
    visible = 1U;
    WX_REG = 7U;
    WY_REG = 0U;
    SHOW_WIN;
    VeilMenuView_Render();
}

void VeilMenuView_Hide(void) {
    visible = 0U;
    WY_REG = (144U - (1U << 3));
}

void VeilMenuView_Render(void) {
    if (!visible) return;
    if (veil_menu.page < VEIL_MENU_ITEM_COUNT) {
        draw_page();
    } else {
        clear_window();
        draw_text(1U, 0U, "VEIL OF NEVERWINTER");
        draw_menu_list();
        draw_text(1U, 16U, "A SELECT  B CLOSE");
    }
    veil_menu.dirty = 0U;
}
