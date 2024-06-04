#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_

/* MAKE FUNCTIONS STATIC, SO THEY CAN BE IN EVERY FILE */

typedef unsigned int (*GetVariableName_t)(unsigned int a1);
#if COD_VERSION == COD1_1_1
static const GetVariableName_t GetVariableName = (GetVariableName_t)0x080a3060;
#elif COD_VERSION == COD1_1_5
static const GetVariableName_t GetVariableName = (GetVariableName_t)0x080a6aac;
#endif

typedef unsigned int (*GetNextVariable_t)(unsigned int a1);
#if COD_VERSION == COD1_1_1
static const GetNextVariable_t GetNextVariable = (GetNextVariable_t)0x080a3028;
#elif COD_VERSION == COD1_1_5
static const GetNextVariable_t GetNextVariable = (GetNextVariable_t)0x080a6a38;
#endif

typedef char * (*SL_ConvertToString_t)(unsigned int index);
#if COD_VERSION == COD1_1_1
static const SL_ConvertToString_t SL_ConvertToString = (SL_ConvertToString_t)0x0809cac4;
#elif COD_VERSION == COD1_1_5
static const SL_ConvertToString_t SL_ConvertToString = (SL_ConvertToString_t)0x080a3460;
#endif

typedef int (*Scr_GetFunctionHandle_t)(const char* scriptName, const char* labelName);

typedef int (*Scr_GetNumParam_t)(void);
extern Scr_GetNumParam_t Scr_GetNumParam;

typedef char * (*Cmd_Argv_t)(int arg);
#if COD_VERSION == COD1_1_1
static const Cmd_Argv_t Cmd_Argv = (Cmd_Argv_t)0x0805b258;
#elif COD_VERSION == COD1_1_5
static const Cmd_Argv_t Cmd_Argv = (Cmd_Argv_t)0x080600f4;
#endif

typedef int (*Cmd_Argc_t)();
#if COD_VERSION == COD1_1_1
static const Cmd_Argc_t Cmd_Argc = (Cmd_Argc_t)0x0805b24c;
#elif COD_VERSION == COD1_1_5
static const Cmd_Argc_t Cmd_Argc = (Cmd_Argc_t)0x080600ea;
#endif

typedef void (*SV_Cmd_ArgvBuffer_t)(int arg, char *buffer, int bufferLength);

typedef void (*Com_Printf_t)(const char *format, ...);
#if COD_VERSION == COD1_1_1
static const Com_Printf_t Com_Printf = (Com_Printf_t)0x0806b760;
#elif COD_VERSION == COD1_1_5
static const Com_Printf_t Com_Printf = (Com_Printf_t)0x0806fc10;
#endif

typedef void (*Com_DPrintf_t)(const char *format, ...);
#if COD_VERSION == COD1_1_1
static const Com_DPrintf_t Com_DPrintf = (Com_DPrintf_t)0x0806b79c;
#elif COD_VERSION == COD1_1_5
static const Com_DPrintf_t Com_DPrintf = (Com_DPrintf_t)0x0806fc5f;
#endif

typedef int (*Com_sprintf_t)(char *dest, int size, const char *format, ...);
#if COD_VERSION == COD1_1_1
static const Com_sprintf_t Com_sprintf = (Com_sprintf_t)0x080823a0;
#elif COD_VERSION == COD1_1_5
static const Com_sprintf_t Com_sprintf = (Com_sprintf_t)0x080861a6;
#endif

typedef void (*Com_PrintMessage_t)(int channel, const char *message);
#if COD_VERSION == COD1_1_1
static const Com_PrintMessage_t Com_PrintMessage = (Com_PrintMessage_t)0x0806b530;
#elif COD_VERSION == COD1_1_5
static const Com_PrintMessage_t Com_PrintMessage = (Com_PrintMessage_t)0x0806f827;
#endif

typedef void (*ClientCommand_t)(int clientNum);
extern ClientCommand_t ClientCommand;

// FS
typedef void (*FS_ConvertPath_t)(char *s);
#if COD_VERSION == COD1_1_1
static const FS_ConvertPath_t FS_ConvertPath = (FS_ConvertPath_t)0x08062f4c;
#elif COD_VERSION == COD1_1_5
#endif

