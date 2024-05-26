#include "gsc.hpp"
#include "vcodlib.hpp"

#include <stdint.h>
#include <sys/time.h>

scr_function_t scriptFunctions[] =
{
    #if COMPILE_SQLITE == 1
    {"sqlite_open", gsc_sqlite_open, 0},
    {"sqlite_query", gsc_sqlite_query, 0},
    {"sqlite_close", gsc_sqlite_close, 0},
    {"sqlite_escape_string", gsc_sqlite_escape_string, 0},
    {"sqlite_databases_count", gsc_sqlite_databases_count, 0},
    {"sqlite_tasks_count", gsc_sqlite_tasks_count, 0},
    {"async_sqlite_initialize", gsc_async_sqlite_initialize, 0},
    {"async_sqlite_create_query", gsc_async_sqlite_create_query, 0},
    {"async_sqlite_create_query_nosave", gsc_async_sqlite_create_query_nosave, 0},
    {"async_sqlite_checkdone", gsc_async_sqlite_checkdone, 0},
    #endif

    {"sendCommandToClient", gsc_utils_sendcommandtoclient, 0},

    {"logPrintConsole", gsc_utils_logprintconsole, 0},
    {"getSubStr", gsc_utils_getsubstr, 0, },
    {"getAscii", gsc_utils_getascii, 0},
    {"toUpper", gsc_utils_toupper, 0},
    {"toLower", gsc_utils_tolower, 0},
    {"strtok", gsc_utils_strtok, 0},
    {"replace", gsc_utils_replace, 0},

    #if ENABLE_UNSAFE == 1
    {"file_exists", gsc_utils_file_exists, 0},
    {"fopen", gsc_utils_fopen, 0},
    {"fwrite", gsc_utils_fwrite, 0},
    {"fread", gsc_utils_fread, 0},
    {"fclose", gsc_utils_fclose, 0},
    #endif

    {"getSystemTime", gsc_utils_getsystemtime, 0},
    
    {"getConfigString", gsc_utils_getconfigstring, 0},
    {"makeLocalizedString", gsc_utils_makelocalizedstring, 0},

    {NULL, NULL, 0} // Terminator
};

xfunction_t Scr_GetCustomFunction(const char **fname, int *fdev)
{
    xfunction_t m = Scr_GetFunction(fname, fdev);
    if ( m )
        return m;

    for ( int i = 0; scriptFunctions[i].name; i++ )
    {
        if ( strcasecmp(*fname, scriptFunctions[i].name) )
            continue;

        scr_function_t func = scriptFunctions[i];
        *fname = func.name;
        *fdev = func.developer;
        return func.call;
    }

    return NULL;
}

scr_method_t scriptMethods[] =
{
    {"showToPlayer", gsc_entity_showtoplayer, 0},

    #if COMPILE_SQLITE == 1
    {"async_sqlite_create_entity_query", gsc_async_sqlite_create_entity_query, 0},
    {"async_sqlite_create_entity_query_nosave", gsc_async_sqlite_create_entity_query_nosave, 0},
    #endif

    {"setVelocity", gsc_player_setvelocity, 0},
    {"getVelocity", gsc_player_getvelocity, 0},
    {"aimButtonPressed", gsc_player_button_ads, 0},
    {"leftButtonPressed", gsc_player_button_left, 0},
    {"rightButtonPressed", gsc_player_button_right, 0},
    {"forwardButtonPressed", gsc_player_button_forward, 0},
    {"backButtonPressed", gsc_player_button_back, 0},
    {"moveUpButtonPressed", gsc_player_button_up, 0},
    {"moveDownButtonPressed", gsc_player_button_down, 0},
    {"leanleftButtonPressed", gsc_player_button_leanleft, 0},
    {"leanrightButtonPressed", gsc_player_button_leanright, 0},
    {"reloadButtonPressed", gsc_player_button_reload, 0},
    {"getPlayerAngles", gsc_player_gettagangles, 0},
    {"getStance", gsc_player_getstance, 0},
    {"getIP", gsc_player_getip, 0},
    {"getPing", gsc_player_getping, 0},
    {"getUserinfo", gsc_player_getuserinfo, 0},
    {"setUserinfo", gsc_player_setuserinfo, 0},
    {"processClientCommand", gsc_player_processclientcommand, 0},
    {"dropClient", gsc_player_dropclient, 0},
    {"setSpeed", gsc_player_setspeed, 0},
    {"getFPS", gsc_player_getfps, 0},


    //{"testCommand", gsc_testcommand, 0},

    {NULL, NULL, 0} // Terminator
};

