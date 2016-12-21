#include "HTTP_VARIABLES.h"

int HTTP_VARIABLES_n;
struct Data_struct
{
    char *keys[MAX_ARRAY_LENGTH];
    char *vals[MAX_ARRAY_LENGTH];
    char *method[HTTP_METHOD_ARRAY_LENGTH];
};
struct Data_struct HTTP_VARIABLES_d;

HTTP_VARIABLES::HTTP_VARIABLES(struct Data_struct d, int n)
{
    HTTP_VARIABLES_n = n;
    HTTP_VARIABLES_d = d;
}

HTTP_VARIABLES::~HTTP_VARIABLES()
{
    /*nothing to destruct*/
}

int HTTP_VARIABLES::getIntVariable(char *var_name)
{
    int var = 0;
    for (int i=0; i<HTTP_VARIABLES_n; i++)
    {
        if(strcmp(HTTP_VARIABLES_d.keys[i], var_name) == 0)
        {
            var = atoi(HTTP_VARIABLES_d.vals[i]);
        }
    }
    return var;
}

char* HTTP_VARIABLES::getStringVariable(char *var_name)
{
    char *var;
    for (int i=0; i<HTTP_VARIABLES_n; i++)
    {
        if(strcmp(HTTP_VARIABLES_d.keys[i], var_name) == 0)
        {
            var = HTTP_VARIABLES_d.vals[i];
        }
    }
    return var;
}

int HTTP_VARIABLES::getIntAction()
{
  int get_int_action = 0;
  for (int i=0; i<HTTP_VARIABLES_n; i++)
  {
    if (strcmp(HTTP_VARIABLES_d.keys[i], "action") == 0)
    {
      if(strcmp(HTTP_VARIABLES_d.vals[i], "monitor_pin_digital") == 0)
      {
        get_int_action = MONITOR_PIN_DIGITAL;
        }
      else if(strcmp(HTTP_VARIABLES_d.vals[i], "monitor_pin_analog") == 0)
      {
        get_int_action = MONITOR_PIN_ANALOG;
        }
      else if(strcmp(HTTP_VARIABLES_d.vals[i], "monitor_sensor") == 0)
      {
        get_int_action = MONITOR_SENSOR;
        }
      else if(strcmp(HTTP_VARIABLES_d.vals[i], "control_pin_digital") == 0)
      {
        get_int_action = CONTROL_PIN_DIGITAL;
        }
      else if(strcmp(HTTP_VARIABLES_d.vals[i], "control_pin_pwm") == 0)
      {
        get_int_action = CONTROL_PIN_PWM;
        }
      else if(strcmp(HTTP_VARIABLES_d.vals[i], "control_actuator") == 0)
      {
        get_int_action = CONTROL_ACTUATOR;
        }
      else if(strcmp(HTTP_VARIABLES_d.vals[i], "lcd_display") == 0)
      {
        get_int_action = LCD_DISPLAY;
        }
      else if(strcmp(HTTP_VARIABLES_d.vals[i], "monitor_serial") == 0)
      {
        get_int_action = MONITOR_SERIAL;
        }
      }
    }
    return get_int_action;
  }