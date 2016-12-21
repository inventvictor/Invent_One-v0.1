#ifndef URL_DECODE_H
#define URL_DECODE_H

#include "Arduino.h"

#define MAX_ARRAY_LENGTH 20
#define DELIM_ARRAY_LENGTH 2
#define HTTP_METHOD_ARRAY_LENGTH 2
#define MAX_DATA_ARRAY_LENGTH 200

class URL_DECODE
{
    public:
        URL_DECODE(String URL);
        ~URL_DECODE();
        int decodeUrl();
        struct Data_struct getParams(void);
    };

#endif