typedef int (*FS_Read_t)(void *buffer, int len, fileHandle_t f);
#if COD_VERSION == COD1_1_1
static const FS_Read_t FS_Read = (FS_Read_t)0x080628f4;
#elif COD_VERSION == COD1_1_5
static const FS_Read_t FS_Read = (FS_Read_t)0x08062960;
#endif

typedef long (*FS_SV_FOpenFileRead_t)(const char *filename, fileHandle_t *fp);
#if COD_VERSION == COD1_1_1
static const FS_SV_FOpenFileRead_t FS_SV_FOpenFileRead = (FS_SV_FOpenFileRead_t)0x0806ffb8;
#elif COD_VERSION == COD1_1_5
static const FS_SV_FOpenFileRead_t FS_SV_FOpenFileRead = (FS_SV_FOpenFileRead_t)0x08074596;
#endif

typedef int (*FS_idPak_t)(const char *a1, const char *a2);
#if COD_VERSION == COD1_1_1
static const FS_idPak_t FS_idPak = (FS_idPak_t)0x080709c0;
#elif COD_VERSION == COD1_1_5
static const FS_idPak_t FS_idPak = (FS_idPak_t)0x080754ea;
#endif

#if COD_VERSION == COD1_1_5
typedef qboolean (*FS_svrPak_t)(char *pak);
static const FS_svrPak_t FS_svrPak = (FS_svrPak_t)0x080756bf;
#endif
//

typedef xfunction_t (*Scr_GetFunction_t)(const char** v_functionName, qboolean *v_developer);
extern Scr_GetFunction_t Scr_GetFunction;

typedef xmethod_t (*Scr_GetMethod_t)(const char** v_methodName, qboolean *v_developer);
extern Scr_GetMethod_t Scr_GetMethod;

// Cvars
typedef cvar_t * (*Cvar_Set_t)(const char *var_name, const char *value);
#if COD_VERSION == COD1_1_1
static const Cvar_Set_t Cvar_Set = (Cvar_Set_t)0x0806f0b0;
#elif COD_VERSION == COD1_1_5
#endif

typedef cvar_t * (*Cvar_Set2_t)(const char *var_name, const char *value, qboolean force);
#if COD_VERSION == COD1_1_1
#elif COD_VERSION == COD1_1_5
static const Cvar_Set2_t Cvar_Set2 = (Cvar_Set2_t)0x08072da8;
#endif

typedef cvar_t * (*Cvar_Get_t)(const char *var_name, const char *var_value, unsigned short flags);
#if COD_VERSION == COD1_1_1
static const Cvar_Get_t Cvar_Get = (Cvar_Get_t)0x0806ea34;
#elif COD_VERSION == COD1_1_5
static const Cvar_Get_t Cvar_Get = (Cvar_Get_t)0x08072a7c;
#endif

typedef cvar_t * (*Cvar_FindVar_t)(const char *var_name);
#if COD_VERSION == COD1_1_1
static const Cvar_FindVar_t Cvar_FindVar = (Cvar_FindVar_t)0x0806e9b4;
#elif COD_VERSION == COD1_1_5
static const Cvar_FindVar_t Cvar_FindVar = (Cvar_FindVar_t)0x08072916;
#endif

typedef char * (*Cvar_GetString_t)(const char *cvarName);
#if COD_VERSION == COD1_1_1
static const Cvar_GetString_t Cvar_GetString = (Cvar_GetString_t)0x0806f8ec;
#elif COD_VERSION == COD1_1_5
#endif
//

#if COD_VERSION == COD1_1_1
typedef void (*SV_ClientEnterWorld_t)(client_t *cl, usercmd_t *cmd);
static const SV_ClientEnterWorld_t SV_ClientEnterWorld = (SV_ClientEnterWorld_t)0x080877d8;

typedef void (*SV_SendClientGameState_t)(client_t *cl);
static const SV_SendClientGameState_t SV_SendClientGameState = (SV_SendClientGameState_t)0x08085eec;

typedef qboolean (*Sys_IsLANAddress_t)(netadr_t adr);
static const Sys_IsLANAddress_t Sys_IsLANAddress = (Sys_IsLANAddress_t)0x080c72f8;

typedef void (*SV_AuthorizeRequest_t)(netadr_t adr, int challenge);
static const SV_AuthorizeRequest_t SV_AuthorizeRequest = (SV_AuthorizeRequest_t)0x08084d90;

