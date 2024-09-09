#ifndef _FUNCTIONS_HPP_
#define _FUNCTIONS_HPP_

// trap
typedef void (*trap_Argv_t)(int arg, char *buffer, int bufferLength);

typedef void (*trap_SendServerCommand_t)(int clientnum, svscmd_type type, const char *text);
extern trap_SendServerCommand_t trap_SendServerCommand;

typedef const char * (*trap_GetConfigstringConst_t)(int index);
extern trap_GetConfigstringConst_t trap_GetConfigstringConst;

typedef void (*trap_GetConfigstring_t)( int index, char *buffer, int bufferSize );
extern trap_GetConfigstring_t trap_GetConfigstring;
//

// Cmd
typedef char * (*Cmd_Argv_t)(int arg);
static const Cmd_Argv_t Cmd_Argv = (Cmd_Argv_t)0x0805b258;

typedef int (*Cmd_Argc_t)();
static const Cmd_Argc_t Cmd_Argc = (Cmd_Argc_t)0x0805b24c;

typedef void (*Cmd_AddCommand_t)(const char *cmd_name, xcommand_t function);
static const Cmd_AddCommand_t Cmd_AddCommand = (Cmd_AddCommand_t)0x0805aef8;

typedef void (*Cmd_ArgvBuffer_t)(int arg, char *buffer, int bufferLength);
static const Cmd_ArgvBuffer_t Cmd_ArgvBuffer = (Cmd_ArgvBuffer_t)0x0805b27c;

typedef void (*Cmd_TokenizeString_t)(const char *text_in);
static const Cmd_TokenizeString_t Cmd_TokenizeString = (Cmd_TokenizeString_t)0x0805b398;
//

// Com
typedef void (*Com_Printf_t)(const char *format, ...);
static const Com_Printf_t Com_Printf = (Com_Printf_t)0x0806b760;

typedef void (*Com_DPrintf_t)(const char *format, ...);
static const Com_DPrintf_t Com_DPrintf = (Com_DPrintf_t)0x0806b79c;

typedef int (*Com_sprintf_t)(char *dest, int size, const char *format, ...);
static const Com_sprintf_t Com_sprintf = (Com_sprintf_t)0x080823a0;

typedef void (*Com_PrintMessage_t)(int channel, const char *message);
static const Com_PrintMessage_t Com_PrintMessage = (Com_PrintMessage_t)0x0806b530;

typedef void (*Com_Error_t)(errorParm_t code, const char *format, ...);
static const Com_Error_t Com_Error = (Com_Error_t)0x0806b93c;

typedef char * (*Com_Parse_t)(const char **data_p);
static const Com_Parse_t Com_Parse = (Com_Parse_t)0x08081d1c;

typedef void (*Com_SkipRestOfLine_t)(const char **data);

typedef char * (*Com_ParseRestOfLine_t)(const char **data);

typedef int (*Com_ParseInt_t)(const char **data);
//

// FS
typedef void (*FS_ConvertPath_t)(char *s);
static const FS_ConvertPath_t FS_ConvertPath = (FS_ConvertPath_t)0x08062f4c;

typedef int (*FS_Read_t)(void *buffer, int len, fileHandle_t f);
static const FS_Read_t FS_Read = (FS_Read_t)0x080628f4;

typedef long (*FS_SV_FOpenFileRead_t)(const char *filename, fileHandle_t *fp);
static const FS_SV_FOpenFileRead_t FS_SV_FOpenFileRead = (FS_SV_FOpenFileRead_t)0x0806ffb8;

typedef int (*FS_idPak_t)(const char *a1, const char *a2);
static const FS_idPak_t FS_idPak = (FS_idPak_t)0x080709c0;

typedef int (*FS_ReadFile_t)(const char* qpath, void** buffer);
static const FS_ReadFile_t FS_ReadFile = (FS_ReadFile_t)0x0805e9dc;

typedef void (*FS_FreeFile_t)(void* buffer);
static const FS_FreeFile_t FS_FreeFile = (FS_FreeFile_t)0x080629f4;

typedef int (*FS_FOpenFileByMode_t)(const char *qpath, fileHandle_t *f, fsMode_t mode);
static const FS_FOpenFileByMode_t FS_FOpenFileByMode = (FS_FOpenFileByMode_t)0x08062388;

typedef void (*FS_Write_t)(fileHandle_t h, const char *fmt, ...);
static const FS_Write_t FS_Write = (FS_Write_t)0x0805e3b0;

