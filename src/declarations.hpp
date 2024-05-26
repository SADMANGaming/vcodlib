#ifndef _DECLARATIONS_HPP_
#define _DECLARATIONS_HPP_

#include <setjmp.h>

#define QDECL __attribute__((cdecl))

#define qboolean int
#define qtrue 1
#define qfalse 0

// 3D vectors
#define VectorCopy( a, b )          ( ( b )[0] = ( a )[0],( b )[1] = ( a )[1],( b )[2] = ( a )[2] )
#define VectorScale( v, s, o )      ( ( o )[0] = ( v )[0] * ( s ),( o )[1] = ( v )[1] * ( s ),( o )[2] = ( v )[2] * ( s ) )

#define BIG_INFO_STRING             0x2000
#define GENTITYNUM_BITS             10
#define PACKET_BACKUP               32

#define MAX_CHALLENGES              1024
#define MAX_CLIENTS                 64
#define MAX_CONFIGSTRINGS           2048
#define MAX_DOWNLOAD_BLKSIZE        2048
#define MAX_DOWNLOAD_WINDOW         8
#define MAX_GENTITIES               ( 1 << GENTITYNUM_BITS )
#define MAX_INFO_STRING             0x400
#define MAX_MSGLEN                  0x4000
#define MAX_OSPATH                  256
#define MAX_QPATH                   64
#define	MAX_NAME_LENGTH             32
#define MAX_RELIABLE_COMMANDS       64
#define MAX_STRINGLENGTH            1024

#define CVAR_NOFLAG             0               // 0x0000
#define CVAR_ARCHIVE            (1 << 0)        // 0x0001
#define CVAR_SERVERINFO         (1 << 2)        // 0x0004
#define CVAR_SYSTEMINFO         (1 << 3)        // 0x0008
#define CVAR_CHEAT              (1 << 9)        // 0x0200

#define SVF_SINGLECLIENT        0x800

#define KEY_MASK_FORWARD    127
#define KEY_MASK_BACK       129
#define KEY_MASK_MOVERIGHT  127
#define KEY_MASK_MOVELEFT   129
#define KEY_MASK_MOVEUP     127
#define KEY_MASK_MOVEDOWN   129

#define KEY_MASK_RELOAD         0x8
#define KEY_MASK_LEANLEFT       0x10
#define KEY_MASK_LEANRIGHT      0x20
#define KEY_MASK_ADS_MODE       0x10

// playerState_t->eFlags
// entityState_t->eFlags
#define EF_CROUCHING    0x20
#define EF_PRONE        0x40

#if COD_VERSION == COD1_1_5
#define PMF_JUMPING         0x2000
#endif

typedef unsigned char byte;
typedef signed char sbyte;
typedef struct gclient_s gclient_t;
typedef struct gentity_s gentity_t;

typedef struct scr_entref_s
{
    uint16_t entnum;
    uint16_t classnum;
} scr_entref_t;

typedef enum
{
    ERR_FATAL = 0x0,
    ERR_VID_FATAL = 0x1,
    ERR_DROP = 0x2,
    ERR_SERVERDISCONNECT = 0x3,
    ERR_DISCONNECT = 0x4,
    ERR_NEED_CD = 0x5,
    ERR_AUTOUPDATE = 0x6,
} errorParm_t;

enum svc_ops_e
{
    svc_bad,
    svc_nop,
    svc_gamestate,
    svc_configstring,
    svc_baseline,
    svc_serverCommand,
    svc_download,
    svc_snapshot,
    svc_EOF
};

typedef enum
{
    ET_GENERAL = 0x0,
    ET_PLAYER = 0x1,
    ET_PLAYER_CORPSE = 0x2,
    ET_ITEM = 0x3,
    ET_MISSILE = 0x4,
    ET_INVISIBLE = 0x5,
    ET_SCRIPTMOVER = 0x6,
    ET_FX = 0x7,
    ET_LOOP_FX = 0x8,
    ET_TURRET = 0x9,
    ET_EVENTS = 0xA
} entityType_t;