typedef qboolean (*SV_ClientCommand_t)(client_t *cl, msg_t *msg);
static const SV_ClientCommand_t SV_ClientCommand = (SV_ClientCommand_t)0x08086e08;

typedef void (*SV_SendClientSnapshot_t)(client_t *cl);
static const SV_SendClientSnapshot_t SV_SendClientSnapshot = (SV_SendClientSnapshot_t)0x0808f844;

typedef void (*SV_UserMove_t)(client_t *cl, msg_t *msg, qboolean delta);
static const SV_UserMove_t SV_UserMove = (SV_UserMove_t)0x08086fa4;

typedef void (*SV_SpawnServer_t)(char *server);
static const SV_SpawnServer_t SV_SpawnServer = (SV_SpawnServer_t)0x0808a220;

typedef void (*SV_InitArchivedSnapshot_t)(void);
static const SV_InitArchivedSnapshot_t SV_InitArchivedSnapshot = (SV_InitArchivedSnapshot_t)0x0808b2c8;

typedef void (*SV_RestartGameProgs_t)(int savepersist);
static const SV_RestartGameProgs_t SV_RestartGameProgs = (SV_RestartGameProgs_t)0x08089350;

typedef void (*SV_RunFrame_t)(void);
static const SV_RunFrame_t SV_RunFrame = (SV_RunFrame_t)0x0808d3d4;

typedef void (*SV_AddServerCommand_t)(client_t *client, svscmd_type type, const char *cmd);
static const SV_AddServerCommand_t SV_AddServerCommand = (SV_AddServerCommand_t)0x0808b680;
#endif

typedef void (*SV_GameSendServerCommand_t)(int clientnum, svscmd_type type, const char *text);
extern SV_GameSendServerCommand_t SV_GameSendServerCommand;

typedef void (QDECL *SV_SendServerCommand_t)(client_t *cl, int type, const char *fmt, ...);
#if COD_VERSION == COD1_1_1
static const SV_SendServerCommand_t SV_SendServerCommand = (SV_SendServerCommand_t)0x0808b900;
#elif COD_VERSION == COD1_1_5
static const SV_SendServerCommand_t SV_SendServerCommand = (SV_SendServerCommand_t)0x080920de;
#endif

typedef void (*SV_DropClient_t)(client_t *drop, const char *reason);
#if COD_VERSION == COD1_1_1
static const SV_DropClient_t SV_DropClient = (SV_DropClient_t)0x08085cf4;
#elif COD_VERSION == COD1_1_5
static const SV_DropClient_t SV_DropClient = (SV_DropClient_t)0x0808ac11;
#endif

typedef void (*SV_UpdateServerCommandsToClient_t)(client_t *client, msg_t *msg);
#if COD_VERSION == COD1_1_1
#elif COD_VERSION == COD1_1_5
static const SV_UpdateServerCommandsToClient_t SV_UpdateServerCommandsToClient = (SV_UpdateServerCommandsToClient_t)0x080959d0;
#endif

typedef void (*Info_SetValueForKey_t)(char *s, const char *key, const char *value);
#if COD_VERSION == COD1_1_1
static const Info_SetValueForKey_t Info_SetValueForKey = (Info_SetValueForKey_t)0x080827d4;
#elif COD_VERSION == COD1_1_5
static const Info_SetValueForKey_t Info_SetValueForKey = (Info_SetValueForKey_t)0x08086855;
#endif

typedef char * (*Info_ValueForKey_t)(const char *s, const char *key);
#if COD_VERSION == COD1_1_1
static const Info_ValueForKey_t Info_ValueForKey = (Info_ValueForKey_t)0x08082460;
#elif COD_VERSION == COD1_1_5
static const Info_ValueForKey_t Info_ValueForKey = (Info_ValueForKey_t)0x08086397;
#endif

typedef short (*Scr_ExecThread_t)(int callbackHook, unsigned int numArgs);
extern Scr_ExecThread_t Scr_ExecThread;

typedef short (*Scr_ExecEntThread_t)(gentity_t* ent, int callbackHook, unsigned int numArgs);
extern Scr_ExecEntThread_t Scr_ExecEntThread;

