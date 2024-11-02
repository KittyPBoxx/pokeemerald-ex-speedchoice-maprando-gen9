#include "random_warps.h"
#include "global.h"
#include "event_data.h"
#include "constants/vars.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "item.h"
#include "string_util.h"

struct WarpRemap
{
    s8 fromMapGroup;
    s8 fromMapNum;
    s8 fromWarpId;

    s8 toMapGroup;
    s8 toMapNum;
    s8 toWarpId;
};

// Values in this block with be overwritten by the randomizer
// By default a random set of values is defined in case the user decides to switch on the settings
const struct WarpRemap gWarpRemappingList[RANDOM_WARP_LIMIT] = 
{
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {-1,-1,-1,0,0,0},
    {0,0,1,24,43,0},
    {0,0,2,0,11,4},
    {0,0,3,0,31,1},
    {0,0,5,5,4,0},
    {0,1,0,0,13,4},
    {0,1,1,24,57,2},
    {0,1,2,24,56,3},
    {0,1,4,15,2,2},
    {0,1,5,12,1,0},
    {0,1,7,12,1,0},
    {0,1,8,24,18,1},
    {0,2,0,24,24,4},
    {0,2,1,0,5,7},
    {0,2,2,3,1,2},
    {0,2,3,24,24,22},
    {0,2,4,0,27,0},
    {0,3,0,0,7,1},
    {0,3,1,24,68,0},
    {0,3,2,13,6,2},
    {0,3,3,0,19,4},
    {0,3,5,24,15,1},
    {0,3,6,24,15,1},
    {0,3,8,0,1,3},
    {0,3,10,0,10,2},
    {0,4,0,0,5,4},
    {0,4,2,9,7,0},
    {0,4,3,0,4,2},
    {0,4,6,24,79,2},
    {0,5,0,24,55,6},
    {0,5,1,0,7,11},
    {0,5,2,0,27,5},
    {0,5,4,24,24,3},
    {0,5,6,14,9,0},
    {0,5,12,24,54,4},
    {0,6,1,24,56,0},
    {0,6,2,13,4,2},
    {0,6,4,0,13,3},
    {0,6,6,0,1,0},
    {0,6,8,24,23,0},
    {0,7,0,0,38,0},
    {0,7,1,2,2,2},
    {0,7,2,0,28,0},
    {0,7,3,13,17,0},
    {0,7,11,0,8,3},
    {0,8,0,24,94,1},
    {0,8,1,0,5,5},
    {0,8,2,8,0,0},
    {0,8,3,0,0,1},
    {0,10,2,0,27,2},
    {0,11,1,0,1,2},
    {0,11,2,0,34,1},
    {0,12,0,0,2,5},
    {0,12,1,0,1,1},
    {0,12,2,0,5,3},
    {0,12,3,24,24,21},
    {0,12,5,0,15,5},
    {0,13,0,0,24,0},
    {0,13,2,8,6,0},
    {0,14,1,0,5,1},
    {0,14,2,24,85,0},
    {0,14,4,24,24,1},
    {0,15,0,12,2,2},
    {0,19,0,0,4,6},
    {0,19,2,24,17,0},
    {0,19,3,24,17,0},
    {0,19,4,0,6,1},
    {0,19,5,0,6,1},
    {0,19,6,9,7,2},
    {0,19,7,9,7,2},
    {0,20,0,24,9,1},
    {0,21,0,24,25,8},
    {0,23,0,0,3,8},
    {0,25,0,24,28,1},
    {0,25,2,0,15,2},
    {0,25,3,24,37,1},
    {0,25,4,26,66,1},
    {0,25,5,0,39,0},
    {0,26,1,0,3,0},
    {0,26,3,0,7,0},
    {0,27,0,24,91,0},
    {0,27,1,24,91,0},
    {0,27,2,26,74,1},
    {0,27,3,26,74,1},
    {0,27,4,24,44,4},
    {0,27,5,0,0,4},
    {0,29,0,24,82,0},
    {0,29,1,24,24,2},
    {0,30,0,0,3,1},
    {0,31,0,0,32,0},
    {0,31,2,24,44,2},
    {0,34,0,26,68,0},
    {0,35,0,11,8,0},
    {0,37,0,24,1,3},
    {0,46,0,24,68,1},
    {2,0,0,24,77,1},
    {2,1,0,24,55,11},
    {2,2,0,11,13,0},
    {2,3,0,15,4,0},
    {2,4,0,24,95,0},
    {3,0,0,0,12,0},
    {3,1,0,24,31,0},
    {3,2,0,10,1,0},
    {3,3,0,0,25,0},
    {3,4,0,11,5,2},
    {3,5,0,8,1,0},
    {4,0,0,0,11,3},
    {4,1,0,24,55,4},
    {4,3,0,24,2,1},
    {4,4,0,0,7,10},
    {4,5,0,5,4,2},
    {4,5,3,24,29,1},
    {4,6,0,24,92,0},
    {5,0,0,24,44,5},
    {5,1,0,0,30,0},
    {5,4,0,24,8,4},
    {5,5,0,0,12,3},
    {5,6,0,14,5,0},
    {5,7,0,9,11,0},
    {6,0,0,24,62,2},
    {6,3,0,24,18,4},
    {6,4,0,24,96,0},
    {6,5,0,11,14,0},
    {6,6,0,24,43,3},
    {6,7,0,16,0,0},
    {6,8,0,16,3,0},
    {7,0,0,24,34,0},
    {7,1,0,0,15,1},
    {7,2,0,7,0,2},
    {7,3,0,29,12,0},
    {7,4,0,9,11,2},
    {7,5,0,24,10,0},
    {7,6,0,4,5,3},
    {8,0,0,24,43,1},
    {8,1,0,13,19,1},
    {8,2,0,0,7,9},
    {8,3,0,24,14,1},
    {8,4,0,0,27,4},
    {8,5,0,16,4,0},
    {8,6,0,24,24,10},
    {9,0,0,3,1,0},
    {9,0,2,24,2,3},
    {9,1,0,13,18,0},
    {9,2,0,11,11,0},
    {9,5,0,24,25,6},
    {9,6,0,24,89,1},
    {9,7,0,24,103,0},
    {9,7,1,24,103,0},
    {9,8,0,24,11,4},
    {9,9,0,24,35,1},
    {9,10,0,24,28,0},
    {9,11,0,14,7,0},
    {9,12,0,0,15,3},
    {9,13,0,4,1,0},
    {10,0,0,24,63,0},
    {10,1,0,0,40,0},
    {10,2,0,24,0,3},
    {10,3,0,4,0,0},
    {10,4,0,24,6,2},
    {10,5,0,24,45,3},
    {10,6,0,0,26,4},
    {10,7,0,24,82,1},
    {11,0,0,24,21,0},
    {11,0,1,24,21,0},
    {11,0,2,24,31,3},
    {11,1,0,0,8,2},
    {11,1,1,24,84,0},
    {11,2,0,24,87,0},
    {11,3,0,24,6,0},
    {11,4,0,24,43,4},
    {11,5,0,24,24,14},
    {11,6,0,0,11,0},
    {11,7,0,13,5,1},
    {11,8,0,24,0,1},
    {11,9,0,11,13,2},
    {11,10,0,24,16,0},
    {11,11,0,24,54,0},
    {11,12,0,24,59,0},
    {11,13,0,24,45,1},
    {11,13,2,6,4,2},
    {11,14,0,11,8,2},
    {11,15,0,24,81,1},
    {11,16,0,24,91,1},
    {12,0,0,26,57,0},
    {12,1,0,12,4,0},
    {12,2,0,0,7,4},
    {12,3,0,7,0,0},
    {12,4,0,0,29,1},
    {12,5,0,24,45,2},
    {12,6,0,24,57,4},
    {12,7,0,17,0,0},
    {12,8,0,24,12,0},
    {12,9,0,24,42,0},
    {13,0,0,6,3,0},
    {13,1,0,24,88,1},
    {13,2,0,4,4,0},
    {13,2,1,4,4,0},
    {13,4,0,12,2,0},
    {13,4,2,0,25,5},
    {13,4,3,0,3,2},
    {13,5,0,14,3,0},
    {13,5,1,0,6,6},
    {13,6,0,16,2,0},
    {13,7,0,11,7,0},
    {13,9,1,16,12,0},
    {13,10,0,0,19,6},
    {13,11,0,10,5,0},
    {13,12,0,24,34,1},
    {13,13,0,0,35,1},
    {13,14,0,16,10,2},
    {13,15,0,0,25,2},
    {13,16,0,0,35,0},
    {13,16,2,24,37,0},
    {13,17,0,24,88,0},
    {13,17,1,9,0,2},
    {13,18,0,0,8,0},
    {13,18,1,24,80,0},
    {13,19,0,24,6,1},
    {13,19,1,24,57,5},
    {13,20,0,0,0,2},
    {13,21,0,0,6,0},
    {14,0,0,24,11,2},
    {14,1,0,13,20,2},
    {14,2,0,24,84,1},
    {14,3,0,24,68,2},
    {14,4,0,16,1,0},
    {14,5,0,24,24,19},
    {14,6,0,0,7,2},
    {14,7,0,13,4,3},
    {14,8,1,24,18,0},
    {14,9,0,26,66,0},
    {14,10,0,24,21,1},
    {14,11,0,26,69,0},
    {15,0,0,0,6,5},
    {15,2,0,24,94,0},
    {15,3,0,9,6,0},
    {15,4,0,11,3,0},
    {15,5,0,0,4,0},
    {15,6,0,24,54,3},
    {15,7,0,24,9,3},
    {15,8,0,24,7,1},
    {15,9,0,32,1,0},
    {15,10,0,0,0,0},
    {15,11,0,0,12,2},
    {15,12,0,13,0,0},
    {15,13,0,24,8,0},
    {16,5,0,24,30,1},
    {16,5,1,14,3,2},
    {16,6,0,24,15,4},
    {16,6,1,0,5,2},
    {16,7,0,24,87,2},
    {16,7,1,0,14,6},
    {16,8,0,24,17,4},
    {16,8,1,8,4,2},
    {16,9,0,0,5,10},
    {16,9,1,0,14,5},
    {16,10,0,13,17,1},
    {16,12,0,24,24,8},
    {16,13,0,24,8,2},
    {16,14,0,24,20,0},
    {17,0,0,0,25,1},
    {17,1,0,24,25,9},
    {18,0,0,0,7,13},
    {18,1,0,0,20,0},
    {19,0,0,10,2,0},
    {19,0,1,10,2,0},
    {19,1,0,0,4,7},
    {19,1,1,0,4,7},
    {20,0,0,0,4,3},
    {20,1,0,24,67,2},
    {20,2,0,24,29,2},
    {21,0,0,8,4,0},
    {22,0,0,24,4,0},
    {23,0,2,24,0,5},
    {24,0,0,24,44,3},
    {24,0,1,0,13,1},
    {24,0,2,24,19,3},
    {24,0,3,24,45,0},
    {24,0,4,26,69,1},
    {24,0,5,0,5,6},
    {24,1,0,0,37,0},
    {24,1,1,24,23,2},
    {24,1,2,0,12,4},
    {24,1,3,0,19,2},
    {24,2,0,24,59,2},
    {24,2,1,26,74,0},
    {24,2,2,24,15,0},
    {24,2,4,0,2,4},
    {24,2,5,0,26,1},
    {24,3,0,9,1,0},
    {24,4,0,24,24,5},
    {24,4,1,24,24,11},
    {24,6,0,24,0,4},
    {24,6,1,0,2,6},
    {24,6,2,13,18,1},
    {24,7,0,24,44,1},
    {24,7,1,0,7,12},
    {24,7,2,24,55,0},
    {24,7,3,0,15,4},
    {24,8,0,0,7,7},
    {24,8,1,26,68,1},
    {24,8,2,24,57,7},
    {24,8,3,24,67,0},
    {24,8,4,26,70,0},
    {24,8,5,0,7,6},
    {24,9,0,16,12,2},
    {24,9,1,26,70,1},
    {24,9,2,0,13,2},
    {24,9,3,24,24,6},
    {24,9,4,24,89,2},
    {24,10,0,24,86,3},
    {24,11,0,24,2,2},
    {24,11,1,24,2,2},
    {24,11,2,11,5,0},
    {24,11,3,11,5,0},
    {24,11,4,0,5,12},
    {24,11,5,0,5,12},
    {24,12,0,24,44,6},
    {24,12,1,24,44,6},
    {24,12,2,29,1,1},
    {24,12,3,29,1,1},
    {24,13,0,2,2,0},
    {24,13,1,2,2,0},
    {24,13,2,24,55,10},
    {24,13,3,24,55,10},
    {24,13,4,24,13,4},
    {24,14,0,0,0,3},
    {24,14,1,13,6,0},
    {24,15,0,24,0,2},
    {24,15,1,0,3,5},
    {24,15,4,0,3,7},
    {24,15,5,24,93,0},
    {24,16,0,16,1,1},
    {24,16,1,24,11,0},
    {24,16,2,16,3,1},
    {24,17,0,24,81,2},
    {24,17,1,9,9,0},
    {24,17,2,0,14,1},
    {24,18,0,24,89,0},
    {24,18,1,24,55,2},
    {24,18,2,24,1,0},
    {24,18,3,24,24,15},
    {24,19,0,16,10,4},
    {24,19,1,0,6,7},
    {24,19,2,24,57,3},
    {24,20,0,24,78,0},
    {24,21,0,11,0,0},
    {24,21,1,24,56,4},
    {24,22,1,14,9,2},
    {24,23,0,24,107,0},
    {24,23,2,24,78,1},
    {24,24,0,24,2,0},
    {24,24,1,24,35,0},
    {24,24,2,24,43,2},
    {24,24,3,24,44,0},
    {24,24,5,0,8,1},
    {24,24,6,0,0,5},
    {24,24,7,10,0,0},
    {24,24,8,0,31,0},
    {24,24,9,29,1,0},
    {24,24,10,24,8,5},
    {24,24,11,10,7,0},
    {24,24,12,24,24,13},
    {24,24,13,24,57,0},
    {24,24,15,24,92,1},
    {24,24,16,24,19,4},
    {24,24,17,24,86,1},
    {24,24,18,24,24,9},
    {24,24,19,24,87,1},
    {24,24,20,24,25,4},
    {24,24,22,0,14,4},
    {24,24,24,0,6,4},
    {24,24,50,24,55,9},
    {24,24,51,4,5,0},
    {24,24,52,0,3,3},
    {24,24,53,0,19,1},
    {24,25,0,24,4,1},
    {24,25,1,20,0,0},
    {24,25,2,13,4,0},
    {24,25,3,24,55,5},
    {24,25,4,24,7,0},
    {24,25,5,24,80,1},
    {24,25,7,0,1,6},
    {24,25,8,24,24,17},
    {24,27,1,0,1,10},
    {24,27,50,11,1,0},
    {24,28,2,26,58,0},
    {24,29,0,24,55,7},
    {24,29,1,0,11,1},
    {24,29,3,0,15,0},
    {24,30,0,0,1,8},
    {24,30,1,0,5,8},
    {24,31,0,0,12,5},
    {24,32,0,24,52,0},
    {24,32,1,0,25,3},
    {24,32,2,24,30,2},
    {24,33,0,0,29,2},
    {24,33,1,24,31,2},
    {24,34,0,24,30,0},
    {24,34,1,16,0,1},
    {24,35,1,24,29,3},
    {24,36,0,24,25,0},
    {24,37,0,0,34,0},
    {24,38,0,29,12,2},
    {24,38,1,0,4,8},
    {24,39,1,0,26,0},
    {24,43,0,11,0,2},
    {24,43,1,15,12,0},
    {24,43,2,0,13,0},
    {24,43,3,24,4,2},
    {24,43,4,24,14,0},
    {24,44,0,24,2,4},
    {24,44,1,0,4,4},
    {24,44,2,0,14,3},
    {24,44,3,0,3,10},
    {24,44,4,0,3,4},
    {24,44,5,24,25,1},
    {24,44,6,0,2,1},
    {24,45,0,24,25,2},
    {24,45,1,0,29,0},
    {24,45,2,0,21,0},
    {24,45,3,19,1,0},
    {24,46,0,0,2,2},
    {24,52,0,0,11,2},
    {24,53,0,24,95,1},
    {24,54,0,0,46,0},
    {24,54,2,24,8,1},
    {24,54,3,24,17,1},
    {24,54,4,0,2,0},
    {24,55,1,26,87,0},
    {24,55,2,0,7,5},
    {24,55,4,14,0,0},
    {24,55,5,9,0,0},
    {24,55,7,24,22,1},
    {24,55,8,24,55,8},
    {24,55,9,24,9,0},
    {24,55,10,32,0,2},
    {24,55,11,0,14,0},
    {24,56,0,0,12,1},
    {24,56,2,13,16,0},
    {24,56,3,24,25,5},
    {24,56,4,24,28,2},
    {24,57,0,24,1,1},
    {24,57,1,0,3,9},
    {24,57,6,24,12,2},
    {24,57,7,24,24,23},
    {24,58,0,9,13,0},
    {24,58,1,24,20,1},
    {24,58,2,0,4,5},
    {24,59,0,24,93,1},
    {24,59,2,24,24,18},
    {24,61,0,13,20,0},
    {24,62,0,24,62,0},
    {24,62,2,0,10,1},
    {24,63,0,13,10,0},
    {24,67,0,0,26,2},
    {24,67,1,20,0,2},
    {24,67,2,24,81,0},
    {24,68,0,0,5,0},
    {24,68,1,0,6,2},
    {24,68,2,24,77,0},
    {24,73,0,0,5,9},
    {24,77,0,0,23,0},
    {24,77,1,24,19,0},
    {24,78,0,0,10,0},
    {24,78,1,26,70,2},
    {24,79,0,24,24,0},
    {24,79,2,13,19,0},
    {24,80,0,12,7,0},
    {24,80,1,24,67,1},
    {24,81,0,24,25,3},
    {24,81,1,24,0,0},
    {24,81,2,0,2,3},
    {24,82,0,11,14,1},
    {24,82,1,24,16,1},
    {24,82,2,11,2,0},
    {24,84,0,24,96,1},
    {24,84,1,6,4,0},
    {24,85,0,0,6,3},
    {24,86,0,24,86,0},
    {24,86,1,24,24,24},
    {24,86,2,13,0,2},
    {24,86,3,24,16,4},
    {24,87,0,13,16,2},
    {24,87,1,24,24,20},
    {24,87,2,24,8,6},
    {24,88,0,11,1,1},
    {24,89,0,19,0,0},
    {24,89,2,16,2,1},
    {24,90,0,0,1,4},
    {24,91,0,24,19,1},
    {24,91,1,24,24,16},
    {24,92,0,24,57,1},
    {24,92,1,0,3,11},
    {24,93,0,24,7,3},
    {24,93,1,4,5,2},
    {24,94,0,26,75,0},
    {24,94,1,24,52,1},
    {24,95,0,0,14,2},
    {24,95,1,16,10,0},
    {24,96,0,0,10,3},
    {24,97,0,24,82,2},
    {24,102,0,0,1,5},
    {24,104,1,0,25,4},
    {24,107,0,0,36,0},
    {26,56,0,0,4,1},
    {26,56,1,0,4,1},
    {26,59,0,24,29,0},
    {26,60,0,10,5,2},
    {26,66,1,24,7,2},
    {26,67,0,0,6,8},
    {26,68,0,0,6,9},
    {26,68,1,29,11,0},
    {26,69,0,32,0,0},
    {26,69,1,24,8,3},
    {26,70,1,24,2,5},
    {26,71,0,24,9,2},
    {26,73,1,24,1,2},
    {26,74,1,0,26,3},
    {26,75,0,24,13,0},
    {26,76,0,24,79,0},
    {26,86,0,24,54,2},
    {28,0,0,5,0,0},
    {29,0,0,0,19,0},
    {29,2,0,24,13,2},
    {29,3,2,24,24,12},
    {29,11,0,24,105,0},
    {29,11,2,13,5,0},
    {29,12,0,0,5,11},
    {29,12,2,24,31,1},
    {30,0,0,15,0,0},
    {31,0,0,15,2,0},
    {32,0,0,0,7,3},
    {32,0,2,0,7,8},
    {32,1,0,24,57,6},
    {32,2,0,3,3,0},
    {33,0,0,29,11,2}
};

