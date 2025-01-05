#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <capstone/capstone.h>
#include "global.h"
#include "elf.h"
#include "util.h"

// Get constants from the repository
#include "constants/global.h"
#include "constants/species.h"
#include "constants/trainers.h"
#include "constants/items.h"
#include "constants/abilities.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/event_objects.h"
#include "constants/battle_frontier_mons.h"

/*
 * ---------------------------------------------------------
 * Type definitions
 * ---------------------------------------------------------
 */

#define len(arr) (sizeof(arr)/sizeof(*arr))
#define UNUSED __attribute__((unused))

struct StaticPokemon {
    const char * label;
    int offset;
};

struct Mart {
    int size;
    const char * label;
};

struct GivenItems {
    const char * label;
};

struct TutorMoves {
    const char * label;
};

static csh sCapstone;

static Elf32_Shdr * sh_text;

/*
 * ---------------------------------------------------------
 * Data
 * ---------------------------------------------------------
 */

static const char * gTypeNames[] = {
    "Normal",                   // 0
    "Fighting",                 // 1
    "Flying",                   // 2
    "Poison",                   // 3
    "Ground",                   // 4
    "Rock",                     // 5
    "Grass", // "Bug",          // 6
    "Ghost", // "Mystery"       // 7
    "Steel",                    // 8
    "Fire",                     // 9
    "Water",                    // 10
    "Electric",                 // 11
    "Psychic",                  // 12
    "Ice",                      // 13
    "Dragon",                   // 14
    "Dark",                     // 15
    "Fairy"                     // 16
};