typedef enum
{
    CS_FREE,
    CS_ZOMBIE,
    CS_CONNECTED,
    CS_PRIMED,
    CS_ACTIVE
} clientConnectState_t;

typedef enum
{
	STATE_PLAYING,
	STATE_DEAD,
	STATE_SPECTATOR,
	STATE_INTERMISSION
} sessionState_t;

typedef enum
{
    NA_BOT = 0,
    NA_BAD = 0,
    NA_LOOPBACK = 2,
    NA_BROADCAST = 3,
    NA_IP = 4,
    NA_IPX = 5,
    NA_BROADCAST_IPX = 6
} netadrtype_t;

typedef struct
{
    netadrtype_t type;
    byte ip[4];
    unsigned short port;
    byte ipx[10];
} netadr_t;

typedef enum
{
    NS_CLIENT,
    NS_SERVER
} netsrc_t;

typedef struct
{
    qboolean overflowed;
    byte *data;
    int maxsize;
    int cursize;
    int readcount;
    int bit;
} msg_t;

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];

typedef struct cvar_s
{
    char *name;
    char *string;
    char *resetString;
    char *latchedString;
    int flags;
    qboolean modified;
    int modificationCount;
    float value;
    int integer;
    struct cvar_s *next;
    struct cvar_s *hashNext;
} cvar_t;

union VariableUnion
{
    int intValue;
    float floatValue;
    unsigned int stringValue;
    const float *vectorValue;
    const char *codePosValue;
    unsigned int pointerValue;
    //...
};

typedef struct
{
    union VariableUnion u;
    int type;
} VariableValue;

typedef struct
{
    const char *fieldBuffer;
    struct HunkUser *programHunkUser;
    uint16_t canonicalStrCount;
    byte developer;
    byte developer_script;
    byte evaluate;
    byte pad[3];
    const char *error_message;
    int error_index;
    unsigned int time;
    unsigned int timeArrayId;
    unsigned int pauseArrayId;
    unsigned int levelId;
    unsigned int gameId;
    unsigned int animId;
    unsigned int freeEntList;
    unsigned int tempVariable;
    byte bInited;
    byte pad2;
    uint16_t savecount;
    unsigned int checksum;
    unsigned int entId;
    unsigned int entFieldName;
    const char *programBuffer;
    const char *endScriptBuffer;
} scrVarPub_t; // TODO: verify

typedef struct
{
    unsigned int *localVars;
    byte pad[356];
    VariableValue *top;
    //...
} scrVmPub_t;

typedef int	fileHandle_t;
typedef void *unzFile;
typedef void (*xfunction_t)();
typedef void (*xmethod_t)(scr_entref_t);

typedef struct scr_function_s
{
    const char      *name;
    xfunction_t     call;
    qboolean        developer;
} scr_function_t;

typedef struct scr_method_s
{
    const char     *name;
    xmethod_t      call;
    qboolean       developer;
} scr_method_t;

struct directory_t
{
    char path[MAX_OSPATH];
    char gamedir[MAX_OSPATH];
};

struct pack_t
{
    char pakFilename[MAX_OSPATH];
    char pakBasename[MAX_OSPATH];
    char pakGamename[MAX_OSPATH];
    unzFile handle;
    int checksum;
    int pure_checksum;
    int numFiles;
    int referenced;
    int hashSize;
    //...
};

struct searchpath_t
{
    searchpath_t *next;
    pack_t *pak;
    directory_t *dir;
    //...
};

typedef struct leakyBucket_s leakyBucket_t;
struct leakyBucket_s
{
    netadrtype_t type;
    unsigned char adr[4];
    uint64_t lastTime;
    signed char	burst;
    long hash;
    leakyBucket_t *prev, *next;
};

typedef struct usercmd_s
{
    int serverTime;
    byte buttons; // console, chat, ads, attack, use
    byte wbuttons; // lean left, lean right, reload
    byte weapon;
    byte flags;
    int angles[3];
    signed char forwardmove, rightmove, upmove;
    byte unknown;
} usercmd_t;

