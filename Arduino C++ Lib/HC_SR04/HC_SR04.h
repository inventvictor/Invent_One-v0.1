#ifndef HC_SR04_H
#define HC_SR04_H

#include "Arduino.h"

class HC_SR04
{
  public:
      HC_SR04(int TRIG_PIN, int ECHO_PIN);
      ~HC_SR04();
      int getObstacleDistance();
      
  };

#endif
