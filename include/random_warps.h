#ifndef RANDOM_WARPS_H
#define RANDOM_WARPS_H

#define RANDOM_WARP_LIMIT 632
#define RANDOM_WARP_LIMIT_SEARCH_HIGH (RANDOM_WARP_LIMIT - 1)
#define RANDOM_WARP_LIMIT_SEARCH_LOW 0

#include "gba/types.h"

void InterceptWarp(s8 *mapGroup, s8 *mapNum, s8 *warpId, s8 *x, s8 *y);
void CorrectPositionAfterIntercept();
void resetPositionCorrection();
void ApplyFixesForEveryWarp();
bool8 CheckAllWarps();

extern s8 xPositionCorrection;
extern s8 yPositionCorrection;

#endif // RANDOM_WARPS_H