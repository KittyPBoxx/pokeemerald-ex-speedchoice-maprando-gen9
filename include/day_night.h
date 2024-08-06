#ifndef GUARD_DAY_NIGHT_H
#define GUARD_DAY_NIGHT_H

u8 GetCurrentTimeOfDay(void);
void LoadCompressedPaletteDayNight(const u32 *src, u16 offset, u16 size);
void AdvanceTimeToNextPeriod(void);

#endif // GUARD_DAY_NIGHT_H