// Variables in ram
// For positive values this will set the player coords after warp
// If the value is -1 player position will be set normally
// If xPostionCorrection -2 it will use the normal position -1
s8 xPositionCorrection;
s8 yPositionCorrection;

// s8 WarpRemapCompare(s8 *mapGroup, s8 *mapNum, s8 *warpId, struct WarpRemap comparison) 
// {
//     if ((*mapGroup) < comparison.fromMapGroup) 
//     {
//         return -1;
//     } 
//     else if ((*mapGroup) > comparison.fromMapGroup)
//     {
//         return 1;
//     }

//     if ((*mapNum) < comparison.fromMapNum) 
//     {
//         return -1;
//     } 
//     else if ((*mapNum) > comparison.fromMapNum)
//     {
//         return 1;
//     }

//     if ((*warpId) < comparison.fromWarpId) 
//     {
//         return -1;
//     } 
//     else if ((*warpId) > comparison.fromWarpId)
//     {
//         return 1;
//     }

//     return 0;
// }

u16 WarpRemapBinarySearch(s8 *mapGroup, s8 *mapNum, s8 *warpId) 
{
    // u16 high = RANDOM_WARP_LIMIT_SEARCH_HIGH;
    // u16 low  = RANDOM_WARP_LIMIT_SEARCH_LOW;
    u16 i = 0;
    u16 matchCount = 0;
    u16 index;

    // while (low <= high) 
    // {
    //     int mid = low + (high - low) / 2;

    //     int comparison = WarpRemapCompare(mapGroup, mapNum, warpId, gWarpRemappingList[mid]);
        
    //     if (comparison == 0) {
    //         return mid;
    //     } else if (comparison < 0) {
    //         high = mid - 1;
    //     } else {
    //         low = mid + 1;
    //     }
    // }

    // I don't see an issue in the binary search, so this should be nessacery. However sometimes it seems to get weird issues. I can't see an issume looking at the warp tables binary data, so I assume in this 'bad' code we're dodging compiler optimisations...
    // The match count is pretty stupid but at least it should make the check script fail
    for (i = 0; i < RANDOM_WARP_LIMIT; i++) {
        if ((*mapGroup) == gWarpRemappingList[i].fromMapGroup && (*mapNum) == gWarpRemappingList[i].fromMapNum && (*warpId) == gWarpRemappingList[i].fromWarpId) {
            index = i;
            matchCount++;
        } 
    }

    if (matchCount == 1) {
        return index;
    }

    return RANDOM_WARP_LIMIT;
}