xmethod_t Scr_GetCustomMethod(const char **fname, qboolean *fdev)
{
    xmethod_t m = Scr_GetMethod(fname, fdev);
    
    if ( m )
        return m;

    for ( int i = 0; scriptMethods[i].name; i++ )
    {
        if ( strcasecmp(*fname, scriptMethods[i].name) )
            continue;

        scr_method_t func = scriptMethods[i];

        *fname = func.name;
        *fdev = func.developer;

        return func.call;
    }


    return NULL;
}

void stackError(const char *format, ...)
{
    char s[MAX_STRINGLENGTH];
    int len = 0;
    va_list va;

    va_start(va, format);
    Q_vsnprintf(s, sizeof(s) - 1, format, va);
    va_end(va);

    len = strlen(s);
    s[len] = '\n';
    s[len + 1] = '\0';
    Com_PrintMessage(0, s);
    //Scr_CodeCallback_Error(qfalse, qfalse, "stackError", s);
    Scr_Error(s); //TODO: look about calling Scr_CodeCallback_Error instead
}

int stackGetParams(const char *params, ...)
{
    va_list args;
    va_start(args, params);

    int errors = 0;

    for ( size_t i = 0; i < strlen(params); i++ )
    {
        switch ( params[i] )
        {
        case ' ': // Ignore param
            break;

        case 'i':
        {
            int *tmp = va_arg(args, int *);
            if ( !stackGetParamInt(i, tmp) )
            {
                Com_DPrintf("\nstackGetParams() Param %i is not an int\n", i);
                errors++;
            }
            break;
        }

        case 'v':
        {
            float *tmp = va_arg(args, float *);
            if ( !stackGetParamVector(i, tmp) )
            {
                Com_DPrintf("\nstackGetParams() Param %i is not a vector\n", i);
                errors++;
            }
            break;
        }

        case 'f':
        {
            float *tmp = va_arg(args, float *);
            if ( ! stackGetParamFloat(i, tmp) )
            {
                Com_DPrintf("\nstackGetParams() Param %i is not a float\n", i);
                errors++;
            }
            break;
        }

        case 's':
        {
            char **tmp = va_arg(args, char **);
            if ( !stackGetParamString(i, tmp) )
            {
                Com_DPrintf("\nstackGetParams() Param %i is not a string\n", i);
                errors++;
            }
            break;
        }

        case 'c':
        {
            unsigned int *tmp = va_arg(args, unsigned int *);
            if ( !stackGetParamConstString(i, tmp) )
            {
                Com_DPrintf("\nstackGetParams() Param %i is not a const string\n", i);
                errors++;
            }
            break;
        }

        case 'l':
        {
            char **tmp = va_arg(args, char **);
            if ( !stackGetParamLocalizedString(i, tmp) )
            {
                Com_DPrintf("\nstackGetParams() Param %i is not a localized string\n", i);
                errors++;
            }
            break;
        }

        default:
            errors++;
            Com_DPrintf("\nUnknown identifier [%c] passed to stackGetParams()\n", params[i]);
            break;
        }
    }

    va_end(args);
    return errors == 0; // success if no errors
}