typedef void netProfileInfo_t;

typedef struct
{
    netsrc_t sock;
    int dropped;
    netadr_t remoteAddress;
    int qport;
    int incomingSequence;
    int outgoingSequence;
    int fragmentSequence;
    int fragmentLength;
    byte fragmentBuffer[MAX_MSGLEN];
    qboolean unsentFragments;
    int unsentFragmentStart;
    int unsentLength;
    byte unsentBuffer[MAX_MSGLEN];
    netProfileInfo_t *netProfile;
} netchan_t;

typedef struct
{
    char command[MAX_STRINGLENGTH];
    int cmdTime;
    int cmdType;
} reliableCommands_t;

typedef struct
{
    netadr_t adr;
    int challenge;
    int time;
    int pingTime;
    int firstTime;
    int firstPing;
    qboolean connected;
    int guid;
#if COD_VERSION == COD1_1_5
    char pbguid[64];
    int ipAuthorize;
#endif
} challenge_t;

typedef enum
{
    TR_STATIONARY = 0,
    TR_INTERPOLATE = 1,
    TR_LINEAR = 2,
    TR_LINEAR_STOP = 3,
    TR_SINE = 4,
    TR_GRAVITY = 5,
    TR_GRAVITY_PAUSED = 6,
    TR_ACCELERATE = 7,
    TR_DECCELERATE = 8
} trType_t;

typedef struct
{
    trType_t trType;
    int trTime;
    int trDuration;
    vec3_t trBase;
    vec3_t trDelta;
} trajectory_t;

typedef struct entityState_s
{
    int number;
    entityType_t eType;
    int eFlags;
    trajectory_t pos;
    trajectory_t apos;
    int time;
    int time2;
    vec3_t origin2;
    vec3_t angles2;
    int otherEntityNum;
    int attackerEntityNum;
    int groundEntityNum;
    int constantLight;
    int loopSound;
    int surfType;
    int index; // modelIndex
    int clientNum;
    int iHeadIcon;
    int iHeadIconTeam;
    int solid;
    int eventParm;
    int eventSequence;
    int events[4];
    unsigned int eventParms[4];
    int weapon;
    int legsAnim;
    int torsoAnim;
    int leanf;
    int scale; // used as loopfxid, hintstring, ... and doesn't actually scale a player's model size
    int dmgFlags;
    int animMovetype;
    float fTorsoHeight;
    float fTorsoPitch;
    float fWaistPitch;
} entityState_t;

typedef struct
{
    byte pad[4];
    int svFlags;
    int singleClient;
    byte pad2[4];
    vec3_t mins;
    vec3_t maxs;
    int contents;
    vec3_t absmin;
    vec3_t absmax;
    vec3_t currentOrigin;
    vec3_t currentAngles;
    int ownerNum;
    int eventTime;
} entityShared_t;

typedef enum
{
    PM_NORMAL = 0x0,
    PM_NORMAL_LINKED = 0x1,
    PM_NOCLIP = 0x2,
    PM_UFO = 0x3,
    PM_SPECTATOR = 0x4,
    PM_INTERMISSION = 0x5,
    PM_DEAD = 0x6,
    PM_DEAD_LINKED = 0x7,
} pmtype_t;

typedef enum
{
    WEAPON_READY = 0x0,
    WEAPON_RAISING = 0x1,
    WEAPON_DROPPING = 0x2,
    WEAPON_FIRING = 0x3,
    WEAPON_RECHAMBERING = 0x4,
    WEAPON_RELOADING = 0x5,
    WEAPON_RELOADING_INTERUPT = 0x6,
    WEAPON_RELOAD_START = 0x7,
    WEAPON_RELOAD_START_INTERUPT = 0x8,
    WEAPON_RELOAD_END = 0x9,
    WEAPON_MELEE_INIT = 0xA,
    WEAPON_MELEE_FIRE = 0xB,
    WEAPONSTATES_NUM = 0xC,
} weaponstate_t;

