#include "global.h"
#include "crt0.h"
#include "malloc.h"
#include "link.h"
#include "link_rfu.h"
#include "librfu.h"
#include "m4a.h"
#include "bg.h"
#include "rtc.h"
#include "scanline_effect.h"
#include "overworld.h"
#include "play_time.h"
#include "random.h"
#include "dma3.h"
#include "gba/flash_internal.h"
#include "load_save.h"
#include "gpu_regs.h"
#include "agb_flash.h"
#include "sound.h"
#include "battle.h"
#include "battle_controllers.h"
#include "text.h"
#include "intro.h"
#include "main.h"
#include "trainer_hill.h"
#include "test_runner.h"
#include "constants/rgb.h"
#include "done_button.h"
#include "palette.h"
#include "region_map.h"
#include "speedchoice.h"
#include "main_menu.h"
#include "save.h"
#include "new_game.h"
#include "io_reg.h"

static void VBlankIntr(void);
static void HBlankIntr(void);
static void VCountIntr(void);
static void SerialIntr(void);
static void IntrDummy(void);

// Defined in the linker script so that the test build can override it.
extern void gInitialMainCB2(void);

const u8 gGameVersion = GAME_VERSION;

const u8 gGameLanguage = GAME_LANGUAGE; // English

const char BuildDateTime[] = "2005 02 21 11:10";

const IntrFunc gIntrTableTemplate[] =
{
    VCountIntr, // V-count interrupt
    SerialIntr, // Serial interrupt
    Timer3Intr, // Timer 3 interrupt
    HBlankIntr, // H-blank interrupt
    VBlankIntr, // V-blank interrupt
    IntrDummy,  // Timer 0 interrupt
    IntrDummy,  // Timer 1 interrupt
    IntrDummy,  // Timer 2 interrupt
    IntrDummy,  // DMA 0 interrupt
    IntrDummy,  // DMA 1 interrupt
    IntrDummy,  // DMA 2 interrupt
    IntrDummy,  // DMA 3 interrupt
    IntrDummy,  // Key interrupt
    IntrDummy,  // Game Pak interrupt
};

#define INTR_COUNT ((int)(sizeof(gIntrTableTemplate)/sizeof(IntrFunc)))

u16 gKeyRepeatStartDelay;
bool8 gLinkTransferringData;
struct Main gMain;
u16 gKeyRepeatContinueDelay;
bool8 gSoftResetDisabled;
IntrFunc gIntrTable[INTR_COUNT];
u8 gLinkVSyncDisabled;
u32 IntrMain_Buffer[0x200];
s8 gPcmDmaCounter;
void *gAgbMainLoop_sp;

static EWRAM_DATA u16 sTrainerId = 0;

//EWRAM_DATA void (**gFlashTimerIntrFunc)(void) = NULL;
EWRAM_DATA u8 gSoftResetFlag;

static void DoSoftResetWithoutRTCReset(void);
static void UpdateLinkAndCallCallbacks(void);
static void InitMainCallbacks(void);
static void CallCallbacks(void);
#ifdef BUGFIX
static void SeedRngWithRtc(void);
#endif
static void ReadKeys(void);
static void CB2_PostSoftResetInit(void);
void InitIntrHandlers(void);
static void WaitForVBlank(void);
void EnableVCountIntrAtLine150(void);
void DoFrameTimers(void);

#define B_START_SELECT (B_BUTTON | START_BUTTON | SELECT_BUTTON)

void AgbMain()
{
    if (SiiRtcProbe() != 0x11) // 0x11 = RTC in protected mode
        gSoftResetFlag = 1;

    *(vu16 *)BG_PLTT = RGB_WHITE; // Set the backdrop to white on startup
    InitGpuRegManager();
    REG_WAITCNT = WAITCNT_PREFETCH_ENABLE | WAITCNT_WS0_S_1 | WAITCNT_WS0_N_3;
    InitKeys();
    InitIntrHandlers();
    m4aSoundInit();
    EnableVCountIntrAtLine150();
    InitRFU();
    RtcInit();
    CheckForFlashMemory();
    InitMainCallbacks();
    InitMapMusic();
#ifdef BUGFIX
    SeedRngWithRtc(); // see comment at SeedRngWithRtc definition below
#endif
    ClearDma3Requests();
    ResetBgs();
    SetDefaultFontsPointer();
    InitHeap(gHeap, HEAP_SIZE);

    gSoftResetDisabled = FALSE;

    if (gFlashMemoryPresent != TRUE)
        SetMainCallback2(NULL);

    gLinkTransferringData = FALSE;

#ifndef NDEBUG
#if (LOG_HANDLER == LOG_HANDLER_MGBA_PRINT)
    (void) MgbaOpen();
#elif (LOG_HANDLER == LOG_HANDLER_AGB_PRINT)
    AGBPrintfInit();
#endif
#endif
    gAgbMainLoop_sp = __builtin_frame_address(0);
    AgbMainLoop();
}

