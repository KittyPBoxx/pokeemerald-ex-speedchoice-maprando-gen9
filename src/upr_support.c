#include "global.h"
#include "item.h"
#include "event_data.h"
#include "string_util.h"
#include "party_menu.h"
#include "constants/party_menu.h"
#include "upr_support.h"
#include "random.h"
#include "constants/species.h"

#define DEFAULT_LEARNSET_COMPATIBILITY 0
#define FULL_LEARNSET_COMPATIBILITY 1
#define TYPE_MATCH_COMPATIBILITY 2

#define BIRCH_INTRO_MON SPECIES_LOTAD
#define STARTER_ITEM ITEM_NONE
#define BATTLE_TUTORIAL_OPPONENT SPECIES_ZIGZAGOON
#define WALLY_CATCH_TUTORIAL_MON SPECIES_ZIGZAGOON
#define WALLY_CATCH_TUTORIAL_OPPONENT SPECIES_RALTS
#define PC_START_ITEM ITEM_POTION
#define TUTOR_COMPATIBILITY DEFAULT_LEARNSET_COMPATIBILITY 
#define TMHM_COMPATIBILITY DEFAULT_LEARNSET_COMPATIBILITY 
#define MART_PROMO_ITEM ITEM_PREMIER_BALL 
#define TRAINER_LEVEL_BOOST_PERCENT 100
#define GEN_RESTRICTIONS 0xFFFF // If any of the first 9 bits are 0 we don't allow that gen


// Berries are a u8 but the last bit is used for weeds 
// (so we need to be over last berry but under 127)
#define RANDOM_ITEM_BERRY (LAST_BERRY_INDEX + 3) 

const u16 gUprStaticVars[] = { BIRCH_INTRO_MON,
                               STARTER_ITEM,
                               BATTLE_TUTORIAL_OPPONENT,
                               WALLY_CATCH_TUTORIAL_MON,
                               WALLY_CATCH_TUTORIAL_OPPONENT,
                               PC_START_ITEM,
                               TUTOR_COMPATIBILITY,
                               TMHM_COMPATIBILITY,
                               MART_PROMO_ITEM, 
                               TRAINER_LEVEL_BOOST_PERCENT, // Set by upr so upr's level increase will still work with level scaling
                               GEN_RESTRICTIONS}; // Used so we can restrict gens for evo every level

