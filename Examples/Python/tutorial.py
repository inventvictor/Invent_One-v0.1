
import requests
import time
import sys

for i in range(0, 256, 15):
    payload = {"action": "control_pin_pwm", "pin": "6", "signal": ""}
    payload["signal"] = str(i)
    r =  requests.get("http://192.168.43.200/ghy670", params=payload)
    print r.content

#http://192.168.43.200/jbdkbg?action=control_pin_digital&pin=10&state=0
# def my_print(text):
#     sys.stdout.write(str(text))
#     sys.stdout.flush()

# def do():
#     payload = {"action": "monitor_pin_analog", "pin": "5"}
#     r = requests.get("http://192.168.43.200/ghy670", params=payload)
#     return r.content

# if __name__ == "__main__":
#     while True:
#         my_print (do())

# payload = {"action": "monitor_pin_digital", "pin": "10"}
# r = requests.get("http://192.168.43.200/ghy670", params=payload)
# print r.text
# r = requests.get("http://universities.hipolabs.com/search?name=nigeria")

# while True:
#     payload_pir = {"action": "monitor_pin_digital", "pin": "8"}
#     payload_led = {"action": "control_pin_digital", "pin": "10", "state": "1"}
#     payload_led_ = {"action": "control_pin_digital", "pin": "10", "state":"0"}
#     r = requests.get("http://192.168.43.200/ghy670", params=payload_pir)
#     payload_lcd = {"action": "lcd_display", "value": r.content.strip()}
#     requests.put("http://192.168.43.200/ghy670", params=payload_lcd)
#     # if r.text.strip() == "1":
#     #     p = requests.get("http://192.168.43.200/ghy670", params=payload_led, headers={"content-type":"text/plain"})
#     #     my_print(p.text)
#     # elif  r.text.strip() == "0":
#     #     q = requests.get("http://192.168.43.200/ghy670", params=payload_led_, headers={"content-type":"text/plain"})
#     #     my_print(q.text)
#     my_print(r.text)

# def do(val):
#     payload = {"action": "lcd_display", "value": val}
#     r = requests.put("http://192.168.43.200/ghy670", params=payload)
#     return r.content
# if __name__ == "__main__":
#     do("Omoniyi Jo")



