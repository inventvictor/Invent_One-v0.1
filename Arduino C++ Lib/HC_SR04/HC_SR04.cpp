#include "HC_SR04.h"
int TRIG_PIN, ECHO_PIN;
int duration, distance;
HC_SR04::HC_SR04(int trig_p, int echo_p)
{
  TRIG_PIN = trig_p;
  ECHO_PIN = echo_p;
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  }

HC_SR04::~HC_SR04()
{
  /*nothing to destruct*/
  }

int HC_SR04::getObstacleDistance()
{
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
  }