const u16 gUprBerryTrees[] = {
    ITEM_NONE, // BERRY_TREE_ROUTE_102_PECHA    
    ITEM_NONE, // BERRY_TREE_ROUTE_102_ORAN     
    ITEM_NONE, // BERRY_TREE_ROUTE_104_SOIL_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_ORAN_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_103_CHERI_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_103_LEPPA    
    ITEM_NONE, // BERRY_TREE_ROUTE_103_CHERI_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_104_CHERI_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_104_SOIL_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_LEPPA    
    ITEM_NONE, // BERRY_TREE_ROUTE_104_ORAN_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_SOIL_3   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_PECHA    
    ITEM_NONE, // BERRY_TREE_ROUTE_123_QUALOT_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_POMEG_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_110_NANAB_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_110_NANAB_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_110_NANAB_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_111_RAZZ_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_111_RAZZ_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_112_RAWST_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_112_PECHA_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_112_PECHA_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_112_RAWST_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_116_PINAP_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_116_CHESTO_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_117_WEPEAR_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_117_WEPEAR_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_117_WEPEAR_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_POMEG_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_118_SITRUS_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_118_SOIL     
    ITEM_NONE, // BERRY_TREE_ROUTE_118_SITRUS_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_119_POMEG_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_119_POMEG_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_119_POMEG_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_120_ASPEAR_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_120_ASPEAR_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_120_ASPEAR_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_120_PECHA_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_120_PECHA_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_120_PECHA_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_120_RAZZ     
    ITEM_NONE, // BERRY_TREE_ROUTE_120_NANAB    
    ITEM_NONE, // BERRY_TREE_ROUTE_120_PINAP    
    ITEM_NONE, // BERRY_TREE_ROUTE_120_WEPEAR   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_PERSIM   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_ASPEAR   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_RAWST    
    ITEM_NONE, // BERRY_TREE_ROUTE_121_CHESTO   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_SOIL_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_NANAB_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_121_NANAB_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_121_SOIL_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_115_BLUK_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_115_BLUK_2   
    ITEM_NONE, // BERRY_TREE_UNUSED             
    ITEM_NONE, // BERRY_TREE_ROUTE_123_POMEG_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_POMEG_4  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_GREPA_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_GREPA_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_LEPPA_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_SOIL     
    ITEM_NONE, // BERRY_TREE_ROUTE_123_LEPPA_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_GREPA_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_116_CHESTO_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_116_PINAP_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_114_PERSIM_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_115_KELPSY_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_115_KELPSY_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_115_KELPSY_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_GREPA_4  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_QUALOT_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_QUALOT_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_104_SOIL_4   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_CHERI_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_114_PERSIM_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_114_PERSIM_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_QUALOT_4 
    ITEM_NONE, // BERRY_TREE_ROUTE_111_ORAN_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_111_ORAN_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_130_LIECHI   
    ITEM_NONE, // BERRY_TREE_ROUTE_119_HONDEW_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_119_HONDEW_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_119_SITRUS   
    ITEM_NONE, // BERRY_TREE_ROUTE_119_LEPPA    
    ITEM_NONE, // BERRY_TREE_ROUTE_123_PECHA    
    ITEM_NONE, // BERRY_TREE_ROUTE_123_SITRUS   
    ITEM_NONE, // BERRY_TREE_ROUTE_123_RAWST    
    ITEM_NONE, // BERRY_TREE_ROUTE_102_PECHA    
    ITEM_NONE, // BERRY_TREE_ROUTE_102_ORAN     
    ITEM_NONE, // BERRY_TREE_ROUTE_104_SOIL_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_ORAN_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_103_CHERI_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_103_LEPPA    
    ITEM_NONE, // BERRY_TREE_ROUTE_103_CHERI_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_104_CHERI_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_104_SOIL_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_LEPPA    
    ITEM_NONE, // BERRY_TREE_ROUTE_104_ORAN_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_SOIL_3   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_PECHA    
    ITEM_NONE, // BERRY_TREE_ROUTE_123_QUALOT_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_POMEG_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_110_NANAB_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_110_NANAB_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_110_NANAB_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_111_RAZZ_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_111_RAZZ_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_112_RAWST_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_112_PECHA_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_112_PECHA_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_112_RAWST_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_116_PINAP_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_116_CHESTO_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_117_WEPEAR_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_117_WEPEAR_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_117_WEPEAR_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_POMEG_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_118_SITRUS_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_118_SOIL     
    ITEM_NONE, // BERRY_TREE_ROUTE_118_SITRUS_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_119_POMEG_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_119_POMEG_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_119_POMEG_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_120_ASPEAR_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_120_ASPEAR_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_120_ASPEAR_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_120_PECHA_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_120_PECHA_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_120_PECHA_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_120_RAZZ     
    ITEM_NONE, // BERRY_TREE_ROUTE_120_NANAB    
    ITEM_NONE, // BERRY_TREE_ROUTE_120_PINAP    
    ITEM_NONE, // BERRY_TREE_ROUTE_120_WEPEAR   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_PERSIM   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_ASPEAR   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_RAWST    
    ITEM_NONE, // BERRY_TREE_ROUTE_121_CHESTO   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_SOIL_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_121_NANAB_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_121_NANAB_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_121_SOIL_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_115_BLUK_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_115_BLUK_2   
    ITEM_NONE, // BERRY_TREE_UNUSED             
    ITEM_NONE, // BERRY_TREE_ROUTE_123_POMEG_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_POMEG_4  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_GREPA_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_GREPA_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_LEPPA_1  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_SOIL     
    ITEM_NONE, // BERRY_TREE_ROUTE_123_LEPPA_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_GREPA_3  
    ITEM_NONE, // BERRY_TREE_ROUTE_116_CHESTO_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_116_PINAP_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_114_PERSIM_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_115_KELPSY_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_115_KELPSY_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_115_KELPSY_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_GREPA_4  
    ITEM_NONE, // BERRY_TREE_ROUTE_123_QUALOT_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_QUALOT_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_104_SOIL_4   
    ITEM_NONE, // BERRY_TREE_ROUTE_104_CHERI_2  
    ITEM_NONE, // BERRY_TREE_ROUTE_114_PERSIM_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_114_PERSIM_3 
    ITEM_NONE, // BERRY_TREE_ROUTE_123_QUALOT_4 
    ITEM_NONE, // BERRY_TREE_ROUTE_111_ORAN_1   
    ITEM_NONE, // BERRY_TREE_ROUTE_111_ORAN_2   
    ITEM_NONE, // BERRY_TREE_ROUTE_130_LIECHI   
    ITEM_NONE, // BERRY_TREE_ROUTE_119_HONDEW_1 
    ITEM_NONE, // BERRY_TREE_ROUTE_119_HONDEW_2 
    ITEM_NONE, // BERRY_TREE_ROUTE_119_SITRUS   
    ITEM_NONE, // BERRY_TREE_ROUTE_119_LEPPA    
    ITEM_NONE, // BERRY_TREE_ROUTE_123_PECHA    
    ITEM_NONE, // BERRY_TREE_ROUTE_123_SITRUS   
    ITEM_NONE  // BERRY_TREE_ROUTE_123_RAWST    
};