typedef void (*FS_FCloseFile_t)(fileHandle_t f);
static const FS_FCloseFile_t FS_FCloseFile = (FS_FCloseFile_t)0x0805c114;

typedef void (*FS_WriteFile_t)(const char* filename, const void* buffer, int size);
static const FS_WriteFile_t FS_WriteFile = (FS_WriteFile_t)0x08062a2c;
//

// Cvar
typedef cvar_t * (*Cvar_Set_t)(const char *var_name, const char *value);
static const Cvar_Set_t Cvar_Set = (Cvar_Set_t)0x0806f0b0;

typedef cvar_t * (*Cvar_Get_t)(const char *var_name, const char *var_value, unsigned short flags);
static const Cvar_Get_t Cvar_Get = (Cvar_Get_t)0x0806ea34;

typedef cvar_t * (*Cvar_FindVar_t)(const char *var_name);
static const Cvar_FindVar_t Cvar_FindVar = (Cvar_FindVar_t)0x0806e9b4;

typedef char * (*Cvar_VariableString_t)(const char *cvarName);
static const Cvar_VariableString_t Cvar_VariableString = (Cvar_VariableString_t)0x0806f8ec;
//

// SV
typedef void (*SV_ClientEnterWorld_t)(client_t *cl, usercmd_t *cmd);
static const SV_ClientEnterWorld_t SV_ClientEnterWorld = (SV_ClientEnterWorld_t)0x080877d8;

typedef void (*SV_SendClientGameState_t)(client_t *cl);
static const SV_SendClientGameState_t SV_SendClientGameState = (SV_SendClientGameState_t)0x08085eec;

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

typedef void (QDECL *SV_SendServerCommand_t)(client_t *cl, int type, const char *fmt, ...);
static const SV_SendServerCommand_t SV_SendServerCommand = (SV_SendServerCommand_t)0x0808b900;

typedef void (*SV_DropClient_t)(client_t *drop, const char *reason);
static const SV_DropClient_t SV_DropClient = (SV_DropClient_t)0x08085cf4;

typedef void (*SVC_RemoteCommand_t)(netadr_t from, msg_t *msg);
static const SVC_RemoteCommand_t SVC_RemoteCommand = (SVC_RemoteCommand_t)0x0808c404;

typedef void (*SV_GetChallenge_t)(netadr_t from);
static const SV_GetChallenge_t SV_GetChallenge = (SV_GetChallenge_t)0x08084d90;

typedef void (*SV_DirectConnect_t)(netadr_t from);
static const SV_DirectConnect_t SV_DirectConnect = (SV_DirectConnect_t)0x08085498;

typedef void (*SV_SetConfigstring_t)(int index, const char *val);
static const SV_SetConfigstring_t SV_SetConfigstring = (SV_SetConfigstring_t)0x08089bf0;

typedef playerState_t * (*SV_GameClientNum_t)(int num);
static const SV_GameClientNum_t SV_GameClientNum = (SV_GameClientNum_t)0x08089270;

typedef void (*SV_AuthorizeIpPacket_t)(netadr_t from);
static const SV_AuthorizeIpPacket_t SV_AuthorizeIpPacket = (SV_AuthorizeIpPacket_t)0x0808514c;

typedef client_t * (*SV_GetPlayerByNum_t)(void);
static const SV_GetPlayerByNum_t SV_GetPlayerByNum = (SV_GetPlayerByNum_t)0x08083b9c;

typedef void (*SV_MapRestart_f_t)(void);
static const SV_MapRestart_f_t SV_MapRestart_f = (SV_MapRestart_f_t)0x08083de4;

typedef void (*SV_ExecuteClientCommand_t)(client_t *cl, char *s, qboolean clientOK);
static const SV_ExecuteClientCommand_t SV_ExecuteClientCommand = (SV_ExecuteClientCommand_t)0x08086d58;

typedef void (*SV_Netchan_AddOOBProfilePacket_t)(int iLength);
static const SV_Netchan_AddOOBProfilePacket_t SV_Netchan_AddOOBProfilePacket = (SV_Netchan_AddOOBProfilePacket_t)0x0808dd10;
//

// Info
typedef void (*Info_SetValueForKey_t)(char *s, const char *key, const char *value);
static const Info_SetValueForKey_t Info_SetValueForKey = (Info_SetValueForKey_t)0x080827d4;