void AgbMainLoop(void)
{
    for (;;)
    {
        ReadKeys();

        if (gSoftResetDisabled == FALSE
         && JOY_HELD_RAW(A_BUTTON)
         && JOY_HELD_RAW(B_START_SELECT) == B_START_SELECT)
        {
            rfu_REQ_stopMode();
            rfu_waitREQComplete();
            DoSoftResetWithoutRTCReset();
        }

        if (Overworld_SendKeysToLinkIsRunning() == TRUE)
        {
            gLinkTransferringData = TRUE;
            UpdateLinkAndCallCallbacks();
            gLinkTransferringData = FALSE;
        }
        else
        {
            gLinkTransferringData = FALSE;
            UpdateLinkAndCallCallbacks();

            if (Overworld_RecvKeysFromLinkIsRunning() == TRUE)
            {
                gMain.newKeys = 0;
                ClearSpriteCopyRequests();
                gLinkTransferringData = TRUE;
                UpdateLinkAndCallCallbacks();
                gLinkTransferringData = FALSE;
            }
        }

        PlayTimeCounter_Update();
        DoFrameTimers();
        MapMusicMain();
        WaitForVBlank();
    }
}

void DoFrameTimers(void)
{
    if(gFrameTimers.frameCount != 0xFFFFFFFF)
        gFrameTimers.frameCount++;
    if(sInField && gFrameTimers.owFrameCount != 0xFFFFFFFF)
        gFrameTimers.owFrameCount++;
    else if(sInBattle && gFrameTimers.battleFrameCount != 0xFFFFFFFF)
        gFrameTimers.battleFrameCount++;
    else if(sInIntro && gFrameTimers.introsFrameCount != 0xFFFFFFFF)
        gFrameTimers.introsFrameCount++;
    else if(sInSubMenu && gFrameTimers.menuFrameCount != 0xFFFFFFFF)
        gFrameTimers.menuFrameCount++;
    else if(!sInField && !sInBattle && !sInIntro && !sInSubMenu) // no category detected, we consider this a menu frame. (between menu transitions?)
    {
        if (gFrameTimers.menuFrameCount != 0xFFFFFFFF)
            gFrameTimers.menuFrameCount++;
    }
}

static void UpdateLinkAndCallCallbacks(void)
{
    if (!HandleLinkConnection())
        CallCallbacks();
}

static void InitMainCallbacks(void)
{
    gMain.vblankCounter1 = 0;
    gTrainerHillVBlankCounter = NULL;
    gMain.vblankCounter2 = 0;
    gMain.callback1 = NULL;
   
    if(gSoftResetFlag)
    {
        SetMainCallback2(CB2_PostSoftResetInit);
    }
    else
    {
        SetMainCallback2(gInitialMainCB2);
    }

    gSaveBlock2Ptr = &gSaveblock2.block;
    gPokemonStoragePtr = &gPokemonStorage.block;
}

static void CallCallbacks(void)
{
    if (gMain.callback1)
        gMain.callback1();

    if (gMain.callback2)
        gMain.callback2();
}

void SetMainCallback2(MainCallback callback)
{
    gMain.callback2 = callback;
    gMain.state = 0;
}

void StartTimer1(void)
{
    if (HQ_RANDOM)
    {
        REG_TM2CNT_L = 0;
        REG_TM2CNT_H = TIMER_ENABLE | TIMER_COUNTUP;
    }

    REG_TM1CNT_H = TIMER_ENABLE;
}

void SeedRngAndSetTrainerId(void)
{
    u32 val;

    if (HQ_RANDOM)
    {
        REG_TM1CNT_H = 0;
        REG_TM2CNT_H = 0;
        val = ((u32)REG_TM2CNT_L) << 16;
        val |= REG_TM1CNT_L;
        SeedRng(val);
        sTrainerId = Random();
    }
    else
    {
        // Do it exactly like it was originally done, including not stopping
        // the timer beforehand.
        val = REG_TM1CNT_L;
        SeedRng((u16)val);
        REG_TM1CNT_H = 0;
        sTrainerId = val;
    }
}

u16 GetGeneratedTrainerIdLower(void)
{
    return sTrainerId;
}