// This is to ensure the compiler never tries to inline constant vars from the array
u16 __attribute__((optimize("O0"))) uprAccessVar(u16 index)
{
    return gUprStaticVars[index];
}

// We need to make sure the compiler dosn't try and optimize these checks because the values will change after compilation
void __attribute__((optimize("O0"))) handleRandomizedBerryTreeSetup()
{
    // We could just check the first item, the loop is to try and make sure the compiler will never try and be clever
    // It dosn't know that we'll be modifying the bytes of gUprBerryTrees post complation
    int i;
    for (i = 0; i < 5; i ++)
    {
        if (gUprBerryTrees[i] != ITEM_NONE)
        {
            for (i = 0; i < BERRY_TREES_COUNT; i ++)
            {
                gSaveBlock1Ptr->berryTrees[i].berry = ITEM_TO_BERRY(RANDOM_ITEM_BERRY);
            }
            return;
        }
    }

}

bool8 handleRandomizedBerryTreeDataText(u8 treeId, u8 count, u8 berry)
{
    if (berry != ITEM_TO_BERRY(RANDOM_ITEM_BERRY))
        return FALSE;

    if (gUprBerryTrees[treeId] >= FIRST_BERRY_INDEX && gUprBerryTrees[treeId] <= LAST_BERRY_INDEX)
    {
        gSpecialVar_0x8006 = count;
    }
    else 
    {
        gSpecialVar_0x8006 = gItemsInfo[gUprBerryTrees[treeId]].price > 500 ? 1 : count;
    }
    
    CopyItemNameHandlePlural(gUprBerryTrees[treeId], gStringVar1, gSpecialVar_0x8006);

    return TRUE;
}


bool8 handleRandomizedBerryTreeItemCountText(u8 treeId, u8 count, u8 berry) 
{
    if (berry != ITEM_TO_BERRY(RANDOM_ITEM_BERRY))
        return FALSE;

    if (gUprBerryTrees[treeId] >= FIRST_BERRY_INDEX && gUprBerryTrees[treeId] <= LAST_BERRY_INDEX)
    {
        CopyItemNameHandlePlural(gUprBerryTrees[treeId], gStringVar1, count);
    }
    else 
    {
        CopyItemNameHandlePlural(gUprBerryTrees[treeId], gStringVar1, gItemsInfo[gUprBerryTrees[treeId]].price > 500 ? 1 : count);
    }
    
    gSpecialVar_Result = FALSE;

    return TRUE;
}

bool8 handleRandomizedBerryTreeGive(u8 treeId, u8 count, u8 berry)
{
    if (berry != ITEM_TO_BERRY(RANDOM_ITEM_BERRY))
        return FALSE;

    if (gUprBerryTrees[treeId] >= FIRST_BERRY_INDEX && gUprBerryTrees[treeId] <= LAST_BERRY_INDEX)
    {
        gSpecialVar_0x8004 = AddBagItem(gUprBerryTrees[treeId], count);
    }
    else 
    {
        gSpecialVar_0x8004 = AddBagItem(gUprBerryTrees[treeId], gItemsInfo[gUprBerryTrees[treeId]].price > 500 ? 1 : count);
    }

    return TRUE;
}

u8 handleRandomizedBerryTreeGraphics(u8 berryId, u8 treeId) 
{
    if (berryId != ITEM_TO_BERRY(RANDOM_ITEM_BERRY))
        return berryId;

    return (u8) (gUprBerryTrees[(treeId + 10) % BERRY_TREES_COUNT % BERRY_TREES_COUNT] % (LAST_BERRY_INDEX - FIRST_BERRY_INDEX));
}