typedef char * (*Info_ValueForKey_t)(const char *s, const char *key);
static const Info_ValueForKey_t Info_ValueForKey = (Info_ValueForKey_t)0x08082460;
//

// SVC
typedef void (*SVC_Info_t)(netadr_t from);
static const SVC_Info_t SVC_Info = (SVC_Info_t)0x0808c1ac;

typedef void (*SVC_Status_t)(netadr_t from);
static const SVC_Status_t SVC_Status = (SVC_Status_t)0x0808bd58;
//

// NET
typedef const char * (*NET_AdrToString_t)(netadr_t a);
static const NET_AdrToString_t NET_AdrToString = (NET_AdrToString_t)0x08080ef4;

typedef void (*NET_OutOfBandPrint_t)(netsrc_t net_socket, netadr_t adr, const char *format, ...);
static const NET_OutOfBandPrint_t NET_OutOfBandPrint = (NET_OutOfBandPrint_t)0x08080920;
//

// G
typedef void (*G_Say_t)(gentity_s *ent, gentity_s *target, int mode, const char *chatText);
extern G_Say_t G_Say;

typedef void (*G_RegisterCvars_t)(void);
extern G_RegisterCvars_t G_RegisterCvars;
//

// MSG
typedef int (*MSG_ReadBits_t)(msg_t *msg, int numBits);
static const MSG_ReadBits_t MSG_ReadBits = (MSG_ReadBits_t)0x0807f18c;

typedef int (*MSG_ReadBitsCompress_t)(const byte* input, byte* outputBuf, int readsize);
static const MSG_ReadBitsCompress_t MSG_ReadBitsCompress = (MSG_ReadBitsCompress_t)0x0807f23c;

typedef void (*MSG_Init_t)(msg_t *buf, byte *data, int length);
static const MSG_Init_t MSG_Init = (MSG_Init_t)0x0807eeb8;

typedef void (*MSG_WriteByte_t)(msg_t *msg, int c);
static const MSG_WriteByte_t MSG_WriteByte = (MSG_WriteByte_t)0x0807f090;

typedef void (*MSG_WriteShort_t)(msg_t *msg, int c);
static const MSG_WriteShort_t MSG_WriteShort = (MSG_WriteShort_t)0x0807f0bc;

typedef void (*MSG_WriteLong_t)(msg_t *msg, int c);
static const MSG_WriteLong_t MSG_WriteLong = (MSG_WriteLong_t)0x0807f0ec;

typedef void (*MSG_WriteString_t)(msg_t *msg, const char *s);
static const MSG_WriteString_t MSG_WriteString = (MSG_WriteString_t)0x0807a620;

typedef void (*MSG_WriteData_t)(msg_t *msg, const void *data, int length);
static const MSG_WriteData_t MSG_WriteData = (MSG_WriteData_t)0x0807eef0;

typedef char * (*MSG_ReadString_t)(msg_t *msg);
static const MSG_ReadString_t MSG_ReadString = (MSG_ReadString_t)0x0807f320;

typedef void (*MSG_BeginReading_t)(msg_t *buf);
static const MSG_BeginReading_t MSG_BeginReading = (MSG_BeginReading_t)0x0807f174;

typedef int (*MSG_ReadLong_t)(msg_t *msg);
static const MSG_ReadLong_t MSG_ReadLong = (MSG_ReadLong_t)0x0807f2f0;

typedef char * (*MSG_ReadStringLine_t)(msg_t *msg);
static const MSG_ReadStringLine_t MSG_ReadStringLine = (MSG_ReadStringLine_t)0x0807f3fc;
//

// Weapon
typedef int (*BG_GetNumWeapons_t)(void);
extern BG_GetNumWeapons_t BG_GetNumWeapons;

typedef WeaponDef_t * (*BG_GetInfoForWeapon_t)(unsigned int weaponIndex);
extern BG_GetInfoForWeapon_t BG_GetInfoForWeapon;

typedef int (*BG_GetWeaponIndexForName_t)(const char *name);
extern BG_GetWeaponIndexForName_t BG_GetWeaponIndexForName;
//

// Anim
typedef int (*BG_AnimationIndexForString_t)(char *src);
extern BG_AnimationIndexForString_t BG_AnimationIndexForString;
//

// Scr
typedef xfunction_t (*Scr_GetFunction_t)(const char** v_functionName, qboolean *v_developer);
extern Scr_GetFunction_t Scr_GetFunction;

