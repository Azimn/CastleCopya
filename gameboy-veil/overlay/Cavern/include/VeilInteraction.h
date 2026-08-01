#ifndef VEIL_INTERACTION_H
#define VEIL_INTERACTION_H

#include <asm/gbz80/types.h>

#define VEIL_INTERACTION_NONE 0U
#define VEIL_INTERACTION_VAELITH 1U
#define VEIL_INTERACTION_OBJECTIVE 2U

struct VeilInteractionState {
    UINT8 nearby;
    UINT8 dialogue_open;
    UINT8 dialogue_node;
    UINT8 choice;
    UINT8 message_timer;
};

extern struct VeilInteractionState veil_interaction;

void VeilInteraction_Init(void);
UINT8 VeilInteraction_Update(void);
void VeilInteraction_Render(void);
void VeilInteraction_Close(void);

#endif