const struct StaticPokemon gStaticPokemon[][8] = {
    {{"RustboroCity_DevonCorp_2F_EventScript_LileepReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveLileep", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveLileep", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedLileepFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_AnorithReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorith", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveAnorith", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedAnorithFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_ShieldonReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveShieldon", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveShieldon", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedShieldonFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedShieldonFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_CranidosReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveCranidos", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveCranidos", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedCranidosFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedCranidosFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_OmanyteReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveOmanyte", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveOmanyte", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedOmanyteFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedOmanyteFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_KabutoReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveKabuto", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveKabuto", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedKabutoFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedKabutoFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_TirtougaReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveTirtouga", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveTirtouga", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedTirtougaFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedTirtougaFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_ArchenReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveArchen", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveArchen", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedArchenFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedArchenFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_TyruntReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveTyrunt", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveTyrunt", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedTyruntFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedTyruntFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_AmauraReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveAmaura", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveAmaura", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedAmauraFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedAmauraFanfare", 0x10}},
    {{"RustboroCity_DevonCorp_2F_EventScript_AerodactylReady", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveAerodactyl", 0x3}, {"RustboroCity_DevonCorp_2F_EventScript_ReceiveAerodactyl", 0xC}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedAerodactylFanfare", 0x2}, {"RustboroCity_DevonCorp_2F_EventScript_ReceivedAerodactylFanfare", 0x10}},
    {{"MarineCave_End_EventScript_Kyogre", 0x17}, {"MarineCave_End_EventScript_Kyogre", 0x25}, {"MarineCave_End_EventScript_RanFromKyogre", 0x3}},
    {{"TerraCave_End_EventScript_Groudon", 0x17}, {"TerraCave_End_EventScript_Groudon", 0x25}, {"TerraCave_End_EventScript_RanFromGroudon", 0x3}},
    {{"DesertRuins_EventScript_Regirock", 0x2}, {"DesertRuins_EventScript_Regirock", 0x8}, {"DesertRuins_EventScript_RanFromRegirock", 0x3}},
    {{"IslandCave_EventScript_Regice", 0x2}, {"IslandCave_EventScript_Regice", 0x8}, {"IslandCave_EventScript_RanFromRegice", 0x3}},
    {{"AncientTomb_EventScript_Registeel", 0x2}, {"AncientTomb_EventScript_Registeel", 0x8}, {"AncientTomb_EventScript_RanFromRegisteel", 0x3}},
    {{"SkyPillar_Top_EventScript_Rayquaza", 0x3}, {"SkyPillar_Top_EventScript_Rayquaza", 0xC}, {"SkyPillar_Top_EventScript_RanFromRayquaza", 0x3}},
    {{"EventScript_BattleKecleon", 0x1F}, {"EventScript_BattleKecleon", 0x28}},
    {{"Route120_EventScript_StevenBattleKecleon", 0x4B}, {"Route120_EventScript_StevenBattleKecleon", 0x54}},
    {{"NewMauville_Inside_EventScript_Voltorb1", 0x3}, {"NewMauville_Inside_EventScript_Voltorb1", 0xF}},
    {{"NewMauville_Inside_EventScript_Voltorb2", 0x3}, {"NewMauville_Inside_EventScript_Voltorb2", 0xF}},
    {{"NewMauville_Inside_EventScript_Voltorb3", 0x3}, {"NewMauville_Inside_EventScript_Voltorb3", 0xF}},
    {{"AquaHideout_B1F_EventScript_Electrode1", 0x3}, {"AquaHideout_B1F_EventScript_Electrode1", 0xF}},
    {{"AquaHideout_B1F_EventScript_Electrode2", 0x3}, {"AquaHideout_B1F_EventScript_Electrode2", 0xF}},
    {{"BattleFrontier_OutsideEast_EventScript_WaterSudowoodo", 0x1F}, {"BattleFrontier_OutsideEast_EventScript_WaterSudowoodo", 0x2D}},
    {{"SouthernIsland_Interior_EventScript_SetLatiosBattleVars", 0x3}},
    {{"SouthernIsland_Interior_EventScript_SetLatiasBattleVars", 0x3}},
    {{"BirthIsland_Exterior_EventScript_Deoxys", 0x26}, {"BirthIsland_Exterior_EventScript_Deoxys", 0x36}, {"BirthIsland_Exterior_EventScript_DefeatedDeoxys", 0x6}, {"BirthIsland_Exterior_EventScript_RanFromDeoxys", 0x3}},
    {{"FarawayIsland_Interior_EventScript_Mew", 0x1B}, {"FarawayIsland_Interior_EventScript_Mew", 0x55}, {"FarawayIsland_Interior_EventScript_MewDefeated", 0x6}, {"FarawayIsland_Interior_EventScript_PlayerOrMewRan", 0x3}},
    {{"NavelRock_Top_EventScript_HoOh", 0x30}, {"NavelRock_Top_EventScript_HoOh", 0x5F}, {"NavelRock_Top_EventScript_DefeatedHoOh", 0x6}, {"NavelRock_Top_EventScript_RanFromHoOh", 0x3}},
    {{"NavelRock_Bottom_EventScript_Lugia", 0x45}, {"NavelRock_Bottom_EventScript_Lugia", 0x50}, {"NavelRock_Bottom_EventScript_DefeatedLugia", 0x6}, {"NavelRock_Bottom_EventScript_RanFromLugia", 0x3}},
    {{"MossdeepCity_StevensHouse_EventScript_GiveBeldum", 0x3}, {"MossdeepCity_StevensHouse_EventScript_GiveBeldum", 0xC}, {"MossdeepCity_StevensHouse_EventScript_ReceivedBeldumFanfare", 0x2}, {"MossdeepCity_StevensHouse_EventScript_ReceivedBeldumFanfare", 0x13}},
    {{"Route119_WeatherInstitute_2F_EventScript_ReceiveCastform", 0xB}, {"Route119_WeatherInstitute_2F_EventScript_ReceiveCastform", 0x14}},
    {{"MossdeepCity_DoSpiritombEncounter", 0x1}, {"MossdeepCity_DoSpiritombEncounter", 0x10}}
};

