#include "global.h"
#include "day_night.h"
#include "decompress.h"
#include "event_data.h"
#include "field_tasks.h"
#include "field_weather.h"
#include "overworld.h"
#include "palette.h"
#include "rtc.h"
#include "constants/day_night.h"
#include "constants/rgb.h"
#include "strings.h"
#include "string_util.h"
#include "fieldmap.h"

void AdvanceTimeToNextPeriod(void)
{
    u8 time = GetCurrentTimeOfDay();

    switch(time) 
    {
        case TIME_MORNING: // Set it to TIME_DAY.
            gLocalTime.hours = HOUR_DAY;
            gLocalTime.minutes = 0;
            gLocalTime.seconds = 0;
            break;
        case TIME_DAY: // Set it to TIME_EVENING.
            gLocalTime.hours = TIME_EVENING;
            gLocalTime.minutes = 0;
            gLocalTime.seconds = 0;
            break;
        case TIME_EVENING: // Set it to TIME_NIGHT.
            gLocalTime.hours = HOUR_NIGHT;
            gLocalTime.minutes = 0;
            gLocalTime.seconds = 0;
            break;                  
        case TIME_NIGHT: // Set it to TIME_MORNING.
            gLocalTime.days += 1;
            gLocalTime.hours = HOUR_MORNING;
            gLocalTime.minutes = 0;
            gLocalTime.seconds = 0;
            break;
    }
    RtcReset();
    RtcCalcLocalTimeOffset(
        gLocalTime.days,
        gLocalTime.hours,
        gLocalTime.minutes,
        gLocalTime.seconds);
    gSaveBlock2Ptr->lastBerryTreeUpdate = gLocalTime;
    VarSet(VAR_DAYS, gLocalTime.days);
    DisableResetRTC();
}

/*
#define HOUR_MORNING 4
#define HOUR_DAY 10
#define HOUR_EVENING 19
#define HOUR_NIGHT 20
*/
static u8 DNS_GetTimeOfDay(s8 hours)
{
    if (hours < HOUR_MORNING)
        return TIME_NIGHT;
    else if (hours < HOUR_DAY)
        return TIME_MORNING;
    else if (hours < HOUR_EVENING)
        return TIME_DAY;
    else if (hours < HOUR_NIGHT)
        return HOUR_EVENING;
    else
        return TIME_NIGHT;
}

u8 GetCurrentTimeOfDay(void)
{
    return DNS_GetTimeOfDay(gLocalTime.hours);
}

void LoadCompressedPaletteDayNight(const u32 *src, u16 offset, u16 size)
{
    LZ77UnCompWram(src, gPaletteDecompressionBuffer);
    CpuCopy16(gPaletteDecompressionBuffer, &gPlttBufferUnfaded[offset], size);
    CpuCopy16(&gPlttBufferUnfaded[offset], &gPlttBufferFaded[offset], size);
    UpdateBattlePalettesWithTime(PALETTES_ALL);
}