typedef unsigned short (*Scr_ExecEntThreadNum_t)(int entnum, unsigned int classnum, int handle, unsigned int paramcount);
extern Scr_ExecEntThreadNum_t Scr_ExecEntThreadNum;

typedef short (*Scr_FreeThread_t)(short thread_id);
extern Scr_FreeThread_t Scr_FreeThread;

typedef void (*SVC_RemoteCommand_t)(netadr_t from, msg_t *msg);
#if COD_VERSION == COD1_1_1
static const SVC_RemoteCommand_t SVC_RemoteCommand = (SVC_RemoteCommand_t)0x0808c404;
#elif COD_VERSION == COD1_1_5
static const SVC_RemoteCommand_t SVC_RemoteCommand = (SVC_RemoteCommand_t)0x080930d0;
#endif

typedef void (*SV_GetChallenge_t)(netadr_t from);
#if COD_VERSION == COD1_1_1
static const SV_GetChallenge_t SV_GetChallenge = (SV_GetChallenge_t)0x08084d90;
#elif COD_VERSION == COD1_1_5
static const SV_GetChallenge_t SV_GetChallenge = (SV_GetChallenge_t)0x080889d0;
#endif

typedef void (*SV_DirectConnect_t)(netadr_t from);
#if COD_VERSION == COD1_1_1
static const SV_DirectConnect_t SV_DirectConnect = (SV_DirectConnect_t)0x08085498;
#elif COD_VERSION == COD1_1_5
static const SV_DirectConnect_t SV_DirectConnect = (SV_DirectConnect_t)0x08089e7e;
#endif

typedef void (*SVC_Info_t)(netadr_t from);
#if COD_VERSION == COD1_1_1
static const SVC_Info_t SVC_Info = (SVC_Info_t)0x0808c1ac;
#elif COD_VERSION == COD1_1_5
static const SVC_Info_t SVC_Info = (SVC_Info_t)0x08092a74;
#endif

typedef void (*SVC_Status_t)(netadr_t from);
#if COD_VERSION == COD1_1_1
static const SVC_Status_t SVC_Status = (SVC_Status_t)0x0808bd58;
#elif COD_VERSION == COD1_1_5
static const SVC_Status_t SVC_Status = (SVC_Status_t)0x0809246e;
#endif

typedef const char * (*NET_AdrToString_t)(netadr_t a);
#if COD_VERSION == COD1_1_1
static const NET_AdrToString_t NET_AdrToString = (NET_AdrToString_t)0x08080ef4;
#elif COD_VERSION == COD1_1_5
static const NET_AdrToString_t NET_AdrToString = (NET_AdrToString_t)0x08083e10;
#endif

typedef void (*Scr_Error_t)(const char *string);
extern Scr_Error_t Scr_Error;

// Game module
typedef int (QDECL *VM_Call_t)( int, int callnum, ... );
#if COD_VERSION == COD1_1_1
static const VM_Call_t VM_Call = (VM_Call_t)0x08092158;
#elif COD_VERSION == COD1_1_5
#endif

typedef void (*G_Say_t)(gentity_s *ent, gentity_s *target, int mode, const char *chatText);
extern G_Say_t G_Say;

typedef void (*G_RegisterCvars_t)(void);
extern G_RegisterCvars_t G_RegisterCvars;
//

typedef const char * (*SV_GetConfigstringConst_t)(int index);
extern SV_GetConfigstringConst_t SV_GetConfigstringConst;

typedef void (*SV_GetConfigstring_t)( int index, char *buffer, int bufferSize );
extern SV_GetConfigstring_t SV_GetConfigstring;

typedef void (*SV_SetConfigstring_t)(int index, const char *val);
#if COD_VERSION == COD1_1_1
static const SV_SetConfigstring_t SV_SetConfigstring = (SV_SetConfigstring_t)0x08089bf0;
#elif COD_VERSION == COD1_1_5
static const SV_SetConfigstring_t SV_SetConfigstring = (SV_SetConfigstring_t)0x0808ff60;
#endif

typedef void * (*Z_MallocInternal_t)(int size);
#if COD_VERSION == COD1_1_1
static const Z_MallocInternal_t Z_MallocInternal = (Z_MallocInternal_t)0x080681e8;
#elif COD_VERSION == COD1_1_5
static const Z_MallocInternal_t Z_MallocInternal = (Z_MallocInternal_t)0x0806bbcc;
#endif