typedef struct playerState_s
{
    int commandTime;
    pmtype_t pm_type;
    int bobCycle;
    int pm_flags;
    int pm_time;
    vec3_t origin;
    vec3_t velocity;
    vec2_t oldVelocity;
    int weaponTime;
    int weaponDelay;
    int gravity;
    float leanf;
    int speed;
    vec3_t delta_angles;
    int groundEntityNum;
    vec3_t vLadderVec;
    int jumpTime;
    float jumpOriginZ;
    int legsTimer;
    int legsAnim;
    int torsoTimer;
    int torsoAnim;
    int movementDir;
    int eFlags;
    int eventSequence;
    int events[4];
    unsigned int eventParms[4];
    int oldEventSequence;
    int clientNum;
    unsigned int weapon;
    weaponstate_t weaponstate;
    float fWeaponPosFrac;
    int adsDelayTime;
    //TODO: check if one of two the above is "int viewmodelIndex" instead
    vec3_t viewangles;
#if COD_VERSION == COD1_1_1
    byte pad[8196];
#elif COD_VERSION == COD1_1_5
    byte pad[8192];
#endif
} playerState_t;

#if COD_VERSION == COD1_1_1
typedef struct
{
	sessionState_t sessionState;
    //...
} clientSession_t;

struct gclient_s
{
	playerState_t ps;
	clientSession_t sess;
    //...
};
#endif

struct gentity_s
{
  entityState_t s;
  entityShared_t r;
  byte pad[4];
  struct gclient_s *client;
  byte pad2[440];
};

typedef struct
{
    playerState_t ps;
    int num_entities;
    int num_clients;
    int first_entity;
    int first_client;
    unsigned int messageSent;
    unsigned int messageAcked;
    int messageSize;
} clientSnapshot_t;

typedef struct client_s
{
    clientConnectState_t state;
    qboolean delayed;
    const char *delayDropMsg;
    char userinfo[MAX_INFO_STRING];
    reliableCommands_t	reliableCommands[MAX_RELIABLE_COMMANDS];
    int reliableSequence;
    int reliableAcknowledge;
    int reliableSent;
    int messageAcknowledge;
    int gamestateMessageNum;
    int challenge;
    usercmd_t lastUsercmd;
    int lastClientCommand;
    char lastClientCommandString[MAX_STRINGLENGTH];
    gentity_t *gentity;
    char name[MAX_NAME_LENGTH];
    char downloadName[MAX_QPATH];
    fileHandle_t download;
    int downloadSize;
    int downloadCount;
    int downloadClientBlock;
    int downloadCurrentBlock;
    int downloadXmitBlock;
    unsigned char *downloadBlocks[MAX_DOWNLOAD_WINDOW];
    int downloadBlockSize[MAX_DOWNLOAD_WINDOW];
    qboolean downloadEOF;
    int downloadSendTime;
#if COD_VERSION == COD1_1_5
    char wwwDownloadURL[MAX_OSPATH];
    qboolean wwwDownload;
    qboolean wwwDownloadStarted;
    qboolean wwwDlAck;
    qboolean wwwDl_failed;
#endif
    int deltaMessage;
    int nextReliableTime;
    int lastPacketTime;
    int lastConnectTime;
    int nextSnapshotTime;
    qboolean rateDelayed;
    int timeoutCount;
    clientSnapshot_t frames[PACKET_BACKUP];
    int ping;
    int rate;
    int snapshotMsec;
    int pureAuthentic;
    netchan_t netchan;
#if COD_VERSION == COD1_1_5
    int guid;
#endif
    unsigned short clscriptid;
    int bot;
    int serverId;
#if COD_VERSION == COD1_1_5
    char PBguid[33];
#endif
} client_t;

typedef struct
{
    qboolean initialized;
#if COD_VERSION == COD1_1_1
    byte pad[8];
#elif COD_VERSION == COD1_1_5
    byte pad[10];
#endif
    client_t *clients;
    //...
} serverStatic_t;

typedef enum
{
    SS_DEAD,
    SS_LOADING,
    SS_GAME
} serverState_t;

