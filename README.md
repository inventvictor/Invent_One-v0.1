# Invent_One-v0.1

Hardware for quick WiFi Offline prototyping.

The module designed uses the **ATMEGA 328** as its core microcontroller and also the **ESP-01** for WiFi capabilities. The ATMEGA 328 was programmed using the Arduino software. Thanks to :octocat: @igrr (https://github.com/esp8266/Arduino) :+1: for making the ESP-01 easily programmable via the Arduino software.

**Features**
* 14 GPIOs (General purpose input output)
* 6 Digital pins
* 4 Analog pins
* 1 Serial communication (TX & RX)
* 9V-12V Voltage input
* LCD (liquid crystal display) port

![Invent_Onev0.1](https://github.com/inventvictor/Invent_One-v0.1/blob/master/Eagle%20cad%20design/gitP.PNG)

**How it works**

The module, **ESP-01**, hosts a server that obtains an IP Address when it joins the pre-programmed WiFi credentials. The module has been pre-designed to create some sort of **abstraction**. You dont have to code up any hardware lang or wire up any circuit to do some basic things such as trying to turn on an led bulb or reading output from a sensor. Everything has been codeded abstractively in this module.

**Here is a simple documentation**

*To control a digital pin*

| Method        | URL           | Parameters                  | 
| ------------- |:-------------:| ---------------------------:|
| GET           | /invent       | action = control_pin_digital|
|               |               | pin = *digital_pin_number*  |
|               |               | state = 0 or 1              |
|               |               | 0 means LO, 1 means HI      |

for example; lets say the board designed, after connecting to its pre-programmed WiFi credentials, obtains a local IP address (192.168.43.200), you will need to make a http request like this...
http://192.168.43.200/invent?action=control_pin_digital&pin=2&state=1 to make pin 2 go HIGH... pretty easy hun!!!  very easy!!! from any language will just do (python, C#, php, Js, and so on).....pretty awesome.

*To monitor a digital pin*

| Method        | URL           | Parameters                  | 
| ------------- |:-------------:| ---------------------------:|
| GET           | /invent       | action = monitor_pin_digital|
|               |               | pin = *digital_pin_number*  |

for example; http://192.168.43.200/jbdkbg?action=monitor_pin_digital&pin=2

*To control an analog pin*

| Method        | URL           | Parameters                  | 
| ------------- |:-------------:| ---------------------------:|
| GET           | /invent       | action = control_pin_analog|
|               |               | pin = *analog_pin_number*  |
|               |               | signal = 0-255              |

for example; http://192.168.43.200/invent?action=control_pin_analog&pin=A0&signal=183

*To monitor an analog pin*

| Method        | URL           | Parameters                  | 
| ------------- |:-------------:| ---------------------------:|
| GET           | /invent       | action = control_pin_analog|
|               |               | pin = *analog_pin_number*  |

for example; http://192.168.43.200/jbdkbg?action=monitor_pin_analog&pin=A0

*To monitor serial*

| Method        | URL           | Parameters                  | 
| ------------- |:-------------:| ---------------------------:|
| GET           | /invent       | action = monitor_serial     |


for example; http://192.168.43.200/jbdkbg?action=monitor_serial

*To write to LCD*

| Method        | URL           | Parameters                  | 
| ------------- |:-------------:| ---------------------------:|
| PUT          | /invent       | action = lcd_display         |
|               |              | value = *something to write to LCD*  |

for example; http://192.168.43.200/invent?action=lcd_display&value=Joseph
