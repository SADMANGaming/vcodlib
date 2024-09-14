#include "gsc_bgame.hpp"
#define MAX_PS_EVENTS 2


void G_AddPredictableEvent( gentity_t *ent, int event, int eventParm ) {
	if ( !ent->client ) {
		return;
	}
	BG_AddPredictableEventToPlayerstate( event, eventParm, &ent->client->ps );
}

void BG_AddPredictableEventToPlayerstate( int newEvent, int eventParm, playerState_t *ps ) {

	ps->events[ps->eventSequence & (MAX_PS_EVENTS-1)] = newEvent;
	ps->eventParms[ps->eventSequence & (MAX_PS_EVENTS-1)] = eventParm;
	ps->eventSequence++;
}
