#if COMPILE_LIBCURL == 1
#include <curl/curl.h>
#include <string>
#endif

#include <string>

#include "gsc_utils.hpp"

void gsc_utils_sendcommandtoclient()
{
    int clientNum;
    char *message;

    if ( !stackGetParams("is", &clientNum, &message) )
    {
        stackError("gsc_utils_sendcommandtoclient() one or more arguments is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    trap_SendServerCommand(clientNum, SV_CMD_CAN_IGNORE, message);
    stackPushBool(qtrue);
}

void gsc_utils_logprintconsole()
{
    char *str;

    if ( !stackGetParams("s", &str) )
    {
        stackError("gsc_utils_logprintconsole() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( !strlen(str) || strlen(str) > MAX_STRINGLENGTH )
    {
        stackError("gsc_utils_logprintconsole() invalid string length");
        stackPushUndefined();
        return;
    }

    Com_Printf("%s", str);

    stackPushBool(qtrue);
}

void gsc_utils_getsubstr()
{
    int end;
    char c;
    int i;
    int source;
    int start;
    const char *string;
    char tempString[1024];

    string = Scr_GetString(0);
    start = Scr_GetInt(1u);

    if ( Scr_GetNumParam() <= 2 )
        end = 0x7FFFFFFF;
    else
        end = Scr_GetInt(2u);

    source = start;

    for ( i = 0; source < end; ++i )
    {
        if ( i > 1023 )
            stackError("gsc_utils_getsubstr() string too long");

        c = string[source];

        if ( !c )
            break;

        tempString[i] = c;
        ++source;
    }

    tempString[i] = 0;
    stackPushString(tempString);
}

void gsc_utils_getascii()
{
    char *str;

    if ( !stackGetParams("s", &str) )
    {
        stackError("gsc_utils_getascii() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( !strlen(str) )
    {
        stackError("gsc_utils_getascii() string length is 0");
        stackPushUndefined();
        return;
    }

    stackPushInt(str[0]);
}

void gsc_utils_toupper()
{
    char *str;

    if ( !stackGetParams("s", &str) )
    {
        stackError("gsc_utils_toupper() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( !strlen(str) )
    {
        stackError("gsc_utils_toupper() string length is 0");
        stackPushUndefined();
        return;
    }

    stackPushString(Q_strupr(str));
}

void gsc_utils_tolower() // From cod2rev
{
    char c;
    int i;
    const char *string;
    char tempString[MAX_STRINGLENGTH];

    if ( !stackGetParams("s", &string) )
    {
        stackError("gsc_utils_tolower() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    for ( i = 0; i < MAX_STRINGLENGTH; ++i )
    {
        c = tolower(*string);
        tempString[i] = c;

        if ( !c )
        {
            stackPushString(tempString);
            return;
        }

        ++string;
    }

    stackError("gsc_utils_tolower() string too long");
}

void gsc_utils_strtok() // From cod2rev
{
    signed int j;
    char c;
    int dest;
    int i;
    signed int len;
    const char *tok;
    const char *delim;
    char tempString[1024];

    delim = Scr_GetString(0);
    tok = Scr_GetString(1u);
    len = strlen(tok);
    dest = 0;

    Scr_MakeArray();

    for ( i = 0; ; ++i )
    {
        c = delim[i];

        if ( !c )
            break;

        for ( j = 0; j < len; ++j )
        {
            if ( c == tok[j] )
            {
                if ( dest )
                {
                    tempString[dest] = 0;
                    Scr_AddString(tempString);
                    Scr_AddArray();
                    dest = 0;
                }

                goto skip;
            }
        }

        tempString[dest] = c;

        if ( ++dest > 1023 )
            stackError("gsc_utils_strtok() string too long");
skip:
        ;
    }

    if ( dest )
    {
        tempString[dest] = 0;
        Scr_AddString(tempString);
        Scr_AddArray();
    }
}

void gsc_utils_replace() //TODO: check if needs improvements
{
    char* orig;
    char* rep;
    char* with;

    if ( !stackGetParams("sss", &orig, &rep, &with) )
    {
        stackError("gsc_utils_replace() one or more arguments is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }
    
    char *result; // the return string
    char *ins; // the next insert point
    char *tmp; // varies
    int len_rep; // length of rep
    int len_with; // length of with
    int len_front; // distance between rep and end of last rep
    int count; // number of replacements

    if (!orig)
        return;
    if (!rep || !(len_rep = strlen(rep)))
        return;
    if (!(ins = strstr(orig, rep))) 
        return;
    if (!with)
        with = (char*)"";
    len_with = strlen(with);

    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    tmp = result = (char*)malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    
    stackPushString(result);
}

void gsc_utils_file_exists()
{
    char *filename;

    if ( !stackGetParams("s", &filename) )
    {
        stackError("gsc_utils_file_exists() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    int file_exists = access(filename, F_OK) != -1;
    stackPushInt(file_exists);
}

void gsc_utils_fopen()
{
    FILE *file;
    char *filename, *mode;

    if ( !stackGetParams("ss", &filename, &mode) )
    {
        stackError("gsc_utils_fopen() one or more arguments is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    file = fopen(filename, mode);

    if ( !file )
    {
        stackError("gsc_utils_fopen() returned an error");
        stackPushUndefined();
        return;
    }

    stackPushInt((int)file);
}

void gsc_utils_fread()
{
    FILE *file;

    if ( !stackGetParams("i", &file) )
    {
        stackError("gsc_utils_fread() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( !file )
    {
        stackError("gsc_utils_fread() returned an error");
        stackPushUndefined();
        return;
    }

    char buffer[256];
    int ret = fread(buffer, 1, 255, file);

    if ( !ret )
    {
        stackPushUndefined();
        return;
    }

    buffer[ret] = '\0';
    stackPushString(buffer);
}

void gsc_utils_fwrite()
{
    FILE *file;
    char *buffer;

    if ( !stackGetParams("is", &file, &buffer) )
    {
        stackError("gsc_utils_fwrite() one or more arguments is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( !file )
    {
        stackError("gsc_utils_fwrite() returned an error");
        stackPushUndefined();
        return;
    }

    stackPushInt(fwrite(buffer, 1, strlen(buffer), file));
}

void gsc_utils_fclose()
{
    FILE *file;

    if ( !stackGetParams("i", &file) )
    {
        stackError("gsc_utils_fclose() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    if ( !file )
    {
        stackError("gsc_utils_fclose() returned an error");
        stackPushUndefined();
        return;
    }

    stackPushInt(fclose(file));
}

void gsc_utils_getsystemtime()
{
    time_t timer;
    stackPushInt(time(&timer));
}

void gsc_utils_getconfigstring()
{
    int index;

    if ( !stackGetParams("i", &index) )
    {
        stackError("gsc_utils_getconfigstring() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }
    
    if ( index < 0 || index >= MAX_CONFIGSTRINGS )
    {
        stackError("gsc_utils_getconfigstring() configstring index is out of range");
        stackPushUndefined();
        return;
    }

    const char *string = trap_GetConfigstringConst(index);

    if ( !*string )
        stackPushUndefined();
    else
        stackPushString(string);
}

void gsc_utils_makelocalizedstring()
{
    char *str;

    if ( !stackGetParams("s", &str) )
    {
        stackError("gsc_utils_makelocalizedstring() argument is undefined or has a wrong type");
        stackPushUndefined();
        return;
    }

    stackPushString(str);

    VariableValue *var;
    int param = 0;

    var = &scrVmPub.top[-param];
    var->type = STACK_LOCALIZED_STRING;
}

void gsc_utils_ban()
{
    int numParam = Scr_GetNumParam();
    if (numParam)
    {
        std::string command = "ban";
        command.append(" ");
        for (int i = 0; i < numParam; i++)
        {
            std::string param = Scr_GetString(i);
            command.append(param);
        }
        Cbuf_ExecuteText(EXEC_APPEND, custom_va(command.c_str()));
    }
}

void gsc_utils_unban()
{
    int numParam = Scr_GetNumParam();
    if (numParam)
    {
        std::string command = "unban";
        command.append(" ");
        for (int i = 0; i < numParam; i++)
        {
            std::string param = Scr_GetString(i);
            command.append(param);
        }
        Cbuf_ExecuteText(EXEC_APPEND, custom_va(command.c_str()));
    }
}

#if COMPILE_LIBCURL == 1
void gsc_utils_webhookmessage() // TODO: See if needs threading
{
    char *url;
    char *message;
    if(!stackGetParams("ss", &url, &message))
    {
        stackError("gsc_utils_webhookmessage() one or more arguments are undefined or have a wrong type");
        stackPushUndefined();
        return;
    }

    CURL *curl;
    CURLcode responseCode;
    struct curl_slist *headers = NULL;
    std::string payload = "{\"content\":\"" + std::string(message) + "\"}";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl)
    {
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

        responseCode = curl_easy_perform(curl);
        if(responseCode != CURLE_OK)
            Com_Printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(responseCode));

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    else
        Com_Printf("curl_easy_init() failed\n");
    
    curl_global_cleanup();
}
#endif