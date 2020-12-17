/* Copyright (c) Microsoft Corporation.
   Licensed under the MIT License. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json_utils.h"

bool findJsonInt(const char* json, jsmntok_t* tokens, int tokens_count, const char* s, int* value)
{
    for (int i = 0; i < tokens_count - 1; i++)
    {
        if (tokens[i].type == JSMN_STRING && tokens[i + 1].type == JSMN_PRIMITIVE)
        {
            if (((int)strlen(s) == tokens[i].end - tokens[i].start) &&
                (strncmp(json + tokens[i].start, s, (size_t)(tokens[i].end - tokens[i].start)) == 0))
            {
                *value = strtoul(json + tokens[i + 1].start, NULL, 10);

                return true;
            }
        }
    }

    return false;
}

bool findJsonULong(const char* json, jsmntok_t* tokens, int tokens_count, const char* s, unsigned long* value)
{
    for (int i = 0; i < tokens_count - 1; i++)
    {
        if (tokens[i].type == JSMN_STRING && tokens[i + 1].type == JSMN_PRIMITIVE)
        {
            if (((int)strlen(s) == tokens[i].end - tokens[i].start) &&
                (strncmp(json + tokens[i].start, s, (size_t)(tokens[i].end - tokens[i].start)) == 0))
            {
                *value = strtoul(json + tokens[i + 1].start, NULL, 10);

                return true;
            }
        }
    }

    return false;
}

bool findJsonString(const char* json, jsmntok_t* tokens, int tokens_count, const char* s, char* value)
{
    size_t key_len;
    size_t value_len;
    for (int i = 0; i < tokens_count - 1; i++)
    {
        if (tokens[i].type == JSMN_STRING && tokens[i + 1].type == JSMN_STRING)
        {
            key_len = (size_t)(tokens[i].end - tokens[i].start);
            if ((strlen(s) == key_len) && (strncmp(json + tokens[i].start, s, key_len) == 0))
            {
                value_len = (size_t)(tokens[i + 1].end - tokens[i + 1].start);
                strncpy(value, json + tokens[i + 1].start, value_len);
                value[value_len] = 0;

                return true;
            }
        }
    }

    return false;
}
