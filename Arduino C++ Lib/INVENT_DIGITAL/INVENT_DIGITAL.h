#ifndef INVENT_DIGITAL_H
#define INVENT_DIGITAL_H

#include "Arduino.h"

class INVENT_DIGITAL
{
    public:
        INVENT_DIGITAL(int PIN);
        INVENT_DIGITAL(int PIN, int STATE);
        ~INVENT_DIGITAL();
        void write();
        int read();
};

#endif