#if defined _EykNotify_included
    #endinput
#endif
#define _EykNotify_included

#define MAX_NOTIFICATIONS 5

static const NOTIFICATION_WIDTH = 50.0;
static const NOTIFICATION_START_X = 350.0;
static const NOTIFICATION_START_Y = 313.0;

new PlayerText: NotifyModel[MAX_PLAYERS][MAX_NOTIFICATIONS];
new PlayerText: NotifyColor[MAX_PLAYERS][MAX_NOTIFICATIONS];
new PlayerText: NotifyText[MAX_PLAYERS][MAX_NOTIFICATIONS];
new PlayerText: NotifyAmount[MAX_PLAYERS][MAX_NOTIFICATIONS];
new bool: NotifySlotUsed[MAX_PLAYERS][MAX_NOTIFICATIONS];
new NotifyTimer[MAX_PLAYERS][MAX_NOTIFICATIONS];

stock CreateNotification(playerid, model, bool:isGreen, bool:isAdded, amount) {
    new slot = GetFreeNotificationSlot(playerid);
    if(slot == -1) return 0;
    
    // Position based on slot number (left to right)
    new Float:xPos = NOTIFICATION_START_X - (slot * NOTIFICATION_WIDTH);
    new Float:yPos = NOTIFICATION_START_Y;
    
    NotifyModel[playerid][slot] = CreatePlayerTextDraw(playerid, xPos, yPos + 4.0, "_");
    PlayerTextDrawTextSize(playerid, NotifyModel[playerid][slot], 29.0, 35.0);
    PlayerTextDrawAlignment(playerid, NotifyModel[playerid][slot], 1);
    PlayerTextDrawColor(playerid, NotifyModel[playerid][slot], -1);
    PlayerTextDrawSetShadow(playerid, NotifyModel[playerid][slot], 0);
    PlayerTextDrawSetOutline(playerid, NotifyModel[playerid][slot], 0);
    PlayerTextDrawBackgroundColor(playerid, NotifyModel[playerid][slot], 471604479);
    PlayerTextDrawFont(playerid, NotifyModel[playerid][slot], 5);
    PlayerTextDrawSetProportional(playerid, NotifyModel[playerid][slot], 0);
    PlayerTextDrawSetPreviewModel(playerid, NotifyModel[playerid][slot], model);
    PlayerTextDrawSetPreviewRot(playerid, NotifyModel[playerid][slot], 0.0, 0.0, 0.0, 1.0);
    PlayerTextDrawSetPreviewVehCol(playerid, NotifyModel[playerid][slot], 0, 0);
    
    NotifyColor[playerid][slot] = CreatePlayerTextDraw(playerid, xPos - 8.0, yPos, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, NotifyColor[playerid][slot], 31.0, 8.0);
    PlayerTextDrawAlignment(playerid, NotifyColor[playerid][slot], 1);
    PlayerTextDrawColor(playerid, NotifyColor[playerid][slot], isGreen ? 0x00FF00FF : 0xFF0000FF);
    PlayerTextDrawSetShadow(playerid, NotifyColor[playerid][slot], 0);
    PlayerTextDrawSetOutline(playerid, NotifyColor[playerid][slot], 0);
    PlayerTextDrawBackgroundColor(playerid, NotifyColor[playerid][slot], 255);
    PlayerTextDrawFont(playerid, NotifyColor[playerid][slot], 4);
    PlayerTextDrawSetProportional(playerid, NotifyColor[playerid][slot], 1);
    
    static textStr[16];
    if(isAdded) format(textStr, sizeof(textStr), "Adicionado");
    else format(textStr, sizeof(textStr), "Removido");
    NotifyText[playerid][slot] = CreatePlayerTextDraw(playerid, xPos + 8.0, yPos, textStr);
    PlayerTextDrawLetterSize(playerid, NotifyText[playerid][slot], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, NotifyText[playerid][slot], 2);
    PlayerTextDrawColor(playerid, NotifyText[playerid][slot], -1);
    PlayerTextDrawSetShadow(playerid, NotifyText[playerid][slot], 0);
    PlayerTextDrawSetOutline(playerid, NotifyText[playerid][slot], 0);
    PlayerTextDrawBackgroundColor(playerid, NotifyText[playerid][slot], 150);
    PlayerTextDrawFont(playerid, NotifyText[playerid][slot], 1);
    PlayerTextDrawSetProportional(playerid, NotifyText[playerid][slot], 1);
    
    static amountStr[16];
    format(amountStr, sizeof(amountStr), "%dx", amount);
    NotifyAmount[playerid][slot] = CreatePlayerTextDraw(playerid, xPos + 28.0, yPos + 33.0, amountStr);
    PlayerTextDrawLetterSize(playerid, NotifyAmount[playerid][slot], 0.119, 0.599);
    PlayerTextDrawAlignment(playerid, NotifyAmount[playerid][slot], 3);
    PlayerTextDrawColor(playerid, NotifyAmount[playerid][slot], -1);
    PlayerTextDrawSetShadow(playerid, NotifyAmount[playerid][slot], 0);
    PlayerTextDrawSetOutline(playerid, NotifyAmount[playerid][slot], 0);
    PlayerTextDrawBackgroundColor(playerid, NotifyAmount[playerid][slot], 150);
    PlayerTextDrawFont(playerid, NotifyAmount[playerid][slot], 1);
    PlayerTextDrawSetProportional(playerid, NotifyAmount[playerid][slot], 1);
    
    PlayerTextDrawShow(playerid, NotifyModel[playerid][slot]);
    PlayerTextDrawShow(playerid, NotifyColor[playerid][slot]);
    PlayerTextDrawShow(playerid, NotifyText[playerid][slot]);
    PlayerTextDrawShow(playerid, NotifyAmount[playerid][slot]);
    
    NotifySlotUsed[playerid][slot] = true;
    NotifyTimer[playerid][slot] = SetTimerEx("HideNotification", 5000, false, "ii", playerid, slot);
    
    return 1;
}

stock GetFreeNotificationSlot(playerid) {
    for(new i = 0; i < MAX_NOTIFICATIONS; i++) {
        if(!NotifySlotUsed[playerid][i]) return i;
    }
    return -1;
}

stock DestroyNotification(playerid, slot) {
    if(slot < 0 || slot >= MAX_NOTIFICATIONS || !NotifySlotUsed[playerid][slot]) return 0;
    
    PlayerTextDrawDestroy(playerid, NotifyModel[playerid][slot]);
    PlayerTextDrawDestroy(playerid, NotifyColor[playerid][slot]);
    PlayerTextDrawDestroy(playerid, NotifyText[playerid][slot]);
    PlayerTextDrawDestroy(playerid, NotifyAmount[playerid][slot]);
    
    NotifySlotUsed[playerid][slot] = false;
    KillTimer(NotifyTimer[playerid][slot]);
    
    return 1;
}

// Função removida - reorganização automática desabilitada para evitar problemas com timer

stock DestroyAllNotifications(playerid) {
    for(new i = 0; i < MAX_NOTIFICATIONS; i++) {
        if(NotifySlotUsed[playerid][i]) {
            DestroyNotification(playerid, i);
        }
    }
}

forward HideNotification(playerid, slot);
public HideNotification(playerid, slot) {
    DestroyNotification(playerid, slot);
}

public OnPlayerDisconnect(playerid, reason) {
    DestroyAllNotifications(playerid);
    #if defined EykNotify_OnPlayerDisconnect
        return EykNotify_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect EykNotify_OnPlayerDisconnect
#if defined EykNotify_OnPlayerDisconnect
    forward EykNotify_OnPlayerDisconnect(playerid, reason);
#endif

