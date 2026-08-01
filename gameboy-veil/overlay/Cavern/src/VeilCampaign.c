#include "VeilCampaign.h"

struct VeilCampaignState veil_campaign;

static UINT8 clamp_u4(INT16 value) {
    if (value < 0) return 0U;
    if (value > 15) return 15U;
    return (UINT8)value;
}

static INT8 clamp_rep(INT16 value) {
    if (value < -8) return -8;
    if (value > 7) return 7;
    return (INT8)value;
}

void VeilCampaign_NewGame(void) {
    UINT8 i;

    veil_campaign.version = VEIL_SAVE_VERSION;
    veil_campaign.mission = 1U;
    veil_campaign.race = 0U;
    veil_campaign.class_id = 0U;
    veil_campaign.approach = VEIL_APPROACH_MARTIAL;
    veil_campaign.background = 0U;
    veil_campaign.active_companion = 0U;

    for (i = 0U; i != VEIL_COMPANION_COUNT; ++i) {
        veil_campaign.companion_trust[i] = 8U;
    }

    for (i = 0U; i != VEIL_FACTION_COUNT; ++i) {
        veil_campaign.faction_reputation[i] = 0;
    }

    veil_campaign.story_flags = 0U;
    veil_campaign.sidequest_flags = 0U;
    veil_campaign.ending_route = 0U;
    veil_campaign.checksum = VeilCampaign_CalculateChecksum();
}

void VeilCampaign_SetFlag(UINT16 flag) {
    veil_campaign.story_flags |= flag;
    veil_campaign.checksum = VeilCampaign_CalculateChecksum();
}

void VeilCampaign_ClearFlag(UINT16 flag) {
    veil_campaign.story_flags &= (UINT16)(~flag);
    veil_campaign.checksum = VeilCampaign_CalculateChecksum();
}

UINT8 VeilCampaign_HasFlag(UINT16 flag) {
    return (veil_campaign.story_flags & flag) != 0U;
}

void VeilCampaign_AdjustTrust(UINT8 companion, INT8 amount) {
    INT16 value;

    if (companion >= VEIL_COMPANION_COUNT) return;
    value = (INT16)veil_campaign.companion_trust[companion] + (INT16)amount;
    veil_campaign.companion_trust[companion] = clamp_u4(value);
    veil_campaign.checksum = VeilCampaign_CalculateChecksum();
}

void VeilCampaign_AdjustFaction(UINT8 faction, INT8 amount) {
    INT16 value;

    if (faction >= VEIL_FACTION_COUNT) return;
    value = (INT16)veil_campaign.faction_reputation[faction] + (INT16)amount;
    veil_campaign.faction_reputation[faction] = clamp_rep(value);
    veil_campaign.checksum = VeilCampaign_CalculateChecksum();
}

UINT8 VeilCampaign_CalculateChecksum(void) {
    UINT8 i;
    UINT8 checksum = 0x5AU;

    checksum ^= veil_campaign.version;
    checksum ^= veil_campaign.mission;
    checksum ^= veil_campaign.race;
    checksum ^= veil_campaign.class_id;
    checksum ^= veil_campaign.approach;
    checksum ^= veil_campaign.background;
    checksum ^= veil_campaign.active_companion;

    for (i = 0U; i != VEIL_COMPANION_COUNT; ++i) {
        checksum = (UINT8)((checksum << 1) | (checksum >> 7));
        checksum ^= veil_campaign.companion_trust[i];
    }

    for (i = 0U; i != VEIL_FACTION_COUNT; ++i) {
        checksum = (UINT8)((checksum << 1) | (checksum >> 7));
        checksum ^= (UINT8)veil_campaign.faction_reputation[i];
    }

    checksum ^= (UINT8)(veil_campaign.story_flags & 0x00FFU);
    checksum ^= (UINT8)(veil_campaign.story_flags >> 8);
    checksum ^= (UINT8)(veil_campaign.sidequest_flags & 0x00FFU);
    checksum ^= (UINT8)(veil_campaign.sidequest_flags >> 8);
    checksum ^= veil_campaign.ending_route;

    return checksum;
}

UINT8 VeilCampaign_IsValid(void) {
    if (veil_campaign.version != VEIL_SAVE_VERSION) return 0U;
    if (veil_campaign.mission == 0U || veil_campaign.mission > VEIL_MISSION_COUNT) return 0U;
    if (veil_campaign.approach > VEIL_APPROACH_ARCANE) return 0U;
    if (veil_campaign.active_companion >= VEIL_COMPANION_COUNT) return 0U;
    return veil_campaign.checksum == VeilCampaign_CalculateChecksum();
}