enum svscmd_type
{
    SV_CMD_CAN_IGNORE = 0x0,
    SV_CMD_RELIABLE = 0x1,
};

#if COD_VERSION == COD1_1_5
typedef struct WeaponDef_t
{
    int number;
    char* name;
    char* displayName;
    byte pad[0x1E4];
    int reloadAddTime;
    byte pad2[0x20];
    float moveSpeedScale;
    float adsZoomFov;
    float adsZoomInFrac;
    float adsZoomOutFrac;
    byte pad3[0x44];
    int adsTransInTime;
    int adsTransOutTime;
    byte pad4[0x8];
    float idleCrouchFactor;
    float idleProneFactor;
    byte pad5[0x50];
    int rechamberWhileAds;
    float adsViewErrorMin;
    float adsViewErrorMax;
    byte pad6[0x14C];
    float OOPosAnimLength[2];
    //...
} WeaponDef_t;

struct WeaponProperties // Custom struct for g_legacyStyle
{
    int reloadAddTime;
    int adsTransInTime;
    float adsZoomInFrac;
    float idleCrouchFactor;
    float idleProneFactor;
    int rechamberWhileAds;
    float adsViewErrorMin;
    float adsViewErrorMax;
};
#endif

struct pmove_t
{
    playerState_t *ps;
    usercmd_t cmd;
    //...
};

extern gentity_t *g_entities;

#if COD_VERSION == COD1_1_1
static const int varpub_offset = 0x082f17d8;
#elif COD_VERSION == COD1_1_5
static const int varpub_offset = 0x08306cb8;
#endif

#if COD_VERSION == COD1_1_1
static const int vmpub_offset = 0x082f57e0;
#elif COD_VERSION == COD1_1_5
static const int vmpub_offset = 0x0830acc0;
#endif

#if COD_VERSION == COD1_1_1
#elif COD_VERSION == COD1_1_5
static const int sv_offset = 0x0836b820;
#endif

#if COD_VERSION == COD1_1_1
static const int svs_offset = 0x083b67a0;
#elif COD_VERSION == COD1_1_5
static const int svs_offset = 0x083ccd80;
#endif

#if COD_VERSION == COD1_1_1
static const int fs_searchpaths_offset = 0x080dd590;
#elif COD_VERSION == COD1_1_5
static const int fs_searchpaths_offset = 0x080e8c30;
#endif

#define scrVarPub (*((scrVarPub_t*)( varpub_offset )))
#define scrVmPub (*((scrVmPub_t*)( vmpub_offset )))
//#define sv (*((server_t*)( sv_offset )))
#define svs (*((serverStatic_t*)( svs_offset )))
#define fs_searchpaths (*((searchpath_t**)( fs_searchpaths_offset )))

// Check for critical structure sizes and fail if not match
#if __GNUC__ >= 6

static_assert((sizeof(netchan_t) == 32832), "ERROR: netchan_t size is invalid!");
static_assert((sizeof(entityState_t) == 240), "ERROR: entityState_t size is invalid!");
#if COD_VERSION == COD1_1_1
static_assert((sizeof(client_t) == 370940), "ERROR: client_t size is invalid!");
static_assert((sizeof(playerState_t) == 8400), "ERROR: playerState_t size is invalid!");
static_assert((sizeof(entityShared_t) == 100), "ERROR: entityShared_t size is invalid!");
static_assert((sizeof(gentity_t) == 788), "ERROR: gentity_t size is invalid!");
#elif COD_VERSION == COD1_1_5
static_assert((sizeof(client_t) == 371124), "ERROR: client_t size is invalid!");
static_assert((sizeof(playerState_t) == 8396), "ERROR: playerState_t size is invalid!");
#endif

#endif

#endif

// Custom data types

#define MAX_ERROR_BUFFER 64

typedef struct src_error_s
{
    char internal_function[64];
    char message[1024];
} scr_error_t;

typedef struct customPlayerState_s
{
    int speed;
    int fps;
    int frames;
    uint64_t frameTime;
} customPlayerState_t;

typedef struct callback_s
{
    int *pos;
    const char *name;
} callback_t;