void ApplyFixesForSpecialWarps(s8 *mapGroup, s8 *mapNum, s8 *warpId)
{
    if ((*mapGroup) == 8 && (*mapNum) == 1 && (*warpId) == 0) 
    {
        // If left of Petalburg is locked we start catch tutorial
        // otherwise we set to battle state so it can be started immediately
        if (VarGet(VAR_PETALBURG_CITY_STATE) < 1) 
        {
            VarSet(VAR_PETALBURG_GYM_STATE, 0);
        } 
        else 
        {
            VarSet(VAR_PETALBURG_GYM_STATE, 6);
        }

        // Unlock left of petalburg
        VarSet(VAR_PETALBURG_CITY_STATE, 1);

    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 0 && (*warpId) == 0) 
    {
        // E4 rooms needs to walk fowards when entering from front
        // But not if we enter from the back
        VarSet(VAR_ELITE_4_STATE, 0);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 0 && (*warpId) == 1)  
    {
        VarSet(VAR_ELITE_4_STATE, 1);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 1 && (*warpId) == 0) 
    {
        VarSet(VAR_ELITE_4_STATE, 1);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 1 && (*warpId) == 1) 
    {
        VarSet(VAR_ELITE_4_STATE, 2);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 2 && (*warpId) == 0) 
    {
        VarSet(VAR_ELITE_4_STATE, 2);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 2 && (*warpId) == 1) 
    {
        VarSet(VAR_ELITE_4_STATE, 3);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 3 && (*warpId) == 0) 
    {
        VarSet(VAR_ELITE_4_STATE, 3);
    } 
    else if ((*mapGroup) == 16 && (*mapNum) == 3 && (*warpId) == 1) 
    {
        VarSet(VAR_ELITE_4_STATE, 4);
    } 
    else  if ((*mapGroup) == 10 && (*mapNum) == 0 && (*warpId) == 0) 
    {
        // Make sure wattson is always in the gym
        FlagClear(FLAG_HIDE_MAUVILLE_GYM_WATTSON);
    } 
    else if (((*mapGroup) == 29 && (*mapNum) == 1 && (*warpId) == 0) || 
             ((*mapGroup) == 29 && (*mapNum) == 1 && (*warpId) == 1))
    {
        // Make Sure the trick master won't crash the game
        // If we enter after collecting tent he will give the tent again
        if (VarGet(VAR_TRICK_HOUSE_LEVEL) > 7) 
        {
            VarSet(VAR_TRICK_HOUSE_LEVEL, 7);
        }
    } 
    else if ((*mapGroup) == 14 && (*mapNum) == 7 && (*warpId) == 0) 
    {
        // Make sure steven gives tickets and dive when we enter his house
        if (VarGet(VAR_STEVENS_HOUSE_STATE) == 0) 
        {
            VarSet(VAR_STEVENS_HOUSE_STATE, 1);
            FlagClear(FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_STEVEN);
        }
    }
    else if ((*mapGroup) == 24 && (*mapNum) == 67 && (*warpId) == 1) 
    {
        FlagSet(FLAG_SYS_BRAILLE_REGICE_COMPLETED);
    }
    else if ((*mapGroup) == 24 && (*mapNum) == 68 && (*warpId) == 1) 
    {
        FlagSet(FLAG_SYS_REGISTEEL_PUZZLE_COMPLETED);
    }
    else if ((*mapGroup) == 24 && (*mapNum) == 6 && (*warpId) == 1) 
    {
        FlagSet(FLAG_SYS_REGIROCK_PUZZLE_COMPLETED);
    }
    else if ((*mapGroup) == 24 && (*mapNum) == 52 && (*warpId) == 1) 
    {
        VarSet(VAR_NEW_MAUVILLE_STATE, 1);
    }
    else if ((*mapGroup) == 24 && (*mapNum) == 13 && (*warpId) == 4) 
    {
        VarSet(VAR_JAGGED_PASS_STATE, 2);
    }
    else if ((*mapGroup) == 24 && (*mapNum) == 57 && (*warpId) == 5) 
    {
        FlagSet(FLAG_USED_STORAGE_KEY);
    }
    else if ((*mapGroup) == 24 && (*mapNum) == 78 && (*warpId) == 1) 
    {
        FlagSet(FLAG_WALLACE_GOES_TO_SKY_PILLAR);
    }
}

