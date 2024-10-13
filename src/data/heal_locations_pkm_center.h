#define DEFAULT_POKEMON_CENTER_COORDS .x = 7, .y = 4

static const struct HealLocation sHealLocationsPokemonCenter[HEAL_LOCATION_COUNT - 1] =
{
    [HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F - 1] =
    {
        .group = MAP_GROUP(LITTLEROOT_TOWN_BRENDANS_HOUSE_1F),
        .map = MAP_NUM(LITTLEROOT_TOWN_BRENDANS_HOUSE_1F),
        .x = 2,
        .y = 7,
    },
    [HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F - 1] =
    {
        .group = MAP_GROUP(LITTLEROOT_TOWN_MAYS_HOUSE_1F),
        .map = MAP_NUM(LITTLEROOT_TOWN_MAYS_HOUSE_1F),
        .x = 8,
        .y = 7,
    },
    [HEAL_LOCATION_PETALBURG_CITY - 1] =
    {
        .group = MAP_GROUP(PETALBURG_CITY_POKEMON_CENTER_1F),
        .map = MAP_NUM(PETALBURG_CITY_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_SLATEPORT_CITY - 1] =
    {
        .group = MAP_GROUP(SLATEPORT_CITY_POKEMON_CENTER_1F), 
        .map = MAP_NUM(SLATEPORT_CITY_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_MAUVILLE_CITY - 1] =
    {
        .group = MAP_GROUP(MAUVILLE_CITY_POKEMON_CENTER_1F),
        .map = MAP_NUM(MAUVILLE_CITY_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_RUSTBORO_CITY - 1] =
    {
        .group = MAP_GROUP(RUSTBORO_CITY_POKEMON_CENTER_1F),
        .map = MAP_NUM(RUSTBORO_CITY_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_FORTREE_CITY - 1] =
    {
        .group = MAP_GROUP(FORTREE_CITY_POKEMON_CENTER_1F),
        .map = MAP_NUM(FORTREE_CITY_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_LILYCOVE_CITY - 1] =
    {
        .group = MAP_GROUP(LILYCOVE_CITY_POKEMON_CENTER_1F),
        .map = MAP_NUM(LILYCOVE_CITY_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_MOSSDEEP_CITY - 1] =
    {
        .group = MAP_GROUP(MOSSDEEP_CITY_POKEMON_CENTER_1F),
        .map = MAP_NUM(MOSSDEEP_CITY_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_SOOTOPOLIS_CITY - 1] =
    {
        .group = MAP_GROUP(SOOTOPOLIS_CITY_POKEMON_CENTER_1F),
        .map = MAP_NUM(SOOTOPOLIS_CITY_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_EVER_GRANDE_CITY - 1] =
    {
        .group = MAP_GROUP(EVER_GRANDE_CITY_POKEMON_CENTER_1F),
        .map = MAP_NUM(EVER_GRANDE_CITY_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE - 1] =
    {
        .group = MAP_GROUP(LITTLEROOT_TOWN_BRENDANS_HOUSE_1F),
        .map = MAP_NUM(LITTLEROOT_TOWN_BRENDANS_HOUSE_1F),
        .x = 2,
        .y = 7,
    },
    [HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE - 1] =
    {
        .group = MAP_GROUP(LITTLEROOT_TOWN_MAYS_HOUSE_1F),
        .map = MAP_NUM(LITTLEROOT_TOWN_MAYS_HOUSE_1F),
        .x = 8,
        .y = 7,
    },
    [HEAL_LOCATION_OLDALE_TOWN - 1] =
    {
        .group = MAP_GROUP(OLDALE_TOWN_POKEMON_CENTER_1F),
        .map = MAP_NUM(OLDALE_TOWN_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_DEWFORD_TOWN - 1] =
    {
        .group = MAP_GROUP(DEWFORD_TOWN_POKEMON_CENTER_1F),
        .map = MAP_NUM(DEWFORD_TOWN_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_LAVARIDGE_TOWN - 1] =
    {
        .group = MAP_GROUP(LAVARIDGE_TOWN_POKEMON_CENTER_1F),
        .map = MAP_NUM(LAVARIDGE_TOWN_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_FALLARBOR_TOWN - 1] =
    {
        .group = MAP_GROUP(FALLARBOR_TOWN_POKEMON_CENTER_1F),
        .map = MAP_NUM(FALLARBOR_TOWN_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_VERDANTURF_TOWN - 1] =
    {
        .group = MAP_GROUP(VERDANTURF_TOWN_POKEMON_CENTER_1F),
        .map = MAP_NUM(VERDANTURF_TOWN_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_PACIFIDLOG_TOWN - 1] =
    {
        .group = MAP_GROUP(PACIFIDLOG_TOWN_POKEMON_CENTER_1F),
        .map = MAP_NUM(PACIFIDLOG_TOWN_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE - 1] =
    {
        .group = MAP_GROUP(EVER_GRANDE_CITY_POKEMON_LEAGUE_1F),
        .map = MAP_NUM(EVER_GRANDE_CITY_POKEMON_LEAGUE_1F),
        .x = 3,
        .y = 4,
    },
    [HEAL_LOCATION_SOUTHERN_ISLAND_EXTERIOR - 1] =
    {
        .group = MAP_GROUP(SOUTHERN_ISLAND_EXTERIOR),
        .map = MAP_NUM(SOUTHERN_ISLAND_EXTERIOR),
        .x = 15,
        .y = 20,
    },
    [HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST - 1] =
    {
        .group = MAP_GROUP(BATTLE_FRONTIER_POKEMON_CENTER_1F),
        .map = MAP_NUM(BATTLE_FRONTIER_POKEMON_CENTER_1F),
        DEFAULT_POKEMON_CENTER_COORDS,
    },
    [HEAL_LOCATION_ROUTE_101 - 1] =
    {
        .group = 0,
        .map = 16,
        .x = 5,
        .y = 10,
    },
    [HEAL_LOCATION_ROUTE_102 - 1] =     
    {
        .group = 0,
        .map = 17,
        .x = 40,
        .y = 10,
    }, 
    [HEAL_LOCATION_ROUTE_103 - 1] =     
    {
        .group = 0,
        .map = 18,
        .x = 11,
        .y = 10,
    }, 
    [HEAL_LOCATION_ROUTE_104 - 1] =     
    {
        .group = 0,
        .map = 19,
        .x = 17,
        .y = 51,
    }, 
    [HEAL_LOCATION_ROUTE_105 - 1] =     
    {
        .group = 0,
        .map = 20,
        .x = 15,
        .y = 58,
    }, 
    [HEAL_LOCATION_ROUTE_106 - 1] =     
    {
        .group = 0,
        .map = 21,
        .x = 59,
        .y = 14,
    }, 
    [HEAL_LOCATION_ROUTE_107 - 1] =     
    {
        .group = 0,
        .map = 22,
        .x = 3,
        .y = 11,
    }, 
    [HEAL_LOCATION_ROUTE_108 - 1] =     
    {
        .group = 0,
        .map = 23,
        .x = 29,
        .y = 6,
    }, 
    [HEAL_LOCATION_ROUTE_109 - 1] =     
    {
        .group = 0,
        .map = 24,
        .x = 12,
        .y = 6,
    }, 
    [HEAL_LOCATION_ROUTE_110 - 1] =     
    {
        .group = 0,
        .map = 25,
        .x = 11,
        .y = 67,
    }, 
    [HEAL_LOCATION_ROUTE_111 - 1] =     
    {
        .group = 0,
        .map = 26,
        .x = 26,
        .y = 19,
    }, 
    [HEAL_LOCATION_ROUTE_112 - 1] =     
    {
        .group = 0,
        .map = 27,
        .x = 22,
        .y = 38,
    }, 
    [HEAL_LOCATION_ROUTE_113 - 1] =     
    {
        .group = 0,
        .map = 28,
        .x = 33,
        .y = 6,
    }, 
    [HEAL_LOCATION_ROUTE_114 - 1] =     
    {
        .group = 0,
        .map = 29,
        .x = 22,
        .y = 37,
    }, 
    [HEAL_LOCATION_ROUTE_115 - 1] =     
    {
        .group = 0,
        .map = 30,
        .x = 16,
        .y = 65,
    }, 
    [HEAL_LOCATION_ROUTE_116 - 1] =     
    {
        .group = 0,
        .map = 31,
        .x = 36,
        .y = 10,
    }, 
    [HEAL_LOCATION_ROUTE_117 - 1] =     
    {
        .group = 0,
        .map = 32,
        .x = 51,
        .y = 6,
    }, 
    [HEAL_LOCATION_ROUTE_118 - 1] =     
    {
        .group = 0,
        .map = 33,
        .x = 13,
        .y = 7,
    }, 
    [HEAL_LOCATION_ROUTE_119 - 1] =     
    {
        .group = 0,
        .map = 34,
        .x = 6,
        .y = 33,
    }, 
    [HEAL_LOCATION_ROUTE_120 - 1] =     
    {
        .group = 0,
        .map = 35,
        .x = 27,
        .y = 4,
    }, 
    [HEAL_LOCATION_ROUTE_121 - 1] =     
    {
        .group = 0,
        .map = 36,
        .x = 37,
        .y = 6,
    }, 
    [HEAL_LOCATION_ROUTE_122 - 1] =     
    {
        .group = 0,
        .map = 37,
        .x = 22,
        .y = 30,
    }, 
    [HEAL_LOCATION_ROUTE_123 - 1] =     
    {
        .group = 0,
        .map = 38,
        .x = 22,
        .y = 7,
    }, 
    [HEAL_LOCATION_ROUTE_124 - 1] =     
    {
        .group = 0,
        .map = 39,
        .x = 70,
        .y = 49,
    }, 
    [HEAL_LOCATION_ROUTE_125 - 1] =     
    {
        .group = 0,
        .map = 40,
        .x = 22,
        .y = 20,
    }, 
    [HEAL_LOCATION_ROUTE_126 - 1] =    
    {
        .group = 0,
        .map = 41,
        .x = 44,
        .y = 69,
    }, 
    [HEAL_LOCATION_ROUTE_127 - 1] =     
    {
        .group = 0,
        .map = 42,
        .x = 45,
        .y = 25,
    }, 
    [HEAL_LOCATION_ROUTE_128 - 1] =     
    {
        .group = 0,
        .map = 43,
        .x = 40,
        .y = 22,
    }, 
    [HEAL_LOCATION_ROUTE_129 - 1] =     
    {
        .group = 0,
        .map = 44,
        .x = 42,
        .y = 20,
    }, 
    [HEAL_LOCATION_ROUTE_130 - 1] =     
    {
        .group = 0,
        .map = 45,
        .x = 20,
        .y = 25,
    }, 
    [HEAL_LOCATION_ROUTE_131 - 1] =     
    {
        .group = 0,
        .map = 46,
        .x = 35,
        .y = 27,
    }, 
    [HEAL_LOCATION_ROUTE_132 - 1] =     
    {
        .group = 0,
        .map = 47,
        .x = 27,
        .y = 25,
    }, 
    [HEAL_LOCATION_ROUTE_133 - 1] =     
    {
        .group = 0,
        .map = 48,
        .x = 41,
        .y = 16,
    }, 
    [HEAL_LOCATION_ROUTE_134 - 1] =     
    {
        .group = 0,
        .map = 49,
        .x = 77,
        .y = 29,
    }, 
    [HEAL_LOCATION_ROUTE_110_TOP - 1] =     
    {
        .group = 0,
        .map = 25,
        .x = 15,
        .y = 17,
    },
    [HEAL_LOCATION_ROUTE_104_TOP - 1] =     
    {
        .group = 0,
        .map = 19,
        .x = 5,
        .y = 19,
    },
    [HEAL_LOCATION_ROUTE_111_BOTTOM - 1] =     
    {
        .group = 0,
        .map = 26,
        .x = 31,
        .y = 114,
    }, 
    [HEAL_LOCATION_ROUTE_119_BOTTOM - 1] =     
    {
        .group = 0,
        .map = 34,
        .x = 33,
        .y = 110,
    }, 
    [HEAL_LOCATION_ROUTE_120_BOTTOM - 1] =     
    {
        .group = 0,
        .map = 35,
        .x = 38,
        .y = 89,
    },  
};

#undef DEFAULT_POKEMON_CENTER_COORDS

// localIds can be found in the generated events.inc file for the specific heal location map
// e.g. for OldaleTown_PokemonCenter1F/events.inc the following entry gets generated:
// object_event 1, OBJ_EVENT_GFX_NURSE, 7, 2, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, OldaleTown_PokemonCenter_1F_EventScript_Nurse, 0
// In this case the localId is 1.
static const u8 sHealNpcLocalId[HEAL_LOCATION_COUNT - 1] =
{
    [HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F - 1] = 1,
    [HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F - 1] = 1,
    [HEAL_LOCATION_PETALBURG_CITY - 1] = 1,
    [HEAL_LOCATION_SLATEPORT_CITY - 1] = 1,
    [HEAL_LOCATION_MAUVILLE_CITY - 1] = 1,
    [HEAL_LOCATION_RUSTBORO_CITY - 1] = 1,
    [HEAL_LOCATION_FORTREE_CITY - 1] = 1,
    [HEAL_LOCATION_LILYCOVE_CITY - 1] = 1,
    [HEAL_LOCATION_MOSSDEEP_CITY - 1] = 1,
    [HEAL_LOCATION_SOOTOPOLIS_CITY - 1] = 1,
    [HEAL_LOCATION_EVER_GRANDE_CITY - 1] = 1,
    [HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE - 1] = 1,
    [HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE - 1] = 1,
    [HEAL_LOCATION_OLDALE_TOWN - 1] = 1,
    [HEAL_LOCATION_DEWFORD_TOWN - 1] = 1,
    [HEAL_LOCATION_LAVARIDGE_TOWN - 1] = 1,
    [HEAL_LOCATION_FALLARBOR_TOWN - 1] = 1,
    [HEAL_LOCATION_VERDANTURF_TOWN - 1] = 1,
    [HEAL_LOCATION_PACIFIDLOG_TOWN - 1] = 1,
    [HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE - 1] = 1,
    [HEAL_LOCATION_SOUTHERN_ISLAND_EXTERIOR - 1] = 0, // no heal npc
    [HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST - 1] = 1,
    [HEAL_LOCATION_ROUTE_101 - 1] = 0,
    [HEAL_LOCATION_ROUTE_102 - 1] = 0,
    [HEAL_LOCATION_ROUTE_103 - 1] = 0,
    [HEAL_LOCATION_ROUTE_104 - 1] = 0,
    [HEAL_LOCATION_ROUTE_105 - 1] = 0,
    [HEAL_LOCATION_ROUTE_106 - 1] = 0,
    [HEAL_LOCATION_ROUTE_107 - 1] = 0,
    [HEAL_LOCATION_ROUTE_108 - 1] = 0,
    [HEAL_LOCATION_ROUTE_109 - 1] = 0,
    [HEAL_LOCATION_ROUTE_110 - 1] = 0,
    [HEAL_LOCATION_ROUTE_111 - 1] = 0,
    [HEAL_LOCATION_ROUTE_112 - 1] = 0,
    [HEAL_LOCATION_ROUTE_113 - 1] = 0,
    [HEAL_LOCATION_ROUTE_114 - 1] = 0,
    [HEAL_LOCATION_ROUTE_115 - 1] = 0,
    [HEAL_LOCATION_ROUTE_116 - 1] = 0,
    [HEAL_LOCATION_ROUTE_117 - 1] = 0,
    [HEAL_LOCATION_ROUTE_118 - 1] = 0,
    [HEAL_LOCATION_ROUTE_119 - 1] = 0,
    [HEAL_LOCATION_ROUTE_120 - 1] = 0,
    [HEAL_LOCATION_ROUTE_121 - 1] = 0,
    [HEAL_LOCATION_ROUTE_122 - 1] = 0,
    [HEAL_LOCATION_ROUTE_123 - 1] = 0,
    [HEAL_LOCATION_ROUTE_124 - 1] = 0,
    [HEAL_LOCATION_ROUTE_125 - 1] = 0,
    [HEAL_LOCATION_ROUTE_126 - 1] = 0,
    [HEAL_LOCATION_ROUTE_127 - 1] = 0,
    [HEAL_LOCATION_ROUTE_128 - 1] = 0,
    [HEAL_LOCATION_ROUTE_129 - 1] = 0,
    [HEAL_LOCATION_ROUTE_130 - 1] = 0,
    [HEAL_LOCATION_ROUTE_131 - 1] = 0,
    [HEAL_LOCATION_ROUTE_132 - 1] = 0,
    [HEAL_LOCATION_ROUTE_133 - 1] = 0,
    [HEAL_LOCATION_ROUTE_134 - 1] = 0,
    [HEAL_LOCATION_ROUTE_110_TOP - 1] = 0,
    [HEAL_LOCATION_ROUTE_104_TOP - 1] = 0,
    [HEAL_LOCATION_ROUTE_111_BOTTOM - 1] = 0,
    [HEAL_LOCATION_ROUTE_119_BOTTOM - 1] = 0,
    [HEAL_LOCATION_ROUTE_120_BOTTOM - 1] = 0,
};