// We need to make sure the compiler dosn't try and optimize these checks because the values will change after compilation
u8 __attribute__((optimize("O0"))) handleRandomizedTeachableLearnsets(u16 species, u16 move) 
{
    u32 seed;
    u16 i = 0;

    if (species == SPECIES_EGG)
    {
        return CANNOT_LEARN_MOVE;
    }

    if (gPartyMenu.action == PARTY_ACTION_MOVE_TUTOR)
    {
        i = TUTOR_COMPATIBILITY_INDEX;

        if (gUprStaticVars[i] == DEFAULT_LEARNSET_COMPATIBILITY)
        {
            return USE_EXISTING_LEARNSET;
        }

        if (gUprStaticVars[i] == FULL_LEARNSET_COMPATIBILITY)
        {
            return CAN_LEARN_MOVE;
        }

        if (gUprStaticVars[i] == TYPE_MATCH_COMPATIBILITY)
        {
            return gMovesInfo[move].type == gSpeciesInfo[species].types[0] || gMovesInfo[move].type == gSpeciesInfo[species].types[1];
        }

        seed = gUprStaticVars[i] + species + move;
        return (PRandom(&seed) % 2);

    }
    else 
    {
        i = TMHM_COMPATIBILITY_INDEX;

        if (gUprStaticVars[i] == DEFAULT_LEARNSET_COMPATIBILITY)
        {
            return USE_EXISTING_LEARNSET;
        }

        if (gUprStaticVars[i] == FULL_LEARNSET_COMPATIBILITY)
        {
            return CAN_LEARN_MOVE;
        }

        if (gUprStaticVars[i] == TYPE_MATCH_COMPATIBILITY)
        {
            return gMovesInfo[move].type == gSpeciesInfo[species].types[0] || gMovesInfo[move].type == gSpeciesInfo[species].types[1];
        }

        seed = gUprStaticVars[i] + species + move;
        return (PRandom(&seed) % 2);
        
    }

}

#define GENS_TO_RESTRICT 9
#define MAX_ROLLS 100

typedef struct {
    u16 lower;
    u16 upper;
} GenRange;

bool8 isInGenRange(u16 value, GenRange range) 
{
    return (value >= range.lower && value <= range.upper);
}

u16 getRandomValueFromRange(u32 seed, GenRange range) {
    return (PRandom(&seed) % (range.upper - range.lower + 1)) + range.lower;
}

u16 __attribute__((optimize("O0")))  getRandomSpeciesWithGenRestrictions(u32 seed, u16 candidateSpecies) 
{
    u8 i;
    u8 restrictionSum;
    u8 restriction = 0;
    u16 newSpecies = candidateSpecies;
    u16 restrictions = uprAccessVar(GEN_RESTRICTIONS_INDEX);

    GenRange gens[GENS_TO_RESTRICT] = {
        {SPECIES_BULBASAUR    , SPECIES_MEW}, 
        {SPECIES_CHIKORITA    , SPECIES_CELEBI}, 
        {SPECIES_TREECKO      , SPECIES_DEOXYS}, 
        {SPECIES_TURTWIG      , SPECIES_ARCEUS},
        {SPECIES_VICTINI      , SPECIES_GENESECT}, 
        {SPECIES_CHESPIN      , SPECIES_VOLCANION}, 
        {SPECIES_ROWLET       , SPECIES_MELMETAL}, 
        {SPECIES_GROOKEY      , SPECIES_ENAMORUS}, 
        {SPECIES_SPRIGATITO   , SPECIES_PECHARUNT} // This is not gen9, just whatever is left
    };

    bool8 gensAllowed[GENS_TO_RESTRICT] = { (restrictions & 1)   > 0,
                                            (restrictions & 2)   > 0,
                                            (restrictions & 4)   > 0,
                                            (restrictions & 8)   > 0,
                                            (restrictions & 16)  > 0,
                                            (restrictions & 32)  > 0,
                                            (restrictions & 64)  > 0,
                                            (restrictions & 128) > 0,
                                            (restrictions & 256) > 0 };

    for (i = 0; i < GENS_TO_RESTRICT; i++)
        restrictionSum += gensAllowed[i];                                        

    // If they are trying to restrict everything or nothing, do nothing
    if (restrictionSum == 0 || restrictionSum == GENS_TO_RESTRICT)
        return candidateSpecies;

    // Set restriction to the gen that the species is from
    restriction = GENS_TO_RESTRICT;
    for (i = 0; i < GENS_TO_RESTRICT; i++) 
    {
        if (isInGenRange(candidateSpecies, gens[i]))
            restriction = i;

        if (restriction != GENS_TO_RESTRICT)
            break; 
    }

    // A species was picked that is not in any gen, so just return it
    if (restriction == GENS_TO_RESTRICT)
        return candidateSpecies;

    // The species was allowed
    if (gensAllowed[restriction])
        return candidateSpecies;

    // Find a random gen to select from
    for (i = 0; i < MAX_ROLLS; i++) 
    {
        restriction = PRandom(&seed) % GENS_TO_RESTRICT;
        if (gensAllowed[restriction])
            break;
    }

    // If we hit max rolls and didn't find a random gen, then just go in order
    if (!gensAllowed[restriction])
    {
        for (i = 0; i < MAX_ROLLS; i++) 
        {
            restriction = i;
            if (gensAllowed[restriction])
                break;
        }
    }

    // Now we know the gen start rolling for a new species
    for (i = 0; i < MAX_ROLLS; i++) 
    {
        newSpecies = getRandomValueFromRange(seed, gens[restriction]);
        if (newSpecies != candidateSpecies)
            break;
    }


    return newSpecies;
}