void ApplyFixesForEveryWarp()
{
    // Open regi doors
    FlagSet(FLAG_REGI_DOORS_OPENED);

    // Not On Bike Path
    FlagClear(FLAG_SYS_CYCLING_ROAD);

    // Open Sootopolis Gym Door
    FlagSet(FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE);

    // Sootopolis always in nice state
    // We need to prevent locked doors, people standing around and lilycove dept roof being locked off
    VarSet(VAR_SOOTOPOLIS_CITY_STATE, 0);
    FlagSet(FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN);

    // RAYQUAZA always available
    VarSet(VAR_SKY_PILLAR_RAYQUAZA_CRY_DONE, 0);
    FlagClear(FLAG_HIDE_SKY_PILLAR_TOP_RAYQUAZA_STILL);

    // Show steven on the bridge if we don't have the devon scope
    if (FlagGet(FLAG_RECEIVED_DEVON_SCOPE)) 
    {
        FlagSet(FLAG_HIDE_ROUTE_120_STEVEN);
    } 
    else 
    {
        FlagClear(FLAG_HIDE_ROUTE_120_STEVEN);
    }
    
    // Make sure the magma embelem can always be got
    if (CheckBagHasItem(ITEM_MAGMA_EMBLEM, 1)) 
    {
        // Hide Jagged Pass Magma guard if we have magma emblem
        FlagSet(FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD);
    } 
    else 
    {
        VarSet(VAR_MT_PYRE_STATE, 0);
    }

    // Unblock Tunnlers rest house 
    FlagSet(FLAG_RECOVERED_DEVON_GOODS);

    // Unblock Devon corp f1
    FlagSet(FLAG_RETURNED_DEVON_GOODS);

    // Hide Steven and wallace in sootopolis
    FlagSet(FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN);
    FlagSet(FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE);

    // Hide the old man blocking the cave of origin
    FlagSet(FLAG_HIDE_SOOTOPOLIS_CITY_OLD_MAN_EXPERT);

    // Make sure sootopolis dosn't get blocked
    FlagSet(FLAG_HIDE_SOOTOPOLIS_CITY_ARCHIE);
    FlagSet(FLAG_HIDE_SOOTOPOLIS_CITY_MAXIE);
    FlagSet(FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS);
    FlagSet(FLAG_SOOTOPOLIS_ARCHIE_MAXIE_LEAVE);
    FlagClear(FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE);

    // Unhide man from the top of sootopolice
    // We patched him to give waterfall, dress like wallace and stand in front of the gym
    FlagClear(FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1);

    // Remove the brigde Kecleon so we can ride up from lilycove
    FlagSet(FLAG_HIDE_ROUTE_120_KECLEON_BRIDGE);

    // Also remove this kecleon so you don't softlock surfing up from scorched slab
    FlagSet(FLAG_HIDE_ROUTE_120_KECLEON_1);

    // Change Slateport state to 0 (to work around a glitch where game loops exiting the pokecenter)
    // This was needed for the IodineGBA scripted version it might not be needed in the rom hack
    VarSet(VAR_SLATEPORT_CITY_STATE, 0);

    // Remove Team Aqua from slateport and above slateport
    FlagSet(FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA);
    FlagSet(FLAG_HIDE_ROUTE_110_TEAM_AQUA);

    // Hide aqua on weather institute bridge
    FlagSet(FLAG_HIDE_ROUTE_119_TEAM_AQUA);

    // Hide magma on f1 of the space center
    FlagSet(FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA);

    // Hide grunts in aqua hideout enterance
    FlagSet(FLAG_HIDE_AQUA_HIDEOUT_1F_GRUNT_2_BLOCKING_ENTRANCE);
    FlagSet(FLAG_HIDE_AQUA_HIDEOUT_1F_GRUNT_1_BLOCKING_ENTRANCE);

    // Hide magma grunts blocking the cable car
    FlagSet(FLAG_HIDE_ROUTE_112_TEAM_MAGMA);

}

bool8 warpNeedsXOffetShift(s8 *mapGroup, s8 *mapNum, s8 *warpId)
{
    // For warps where we need to shift the x offset to correct it (e.g when going via an escalator)
    if ((*mapGroup) == 8  && (*mapNum) == 5  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 9  && (*mapNum) == 12 && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 10 && (*mapNum) == 6  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 11 && (*mapNum) == 6  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 12 && (*mapNum) == 3  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 13 && (*mapNum) == 7  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 14 && (*mapNum) == 4  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 15 && (*mapNum) == 3  && (*warpId) == 0) { return TRUE; }  
    if ((*mapGroup) == 16 && (*mapNum) == 13 && (*warpId) == 0) { return TRUE; } 
    if ((*mapGroup) == 16 && (*mapNum) == 14 && (*warpId) == 0) { return TRUE; } 
    if ((*mapGroup) == 2  && (*mapNum) == 3  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 3  && (*mapNum) == 2  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 4  && (*mapNum) == 6  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 5  && (*mapNum) == 5  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 6  && (*mapNum) == 5  && (*warpId) == 0) { return TRUE; }   
    if ((*mapGroup) == 7  && (*mapNum) == 1  && (*warpId) == 0) { return TRUE; }   

    return FALSE;
}

