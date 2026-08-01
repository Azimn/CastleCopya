#ifndef VEIL_SCENES_H
#define VEIL_SCENES_H

#include <asm/gbz80/types.h>
#include "VeilCampaign.h"

#define VEIL_COND_NONE       0x00U
#define VEIL_COND_RACE       0x01U
#define VEIL_COND_CLASS      0x02U
#define VEIL_COND_APPROACH   0x04U
#define VEIL_COND_BACKGROUND 0x08U
#define VEIL_COND_COMPANION  0x10U
#define VEIL_COND_TRUST      0x20U
#define VEIL_COND_FLAG       0x40U
#define VEIL_COND_ABILITY    0x80U

#define VEIL_EFFECT_NONE          0U
#define VEIL_EFFECT_SET_FLAG      1U
#define VEIL_EFFECT_CLEAR_FLAG    2U
#define VEIL_EFFECT_TRUST         3U
#define VEIL_EFFECT_FACTION       4U
#define VEIL_EFFECT_NEXT_MISSION  5U

struct VeilCondition {
    UINT8 mask;
    UINT8 key;
    UINT16 value;
};

struct VeilOption {
    UINT8 text_id;
    struct VeilCondition condition;
    UINT8 effect_type;
    INT8 effect_target;
    INT8 effect_value;
    UINT16 effect_flag;
    UINT8 next_scene;
};

struct VeilScene {
    UINT8 scene_id;
    UINT8 speaker_id;
    UINT8 line_id;
    UINT8 option_count;
    const struct VeilOption* options;
};

UINT8 VeilCondition_Passes(const struct VeilCondition* condition);
void VeilOption_Apply(const struct VeilOption* option);
const struct VeilScene* VeilScene_GetM01(UINT8 scene_id);

#endif