typedef xmethod_t (*Scr_GetMethod_t)(const char** v_methodName, qboolean *v_developer);
extern Scr_GetMethod_t Scr_GetMethod;

typedef void (*Scr_Error_t)(const char *string);
extern Scr_Error_t Scr_Error;

typedef short (*Scr_ExecThread_t)(int callbackHook, unsigned int numArgs);
extern Scr_ExecThread_t Scr_ExecThread;

typedef short (*Scr_ExecEntThread_t)(gentity_t* ent, int callbackHook, unsigned int numArgs);
extern Scr_ExecEntThread_t Scr_ExecEntThread;

typedef unsigned short (*Scr_ExecEntThreadNum_t)(int entnum, unsigned int classnum, int handle, unsigned int paramcount);
extern Scr_ExecEntThreadNum_t Scr_ExecEntThreadNum;

typedef short (*Scr_FreeThread_t)(short thread_id);
extern Scr_FreeThread_t Scr_FreeThread;

typedef int (*Scr_GetFunctionHandle_t)(const char* scriptName, const char* labelName);

typedef int (*Scr_GetNumParam_t)(void);
extern Scr_GetNumParam_t Scr_GetNumParam;

typedef int (*Scr_IsSystemActive_t)();
extern Scr_IsSystemActive_t Scr_IsSystemActive;

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

typedef void (*Scr_ObjectError_t)(const char *error);
extern Scr_ObjectError_t Scr_ObjectError;

typedef unsigned short (*Scr_GetConstString_t)(unsigned int param);
extern Scr_GetConstString_t Scr_GetConstString;

typedef void (*Scr_ParamError_t)(int paramNum, const char *error);
extern Scr_ParamError_t Scr_ParamError;
//

// Q
typedef char * (*Q_strlwr_t)(char *s1);
extern Q_strlwr_t Q_strlwr;

typedef char * (*Q_strupr_t)(char *s1);
extern Q_strupr_t Q_strupr;

typedef void (*Q_strcat_t)(char *dest, int size, const char *src);

typedef void (*Q_strncpyz_t)(char *dest, const char *src, int destsize);

typedef void (*Q_CleanStr_t)(char *string);

typedef int (*Q_strncmp_t)(const char *s1, const char *s2, int n);
static const Q_strncmp_t Q_strncmp = (Q_strncmp_t)0x0808315c;
//

typedef qboolean (*StuckInClient_t)(gentity_s *self);
extern StuckInClient_t StuckInClient;

typedef qboolean (*Sys_IsLANAddress_t)(netadr_t adr);
static const Sys_IsLANAddress_t Sys_IsLANAddress = (Sys_IsLANAddress_t)0x080c72f8;

typedef void * (*Z_MallocInternal_t)(int size);
static const Z_MallocInternal_t Z_MallocInternal = (Z_MallocInternal_t)0x080681e8;

typedef unsigned int (*GetVariableName_t)(unsigned int a1);
static const GetVariableName_t GetVariableName = (GetVariableName_t)0x080a3060;

typedef unsigned int (*GetNextVariable_t)(unsigned int a1);
static const GetNextVariable_t GetNextVariable = (GetNextVariable_t)0x080a3028;

typedef char * (*SL_ConvertToString_t)(unsigned int index);
static const SL_ConvertToString_t SL_ConvertToString = (SL_ConvertToString_t)0x0809cac4;

typedef int (QDECL *VM_Call_t)( int, int callnum, ... );
static const VM_Call_t VM_Call = (VM_Call_t)0x08092158;

typedef void (*ClientCommand_t)(int clientNum);
extern ClientCommand_t ClientCommand;

typedef char* (*UI_GetMapRotationToken_t)(void);
static const UI_GetMapRotationToken_t UI_GetMapRotationToken = (UI_GetMapRotationToken_t)0x08084014;

typedef void (*Cbuf_ExecuteText_t)(cbufExec_t exec_when, const char* text);
static const Cbuf_ExecuteText_t Cbuf_ExecuteText = (Cbuf_ExecuteText_t)0x0805a8a0;

typedef void (*Huff_Decompress_t)(msg_t *mbuf, int offset);
static const Huff_Decompress_t Huff_Decompress = (Huff_Decompress_t)0x08071f7c;

typedef int (*Jump_Check_t)();

#endif