int stackGetParamInt(int param, int *value)
{
    if ( param >= Scr_GetNumParam() )
        return 0;

    VariableValue *var;
    var = &scrVmPub.top[-param];

    if ( var->type == STACK_FLOAT )
    {
        *value = var->u.floatValue;
        return 1;
    }

    if ( var->type != STACK_INT )
        return 0;

    *value = var->u.intValue;

    return 1;
}

int stackGetParamFunction(int param, int *value)
{
    printf("####### stackGetParamFunction \n");
    

    if ( param >= Scr_GetNumParam() )
        return 0;

    VariableValue *var;
    var = &scrVmPub.top[-param];

    if ( var->type != STACK_FUNCTION )
        return 0;

    *value = var->u.codePosValue - scrVarPub.programBuffer;

    return 1;
}

int stackGetParamString(int param, char **value)
{
    if ( param >= Scr_GetNumParam() )
        return 0;

    VariableValue *var;
    var = &scrVmPub.top[-param];

    if ( var->type != STACK_STRING )
        return 0;

    *value = SL_ConvertToString(var->u.stringValue);

    return 1;
}

int stackGetParamConstString(int param, unsigned int *value)
{
    if ( param >= Scr_GetNumParam() )
        return 0;

    VariableValue *var;
    var = &scrVmPub.top[-param];

    if ( var->type != STACK_STRING )
        return 0;

    *value = var->u.stringValue;

    return 1;
}

int stackGetParamLocalizedString(int param, char **value)
{
    if ( param >= Scr_GetNumParam() )
        return 0;

    VariableValue *var;
    var = &scrVmPub.top[-param];

    if ( var->type != STACK_LOCALIZED_STRING )
        return 0;

    *value = SL_ConvertToString(var->u.stringValue);

    return 1;
}

int stackGetParamVector(int param, vec3_t value)
{
    if ( param >= Scr_GetNumParam() )
        return 0;

    VariableValue *var;
    var = &scrVmPub.top[-param];

    if ( var->type != STACK_VECTOR )
        return 0;

    VectorCopy(var->u.vectorValue, value);

    return 1;
}

int stackGetParamFloat(int param, float *value)
{
    if ( param >= Scr_GetNumParam() )
        return 0;

    VariableValue *var;
    var = &scrVmPub.top[-param];

    if ( var->type == STACK_INT )
    {
        *value = var->u.intValue;
        return 1;
    }

    if ( var->type != STACK_FLOAT )
        return 0;

    *value = var->u.floatValue;

    return 1;
}

int stackGetParamObject(int param, unsigned int *value)
{
    if ( param >= Scr_GetNumParam() )
        return 0;

    VariableValue *var;
    var = &scrVmPub.top[-param];

    if ( var->type != STACK_OBJECT )
        return 0;

    *value = var->u.pointerValue;

    return 1;
}

/**
 * @brief Base time in seconds
 */
time_t sys_timeBase = 0;

/**
 * @brief Current time in ms, using sys_timeBase as origin
 */
uint64_t Sys_Milliseconds64(void)
{
    struct timeval tp;

    gettimeofday(&tp, NULL);

    if ( !sys_timeBase )
    {
        sys_timeBase = tp.tv_sec;
        return tp.tv_usec / 1000;
    }

    return (tp.tv_sec - sys_timeBase) * 1000 + tp.tv_usec / 1000;
}



/*
void gsc_testcommand(scr_entref_t ref)
{
    int id = ref.entnum;

    if ( id >= MAX_CLIENTS )
    {
        stackError("gsc_player_testcommand() entity %i is not a player", id);
        stackPushUndefined();
        return;
    }

    //client_t* client = &svs.clients[id];
    gentity_t* gentity = &g_entities[id];

    printf("####### currentOrigin = %f, %f, %f \n", gentity->r.currentOrigin[0], gentity->r.currentOrigin[1], gentity->r.currentOrigin[2]);
}*/