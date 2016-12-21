#include "DHT.h"
#include <HC_SR04.h>
#include <HTTP_VARIABLES.h>
#include <INVENT_DIGITAL.h>
#include <URL_DECODE.h>
#include <SoftwareSerial.h>

SoftwareSerial Invent_one_IISerial(2,3); //RX, TX

#define DHTPIN 5 
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

String dataString;
int digital_pin, digital_pin_state;
int analog_pin, analog_pin_signal;
int pin;
int num_param, const_action;

struct Data_struct
{
  char *keys[MAX_ARRAY_LENGTH];
  char *vals[MAX_ARRAY_LENGTH];
  char *method[HTTP_METHOD_ARRAY_LENGTH];
  };
struct Data_struct d_s;

void monitor_pin_digital(int Dpin);
void monitor_pin_analog(int A_pin);
void control_pin_pwm(int A_pin, int A_pin_signal);
void control_pin_digital(int Dpin, int Dpin_state);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(150);
  Invent_one_IISerial.begin(9600);
  Invent_one_IISerial.setTimeout(150);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Invent_one_IISerial.available() > 0)
  {
    dataString = Invent_one_IISerial.readString();
    URL_DECODE url_decode(dataString);
    num_param = url_decode.decodeUrl();
    d_s = url_decode.getParams();
    HTTP_VARIABLES http_variables(d_s, num_param);
    const_action = http_variables.getIntAction();
    switch(const_action)
    {
      case(MONITOR_PIN_DIGITAL):
      {
          monitor_pin_digital(http_variables, digital_pin);
          break;
          }
      case(MONITOR_PIN_ANALOG):
      {
          monitor_pin_analog(http_variables, analog_pin);
          break;
          }
      case(CONTROL_PIN_PWM):
      {
          control_pin_pwm(http_variables, analog_pin, analog_pin_signal);
          break;
        }
      case(CONTROL_PIN_DIGITAL):
      {
          control_pin_digital(http_variables, digital_pin, digital_pin_state);
          break;
          }
      case(MONITOR_SENSOR):
      {
          monitor_sensor(http_variables);
          break;
        }
     }
  }
}

void monitor_pin_digital(HTTP_VARIABLES& http_variables, int Dpin)
{
    Dpin = http_variables.getIntVariable("pin");
    INVENT_DIGITAL invent_digital(Dpin);
    Invent_one_IISerial.println(invent_digital.read());
  }

void monitor_pin_analog(HTTP_VARIABLES& http_variables, int A_pin)
{
    A_pin = http_variables.getIntVariable("pin");
    Invent_one_IISerial.println(analogRead(A_pin));
  }

void control_pin_pwm(HTTP_VARIABLES& http_variables, int A_pin, int A_pin_signal)
{
    A_pin = http_variables.getIntVariable("pin");
    A_pin_signal = http_variables.getIntVariable("signal");
    if (0 <= A_pin_signal <= 255)
    {
      analogWrite(A_pin, A_pin_signal);
      String s = "pin ";
      s += String(A_pin);
      s += " is at signal ";
      s += String(A_pin_signal);
      Invent_one_IISerial.println(s);
      s = "";
      }
    else if(225 <= A_pin_signal <= 1023)
    {
      int mapped_analog_signal = map(A_pin_signal, 0, 1023, 0, 255);
      analogWrite(A_pin, mapped_analog_signal);
      String s = "pin ";
      s += String(A_pin);
      s += " is at signal ";
      s += String(A_pin_signal);
      Invent_one_IISerial.println(s);
      s = "";
      }
  }

void control_pin_digital(HTTP_VARIABLES& http_variables, int Dpin, int Dpin_state)
{
    Dpin = http_variables.getIntVariable("pin");
    Dpin_state = http_variables.getIntVariable("state");
    INVENT_DIGITAL invent_digital(Dpin, Dpin_state);
    invent_digital.write();
    String s = "pin ";
    s += String(Dpin);
    s += " is at state ";
    s += String(Dpin_state);
    Invent_one_IISerial.println(s);
    s = "";
  }

void monitor_sensor(HTTP_VARIABLES& http_variables)
{
    char *sensor_var = http_variables.getStringVariable("sensor");
    if(strcmp(sensor_var, "DHT11") == 0)
    {
      String s = "Humidity=";
      s += String(getHumidityFromDHT());
      s += ", Temperature=";
      s += String(getTemperatureFromDHT());
      Invent_one_IISerial.println(s);
      s = "";
      }
  }

float getHumidityFromDHT()
{
  float nearestHumidity = dht.readHumidity();
  return nearestHumidity;
  }

float getTemperatureFromDHT()
{
  float nearestTemperature = dht.readTemperature();
  return nearestTemperature;
  }
