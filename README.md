# smartCar
this is the smart car competition

|auther|chip|starting date|
|:----------|:---------:|:-----------------|
|Leslie|STC-8H8K64U|2020/10/30|

here are models
---
## oled
|GND|VDD|D0|D1|RES|DC|CS|
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|GND|VCC|1.3|1.4|1.5|3.0|1.6|

`OLED.h` and `OLED.c` are codes about controling oled

### functions

`void Ins_trans(unsigned char command);`
is the function to send command to oled.

`void Initial(void);`
is the function to initialization the oled. (having been put in `void startCartoon(void);`)

`void startCartoon(void);`
the function is used in the begining when the program start, put "新北とうふ店(自家用)" in oled.

### fonts

word mold of **ascii**

word mold of **新北とうふ店(自家用)**

## ultra sound
|VCC|TRIG|ECHO|OUT|GND|
|:-----:|:-----:|:-----:|:-----:|:-----:|
|VCC|0.5|3.2|suspend|GND|

using ultra sound to measure the distance between car and the obstacle

`un16 ULsound_diatance(void)` return the distance (cm)

## motor
using pwm to control the speed of car motor.

|Enable left|M0 left|M1 left|M0 right|M1 right|Enable right|
|:-----------:|:--------:|:--------:|:--------:|:--------:|:-----------:|
|2.0|3.5|5.1|5.0|3.4|2.2|

`void motorStateSet(un8 state, un8 motor)`is used to choose run forward or backward

`void motorSpeedSet(un8 speed, un8 motor)`is used to set the speed of car. 
'speed' is the percentage of the fast speed

## inductance adc
using the left and right inductance to find where the track is.

|left|right|
|:-------:|:------|
|1.0|1.1|

`un16 adcMeasure(un8 select)`the function returns the value that the reference voltage dividing this value is the voltage that the inductance measured.

it means that the higher the value is, the lower the voltage will be.

## 5 keys
define up, down, left, right, mid

|COM|UP|DOWN|LEFT|RIGHT|MID|SET|RESET|
|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
|GND|2.4|2.3|2.1|3.6|3.7|suspend|suspend|

`#define NO_HaveKeyBeenPressed (key_down | key_up | key_mid | key_left | key_right)`

this defination means none of these keys have been pressed.

here are other detiled functions
---
## menu

## control

## main