void EnableVCountIntrAtLine150(void)
{
    u16 gpuReg = (GetGpuReg(REG_OFFSET_DISPSTAT) & 0xFF) | (150 << 8);
    SetGpuReg(REG_OFFSET_DISPSTAT, gpuReg | DISPSTAT_VCOUNT_INTR);
    EnableInterrupts(INTR_FLAG_VCOUNT);
}

// FRLG commented this out to remove RTC, however Emerald didn't undo this!
#ifdef BUGFIX
static void SeedRngWithRtc(void)
{
    #if HQ_RANDOM == FALSE
        u32 seed = RtcGetMinuteCount();
        seed = (seed >> 16) ^ (seed & 0xFFFF);
        SeedRng(seed);
    #else
        #define BCD8(x) ((((x) >> 4) & 0xF) * 10 + ((x) & 0xF))
        u32 seconds;
        struct SiiRtcInfo rtc;
        RtcGetInfo(&rtc);
        seconds =
            ((HOURS_PER_DAY * RtcGetDayCount(&rtc) + BCD8(rtc.hour))
            * MINUTES_PER_HOUR + BCD8(rtc.minute))
            * SECONDS_PER_MINUTE + BCD8(rtc.second);
        SeedRng(seconds);
        #undef BCD8
    #endif
}
#endif

void InitKeys(void)
{
    gKeyRepeatContinueDelay = 5;
    gKeyRepeatStartDelay = 40;

    gMain.heldKeys = 0;
    gMain.newKeys = 0;
    gMain.newAndRepeatedKeys = 0;
    gMain.heldKeysRaw = 0;
    gMain.newKeysRaw = 0;
}

static void ReadKeys(void)
{
    u16 keyInput = REG_KEYINPUT ^ KEYS_MASK;
    gMain.newKeysRaw = keyInput & ~gMain.heldKeysRaw;
    gMain.newKeys = gMain.newKeysRaw;
    gMain.newAndRepeatedKeys = gMain.newKeysRaw;

    // BUG: Key repeat won't work when pressing L using L=A button mode
    // because it compares the raw key input with the remapped held keys.
    // Note that newAndRepeatedKeys is never remapped either.

    if (keyInput != 0 && gMain.heldKeys == keyInput)
    {
        gMain.keyRepeatCounter--;

        if (gMain.keyRepeatCounter == 0)
        {
            gMain.newAndRepeatedKeys = keyInput;
            gMain.keyRepeatCounter = gKeyRepeatContinueDelay;
        }
    }
    else
    {
        // If there is no input or the input has changed, reset the counter.
        gMain.keyRepeatCounter = gKeyRepeatStartDelay;
    }

    gMain.heldKeysRaw = keyInput;
    gMain.heldKeys = gMain.heldKeysRaw;

    // Remap L to A if the L=A option is enabled.
    if (gSaveBlock2Ptr->optionsButtonMode == OPTIONS_BUTTON_MODE_L_EQUALS_A)
    {
        if (JOY_NEW(L_BUTTON))
            gMain.newKeys |= A_BUTTON;

        if (JOY_HELD(L_BUTTON))
            gMain.heldKeys |= A_BUTTON;
    }

    if (JOY_NEW(gMain.watchedKeysMask))
        gMain.watchedKeysPressed = TRUE;

    if (JOY_HELD_RAW(R_BUTTON))
    {
        SetSpeed(MAX_SPEED_ON);   
    }
    else 
    {
        ClearSpeed(MAX_SPEED_ON);   
    }
        
}

void InitIntrHandlers(void)
{
    int i;

    for (i = 0; i < INTR_COUNT; i++)
        gIntrTable[i] = gIntrTableTemplate[i];

    DmaCopy32(3, IntrMain, IntrMain_Buffer, sizeof(IntrMain_Buffer));

    INTR_VECTOR = IntrMain_Buffer;

    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
    SetSerialCallback(NULL);

    REG_IME = 1;

    EnableInterrupts(INTR_FLAG_VBLANK);
}

void SetVBlankCallback(IntrCallback callback)
{
    gMain.vblankCallback = callback;
}

void SetHBlankCallback(IntrCallback callback)
{
    gMain.hblankCallback = callback;
}

void SetVCountCallback(IntrCallback callback)
{
    gMain.vcountCallback = callback;
}

void RestoreSerialTimer3IntrHandlers(void)
{
    gIntrTable[1] = SerialIntr;
    gIntrTable[2] = Timer3Intr;
}

void SetSerialCallback(IntrCallback callback)
{
    gMain.serialCallback = callback;
}

