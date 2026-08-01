#ifndef VEIL_CAMPAIGN_H
#define VEIL_CAMPAIGN_H

#include <asm/gbz80/types.h>

#define VEIL_SAVE_VERSION 1U
#define VEIL_MISSION_COUNT 12U
#define VEIL_COMPANION_COUNT 9U
#define VEIL_FACTION_COUNT 8U

#define VEIL_FLAG_VAELITH_PUBLIC      0x0001U
#define VEIL_FLAG_WORKERS_RESCUED     0x0002U
#define VEIL_FLAG_TEMPLE_EXPOSED      0x0004U
#define VEIL_FLAG_SURVEYOR_PROTECTED  0x0008U
#define VEIL_FLAG_LEDGER_DUPLICATE    0x0010U
#define VEIL_FLAG_DOCKWORKERS_SAVED   0x0020U
#define VEIL_FLAG_ILYRA_PROTECTED     0x0040U
#define VEIL_FLAG_WARDS_AWAKENED      0x0080U
#define VEIL_FLAG_BELL_PRESERVED      0x0100U
#define VEIL_FLAG_DUEL_EXPOSED        0x0200U
#define VEIL_FLAG_DEAD_ENTRUSTED      0x0400U
#define VEIL_FLAG_SARETH_DISCOVERED   0x0800U

#define VEIL_APPROACH_MARTIAL 0U
#define VEIL_APPROACH_SACRED  1U
#define VEIL_APPROACH_SKILLED 2U
#define VEIL_APPROACH_PRIMAL  3U
#define VEIL_APPROACH_ARCANE  4U

struct VeilCampaignState {
    UINT8 version;
    UINT8 mission;
    UINT8 race;
    UINT8 class_id;
    UINT8 approach;
    UINT8 background;
    UINT8 active_companion;
    UINT8 companion_trust[VEIL_COMPANION_COUNT];
    INT8 faction_reputation[VEIL_FACTION_COUNT];
    UINT16 story_flags;
    UINT16 sidequest_flags;
    UINT8 ending_route;
    UINT8 checksum;
};

extern struct VeilCampaignState veil_campaign;

void VeilCampaign_NewGame(void);
void VeilCampaign_SetFlag(UINT16 flag);
void VeilCampaign_ClearFlag(UINT16 flag);
UINT8 VeilCampaign_HasFlag(UINT16 flag);
void VeilCampaign_AdjustTrust(UINT8 companion, INT8 amount);
void VeilCampaign_AdjustFaction(UINT8 faction, INT8 amount);
UINT8 VeilCampaign_CalculateChecksum(void);
UINT8 VeilCampaign_IsValid(void);

#endif