void fixPositionAfterWarp(s8 *mapGroup, s8 *mapNum, s8 *warpId, s8 *x, s8 *y)
{
    // For warps where we need to make sure we end up in the right position after the warp

    if ((*mapGroup) == 0) 
    {
        if ((*mapNum) == 1  && (*warpId) == 5 ) { xPositionCorrection = 0x1E; yPositionCorrection = 0x1B; return;}
        if ((*mapNum) == 5  && (*warpId) == 0 ) { xPositionCorrection = 0x1B; yPositionCorrection = 0x07; return;}
        if ((*mapNum) == 2  && (*warpId) == 0 ) { xPositionCorrection = 0x08; yPositionCorrection = 0x06; return;}
        if ((*mapNum) == 7  && (*warpId) == 5 ) { xPositionCorrection = 0x2D; yPositionCorrection = 0x07; return;}
        if ((*mapNum) == 7  && (*warpId) == 9 ) { xPositionCorrection = 0x35; yPositionCorrection = 0x1D; return;}
        if ((*mapNum) == 7  && (*warpId) == 4 ) { xPositionCorrection = 0x09; yPositionCorrection = 0x07; return;}
        if ((*mapNum) == 8  && (*warpId) == 2 ) { xPositionCorrection = 0x12; yPositionCorrection = 0x2A; return;}
        if ((*mapNum) == 11 && (*warpId) == 3 ) { xPositionCorrection = 0x11; yPositionCorrection = 0x0E; return;}
        if ((*mapNum) == 12 && (*warpId) == 5 ) { xPositionCorrection = 0x09; yPositionCorrection = 0x02; return;}
        if ((*mapNum) == 14 && (*warpId) == 4 ) { xPositionCorrection = 0x08; yPositionCorrection = 0x02; return;}
        if ((*mapNum) == 15 && (*warpId) == 0 ) { xPositionCorrection = 0x08; yPositionCorrection = 0x10; return;}
        if ((*mapNum) == 26 && (*warpId) == 0 ) { xPositionCorrection = 0x0D; yPositionCorrection = 0x72; return;}
        if ((*mapNum) == 10 && (*warpId) == 5 ) { xPositionCorrection = 0x0A; yPositionCorrection = 0x09; return;}
        if ((*mapNum) == 35 && (*warpId) == 1 ) { yPositionCorrection = 0x18; return;}
        if ((*mapNum) == 5  && (*warpId) == 6 ) { yPositionCorrection = 0x06; return;}

        return;
    }

    if ((*mapGroup) == 24) 
    {
        if ((*mapNum) == 8  && (*warpId) == 2 ) { xPositionCorrection = 0x1D; yPositionCorrection = 0x0D; return;}
        if ((*mapNum) == 8  && (*warpId) == 3 ) { xPositionCorrection = 0x1C; yPositionCorrection = 0x15; return;}
        if ((*mapNum) == 9  && (*warpId) == 0 ) { xPositionCorrection = 0x1D; yPositionCorrection = 0x0D; return;}
        if ((*mapNum) == 9  && (*warpId) == 1 ) { xPositionCorrection = 0x1C; yPositionCorrection = 0x15; return;}
        if ((*mapNum) == 13 && (*warpId) == 4 ) { xPositionCorrection = 0x10; yPositionCorrection = 0x13; return;}
        if ((*mapNum) == 16 && (*warpId) == 4 ) { xPositionCorrection = 0x0B; yPositionCorrection = 0x09; return;}
        if ((*mapNum) == 16 && (*warpId) == 2 ) { xPositionCorrection = 0x0A; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 17 && (*warpId) == 5 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 17 && (*warpId) == 4 ) { xPositionCorrection = 0x0A; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 18 && (*warpId) == 2 ) { xPositionCorrection = 0x0C; yPositionCorrection = 0x0A; return;}
        if ((*mapNum) == 18 && (*warpId) == 3 ) { xPositionCorrection = 0x0C; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 19 && (*warpId) == 3 ) { xPositionCorrection = 0x0C; yPositionCorrection = 0x0A; return;}
        if ((*mapNum) == 19 && (*warpId) == 4 ) { xPositionCorrection = 0x0C; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 24 && (*warpId) == 10) { xPositionCorrection = 0x20; yPositionCorrection = 0x13; return;}
        if ((*mapNum) == 25 && (*warpId) == 5 ) { xPositionCorrection = 0x05; yPositionCorrection = 0x08; return;}
        if ((*mapNum) == 25 && (*warpId) == 9 ) { xPositionCorrection = 0x20; yPositionCorrection = 0x14; return;}
        if ((*mapNum) == 29 && (*warpId) == 2 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x01; return;}
        if ((*mapNum) == 78 && (*warpId) == 0 ) { xPositionCorrection = 0x11; yPositionCorrection = 0x0D; return;}
        if ((*mapNum) == 81 && (*warpId) == 0 ) { xPositionCorrection = 0x03; yPositionCorrection = 0x01; return;}
        if ((*mapNum) == 82 && (*warpId) == 1 ) { xPositionCorrection = 0x07; yPositionCorrection = 0x01; return;}
        if ((*mapNum) == 95 && (*warpId) == 0 ) { xPositionCorrection = 0x12; yPositionCorrection = 0x0C; return;}
        if ((*mapNum) == 96 && (*warpId) == 0 ) { xPositionCorrection = 0x12; yPositionCorrection = 0x0C; return;}

        return;
    }

    if ((*mapGroup) == 16) 
    {
        if ((*mapNum) == 0  && (*warpId) == 1 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x03; return;}
        if ((*mapNum) == 1  && (*warpId) == 1 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x03; return;}
        if ((*mapNum) == 2  && (*warpId) == 1 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x03; return;}
        if ((*mapNum) == 3  && (*warpId) == 1 ) { xPositionCorrection = 0x06; yPositionCorrection = 0x03; return;}
        if ((*mapNum) == 10 && (*warpId) == 2 ) { xPositionCorrection = 0x09; yPositionCorrection = 0x02; return;}

        return;
    }


    if ((*mapGroup) == 11 && (*mapNum) == 0  && (*warpId) == 2 ) { xPositionCorrection = 0x0E; yPositionCorrection = 0x02; return;}

    if ((*mapGroup) == 14 && (*mapNum) == 9  && (*warpId) == 2 ) { xPositionCorrection = 0x0D; yPositionCorrection = 0x02; return;}
    if ((*mapGroup) == 14 && (*mapNum) == 10 && (*warpId) == 2 ) { xPositionCorrection = 0x0d; yPositionCorrection = 0x02; return;}
    
    if ((*mapGroup) == 26 && (*mapNum) == 74 && (*warpId) == 1 ) { xPositionCorrection = 0x05; yPositionCorrection = 0x05; return;}
    if ((*mapGroup) == 26 && (*mapNum) == 87 && (*warpId) == 0 ) { xPositionCorrection = 0x0E; yPositionCorrection = 0x13; return;}

}


/*
*   For the remapping to work each warp tile (or group of adjacent tiles) needs a unique destination
*   Previously we patched this but now we can update the warpId based on player x/y pos (there's probably a better way...)
*
*   TODO:
*   DUPES: [24,24,20, 24,24,23] -> 24,24,17
*   NEW  : 24,24,23 -> 24,24,50 (0x32) | patchROM8(0x0872b27d - 0x08000000, 0x32)
*
*
*   DUPES: [24,24,9, 24,24,14, 24,24,21] -> 24,24,12
*   NEW  : 24,24,14 -> 24,24,52 (0x33) | patchROM8(0x0872B26D - 0x08000000, 0x33)
*          24,24,21 -> 24,24,51 (0x34) | patchROM8(0x0872B235 - 0x08000000, 0x34)
*
*   DUPES: [24,24,7, 24,25,9] -> 24,24,4
*   NEW  : 24,25,9  -> 24,24,53 (0x35) | patchROM8(0x0872B379 - 0x08000000, 0x35)
*
*   DUPES: [24,31,3, 24,28,0, 24,33,2] -> 24,27,1
*   NEW  : 24,31,3  -> 24,27,50 (0x32) | patchROM8(0x0872B751 - 0x08000000, 0x32)
*          24,33,2  -> 24,27,70 (0x46) | patchROM8(0x0872B839 - 0x08000000, 0x46)
*/
s8 findProxyWarpIdForDuplicateWarps(s8 *mapGroup, s8 *mapNum, s8 *warpId)
{

    // All dupe warps are in map group 24
    if ((*mapGroup) != 24) 
    {
        return -1;
    } 

    if ((*mapNum) == 24 && (*warpId) == 17 && gSaveBlock1Ptr->pos.y > 0x10) 
    { 
        // 24,24,23
        return 0x32;
    }

    if ((*mapNum) == 24 && (*warpId) == 12 && gSaveBlock1Ptr->pos.x > 0x6) 
    { 
        if (gSaveBlock1Ptr->pos.y > 0x7)
        {
            // 24,24,14
            return 0x33;
        }
        else 
        {
            // 24,24,21
            return 0x34;
        }
        
        return 0;
    }

    if ((*mapNum) == 24 && (*warpId) == 4 && gSaveBlock1Ptr->pos.y > 0xF) 
    { 
        // 24,25,9
        return 0x35;
    }

    if ((*mapNum) == 27 && (*warpId) == 1 && gSaveBlock1Ptr->pos.x > 0x7) 
    { 
        if (gSaveBlock1Ptr->pos.y > 0xD)
        {
            // 24,31,3 
            return 0x32;
        }
        else 
        {
            // 24,33,2
            return 0x46;
        }
        
        return 0;
    }

    return -1;
}

void InterceptWarp(s8 *mapGroup, s8 *mapNum, s8 *warpId, s8 *x, s8 *y)
{
    u16 remappedWarpIndex;
    s8 proxyId;
    xPositionCorrection = -1;
    yPositionCorrection = -1;

    if (!FlagGet(FLAG_MAP_RANDO)) 
    {
        return;
    }

    if ((*warpId) == -1)
    {
        if ((*mapGroup) == 8 && (*mapNum) == 1)
        {
            // Allow battle normans gym after tutorial
            VarSet(VAR_PETALBURG_GYM_STATE, 6);
            FlagSet(FLAG_HIDE_PETALBURG_CITY_WALLY);
            FlagSet(FLAG_HIDE_PETALBURG_GYM_WALLY);

            VarSet(VAR_PETALBURG_WOODS_STATE, 1);
            FlagSet(FLAG_HIDE_PETALBURG_WOODS_DEVON_EMPLOYEE);
            FlagSet(FLAG_HIDE_PETALBURG_WOODS_AQUA_GRUNT);
            FlagSet(FLAG_HIDE_JAGGED_PASS_MAGMA_GUARD);
        }

        return;
    }

    proxyId = findProxyWarpIdForDuplicateWarps(mapGroup, mapNum, warpId);

    if (proxyId != -1) 
    {
        remappedWarpIndex = WarpRemapBinarySearch(mapGroup, mapNum, &proxyId);
    }
    else 
    {
        remappedWarpIndex = WarpRemapBinarySearch(mapGroup, mapNum, warpId);
    }
    
    if (remappedWarpIndex < RANDOM_WARP_LIMIT) 
    {
        bool8 needsXOffsetShift = warpNeedsXOffetShift(mapGroup, mapNum, warpId);

        (*mapGroup) = gWarpRemappingList[remappedWarpIndex].toMapGroup;
        (*mapNum)   = gWarpRemappingList[remappedWarpIndex].toMapNum;
        (*warpId)   = gWarpRemappingList[remappedWarpIndex].toWarpId;

        fixPositionAfterWarp(mapGroup, mapNum, warpId, x, y);

        if (needsXOffsetShift)
            xPositionCorrection = xPositionCorrection - 1;

    }

    ApplyFixesForSpecialWarps(mapGroup, mapNum, warpId);
    ApplyFixesForEveryWarp();
}