static void VBlankIntr(void)
{
    if (gWirelessCommType != 0)
        RfuVSync();
    else if (gLinkVSyncDisabled == FALSE)
        LinkVSync();

    gMain.vblankCounter1++;

    if (gTrainerHillVBlankCounter && *gTrainerHillVBlankCounter < 0xFFFFFFFF)
        (*gTrainerHillVBlankCounter)++;

    if (gMain.vblankCallback)
        gMain.vblankCallback();

    gMain.vblankCounter2++;

    CopyBufferedValuesToGpuRegs();
    ProcessDma3Requests();

    gPcmDmaCounter = gSoundInfo.pcmDmaCounter;

    m4aSoundMain();
    TryReceiveLinkBattleData();

    if (!gTestRunnerEnabled && (!gMain.inBattle || !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_FRONTIER | BATTLE_TYPE_RECORDED))))
        AdvanceRandom();

    UpdateWirelessStatusIndicatorSprite();

    INTR_CHECK |= INTR_FLAG_VBLANK;
    gMain.intrCheck |= INTR_FLAG_VBLANK;
}

void InitFlashTimer(void)
{
    SetFlashTimerIntr(2, gIntrTable + 0x7);
}

static void HBlankIntr(void)
{
    if (gMain.hblankCallback)
        gMain.hblankCallback();

    INTR_CHECK |= INTR_FLAG_HBLANK;
    gMain.intrCheck |= INTR_FLAG_HBLANK;
}

static void VCountIntr(void)
{
    if (gMain.vcountCallback)
        gMain.vcountCallback();

    m4aSoundVSync();
    INTR_CHECK |= INTR_FLAG_VCOUNT;
    gMain.intrCheck |= INTR_FLAG_VCOUNT;
}

static void SerialIntr(void)
{
    if (gMain.serialCallback)
        gMain.serialCallback();

    INTR_CHECK |= INTR_FLAG_SERIAL;
    gMain.intrCheck |= INTR_FLAG_SERIAL;
}

static void IntrDummy(void)
{}

static void WaitForVBlank(void)
{
    gMain.intrCheck &= ~INTR_FLAG_VBLANK;

    // gWirelessCommType gets turned on when you enter a pokecenter.
    // So if we want speedup in pokecenters we can't have desyncless rfu
    // if (gWirelessCommType != 0)
    // {
    //     // Desynchronization may occur if wireless adapter is connected
    //     // and we call VBlankIntrWait();
    //     while (!(gMain.intrCheck & INTR_FLAG_VBLANK))
    //         ;
    // }    if (!(gMain.heldKeysRaw & R_BUTTON) || gPaletteFade.active) 

    if (gPaletteFade.active)
    {
        VBlankIntrWait();
    }
    else if (gGlobalSpeed & (1 << MAX_SPEED_ON))
    {
        return;
    } 
    // else if (gGlobalSpeed & (1 << MED_SPEED_ON))
    // {
    //     if (gMain.vblankCounter1 % 3 == 0)
    //     {
    //         VBlankIntrWait();
    //         // VBlankIntrWait();
    //     }
    // }
    else 
    {
        VBlankIntrWait();
    }


}

void SetTrainerHillVBlankCounter(u32 *counter)
{
    gTrainerHillVBlankCounter = counter;
}

void ClearTrainerHillVBlankCounter(void)
{
    gTrainerHillVBlankCounter = NULL;
}

static void DoSoftResetWithoutRTCReset(void)
{
    REG_IME = 0;
    m4aSoundVSyncOff();
    ScanlineEffect_Stop();
    DmaStop(1);
    DmaStop(2);
    DmaStop(3);

    // Keep the rtc enables during reset so we can use it as a reliable way to check softresets and skip the intro
    // It's not reliable to just modify the softreset to set a flag after setting the stack ptr to 0x3007F00
    //SiiRtcProtect();
    SoftReset(RESET_ALL);
}

void DoSoftReset(void)
{
    REG_IME = 0;
    m4aSoundVSyncOff();
    ScanlineEffect_Stop();
    DmaStop(1);
    DmaStop(2);
    DmaStop(3);
    SiiRtcProtect();
    SoftReset(RESET_ALL);
}


void ClearPokemonCrySongs(void)
{
    CpuFill16(0, gPokemonCrySongs, MAX_POKEMON_CRIES * sizeof(struct PokemonCrySong));
}

static void CB2_PostSoftResetInit(void)
{
    gSoftResetFlag = 0;

    SetSaveBlocksPointers(GetSaveBlocksPointersBaseOffset());
    ResetMenuAndMonGlobals();
    Save_ResetSaveCounters();
    LoadGameSave(SAVE_NORMAL);
    if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
        Sav2_ClearSetDefault();
    SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
    SetMainCallback2(CB2_InitMainMenu);
}
