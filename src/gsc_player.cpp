#include "gsc_player.hpp"

extern customPlayerState_t customPlayerState[MAX_CLIENTS];

void gsc_player_setvelocity(scr_entref_t ref)
{
    int id = ref.entnum;
    vec3_t velocity;

    if ( !stackGetParams("v", &velocity) )
    {
        stackError("gsc_player_setvelocity() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_setvelocity() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    playerState_t *ps = SV_GameClientNum(id);
    VectorCopy(velocity, ps->velocity);

    stackPushBool(qtrue);
}

void gsc_player_getvelocity(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_getvelocity() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    playerState_t *ps = SV_GameClientNum(id);

    stackPushVector(ps->velocity);
}

void gsc_player_getuserinfo(scr_entref_t ref)
{
    int id = ref.entnum;
    char *key;

    if ( !stackGetParams("s", &key) )
    {
        stackError("gsc_player_getuserinfo() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_getuserinfo() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    char *val = Info_ValueForKey(client->userinfo, key);

    if ( strlen(val) )
        stackPushString(val);
    else
        stackPushString("");
}

void gsc_player_setuserinfo(scr_entref_t ref)
{
    int id = ref.entnum;
    char *key, *value;

    if ( !stackGetParams("ss", &key, &value) )
    {
        stackError("gsc_player_setuserinfo() one or more arguments is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_setuserinfo() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    Info_SetValueForKey(client->userinfo, key, value);

    stackPushBool(qtrue);
}

void gsc_player_button_ads(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_ads() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.buttons & KEY_MASK_ADS_MODE ? qtrue : qfalse);
}

void gsc_player_button_left(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_left() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.rightmove == KEY_MASK_MOVELEFT ? qtrue : qfalse);
}

void gsc_player_button_right(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_right() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.rightmove == KEY_MASK_MOVERIGHT ? qtrue : qfalse);
}

void gsc_player_button_forward(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_forward() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.forwardmove == KEY_MASK_FORWARD ? qtrue : qfalse);
}

void gsc_player_button_back(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_back() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.forwardmove == KEY_MASK_BACK ? qtrue : qfalse);
}

void gsc_player_button_up(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_up() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.upmove == KEY_MASK_MOVEUP ? qtrue : qfalse);
}

void gsc_player_button_down(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_down() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.upmove == KEY_MASK_MOVEDOWN ? qtrue : qfalse);
}

void gsc_player_button_leanleft(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_leanleft() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    
    stackPushBool(client->lastUsercmd.wbuttons & KEY_MASK_LEANLEFT ? qtrue : qfalse);
}

void gsc_player_button_leanright(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_leanright() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.wbuttons & KEY_MASK_LEANRIGHT ? qtrue : qfalse);
}

void gsc_player_button_reload(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_button_reload() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    stackPushBool(client->lastUsercmd.wbuttons & KEY_MASK_RELOAD ? qtrue : qfalse);
}

void gsc_player_gettagangles(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_gettagangles() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }
    
    playerState_t *ps = SV_GameClientNum(id);

    stackPushVector(ps->viewangles);
}

void gsc_player_getstance(scr_entref_t ref)
{
    int id = ref.entnum;
    
    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_getstance() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }
    
    playerState_t *ps = SV_GameClientNum(id);
    if ( ps->eFlags & EF_CROUCHING )
        stackPushString("crouch");
    else if ( ps->eFlags & EF_PRONE )
        stackPushString("prone");
    else
        stackPushString("stand");
}

void gsc_player_getip(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_getip() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    char tmp[16];
    snprintf(tmp, sizeof(tmp), "%d.%d.%d.%d", client->netchan.remoteAddress.ip[0], client->netchan.remoteAddress.ip[1], client->netchan.remoteAddress.ip[2], client->netchan.remoteAddress.ip[3]);

    stackPushString(tmp);
}

void gsc_player_getping(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_getping() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    stackPushInt(client->ping);
}

void gsc_player_processclientcommand(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_processclientcommand() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    ClientCommand(id);

    stackPushBool(qtrue);
}