const struct TutorMoves gTutorMoves[][4] = {
    {{"gMoveTutor_explosion_1"}, {"gMoveTutor_explosion_2"}, {"gMoveTutor_explosion_3"}},
    {{"gMoveTutor_doubleEdge_1"}, {"gMoveTutor_doubleEdge_2"}, {"gMoveTutor_doubleEdge_3"}},
    {{"gMoveTutor_dynamicPunch_1"}, {"gMoveTutor_dynamicPunch_2"}, {"gMoveTutor_dynamicPunch_3"}},
    {{"gMoveTutor_substitute_1"}, {"gMoveTutor_substitute_2"}, {"gMoveTutor_substitute_3"}},
    {{"gMoveTutor_sleepTalk_1"}, {"gMoveTutor_sleepTalk_2"}, {"gMoveTutor_sleepTalk_3"}},
    {{"gMoveTutor_metronome_1"}, {"gMoveTutor_metronome_2"}, {"gMoveTutor_metronome_3"}},
    {{"gMoveTutor_mimic_1"}, {"gMoveTutor_mimic_2"}, {"gMoveTutor_mimic_3"}, {"gMoveTutor_mimic_4"}},
    {{"gMoveTutor_furyCutter_1"}, {"gMoveTutor_furyCutter_2"}},
    {{"gMoveTutor_rollout_1"}, {"gMoveTutor_rollout_2"}},
    {{"gMoveTutor_swagger_1"}, {"gMoveTutor_swagger_2"}, {"gMoveTutor_swagger_3"}, {"gMoveTutor_swagger_4"}},
};

// Size is hard coded (rather than scanning till it finds item none) because I don't want to randomize the entire mart in all cases
const struct Mart gMarts[][2] = {
    {{13, "BattleFrontier_Mart_Pokemart"}},
    {{7, "EverGrandeCity_PokemonLeague_1F_Pokemart"}},
    {{12, "FallarborTown_Mart_Pokemart"}},
    {{10, "FortreeCity_Mart_Pokemart"}},
    {{4, "LavaridgeTown_HerbShop_Pokemart"}},
    {{9, "LavaridgeTown_Mart_Pokemart"}},
    {{11, "LilycoveCity_DepartmentStore_2F_Pokemart1"}},
    {{10, "LilycoveCity_DepartmentStore_2F_Pokemart2"}},
    {{6, "LilycoveCity_DepartmentStore_3F_Pokemart_Vitamins"}},
    {{7, "LilycoveCity_DepartmentStore_3F_Pokemart_StatBoosters"}},
    {{14, "MauvilleCitySpeedchoice_Mart_Items"}},
    {{9, "MossdeepCity_Mart_Pokemart"}},
    {{9, "SlateportCity_Mart_Pokemart"}},
    {{9, "SootopolisCity_Mart_Pokemart"}},
    {{11, "VerdanturfTown_Mart_Pokemart"}},
    {{6, "OldaleTownSpeedchoice_Mart_Items1"}, {6, "OldaleTownSpeedchoice_Mart_Items2"}},
    {{11, "PetalburgCity_Mart_Pokemart_Basic"}, {13, "PetalburgCity_Mart_Pokemart_Expanded"}},
    {{12, "RustboroCitySpeedchoice_Mart_Items1"}, {14, "RustboroCitySpeedchoice_Mart_Items2"}},
    {{11, "TrainerHill_Entrance_Pokemart_Basic"}, {12, "TrainerHill_Entrance_Pokemart_Expanded"}},
    {{6, "SlateportCity_Pokemart_EnergyGuru"}} // Only the first 6, because then we have all the patches, mints, feathers e.t.c
};

