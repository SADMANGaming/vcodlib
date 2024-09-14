#ifndef _GSC_BGAME_HPP_
#define _GSC_BGAME_HPP_

#include "gsc.hpp"

void G_AddPredictableEvent( gentity_t *ent, int event, int eventParm );
void BG_AddPredictableEventToPlayerstate( int newEvent, int eventParm, playerState_t *ps );

#endif