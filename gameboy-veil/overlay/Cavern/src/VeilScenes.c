#include "VeilScenes.h"

#define VEIL_RACE_DWARF 1U
#define VEIL_CLASS_ROGUE 3U
#define VEIL_BACKGROUND_NOBLE 1U
#define VEIL_COMPANION_VAELITH 0U
#define VEIL_FACTION_BLACKLAKE 0U

static const struct VeilOption m01_rescue_options[] = {
    { 1U, { VEIL_COND_NONE, 0U, 0U }, VEIL_EFFECT_SET_FLAG, 0, 0, VEIL_FLAG_VAELITH_PUBLIC, 2U },
    { 2U, { VEIL_COND_NONE, 0U, 0U }, VEIL_EFFECT_CLEAR_FLAG, 0, 0, VEIL_FLAG_VAELITH_PUBLIC, 3U },
    { 3U, { VEIL_COND_RACE, 0U, VEIL_RACE_DWARF }, VEIL_EFFECT_TRUST, VEIL_COMPANION_VAELITH, 1, 0U, 2U },
    { 4U, { VEIL_COND_CLASS, 0U, VEIL_CLASS_ROGUE }, VEIL_EFFECT_SET_FLAG, 0, 0, VEIL_FLAG_WORKERS_RESCUED, 2U }
};

static const struct VeilOption m01_public_result_options[] = {
    { 5U, { VEIL_COND_NONE, 0U, 0U }, VEIL_EFFECT_TRUST, VEIL_COMPANION_VAELITH, 2, 0U, 4U },
    { 6U, { VEIL_COND_BACKGROUND, 0U, VEIL_BACKGROUND_NOBLE }, VEIL_EFFECT_FACTION, VEIL_FACTION_BLACKLAKE, 1, 0U, 4U }
};

static const struct VeilOption m01_secret_result_options[] = {
    { 7U, { VEIL_COND_NONE, 0U, 0U }, VEIL_EFFECT_TRUST, VEIL_COMPANION_VAELITH, -1, 0U, 4U }
};

static const struct VeilOption m01_complete_options[] = {
    { 8U, { VEIL_COND_NONE, 0U, 0U }, VEIL_EFFECT_NEXT_MISSION, 0, 0, 0U, 0U }
};

static const struct VeilScene m01_scenes[] = {
    { 1U, 1U, 1U, 4U, m01_rescue_options },
    { 2U, 2U, 2U, 2U, m01_public_result_options },
    { 3U, 2U, 3U, 1U, m01_secret_result_options },
    { 4U, 1U, 4U, 1U, m01_complete_options }
};

UINT8 VeilCondition_Passes(const struct VeilCondition* condition) {
    if (condition == 0) return 0U;

    if (condition->mask == VEIL_COND_NONE) return 1U;
    if ((condition->mask & VEIL_COND_RACE) && veil_campaign.race != (UINT8)condition->value) return 0U;
    if ((condition->mask & VEIL_COND_CLASS) && veil_campaign.class_id != (UINT8)condition->value) return 0U;
    if ((condition->mask & VEIL_COND_APPROACH) && veil_campaign.approach != (UINT8)condition->value) return 0U;
    if ((condition->mask & VEIL_COND_BACKGROUND) && veil_campaign.background != (UINT8)condition->value) return 0U;
    if ((condition->mask & VEIL_COND_COMPANION) && veil_campaign.active_companion != (UINT8)condition->value) return 0U;
    if ((condition->mask & VEIL_COND_TRUST) && veil_campaign.companion_trust[condition->key] < (UINT8)condition->value) return 0U;
    if ((condition->mask & VEIL_COND_FLAG) && !VeilCampaign_HasFlag(condition->value)) return 0U;
    if (condition->mask & VEIL_COND_ABILITY) return 0U;

    return 1U;
}

void VeilOption_Apply(const struct VeilOption* option) {
    if (option == 0) return;

    switch (option->effect_type) {
        case VEIL_EFFECT_SET_FLAG:
            VeilCampaign_SetFlag(option->effect_flag);
            break;
        case VEIL_EFFECT_CLEAR_FLAG:
            VeilCampaign_ClearFlag(option->effect_flag);
            break;
        case VEIL_EFFECT_TRUST:
            VeilCampaign_AdjustTrust((UINT8)option->effect_target, option->effect_value);
            break;
        case VEIL_EFFECT_FACTION:
            VeilCampaign_AdjustFaction((UINT8)option->effect_target, option->effect_value);
            break;
        case VEIL_EFFECT_NEXT_MISSION:
            if (veil_campaign.mission < VEIL_MISSION_COUNT) ++veil_campaign.mission;
            veil_campaign.checksum = VeilCampaign_CalculateChecksum();
            break;
        default:
            break;
    }
}

const struct VeilScene* VeilScene_GetM01(UINT8 scene_id) {
    UINT8 i;
    for (i = 0U; i != 4U; ++i) {
        if (m01_scenes[i].scene_id == scene_id) return &m01_scenes[i];
    }
    return 0;
}