const struct GivenItems gGivenItems[][2] = {
    {{"gGiveItem_1"}},
    {{"gGiveItem_2"}},
    {{"gGiveItem_3"}},
    {{"gGiveItem_4"}},
    {{"gGiveItem_5_May"}, {"gGiveItem_5_Brendan"}},
    {{"gGiveItem_6"}},
    {{"gGiveItem_7"}},
    {{"gGiveItem_8"}},
    {{"gGiveItem_9_Man"}, {"gGiveItem_9_MagmaMan"}},
    {{"gGiveItem_10"}},
    {{"gGiveItem_11"}},
    {{"gGiveItem_12"}},
    {{"gGiveItem_13"}},
    {{"gGiveItem_14"}},
    {{"gGiveItem_15"}},
    {{"gGiveItem_16"}},
    {{"gGiveItem_17"}},
    {{"gGiveItem_18_trick1"}, {"gGiveItem_18_trick1_start"}},
    {{"gGiveItem_19_trick2"}, {"gGiveItem_19_trick2_start"}},
    {{"gGiveItem_20_trick3"}, {"gGiveItem_20_trick3_start"}},
    {{"gGiveItem_21_trick4"}, {"gGiveItem_21_trick4_start"}},
    {{"gGiveItem_22_trick5"}, {"gGiveItem_22_trick5_start"}},
    {{"gGiveItem_23_trick6"}, {"gGiveItem_23_trick6_start"}},
    {{"gGiveItem_24_trick7"}, {"gGiveItem_24_trick7_start"}},
    {{"gGiveItem_25"}},
    {{"gGiveItem_26"}},
    {{"gGiveItem_27"}},
    {{"gGiveItem_28"}},
    {{"gGiveItem_29"}},
    {{"gGiveItem_30"}},
    {{"gGiveItem_31"}},
    {{"gGiveItem_32"}},
    {{"gGiveItem_33"}},
    {{"gGiveItem_34"}},
    {{"gGiveItem_35"}},
    {{"gGiveItem_36"}},
    {{"gGiveItem_37"}},
    {{"gGiveItem_38"}},
    {{"gGiveItem_39"}},
    {{"gGiveItem_40"}},
    {{"gGiveItem_41"}},
    {{"gGiveItem_42"}},
    {{"gGiveItem_43"}},
    {{"gGiveItem_44"}},
    {{"gGiveItem_45"}},
    {{"gGiveItem_46"}},
    {{"gGiveItem_47"}},
    {{"gGiveItem_48"}},
    {{"gGiveItem_49"}},
    {{"gGiveItem_50"}, {"gGiveItem_50_Spare"}},
    {{"gGiveItem_51"}, {"gGiveItem_51_Counter"}},
    {{"gGiveItem_52_6Soda"}, {"gGiveItem_52_1Soda"}},
    {{"gGiveItem_53"}}
};

/** These symbols have been completely changed, we need a way around that
gLevelUpLearnsets
gTMHMLearnsets
*/

