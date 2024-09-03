Text_PlayerUsedFieldTool:
    .string "{PLAYER} used {STR_VAR_2}!$"

EventScript_UseCutTool::
    lockall
    goto EventScript_CutTreeDown

EventScript_UseRockSmashTool::
    lockall
    goto EventScript_SmashRock

EventScript_UseStrengthTool::
    lockall
    call_if_set FLAG_SYS_USE_STRENGTH, EventScript_PushBoulderScript @ qol_field_moves
    setflag FLAG_SYS_USE_STRENGTH
    msgbox Text_StrengthActivated, MSGBOX_DEFAULT
    releaseall
    end

EventScript_PushBoulderScript::
    callnative PushBoulderFromScript
    return

EventScript_UseWaterfallTool::
    lock
    setflag FLAG_SYS_USE_WATERFALL
EventScript_UseWaterfallFieldEffect::
    dofieldeffect FLDEFF_USE_WATERFALL_TOOL
    releaseall
    end

EventScript_CheckDiveToolAndParty::
    checkpartylearnknowsfieldmove ITEM_HM08
    return

EventScript_UseDiveTool::
    lockall
    dofieldeffect FLDEFF_USE_DIVE_TOOL
    goto EventScript_EndDive

EventScript_UseFlashTool::
    animateflash 1
    setflashlevel 1
    delay 40
    end

EventScript_UseSurfTool::
EventScript_UseSurfFieldEffect::
    dofieldeffect FLDEFF_USE_SURF_TOOL
    releaseall
    end

EventScript_AskTeleportTool::
    lock
    msgbox gStringVar4, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_CancelTeleportTool
EventScript_UseTeleportTool::
    dofieldeffect FLDEFF_USE_TELEPORT_TOOL
EventScript_CancelTeleportTool::
    releaseall
    end
