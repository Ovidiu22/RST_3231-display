# RTC_DS3231-getSetTime

A project for setting and then reading the time using an Arduino nano and a DS3231 RTC.
- Set and reading time is done using the driver from LibDriver https://www.libdriver.com/docs/ds3231/index.html
- Time is displayed on a 20x4 LCD
- Set time is done once initially, after which the macro WRITETIME has to be disabled
- Communication between Arduino and RTC module DS3231 is done over I2C

# Schematic

![Schematic](https://user-images.githubusercontent.com/75970114/201161840-f4333bde-0e77-47c1-b04a-a25ce7f1cae8.png)