void CorrectPositionAfterIntercept()
{
    if (!FlagGet(FLAG_MAP_RANDO)) 
    {
        return;
    }

    if (xPositionCorrection == -2)
    {
        gSaveBlock1Ptr->pos.x = gSaveBlock1Ptr->pos.x - 1;
    }
    else if (xPositionCorrection > -1)
    {
        gSaveBlock1Ptr->pos.x = xPositionCorrection;
    }

    if (yPositionCorrection != -1) 
    {
        gSaveBlock1Ptr->pos.y = yPositionCorrection;
    }

    xPositionCorrection = -1;
    yPositionCorrection = -1;
}

void resetPositionCorrection() {
    xPositionCorrection = -1;
    yPositionCorrection = -1;
}

static const u8 comma[] = _(",");
bool8 CheckWarp(s8 mapGroup, s8 mapNum, s8 warpId) {

    u16 remappedWarpIndex = WarpRemapBinarySearch(&mapGroup, &mapNum, &warpId);
    if (remappedWarpIndex == RANDOM_WARP_LIMIT) 
    {
        ConvertIntToDecimalStringN(gStringVar1, mapGroup, STR_CONV_MODE_LEADING_ZEROS, 3);
        gStringVar1[3] = comma[0];
        ConvertIntToDecimalStringN(gStringVar1 + 4, mapNum, STR_CONV_MODE_LEADING_ZEROS, 3);
        gStringVar1[7] = comma[0];
        ConvertIntToDecimalStringN(gStringVar1 + 8, warpId, STR_CONV_MODE_LEADING_ZEROS, 3);
        return FALSE;
    }
    else 
    {
        return TRUE;
    }
}

