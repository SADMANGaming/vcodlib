#include "gsc_entity.hpp"

void gsc_entity_setbounds(scr_entref_t ref)
{
	int id = ref.entnum;
	float width, height;

	if ( !stackGetParams("ff", &width, &height) )
	{
		stackError("gsc_entity_setbounds() one or more arguments is undefined or has a wrong type");
		stackPushUndefined();
		return;
	}

	gentity_t *entity = &g_entities[id];

	vec3_t mins = {-height, -width, -width};
	vec3_t maxs = {width, width, height};

	VectorCopy(mins, entity->r.mins);
	VectorCopy(maxs, entity->r.maxs);

	stackPushBool(qtrue);
}

void gsc_entity_showtoplayer(scr_entref_t ref) //TODO: try like cod2rev instead
{
    int id = ref.entnum;
    gentity_t *clientEnt;
    gentity_t *pEnt;

    pEnt = &g_entities[id];
    if(Scr_GetType(0) == STACK_UNDEFINED)
    {
        pEnt->r.svFlags &= ~SVF_SINGLECLIENT;
        pEnt->r.singleClient = 0;
        stackPushBool(qtrue);
        return;
    }
    
    clientEnt = Scr_GetEntity(0);
    if ( clientEnt->s.number >= MAX_CLIENTS )
    {
        stackError("gsc_entity_showtoplayer() param must be a client entity");
        return;
    }
    
    pEnt->r.svFlags |= SVF_SINGLECLIENT;
    pEnt->r.singleClient = clientEnt->s.number;

    stackPushBool(qtrue);
}