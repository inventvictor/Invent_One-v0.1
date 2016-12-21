#ifndef HTTP_VARIABLES_H
#define HTTP_VARIABLES_H

#include "Arduino.h"
#include "URL_DECODE.h"

#define MONITOR_PIN_DIGITAL 1
#define MONITOR_PIN_ANALOG 2
#define MONITOR_SENSOR 3
#define CONTROL_PIN_DIGITAL 4
#define CONTROL_PIN_PWM 5
#define CONTROL_ACTUATOR 6
#define LCD_DISPLAY 7
#define MONITOR_SERIAL 8

class HTTP_VARIABLES
{
    public:
        HTTP_VARIABLES(struct Data_struct d, int n);
        ~HTTP_VARIABLES();
        int getIntVariable(char *int_variable_name);
        char* getStringVariable(char *string_variable_name);
        int getIntAction();
};

#endif