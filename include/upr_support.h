#ifndef GUARD_UPR_SUPPORT_H
#define GUARD_UPR_SUPPORT_H

// TODO: make sure the birch battle tutorial OW MON is also changed
#include "constants/species.h"
#include "constants/items.h"

#define BIRCH_INTRO_MON_INDEX 0
#define STARTER_ITEM_INDEX 1
#define BATTLE_TUTORIAL_OPPONENT_INDEX 2
#define WALLY_CATCH_TUTORIAL_MON_INDEX 3
#define WALLY_CATCH_TUTORIAL_OPPONENT_INDEX 4
#define PC_START_ITEM_INDEX 5

#define MAX_CABLE_CAR_MON SPECIES_ENAMORUS

extern const u16 gUprStaticVars[];
extern const u16 gUprBerryTrees[];

void handleRandomizedBerryTreeSetup();
bool8 handleRandomizedBerryTreeDataText(u8 treeId, u8 count, u8 berry);
bool8 handleRandomizedBerryTreeItemCountText(u8 treeId, u8 count, u8 berry);
bool8 handleRandomizedBerryTreeGive(u8 treeId, u8 count, u8 berry);
u8 handleRandomizedBerryTreeGraphics(u8 berryId, u8 treeId);

#endif // GUARD_UPR_SUPPORT_H
