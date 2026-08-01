#include "VeilInteraction.h"
#include "VeilCampaign.h"
#include "Keys.h"
#include "Scroll.h"
#include <gb/gb.h>

#define VEIL_WINDOW_W 20U
#define VEIL_WINDOW_H 18U
#define VEIL_FLAG_BLACKLAKE_CELL 0x1000U

extern UINT16 roomNumber;

struct VeilInteractionState veil_interaction;

static const unsigned char blank_tile = 0U;

static void draw_text(UINT8 x, UINT8 y, const char* text) {
    while (*text && x < VEIL_WINDOW_W) {
        unsigned char tile = (unsigned char)(*text);
        set_win_tiles(x, y, 1U, 1U, &tile);
        ++text;
        ++x;
    }
}

static void clear_rows(UINT8 first, UINT8 count) {
    UINT8 y;
    UINT8 x;
    for (y = first; y != (UINT8)(first + count); ++y) {
        for (x = 0U; x != VEIL_WINDOW_W; ++x) {
            set_win_tiles(x, y, 1U, 1U, &blank_tile);
        }
    }
}

static UINT8 player_in_zone(UINT16 min_x, UINT16 max_x, UINT16 min_y, UINT16 max_y) {
    if (!scroll_target) return 0U;
    return scroll_target->x >= min_x && scroll_target->x <= max_x &&
           scroll_target->y >= min_y && scroll_target->y <= max_y;
}

static void show_prompt(void) {
    WX_REG = 7U;
    WY_REG = 128U;
    SHOW_WIN;
    clear_rows(0U, 2U);
    draw_text(12U, 0U, "A TALK");
}

static void hide_prompt(void) {
    clear_rows(0U, 2U);
    WY_REG = 136U;
}

static void open_dialogue(void) {
    veil_interaction.dialogue_open = 1U;
    veil_interaction.dialogue_node = 0U;
    veil_interaction.choice = 0U;
    WX_REG = 7U;
    WY_REG = 80U;
    SHOW_WIN;
    VeilInteraction_Render();
}

static void apply_choice(void) {
    if (veil_interaction.choice == 0U) {
        VeilCampaign_SetFlag(VEIL_FLAG_VAELITH_PUBLIC);
        VeilCampaign_AdjustTrust(0U, 2);
        VeilCampaign_AdjustFaction(0U, 1);
    } else {
        VeilCampaign_ClearFlag(VEIL_FLAG_VAELITH_PUBLIC);
        VeilCampaign_AdjustTrust(0U, 1);
        VeilCampaign_AdjustFaction(3U, 1);
    }
    veil_campaign.checksum = VeilCampaign_CalculateChecksum();
    veil_interaction.dialogue_node = 2U;
    VeilInteraction_Render();
}

void VeilInteraction_Init(void) {
    veil_interaction.nearby = VEIL_INTERACTION_NONE;
    veil_interaction.dialogue_open = 0U;
    veil_interaction.dialogue_node = 0U;
    veil_interaction.choice = 0U;
    veil_interaction.message_timer = 0U;
}

void VeilInteraction_Close(void) {
    veil_interaction.dialogue_open = 0U;
    veil_interaction.dialogue_node = 0U;
    veil_interaction.choice = 0U;
    clear_rows(0U, 8U);
    WY_REG = 136U;
}

UINT8 VeilInteraction_Update(void) {
    UINT8 near_vaelith;

    if (veil_interaction.message_timer) {
        --veil_interaction.message_timer;
        if (!veil_interaction.message_timer) {
            clear_rows(0U, 4U);
            WY_REG = 136U;
        }
        return 1U;
    }

    if (veil_interaction.dialogue_open) {
        if (veil_interaction.dialogue_node == 0U && KEY_TICKED(J_A)) {
            veil_interaction.dialogue_node = 1U;
            VeilInteraction_Render();
        } else if (veil_interaction.dialogue_node == 1U) {
            if (KEY_TICKED(J_UP) || KEY_TICKED(J_DOWN)) {
                veil_interaction.choice ^= 1U;
                VeilInteraction_Render();
            }
            if (KEY_TICKED(J_A)) {
                apply_choice();
            }
        } else if (veil_interaction.dialogue_node == 2U && (KEY_TICKED(J_A) || KEY_TICKED(J_B))) {
            VeilInteraction_Close();
        } else if (KEY_TICKED(J_B)) {
            VeilInteraction_Close();
        }
        return 1U;
    }

    if (roomNumber == 1U && !VeilCampaign_HasFlag(VEIL_FLAG_BLACKLAKE_CELL) &&
        player_in_zone(168U, 224U, 144U, 352U)) {
        VeilCampaign_SetFlag(VEIL_FLAG_BLACKLAKE_CELL);
        veil_campaign.checksum = VeilCampaign_CalculateChecksum();
        veil_interaction.message_timer = 90U;
        WX_REG = 7U;
        WY_REG = 112U;
        SHOW_WIN;
        clear_rows(0U, 4U);
        draw_text(1U, 0U, "OBJECTIVE COMPLETE");
        draw_text(1U, 1U, "CULT CELL FOUND");
        draw_text(1U, 2U, "FIND VAELITH");
        return 1U;
    }

    near_vaelith = (roomNumber == 1U && player_in_zone(48U, 120U, 176U, 352U));
    if (near_vaelith) {
        if (veil_interaction.nearby != VEIL_INTERACTION_VAELITH) {
            veil_interaction.nearby = VEIL_INTERACTION_VAELITH;
            show_prompt();
        }
        if (KEY_TICKED(J_A)) {
            hide_prompt();
            open_dialogue();
            return 1U;
        }
    } else if (veil_interaction.nearby != VEIL_INTERACTION_NONE) {
        veil_interaction.nearby = VEIL_INTERACTION_NONE;
        hide_prompt();
    }

    return 0U;
}

void VeilInteraction_Render(void) {
    clear_rows(0U, 8U);
    WX_REG = 7U;
    WY_REG = 80U;
    SHOW_WIN;

    if (veil_interaction.dialogue_node == 0U) {
        draw_text(1U, 0U, "VAELITH");
        draw_text(1U, 2U, "THE CULT KNOWS ME.");
        draw_text(1U, 3U, "IF I WALK OPENLY,");
        draw_text(1U, 4U, "BLACKLAKE WILL SEE.");
        draw_text(1U, 6U, "A CONTINUE");
    } else if (veil_interaction.dialogue_node == 1U) {
        draw_text(1U, 0U, "HOW DO YOU PROCEED?");
        draw_text(3U, 2U, "RECRUIT HER OPENLY");
        draw_text(3U, 4U, "KEEP HER HIDDEN");
        draw_text(1U, veil_interaction.choice ? 4U : 2U, ">");
        draw_text(1U, 6U, "A CHOOSE  B LEAVE");
    } else {
        draw_text(1U, 0U, "VAELITH");
        if (VeilCampaign_HasFlag(VEIL_FLAG_VAELITH_PUBLIC)) {
            draw_text(1U, 2U, "THEN LET THEM SEE.");
            draw_text(1U, 3U, "I WILL NOT HIDE.");
        } else {
            draw_text(1U, 2U, "QUIETLY, THEN.");
            draw_text(1U, 3U, "I OWE YOU THAT.");
        }
        draw_text(1U, 6U, "A CLOSE");
    }
}