void gsc_player_dropclient(scr_entref_t ref)
{
    int id = ref.entnum;
    char *reason;

    if ( Scr_GetNumParam() > 0 && !stackGetParams("s", &reason) )
    {
        stackError("gsc_player_dropclient() argument has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_dropclient() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];

    if(Scr_GetNumParam() > 0)
        SV_DropClient(client, reason);
    else
        SV_DropClient(client, NULL);

    stackPushBool(qtrue);
}

void gsc_player_setspeed(scr_entref_t ref)
{
    int id = ref.entnum;
    int speed;

    if ( !stackGetParams("i", &speed) )
    {
        stackError("gsc_player_setspeed() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_setspeed() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    if ( speed < 0 )
    {
        stackError("gsc_player_setspeed() param must be equal or above zero");
        stackPushUndefined();
        return;
    }

    customPlayerState[id].speed = speed;

    stackPushBool(qtrue);
}

void gsc_player_getfps(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_getfps() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    stackPushInt(customPlayerState[id].fps);
}

void gsc_player_isonladder(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_isonladder() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    playerState_t *ps = SV_GameClientNum(id);

    stackPushBool(ps->pm_flags & PMF_LADDER ? qtrue : qfalse);
}

void gsc_player_setufo(scr_entref_t ref)
{
    int id = ref.entnum;
    int state;

    if ( !stackGetParams("i", &state) )
    {
        stackError("gsc_player_setufo() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_setufo() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    if (state != 0 && state != 1)
    {
        stackError("gsc_player_setufo() param must be 0 or 1");
        stackPushUndefined();
        return;
    }

    customPlayerState[id].ufo = state;

    stackPushBool(qtrue);
}

void gsc_player_connectionlesspackettoclient(scr_entref_t ref)
{
    int id = ref.entnum;
    char *cmd;

    if ( !stackGetParams("s", &cmd) )
    {
        stackError("gsc_player_connectionlesspackettoclient() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_connectionlesspackettoclient() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    NET_OutOfBandPrint(NS_SERVER, client->netchan.remoteAddress, cmd);

    stackPushBool(qtrue);
}

void gsc_player_isbot(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_isbot() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    client_t *client = &svs.clients[id];
    stackPushBool(client->bIsTestClient); // Use the bot field instead of bIsTestClient

    return;
}
void gsc_player_getlastconnecttime(scr_entref_t ref)
{
	int id = ref.entnum;

	if ( id >= MAX_CLIENTS )
	{
		stackError("gsc_player_getlastconnecttime() entity %i is not a player", id);
		stackPushUndefined();
		return;
	}

	client_t *client = &svs.clients[id];

	stackPushInt(client->lastConnectTime);
}

void gsc_player_setgravity(scr_entref_t ref)
{
	int id = ref.entnum;
    int gravity;

	if ( !stackGetParams("i", &gravity) )
	{
		stackError("gsc_player_setgravity() argument is undefined or has a wrong type");
		stackPushUndefined();
		return;
	}

	if ( id >= MAX_CLIENTS )
	{
		stackError("gsc_player_setgravity() entity %i is not a player", id);
		stackPushUndefined();
		return;
	}

	if ( gravity < 0 )
	{
		stackError("gsc_player_setgravity() param must be equal or above zero");
		stackPushUndefined();
		return;
	}

	customPlayerState[id].gravity = gravity;

	stackPushBool(qtrue);
}
void gsc_player_setjumpheight(scr_entref_t ref)
{
    int id = ref.entnum;
    float jump_height;

    if ( !stackGetParams("f", &jump_height) )
    {
        stackError("gsc_player_setjumpheight() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_setjumpheight() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    if ( jump_height < 0 )
        customPlayerState[id].overrideJumpHeight = false;
    else
    {
        customPlayerState[id].overrideJumpHeight = true;
        customPlayerState[id].jumpHeight = jump_height;
    }

    stackPushBool(qtrue);
}
void gsc_player_setairjumps(scr_entref_t ref)
{
    int id = ref.entnum;
    int airJumps;

    if (!stackGetParams("i", &airJumps))
    {
        stackError("gsc_player_setairjumps() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if (id >= MAX_CLIENTS)
    {
        stackError("gsc_player_setairjumps() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    customPlayerState[id].airJumpsAvailable = airJumps;

    stackPushBool(qtrue);
}


void gsc_player_setstance(scr_entref_t ref)
{
	int id = ref.entnum;
	char *stance;

	if ( !stackGetParams("s", &stance) )
	{
		stackError("gsc_player_setstance() argument is undefined or has a wrong type");
		stackPushUndefined();
		return;
	}

	gentity_t *entity = &g_entities[id];

	if ( entity->client == NULL )
	{
		stackError("gsc_player_setstance() entity %i is not a player", id);
		stackPushUndefined();
		return;
	}

	int event;

	if ( strcmp(stance, "stand") == 0 )
		event = EV_STANCE_FORCE_STAND;
	else if ( strcmp(stance, "crouch") == 0 )
		event = EV_STANCE_FORCE_CROUCH;
	else if ( strcmp(stance, "prone") == 0 )
		event = EV_STANCE_FORCE_PRONE;
	else
	{
		stackError("gsc_player_setstance() invalid argument '%s'. Valid arguments are: 'stand', 'crouch', 'prone'", stance);
		stackPushUndefined();
		return;
	}

	G_AddPredictableEvent(entity, event, 0);

	stackPushBool(qtrue);
}