int main(int argc, char ** argv)
{
    const char * romName = "Emerald EX (U)";
    const char * romCode = "SPDX";
    FILE * elfFile = NULL;
    FILE * outFile = NULL;

    // Argument parser
    for (int i = 1; i < argc; i++) {
        char * arg = argv[i];
        if (strcmp(arg, "--name") == 0) {
            i++;
            if (i == argc) {
                FATAL_ERROR("missing argument to --name\n");
            }
            romName = argv[i];
        } else if (strcmp(arg, "--code") == 0) {
            i++;
            if (i == argc) {
                FATAL_ERROR("missing argument to --code\n");
            }
            romCode = argv[i];
        } else if (arg[0] == '-') {
            FATAL_ERROR("unrecognized option: \"%s\"\n", arg);
        } else if (elfFile == NULL) {
            elfFile = fopen(arg, "rb");
            if (elfFile == NULL) {
                FATAL_ERROR("unable to open file \"%s\" for reading\n", arg);
            }
        } else if (outFile == NULL) {
            outFile = fopen(arg, "w");
            if (outFile == NULL) {
                FATAL_ERROR("unable to open file \"%s\" for writing\n", arg);
            }
        } else {
            FATAL_ERROR("usage: %s ELF OUTPUT [--name NAME] [--code CODE]\n", argv[0]);
        }
    }

    if (outFile == NULL) {
        FATAL_ERROR("usage: %s ELF OUTPUT [--name NAME] [--code CODE]\n", argv[0]);
    }

    fprintf(stderr, "Loading ELF\n");

    // Load the ELF metadata
    InitElf(elfFile);
    #ifdef _MSC_VER
    #define print(format, ...) (fprintf(outFile, format, __VA_ARGS__))
    #else
    #define print(format, ...) (fprintf(outFile, format, ##__VA_ARGS__))
    #endif
    #define config_set(name, value) (print("%s=0x%X\n", (name), (value)))
    #define sym_get(name) (GetSymbolByName((name))->st_value)
    #define config_sym(name, symname) (config_set((name), sym_get(symname) - 0x08000000))

    
    fprintf(stderr, "Capstone Init\n");
    // Initialize Capstone
    cs_open(CS_ARCH_ARM, CS_MODE_THUMB, &sCapstone);
    cs_option(sCapstone, CS_OPT_DETAIL, CS_OPT_ON);
    sh_text = GetSectionHeaderByName(".text");

    fprintf(stderr, "Start writing INI\n");
    // Start writing the INI
    print("[%s]\n", romName);
    print("Game=%s\n", romCode);
    print("Version=0\n");
    print("TableFile=gba_english\n");

    fprintf(stderr, "Finding free space\n");
    // Find the first block after the ROM
    int shnum = GetSectionHeaderCount();
    uint32_t entry = GetEntryPoint();
    uint32_t end = entry;
    for (int i = 0; i < shnum; i++) {
        Elf32_Shdr * sec = GetSectionHeader(i);
        end = max(end, sec->sh_addr + sec->sh_size);
    }
    end -= entry;
    if (end & 0xFFFF) {
        end += 0x10000 - (end & 0xFFFF);
    }
    print("FreeSpace=0x%X\n", end);

    // Pokemon data
    fprintf(stderr, "Configuring Pokemon data\n");
    print("PokemonCount=%d\n", NUM_SPECIES - 1);
    print("PokemonNameLength=%d\n", POKEMON_NAME_LENGTH + 1);

    config_sym("SpeciesInfo", "gSpeciesInfo");
    Elf32_Sym * Em_gSpeciesInfos = GetSymbolByName("gSpeciesInfo");
    print("SpeciesInfoEntrySize=%d\n", Em_gSpeciesInfos->st_size / NUM_SPECIES);
    config_sym("MapBanksPtr", "gMapGroups");
    config_sym("MapLabelsPtr", "gRegionMapEntries");

    config_sym("StaticVars", "gUprStaticVars");

    //fprintf(stderr, "Configuring moves\n");
    //config_sym("PokemonMovesets", "gLevelUpLearnsets");
    //config_sym("PokemonTMHMCompat", "gTMHMLearnsets");

    fprintf(stderr, "Configuring Starters\n");
    config_sym("StarterPokemon", "sStarterMon");

    fprintf(stderr, "Configuring trainers\n");
    config_sym("TrainerData", "gTrainers");
    Elf32_Sym * Em_gTrainers = GetSymbolByName("gTrainers");

    fprintf(stderr, "Configuring wild mons\n");
    config_sym("WildPokemon", "gWildMonHeaders");

    fprintf(stderr, "Configuring trainer names and classes\n");
    print("TrainerEntrySize=%d\n", Em_gTrainers->st_size / (TRAINERS_COUNT - 1));
    config_set("TrainerCount", TRAINERS_COUNT);
    config_sym("TrainerClasses", "gTrainerClasses");
    print("TrainerClassCount=%d\n", TRAINER_CLASS_COUNT);
    print("TrainerClassNameLength=%d\n", 13); // hardcoded for now
    print("TrainerClassStructSize=%d\n", 16); // hardcoded for now (Size of trainer TrainerClass Struct)
    print("TrainerNameLength=%d\n", 11); // hardcoded for now
    print("DoublesTrainerClasses=[%d, %d, %d, %d, %d]\n", TRAINER_CLASS_SR_AND_JR, TRAINER_CLASS_TWINS, TRAINER_CLASS_YOUNG_COUPLE, TRAINER_CLASS_OLD_COUPLE, TRAINER_CLASS_SIS_AND_BRO); // hardcoded for now

    fprintf(stderr, "Configuring frontier mons\n");
    config_sym("FrontierPokemon", "gBattleFrontierMons");
    print("FrontierPokemonCount=%d\n", NUM_FRONTIER_MONS);

    fprintf(stderr, "Configuring items\n");
    Elf32_Sym * Em_gItems = GetSymbolByName("gItemsInfo");
    print("ItemEntrySize=%d\n", Em_gItems->st_size / ITEMS_COUNT);
    print("ItemCount=%d\n", ITEMS_COUNT);
    config_sym("ItemInfoOffset", "gItemsInfo");

    fprintf(stderr, "Configuring move names\n");
    print("MoveCount=%d\n", MOVES_COUNT - 1);
    config_sym("MoveInfoOffset", "gMovesInfo");
    Elf32_Sym * Em_gMoveInfos = GetSymbolByName("gMovesInfo");
    // Not sure why we have to do a minus 5? 
    int moveInfoSize = (Em_gMoveInfos->st_size / MOVES_COUNT) - 5;
    if (moveInfoSize % 2 != 0) 
        fprintf(stderr, "\nWARNING - Move info struct size was not detected as even, which could mean something is wrong\n\n");

    print("MoveInfoSize=%d\n", moveInfoSize);
    
    fprintf(stderr, "Configuring Ability names\n");
    Elf32_Sym * Em_gAbilities = GetSymbolByName("gAbilitiesInfo");
    print("AbilityStructSize=%d\n", Em_gAbilities->st_size / ABILITIES_COUNT);
    print("AbilityCount=%d\n", ABILITIES_COUNT);
    print("AbilityNameLength=%d\n", 16); // Hard coded ABILITY_NAME_LENGTH
    config_sym("AbilitiesOffset", "gAbilitiesInfo");

    //fprintf(stderr, "Configuring tutor moves\n");
    //config_sym("MoveTutorData", "gTutorMoves");
    //Elf32_Sym* Em_gTutorMoves = GetSymbolByName("gTutorMoves");
    //print("MoveTutorMoves=%d\n", Em_gTutorMoves->st_size / 2);
    
    fprintf(stderr, "Configuring item images and palettes\n");

    print("TmPals=[");
    char buffer[64];
    for (int i = 0; i < len(gTypeNames); i++) {
        sprintf(buffer, "gItemIconPalette_%sTMHM", gTypeNames[i]);
        if (i != 0)
            print(",");
        print("0x%X", GetSymbolByName(buffer)->st_value - 0x08000000);
    }
    print("]\n");
    
    fprintf(stderr, "Configuring ball pic\n");
    print("ItemBallPic=%d\n", OBJ_EVENT_GFX_ITEM_BALL);
    
    fprintf(stderr, "Configuring in game trades\n");
    config_sym("TradeTableOffset", "sIngameTrades");
    Elf32_Sym * Em_gIngameTrades = GetSymbolByName("sIngameTrades");
    print("TradeTableSize=%d\n", Em_gIngameTrades->st_size / 60); // hardcoded for now

    fprintf(stderr, "Configuring static pokemon\n");
    // These may need some fixing to support dynamic offsets.
    print("StaticPokemonSupport=1\n");
    for (int i = 0; i < len(gStaticPokemon); i++) {
        print("StaticPokemon[]=[");
        for (int j = 0; j < 8; j++) {
            if (gStaticPokemon[i][j].label == NULL) break;
            if (j != 0)
                print(",");
            print("0x%X", (sym_get(gStaticPokemon[i][j].label) - 0x08000000) + gStaticPokemon[i][j].offset);
        }
        print("]\n");
    }

    fprintf(stderr, "Configuring Berry Trees\n");
    config_sym("BerryTrees", "gUprBerryTrees");

    fprintf(stderr, "Configuring Pickup tables\n");
    config_sym("PickUpTables", "sPickupTable");

    fprintf(stderr, "Configuring Marts\n");
    for (int i = 0; i < len(gMarts); i++) {
        print("Marts[]=[");
        for (int j = 0; j < 2; j++) {
            if (gMarts[i][j].label == NULL) break;
            if (j != 0)
                print(",");
            print("[0x%X,0x%X]", sym_get(gMarts[i][j].label) - 0x08000000, gMarts[i][j].size);
        }
        print("]\n");
    }

    fprintf(stderr, "Configuring Given Items\n");
    for (int i = 0; i < len(gGivenItems); i++) {
        print("GivenItems[]=[");
        for (int j = 0; j < 2; j++) {
            if (gGivenItems[i][j].label == NULL) break;
            if (j != 0)
                print(",");

            int offsetInScript = 0x3;
            print("[0x%X]", offsetInScript + sym_get(gGivenItems[i][j].label) - 0x08000000);
        }
        print("]\n");
    }

    fprintf(stderr, "Configuring type effectivness tables\n");
    config_sym("TypeEffectivenessTable", "gTypeEffectivenessTable");
    

    fprintf(stderr, "Configuring random warps\n");
    config_sym("RandomWarpTable", "gWarpRemappingList");

    // TODO: what's happening with 
    // Contest Prizes, Vending Machines / slateport drinks / mauville prizes / lava cookie
    // TODO: these should only be randomized to TMS, I think they already get randomized

    // Key Items
    // gGiveKeyItem_OLD_ROD::
    // gGiveKeyItem_GO_GOGGLES_May::
    // gGiveKeyItem_GO_GOGGLES_Brendan::
    // gGiveKeyItem_BASEMENT_KEY::
    // gGiveKeyItem_HM_FLASH::
    // gGiveKeyItem_HM_ROCK_SMASH::
    // gGiveKeyItem_COIN_CASE::
    // gGiveKeyItem_HM_DIVE::
    // gGiveKeyItem_EON_TICKET::
    // gGiveKeyItem_AURORA_TICKET::
    // gGiveKeyItem_OLD_SEA_MAP::
    // gGiveKeyItem_MYSTIC_TICKET::
    // gGiveKeyItem_METEORITE::
    // gGiveKeyItem_MAGMA_EMBLEM::
    // gGiveKeyItem_ITEM_HM03::
    // gGiveKeyItem_WAILMER_PAIL::
    // gGiveKeyItem_HM02_May::
    // gGiveKeyItem_HM02_Brendan::
    // gGiveKeyItem_SOOT_SACK::
    // gGiveKeyItem_GOOD_ROD::
    // gGiveKeyItem_ITEM_FINDER_May::
    // gGiveKeyItem_ITEM_FINDER_Brendan::
    // gGiveKeyItem_DEVON_SCOPE::
    // gGiveKeyItem_ITEM_HM_CUT::
    // gGiveKeyItem_LETTER_President::
    // gGiveKeyItem_LETTER_Roxanne::
    // gGiveKeyItem_HM04::
    // gGiveKeyItem_DEVON_GOODS::
    // gGiveKeyItem_POWDER_JAR::
    // gGiveKeyItem_MH_WATERFALL::
    // gGiveKeyItem_EON_TICKET::
    // gGiveKeyItem_POKEBLOCK_CASE::
    // gGiveKeyItem_AMULET_COIN::
    // gGiveKeyItem_SS_TICKET::
    // Probably can't do bikes as they need to switch

    fprintf(stderr, "Configuring tutor text\n");
    for (int i = 0; i < len(gTutorMoves); i++) {
        print("TutorMoves[]=[");
        for (int j = 0; j < 4; j++) {
            if (gTutorMoves[i][j].label == NULL) break;
            if (j != 0)
                print(",");
            int offsetInScript = j == 0 ? 3 : 2;
            print("[0x%X]", offsetInScript + sym_get(gTutorMoves[i][j].label) - 0x08000000);
        }
        print("]\n");
    }
    fprintf(stderr, "Configuring pokedex order\n");

    fprintf(stderr, "Configuring randomizer check value\n");
    config_sym("CheckValueOffset", "gRandomizerCheckValue");

    DestroyResources();
    fclose(outFile);
    fclose(elfFile);
    return 0;
}