// MSG
#if COD_VERSION == COD1_1_1
typedef int (*MSG_ReadBits_t)(msg_t *msg, int numBits);
static const MSG_ReadBits_t MSG_ReadBits = (MSG_ReadBits_t)0x0807f18c;
#endif

typedef int (*MSG_ReadBitsCompress_t)(const byte* input, byte* outputBuf, int readsize);
#if COD_VERSION == COD1_1_1
static const MSG_ReadBitsCompress_t MSG_ReadBitsCompress = (MSG_ReadBitsCompress_t)0x0807f23c;
#elif COD_VERSION == COD1_1_5
#endif

typedef void (*MSG_Init_t)(msg_t *buf, byte *data, int length);
#if COD_VERSION == COD1_1_1
static const MSG_Init_t MSG_Init = (MSG_Init_t)0x0807eeb8;
#elif COD_VERSION == COD1_1_5
static const MSG_Init_t MSG_Init = (MSG_Init_t)0x0807f928;
#endif

typedef void (*MSG_WriteByte_t)(msg_t *msg, int c);
#if COD_VERSION == COD1_1_1
static const MSG_WriteByte_t MSG_WriteByte = (MSG_WriteByte_t)0x0807f090;
#elif COD_VERSION == COD1_1_5
static const MSG_WriteByte_t MSG_WriteByte = (MSG_WriteByte_t)0x0807fcd8;
#endif

typedef void (*MSG_WriteShort_t)(msg_t *msg, int c);
#if COD_VERSION == COD1_1_1
static const MSG_WriteShort_t MSG_WriteShort = (MSG_WriteShort_t)0x0807f0bc;
#elif COD_VERSION == COD1_1_5
static const MSG_WriteShort_t MSG_WriteShort = (MSG_WriteShort_t)0x0807fd65;
#endif

typedef void (*MSG_WriteLong_t)(msg_t *msg, int c);
#if COD_VERSION == COD1_1_1
static const MSG_WriteLong_t MSG_WriteLong = (MSG_WriteLong_t)0x0807f0ec;
#elif COD_VERSION == COD1_1_5
static const MSG_WriteLong_t MSG_WriteLong = (MSG_WriteLong_t)0x0807fdb5;
#endif

typedef void (*MSG_WriteBigString_t)(msg_t *msg, const char *s);
#if COD_VERSION == COD1_1_1
#elif COD_VERSION == COD1_1_5
static const MSG_WriteBigString_t MSG_WriteBigString = (MSG_WriteBigString_t)0x0807fedb;
#endif

typedef void (*MSG_WriteString_t)(msg_t *msg, const char *s);
#if COD_VERSION == COD1_1_1
static const MSG_WriteString_t MSG_WriteString = (MSG_WriteString_t)0x0807a620;
#elif COD_VERSION == COD1_1_5
static const MSG_WriteString_t MSG_WriteString = (MSG_WriteString_t)0x0807fe03;
#endif

typedef void (*MSG_WriteData_t)(msg_t *msg, const void *data, int length);
#if COD_VERSION == COD1_1_1
static const MSG_WriteData_t MSG_WriteData = (MSG_WriteData_t)0x0807eef0;
#elif COD_VERSION == COD1_1_5
static const MSG_WriteData_t MSG_WriteData = (MSG_WriteData_t)0x0807fd10;
#endif

typedef void (*MSG_WriteDeltaEntity_t)(msg_t *msg, struct entityState_s *from, struct entityState_s *to, qboolean force);
#if COD_VERSION == COD1_1_1
#elif COD_VERSION == COD1_1_5
static const MSG_WriteDeltaEntity_t MSG_WriteDeltaEntity = (MSG_WriteDeltaEntity_t)0x0808149a;
#endif
//

typedef void (*SV_SendMessageToClient_t)(msg_t *msg, client_t *cl);
#if COD_VERSION == COD1_1_1
#elif COD_VERSION == COD1_1_5
static const SV_SendMessageToClient_t SV_SendMessageToClient = (SV_SendMessageToClient_t)0x08097a2f;
#endif

typedef void (*SV_Netchan_TransmitNextFragment_t)(netchan_t *chan);
#if COD_VERSION == COD1_1_1
#elif COD_VERSION == COD1_1_5
static const SV_Netchan_TransmitNextFragment_t SV_Netchan_TransmitNextFragment = (SV_Netchan_TransmitNextFragment_t)0x080948d0;
#endif

