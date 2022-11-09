# RTC_DS3231-getSetTime

A project for setting and then reading the time using an Arduino nano and a DS3231 RTC.
- Set and reading time is done using the driver from LibDriver https://www.libdriver.com/docs/ds3231/index.html
- Time is displayed on a 20x4 LCD
- Set time is done once initially, after which the macro WRITETIME has to be disabled
- Communication between Arduino and RTC module DS3231 is done over I2C

# Schmatic

![Schematic](https://user-images.githubusercontent.com/75970114/200906954-67fbd0dd-4b38-4d2f-b043-a4fb75800857.png)
