#include "gsc_weapons.hpp"

qboolean isValidWeaponId(int id)
{
    int weps = BG_GetNumWeapons();

    if ( id > weps || id <= 0 || weps == 0 )
        return qfalse;

    return qtrue;
}

void gsc_weapons_setweaponcookable()
{
    int id;
    char *name;
    int cookable;

    if ( stackGetParams("si", &name, &cookable) ) 
    {
        id = BG_GetWeaponIndexForName(name);
    }
    else if ( !stackGetParams("ii", &id, &cookable) )
    {
        stackError("gsc_weapons_setweaponcookable() one or more arguments is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( !isValidWeaponId(id) )
    {
        stackPushUndefined();
        return;
    }

    WeaponDef_t *weapon = BG_GetInfoForWeapon(id);
    weapon->cookOffHold = cookable;

    stackPushBool(qtrue);
}

void gsc_weapons_setweaponfusetime()
{
    int id;
    char *name;
    int time;

    if ( stackGetParams("si", &name, &time) ) 
    {
        id = BG_GetWeaponIndexForName(name);
    }
    else if ( !stackGetParams("ii", &id, &time) )
    {
        stackError("gsc_weapons_setweaponfusetime() one or more arguments is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( !isValidWeaponId(id) )
    {
        stackPushUndefined();
        return;
    }

    WeaponDef_t *weapon = BG_GetInfoForWeapon(id);
    weapon->fuseTime = time;

    stackPushBool(qtrue);
}