// Weapons
typedef int (*BG_GetNumWeapons_t)(void);
extern BG_GetNumWeapons_t BG_GetNumWeapons;

typedef WeaponDef_t * (*BG_GetInfoForWeapon_t)(unsigned int weaponIndex);
extern BG_GetInfoForWeapon_t BG_GetInfoForWeapon;

typedef int (*BG_GetWeaponIndexForName_t)(const char *name);
extern BG_GetWeaponIndexForName_t BG_GetWeaponIndexForName;
//

// Animations
typedef int (*BG_AnimationIndexForString_t)(char *src);
extern BG_AnimationIndexForString_t BG_AnimationIndexForString;
//

typedef int (*Scr_IsSystemActive_t)();

typedef int (*Scr_GetInt_t)(unsigned int param);
extern Scr_GetInt_t Scr_GetInt;

typedef const char * (*Scr_GetString_t)(unsigned int param);
extern Scr_GetString_t Scr_GetString;

typedef int (*Scr_GetType_t)(unsigned int param);
extern Scr_GetType_t Scr_GetType;

typedef gentity_t * (*Scr_GetEntity_t)(unsigned int index);
extern Scr_GetEntity_t Scr_GetEntity;

typedef void (*Scr_AddBool_t)(qboolean value);
extern Scr_AddBool_t Scr_AddBool;

typedef void (*Scr_AddInt_t)(int value);
extern Scr_AddInt_t Scr_AddInt;

typedef void (*Scr_AddFloat_t)(float value);
extern Scr_AddFloat_t Scr_AddFloat;

typedef void (*Scr_AddString_t)(const char *string);
extern Scr_AddString_t Scr_AddString;

typedef void (*Scr_AddUndefined_t)(void);
extern Scr_AddUndefined_t Scr_AddUndefined;

typedef void (*Scr_AddVector_t)(vec3_t vec);
extern Scr_AddVector_t Scr_AddVector;

typedef void (*Scr_MakeArray_t)(void);
extern Scr_MakeArray_t Scr_MakeArray;

typedef void (*Scr_AddArray_t)(void);
extern Scr_AddArray_t Scr_AddArray;

typedef void (*Scr_AddObject_t)(unsigned int object);
extern Scr_AddObject_t Scr_AddObject;

typedef unsigned int (*Scr_LoadScript_t)(const char *filename);

typedef playerState_t * (*SV_GameClientNum_t)(int num);
#if COD_VERSION == COD1_1_1
static const SV_GameClientNum_t SV_GameClientNum = (SV_GameClientNum_t)0x08089270;
#elif COD_VERSION == COD1_1_5
static const SV_GameClientNum_t SV_GameClientNum = (SV_GameClientNum_t)0x0808d331;
#endif

// Strings
typedef char * (*Q_strlwr_t)(char *s1);
extern Q_strlwr_t Q_strlwr;

typedef char * (*Q_strupr_t)(char *s1);
extern Q_strupr_t Q_strupr;

typedef void (*Q_strcat_t)(char *dest, int size, const char *src);

typedef void (*I_strncpyz_t)(char *dest, const char *src, int destsize);
static const I_strncpyz_t I_strncpyz = (I_strncpyz_t)0x08083288;
//

typedef void (*Com_Error_t)(errorParm_t code, const char *format, ...);
#if COD_VERSION == COD1_1_1
static const Com_Error_t Com_Error = (Com_Error_t)0x0806b93c;
#elif COD_VERSION == COD1_1_5
static const Com_Error_t Com_Error = (Com_Error_t)0x0806fe74;
#endif

typedef void (*SV_AuthorizeIpPacket_t)(netadr_t from);
#if COD_VERSION == COD1_1_1
static const SV_AuthorizeIpPacket_t SV_AuthorizeIpPacket = (SV_AuthorizeIpPacket_t)0x0808514c;
#elif COD_VERSION == COD1_1_5
static const SV_AuthorizeIpPacket_t SV_AuthorizeIpPacket = (SV_AuthorizeIpPacket_t)0x080893c1;
#endif

typedef qboolean (*StuckInClient_t)(gentity_s *self);
extern StuckInClient_t StuckInClient;

#endif