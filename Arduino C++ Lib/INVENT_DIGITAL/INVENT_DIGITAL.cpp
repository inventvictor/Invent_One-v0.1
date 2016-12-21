#include "INVENT_DIGITAL.h"
int PIN, STATE;
int VAL;
INVENT_DIGITAL::INVENT_DIGITAL(int pin, int state) //Constructor for Write
{
    PIN = pin;
    STATE = state;
    pinMode(PIN, OUTPUT);
}

INVENT_DIGITAL::INVENT_DIGITAL(int pin) //Constructor for Read
{
    PIN = pin;
    //pinMode(PIN, INPUT);
}
INVENT_DIGITAL::~INVENT_DIGITAL()
{
    /*nothing to destruct*/
}

void INVENT_DIGITAL::write()
{
    digitalWrite(PIN, STATE);
}

int INVENT_DIGITAL::read()
{
    VAL = digitalRead(PIN);
    return VAL;
}