bool8 CheckAllWarps() 
{
    bool8 result = TRUE;
    result = result && CheckWarp(0,0,1);
    result = result && CheckWarp(0,0,2);
    result = result && CheckWarp(0,0,3);
    result = result && CheckWarp(0,0,5);
    result = result && CheckWarp(0,1,0);
    result = result && CheckWarp(0,1,1);
    result = result && CheckWarp(0,1,2);
    result = result && CheckWarp(0,1,4);
    result = result && CheckWarp(0,1,5);
    result = result && CheckWarp(0,1,7);
    result = result && CheckWarp(0,1,8);
    result = result && CheckWarp(0,2,0);
    result = result && CheckWarp(0,2,1);
    result = result && CheckWarp(0,2,2);
    result = result && CheckWarp(0,2,3);
    result = result && CheckWarp(0,2,4);
    result = result && CheckWarp(0,3,0);
    result = result && CheckWarp(0,3,1);
    result = result && CheckWarp(0,3,2);
    result = result && CheckWarp(0,3,3);
    result = result && CheckWarp(0,3,5);
    result = result && CheckWarp(0,3,6);
    result = result && CheckWarp(0,3,8);
    result = result && CheckWarp(0,3,10);
    result = result && CheckWarp(0,4,0);
    result = result && CheckWarp(0,4,2);
    result = result && CheckWarp(0,4,3);
    result = result && CheckWarp(0,5,0);
    result = result && CheckWarp(0,5,1);
    result = result && CheckWarp(0,5,2);
    result = result && CheckWarp(0,5,4);
    result = result && CheckWarp(0,5,6);
    result = result && CheckWarp(0,5,12);
    result = result && CheckWarp(0,6,1);
    result = result && CheckWarp(0,6,2);
    result = result && CheckWarp(0,6,4);
    result = result && CheckWarp(0,6,6);
    result = result && CheckWarp(0,6,8);
    result = result && CheckWarp(0,7,0);
    result = result && CheckWarp(0,7,1);
    result = result && CheckWarp(0,7,2);
    result = result && CheckWarp(0,7,3);
    result = result && CheckWarp(0,7,4);
    result = result && CheckWarp(0,8,0);
    result = result && CheckWarp(0,8,1);
    result = result && CheckWarp(0,8,2);
    result = result && CheckWarp(0,8,3);
    result = result && CheckWarp(0,10,2);
    result = result && CheckWarp(0,11,1);
    result = result && CheckWarp(0,11,2);
    result = result && CheckWarp(0,12,0);
    result = result && CheckWarp(0,12,1);
    result = result && CheckWarp(0,12,2);
    result = result && CheckWarp(0,12,3);
    result = result && CheckWarp(0,12,5);
    result = result && CheckWarp(0,13,0);
    result = result && CheckWarp(0,13,2);
    result = result && CheckWarp(0,14,1);
    result = result && CheckWarp(0,14,2);
    result = result && CheckWarp(0,14,4);
    result = result && CheckWarp(0,15,0);
    result = result && CheckWarp(0,19,0);
    result = result && CheckWarp(0,19,2);
    result = result && CheckWarp(0,19,3);
    result = result && CheckWarp(0,19,4);
    result = result && CheckWarp(0,19,5);
    result = result && CheckWarp(0,19,6);
    result = result && CheckWarp(0,19,7);
    result = result && CheckWarp(0,20,0);
    result = result && CheckWarp(0,21,0);
    result = result && CheckWarp(0,23,0);
    result = result && CheckWarp(0,25,0);
    result = result && CheckWarp(0,25,2);
    result = result && CheckWarp(0,25,3);
    result = result && CheckWarp(0,25,4);
    result = result && CheckWarp(0,25,5);
    result = result && CheckWarp(0,26,1);
    result = result && CheckWarp(0,26,3);
    result = result && CheckWarp(0,27,0);
    result = result && CheckWarp(0,27,1);
    result = result && CheckWarp(0,27,2);
    result = result && CheckWarp(0,27,3);
    result = result && CheckWarp(0,27,4);
    result = result && CheckWarp(0,27,5);
    result = result && CheckWarp(0,29,0);
    result = result && CheckWarp(0,29,1);
    result = result && CheckWarp(0,30,0);
    result = result && CheckWarp(0,31,0);
    result = result && CheckWarp(0,31,2);
    result = result && CheckWarp(0,34,0);
    result = result && CheckWarp(0,35,0);
    result = result && CheckWarp(0,37,0);
    result = result && CheckWarp(0,46,0);
    result = result && CheckWarp(2,0,0);
    result = result && CheckWarp(2,1,0);
    result = result && CheckWarp(2,2,0);
    result = result && CheckWarp(2,3,0);
    result = result && CheckWarp(2,4,0);
    result = result && CheckWarp(3,0,0);
    result = result && CheckWarp(3,1,0);
    result = result && CheckWarp(3,2,0);
    result = result && CheckWarp(3,3,0);
    result = result && CheckWarp(3,4,0);
    result = result && CheckWarp(3,5,0);
    result = result && CheckWarp(4,0,0);
    result = result && CheckWarp(4,1,0);
    result = result && CheckWarp(4,3,0);
    result = result && CheckWarp(4,4,0);
    result = result && CheckWarp(4,5,0);
    result = result && CheckWarp(4,5,3);
    result = result && CheckWarp(4,6,0);
    result = result && CheckWarp(5,0,0);
    result = result && CheckWarp(5,1,0);
    result = result && CheckWarp(5,4,0);
    result = result && CheckWarp(5,5,0);
    result = result && CheckWarp(5,6,0);
    result = result && CheckWarp(5,7,0);
    result = result && CheckWarp(6,0,0);
    result = result && CheckWarp(6,3,0);
    result = result && CheckWarp(6,4,0);
    result = result && CheckWarp(6,5,0);
    result = result && CheckWarp(6,6,0);
    result = result && CheckWarp(6,7,0);
    result = result && CheckWarp(6,8,0);
    result = result && CheckWarp(7,0,0);
    result = result && CheckWarp(7,1,0);
    result = result && CheckWarp(7,2,0);
    result = result && CheckWarp(7,3,0);
    result = result && CheckWarp(7,4,0);
    result = result && CheckWarp(7,5,0);
    result = result && CheckWarp(7,6,0);
    result = result && CheckWarp(8,0,0);
    result = result && CheckWarp(8,1,0);
    result = result && CheckWarp(8,2,0);
    result = result && CheckWarp(8,3,0);
    result = result && CheckWarp(8,4,0);
    result = result && CheckWarp(8,5,0);
    result = result && CheckWarp(8,6,0);
    result = result && CheckWarp(9,0,0);
    result = result && CheckWarp(9,0,2);
    result = result && CheckWarp(9,1,0);
    result = result && CheckWarp(9,2,0);
    result = result && CheckWarp(9,5,0);
    result = result && CheckWarp(9,6,0);
    result = result && CheckWarp(9,7,0);
    result = result && CheckWarp(9,7,1);
    result = result && CheckWarp(9,8,0);
    result = result && CheckWarp(9,9,0);
    result = result && CheckWarp(9,10,0);
    result = result && CheckWarp(9,11,0);
    result = result && CheckWarp(9,12,0);
    result = result && CheckWarp(9,13,0);
    result = result && CheckWarp(10,0,0);
    result = result && CheckWarp(10,1,0);
    result = result && CheckWarp(10,2,0);
    result = result && CheckWarp(10,3,0);
    result = result && CheckWarp(10,4,0);
    result = result && CheckWarp(10,5,0);
    result = result && CheckWarp(10,6,0);
    result = result && CheckWarp(10,7,0);
    result = result && CheckWarp(11,0,0);
    result = result && CheckWarp(11,0,1);
    result = result && CheckWarp(11,0,2);
    result = result && CheckWarp(11,1,0);
    result = result && CheckWarp(11,1,1);
    result = result && CheckWarp(11,2,0);
    result = result && CheckWarp(11,3,0);
    result = result && CheckWarp(11,4,0);
    result = result && CheckWarp(11,5,0);
    result = result && CheckWarp(11,6,0);
    result = result && CheckWarp(11,7,0);
    result = result && CheckWarp(11,8,0);
    result = result && CheckWarp(11,9,0);
    result = result && CheckWarp(11,10,0);
    result = result && CheckWarp(11,11,0);
    result = result && CheckWarp(11,12,0);
    result = result && CheckWarp(11,13,0);
    result = result && CheckWarp(11,13,2);
    result = result && CheckWarp(11,14,0);
    result = result && CheckWarp(11,15,0);
    result = result && CheckWarp(11,16,0);
    result = result && CheckWarp(12,0,0);
    result = result && CheckWarp(12,1,0);
    result = result && CheckWarp(12,2,0);
    result = result && CheckWarp(12,3,0);
    result = result && CheckWarp(12,4,0);
    result = result && CheckWarp(12,5,0);
    result = result && CheckWarp(12,6,0);
    result = result && CheckWarp(12,7,0);
    result = result && CheckWarp(12,8,0);
    result = result && CheckWarp(12,9,0);
    result = result && CheckWarp(13,0,0);
    result = result && CheckWarp(13,1,0);
    result = result && CheckWarp(13,2,0);
    result = result && CheckWarp(13,2,1);
    result = result && CheckWarp(13,4,0);
    result = result && CheckWarp(13,4,2);
    result = result && CheckWarp(13,4,3);
    result = result && CheckWarp(13,5,0);
    result = result && CheckWarp(13,5,1);
    result = result && CheckWarp(13,6,0);
    result = result && CheckWarp(13,7,0);
    result = result && CheckWarp(13,9,1);
    result = result && CheckWarp(13,10,0);
    result = result && CheckWarp(13,11,0);
    result = result && CheckWarp(13,12,0);
    result = result && CheckWarp(13,13,0);
    result = result && CheckWarp(13,14,0);
    result = result && CheckWarp(13,15,0);
    result = result && CheckWarp(13,16,0);
    result = result && CheckWarp(13,16,2);
    result = result && CheckWarp(13,17,0);
    result = result && CheckWarp(13,17,1);
    result = result && CheckWarp(13,18,0);
    result = result && CheckWarp(13,18,1);
    result = result && CheckWarp(13,19,0);
    result = result && CheckWarp(13,19,1);
    result = result && CheckWarp(13,20,0);
    result = result && CheckWarp(13,21,0);
    result = result && CheckWarp(14,0,0);
    result = result && CheckWarp(14,1,0);
    result = result && CheckWarp(14,2,0);
    result = result && CheckWarp(14,3,0);
    result = result && CheckWarp(14,4,0);
    result = result && CheckWarp(14,5,0);
    result = result && CheckWarp(14,6,0);
    result = result && CheckWarp(14,7,0);
    result = result && CheckWarp(14,8,1);
    result = result && CheckWarp(14,9,0);
    result = result && CheckWarp(14,10,0);
    result = result && CheckWarp(14,11,0);
    result = result && CheckWarp(15,0,0);
    result = result && CheckWarp(15,2,0);
    result = result && CheckWarp(15,3,0);
    result = result && CheckWarp(15,4,0);
    result = result && CheckWarp(15,5,0);
    result = result && CheckWarp(15,6,0);
    result = result && CheckWarp(15,7,0);
    result = result && CheckWarp(15,8,0);
    result = result && CheckWarp(15,9,0);
    result = result && CheckWarp(15,10,0);
    result = result && CheckWarp(15,11,0);
    result = result && CheckWarp(15,12,0);
    result = result && CheckWarp(15,13,0);
    result = result && CheckWarp(16,5,0);
    result = result && CheckWarp(16,5,1);
    result = result && CheckWarp(16,6,0);
    result = result && CheckWarp(16,6,1);
    result = result && CheckWarp(16,7,0);
    result = result && CheckWarp(16,7,1);
    result = result && CheckWarp(16,8,0);
    result = result && CheckWarp(16,8,1);
    result = result && CheckWarp(16,9,0);
    result = result && CheckWarp(16,9,1);
    result = result && CheckWarp(16,10,0);
    result = result && CheckWarp(16,12,0);
    result = result && CheckWarp(16,13,0);
    result = result && CheckWarp(16,14,0);
    result = result && CheckWarp(17,0,0);
    result = result && CheckWarp(17,1,0);
    result = result && CheckWarp(18,0,0);
    result = result && CheckWarp(18,1,0);
    result = result && CheckWarp(19,0,0);
    result = result && CheckWarp(19,0,1);
    result = result && CheckWarp(19,1,0);
    result = result && CheckWarp(19,1,1);
    result = result && CheckWarp(20,0,0);
    result = result && CheckWarp(20,1,0);
    result = result && CheckWarp(20,2,0);
    result = result && CheckWarp(21,0,0);
    result = result && CheckWarp(22,0,0);
    result = result && CheckWarp(23,0,2);
    result = result && CheckWarp(24,0,0);
    result = result && CheckWarp(24,0,1);
    result = result && CheckWarp(24,0,2);
    result = result && CheckWarp(24,0,3);
    result = result && CheckWarp(24,0,4);
    result = result && CheckWarp(24,0,5);
    result = result && CheckWarp(24,1,0);
    result = result && CheckWarp(24,1,1);
    result = result && CheckWarp(24,1,2);
    result = result && CheckWarp(24,1,3);
    result = result && CheckWarp(24,2,0);
    result = result && CheckWarp(24,2,1);
    result = result && CheckWarp(24,2,2);
    result = result && CheckWarp(24,2,4);
    result = result && CheckWarp(24,2,5);
    result = result && CheckWarp(24,3,0);
    result = result && CheckWarp(24,4,0);
    result = result && CheckWarp(24,4,1);
    result = result && CheckWarp(24,6,0);
    result = result && CheckWarp(24,6,1);
    result = result && CheckWarp(24,6,2);
    result = result && CheckWarp(24,7,0);
    result = result && CheckWarp(24,7,1);
    result = result && CheckWarp(24,7,2);
    result = result && CheckWarp(24,7,3);
    result = result && CheckWarp(24,8,0);
    result = result && CheckWarp(24,8,1);
    result = result && CheckWarp(24,8,2);
    result = result && CheckWarp(24,8,3);
    result = result && CheckWarp(24,8,4);
    result = result && CheckWarp(24,8,5);
    result = result && CheckWarp(24,9,0);
    result = result && CheckWarp(24,9,1);
    result = result && CheckWarp(24,9,2);
    result = result && CheckWarp(24,9,3);
    result = result && CheckWarp(24,9,4);
    result = result && CheckWarp(24,10,0);
    result = result && CheckWarp(24,11,0);
    result = result && CheckWarp(24,11,1);
    result = result && CheckWarp(24,11,2);
    result = result && CheckWarp(24,11,3);
    result = result && CheckWarp(24,11,4);
    result = result && CheckWarp(24,11,5);
    result = result && CheckWarp(24,12,0);
    result = result && CheckWarp(24,12,1);
    result = result && CheckWarp(24,12,2);
    result = result && CheckWarp(24,12,3);
    result = result && CheckWarp(24,13,0);
    result = result && CheckWarp(24,13,1);
    result = result && CheckWarp(24,13,2);
    result = result && CheckWarp(24,13,3);
    result = result && CheckWarp(24,13,4);
    result = result && CheckWarp(24,14,0);
    result = result && CheckWarp(24,14,1);
    result = result && CheckWarp(24,15,0);
    result = result && CheckWarp(24,15,1);
    result = result && CheckWarp(24,15,4);
    result = result && CheckWarp(24,15,5);
    result = result && CheckWarp(24,16,0);
    result = result && CheckWarp(24,16,1);
    result = result && CheckWarp(24,16,2);
    result = result && CheckWarp(24,17,0);
    result = result && CheckWarp(24,17,1);
    result = result && CheckWarp(24,17,2);
    result = result && CheckWarp(24,18,0);
    result = result && CheckWarp(24,18,1);
    result = result && CheckWarp(24,18,2);
    result = result && CheckWarp(24,18,3);
    result = result && CheckWarp(24,19,0);
    result = result && CheckWarp(24,19,1);
    result = result && CheckWarp(24,19,2);
    result = result && CheckWarp(24,20,0);
    result = result && CheckWarp(24,21,0);
    result = result && CheckWarp(24,21,1);
    result = result && CheckWarp(24,22,1);
    result = result && CheckWarp(24,23,0);
    result = result && CheckWarp(24,23,2);
    result = result && CheckWarp(24,24,0);
    result = result && CheckWarp(24,24,1);
    result = result && CheckWarp(24,24,2);
    result = result && CheckWarp(24,24,3);
    result = result && CheckWarp(24,24,5);
    result = result && CheckWarp(24,24,6);
    result = result && CheckWarp(24,24,7);
    result = result && CheckWarp(24,24,8);
    result = result && CheckWarp(24,24,9);
    result = result && CheckWarp(24,24,10);
    result = result && CheckWarp(24,24,11);
    result = result && CheckWarp(24,24,12);
    result = result && CheckWarp(24,24,13);
    result = result && CheckWarp(24,24,15);
    result = result && CheckWarp(24,24,16);
    result = result && CheckWarp(24,24,17);
    result = result && CheckWarp(24,24,18);
    result = result && CheckWarp(24,24,19);
    result = result && CheckWarp(24,24,20);
    result = result && CheckWarp(24,24,22);
    result = result && CheckWarp(24,24,24);
    result = result && CheckWarp(24,24,50);
    result = result && CheckWarp(24,24,51);
    result = result && CheckWarp(24,24,52);
    result = result && CheckWarp(24,24,53);
    result = result && CheckWarp(24,25,0);
    result = result && CheckWarp(24,25,1);
    result = result && CheckWarp(24,25,2);
    result = result && CheckWarp(24,25,3);
    result = result && CheckWarp(24,25,4);
    result = result && CheckWarp(24,25,5);
    result = result && CheckWarp(24,25,7);
    result = result && CheckWarp(24,25,8);
    result = result && CheckWarp(24,27,1);
    result = result && CheckWarp(24,27,50);
    result = result && CheckWarp(24,28,2);
    result = result && CheckWarp(24,29,0);
    result = result && CheckWarp(24,29,1);
    result = result && CheckWarp(24,29,3);
    result = result && CheckWarp(24,30,0);
    result = result && CheckWarp(24,30,1);
    result = result && CheckWarp(24,31,0);
    result = result && CheckWarp(24,32,0);
    result = result && CheckWarp(24,32,1);
    result = result && CheckWarp(24,32,2);
    result = result && CheckWarp(24,33,0);
    result = result && CheckWarp(24,33,1);
    result = result && CheckWarp(24,34,0);
    result = result && CheckWarp(24,34,1);
    result = result && CheckWarp(24,35,1);
    result = result && CheckWarp(24,36,0);
    result = result && CheckWarp(24,37,0);
    result = result && CheckWarp(24,38,0);
    result = result && CheckWarp(24,38,1);
    result = result && CheckWarp(24,39,1);
    result = result && CheckWarp(24,43,0);
    result = result && CheckWarp(24,43,1);
    result = result && CheckWarp(24,43,2);
    result = result && CheckWarp(24,43,3);
    result = result && CheckWarp(24,43,4);
    result = result && CheckWarp(24,44,0);
    result = result && CheckWarp(24,44,1);
    result = result && CheckWarp(24,44,2);
    result = result && CheckWarp(24,44,3);
    result = result && CheckWarp(24,44,4);
    result = result && CheckWarp(24,44,5);
    result = result && CheckWarp(24,44,6);
    result = result && CheckWarp(24,45,0);
    result = result && CheckWarp(24,45,1);
    result = result && CheckWarp(24,45,2);
    result = result && CheckWarp(24,45,3);
    result = result && CheckWarp(24,46,0);
    result = result && CheckWarp(24,52,0);
    result = result && CheckWarp(24,53,0);
    result = result && CheckWarp(24,54,0);
    result = result && CheckWarp(24,54,2);
    result = result && CheckWarp(24,54,3);
    result = result && CheckWarp(24,54,4);
    result = result && CheckWarp(24,55,1);
    result = result && CheckWarp(24,55,2);
    result = result && CheckWarp(24,55,4);
    result = result && CheckWarp(24,55,5);
    result = result && CheckWarp(24,55,7);
    result = result && CheckWarp(24,55,8);
    result = result && CheckWarp(24,55,9);
    result = result && CheckWarp(24,55,10);
    result = result && CheckWarp(24,55,11);
    result = result && CheckWarp(24,56,0);
    result = result && CheckWarp(24,56,2);
    result = result && CheckWarp(24,56,3);
    result = result && CheckWarp(24,56,4);
    result = result && CheckWarp(24,57,0);
    result = result && CheckWarp(24,57,1);
    result = result && CheckWarp(24,57,6);
    result = result && CheckWarp(24,57,7);
    result = result && CheckWarp(24,58,0);
    result = result && CheckWarp(24,58,1);
    result = result && CheckWarp(24,58,2);
    result = result && CheckWarp(24,59,0);
    result = result && CheckWarp(24,59,2);
    result = result && CheckWarp(24,61,0);
    result = result && CheckWarp(24,62,0);
    result = result && CheckWarp(24,62,2);
    result = result && CheckWarp(24,63,0);
    result = result && CheckWarp(24,67,0);
    result = result && CheckWarp(24,67,1);
    result = result && CheckWarp(24,67,2);
    result = result && CheckWarp(24,68,0);
    result = result && CheckWarp(24,68,1);
    result = result && CheckWarp(24,68,2);
    result = result && CheckWarp(24,73,0);
    result = result && CheckWarp(24,77,0);
    result = result && CheckWarp(24,77,1);
    result = result && CheckWarp(24,78,0);
    result = result && CheckWarp(24,78,1);
    result = result && CheckWarp(24,79,0);
    result = result && CheckWarp(24,79,2);
    result = result && CheckWarp(24,80,0);
    result = result && CheckWarp(24,80,1);
    result = result && CheckWarp(24,81,0);
    result = result && CheckWarp(24,81,1);
    result = result && CheckWarp(24,81,2);
    result = result && CheckWarp(24,82,0);
    result = result && CheckWarp(24,82,1);
    result = result && CheckWarp(24,82,2);
    result = result && CheckWarp(24,84,0);
    result = result && CheckWarp(24,84,1);
    result = result && CheckWarp(24,85,0);
    result = result && CheckWarp(24,86,0);
    result = result && CheckWarp(24,86,1);
    result = result && CheckWarp(24,86,2);
    result = result && CheckWarp(24,86,3);
    result = result && CheckWarp(24,87,0);
    result = result && CheckWarp(24,87,1);
    result = result && CheckWarp(24,87,2);
    result = result && CheckWarp(24,88,0);
    result = result && CheckWarp(24,89,0);
    result = result && CheckWarp(24,89,2);
    result = result && CheckWarp(24,90,0);
    result = result && CheckWarp(24,91,0);
    result = result && CheckWarp(24,91,1);
    result = result && CheckWarp(24,92,0);
    result = result && CheckWarp(24,92,1);
    result = result && CheckWarp(24,93,0);
    result = result && CheckWarp(24,93,1);
    result = result && CheckWarp(24,94,0);
    result = result && CheckWarp(24,94,1);
    result = result && CheckWarp(24,95,0);
    result = result && CheckWarp(24,95,1);
    result = result && CheckWarp(24,96,0);
    result = result && CheckWarp(24,97,0);
    result = result && CheckWarp(24,102,0);
    result = result && CheckWarp(24,104,1);
    result = result && CheckWarp(24,107,0);
    result = result && CheckWarp(26,56,0);
    result = result && CheckWarp(26,56,1);
    result = result && CheckWarp(26,59,0);
    result = result && CheckWarp(26,60,0);
    result = result && CheckWarp(26,66,1);
    result = result && CheckWarp(26,67,0);
    result = result && CheckWarp(26,68,0);
    result = result && CheckWarp(26,68,1);
    result = result && CheckWarp(26,69,0);
    result = result && CheckWarp(26,69,1);
    result = result && CheckWarp(26,70,1);
    result = result && CheckWarp(26,71,0);
    result = result && CheckWarp(26,73,1);
    result = result && CheckWarp(26,74,1);
    result = result && CheckWarp(26,75,0);
    result = result && CheckWarp(26,76,0);
    result = result && CheckWarp(26,86,0);
    result = result && CheckWarp(28,0,0);
    result = result && CheckWarp(29,0,0);
    result = result && CheckWarp(29,2,0);
    result = result && CheckWarp(29,3,2);
    result = result && CheckWarp(29,11,0);
    result = result && CheckWarp(29,11,2);
    result = result && CheckWarp(29,12,0);
    result = result && CheckWarp(29,12,2);
    result = result && CheckWarp(30,0,0);
    result = result && CheckWarp(31,0,0);
    result = result && CheckWarp(32,0,0);
    result = result && CheckWarp(32,0,2);
    result = result && CheckWarp(32,1,0);
    result = result && CheckWarp(32,2,0);
    result = result && CheckWarp(33,0,0);

    return result;
}