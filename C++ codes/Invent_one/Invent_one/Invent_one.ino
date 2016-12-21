#include <HTTP_VARIABLES.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <URL_DECODE.h>

int num, const_action;
String dataString, lcdString;
SoftwareSerial Invent_oneWifiSerial(10, 11); //RX, TX
LiquidCrystal lcd(12, 9, 5, 4, 3, 2);

struct Data_struct
{
  char *keys[MAX_ARRAY_LENGTH];
  char *vals[MAX_ARRAY_LENGTH];
  char *method[HTTP_METHOD_ARRAY_LENGTH];
  };
struct Data_struct d_s;
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Invent_oneWifiSerial.begin(9600);
  Invent_oneWifiSerial.setTimeout(150);
  Serial.begin(9600);
  Serial.setTimeout(150);
  lcd.clear();
  lcd.print("Invent one board");
  lcd.setCursor(0, 1);
  lcd.print("Connecting......");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Invent_oneWifiSerial.available() > 0)
  {
    dataString = Invent_oneWifiSerial.readString();
    dataString.trim();
    if(dataString.endsWith("ip"))
    {
      lcd.clear();
      lcd.print("IP ADDRESS");
      lcd.setCursor(0, 1);
      int ip_p = dataString.lastIndexOf("p");
      dataString.remove(ip_p);
      int ip_i = dataString.lastIndexOf("i");
      dataString.remove(ip_i);
      lcd.print(dataString);
      }
    else
    {
      URL_DECODE url_decode(dataString);
      num = url_decode.decodeUrl();
      d_s = url_decode.getParams();
      for (int i=0; i<HTTP_METHOD_ARRAY_LENGTH; i++)
      { 
        int int_method = strcmp(d_s.method[i], "GET");
        switch(int_method)
        {
          case (0):
              Serial.println(dataString);
          default :
              int_method = strcmp(d_s.method[i], "POST");
              switch(int_method)
              {
                case (0):
                    Serial.println(dataString);
                default :
                    int_method = strcmp(d_s.method[i], "PUT");
                    switch(int_method)
                    {
                      case(0):
                          Serial.println(dataString);
                          HTTP_VARIABLES http_variables(d_s, num);
                          const_action = http_variables.getIntAction();
                          switch(const_action)
                          {
                            case(LCD_DISPLAY):
                                lcdString = http_variables.getStringVariable("value");
                                lcdString.trim();
                                int sla_ = lcdString.lastIndexOf("/");
                                lcdString.remove(sla_);
                                lcdString.replace("+", " ");
                                lcd.clear();
                                lcd.print(lcdString);
                                Invent_oneWifiSerial.println("Written on LCD");
                            }
                      //default:
                          //should return error back to the access unit
                      }
                }
          }
        }
      }
    }
    if(Serial.available() > 0)
    {
      String feedBackSerial = Serial.readString();
      Invent_oneWifiSerial.println(feedBackSerial);
      }
}

