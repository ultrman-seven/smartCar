# smartCar
this is the smart car competition

|auther|chip|starting date|
|:----------|:---------:|:-----------------|
|Leslie|STC-8H8K64U|2020/10/30|

branch: run test
---
this branch is built due to some big change caused by the shit of MCU

difference from main:

in main, the control of car is put in the interrupt form time4; 
but in this branch, it have been put into a 'while', because some unpredictable error will happen if operate global variable in interrupt function.

generally describe
---
this project is mainly divided into 4 parts: 

**1. display:**

functions about operations of oled(`oled.c` and `oled.h`); 

functions about output (`oledio.h` and `oled_output.c`);

functions about menu to display and operations about it(`menu.c` and `menu.h`);

word molds(`font.c` and `font.h`), used in `oled_output.c`.

**2.motor:**

using m1m0 to set the working mode of the motor;
using PWM to control the speed of motor.
(`motor.c` and `motor.h`)

**3.measure:**

voltage(to seek the way):
using adc to measure the voltage value of inductance.(`indac.h` and `inductance adc.c`)

distance(to check for obstacle):
using ultrasound to measure the distance between car and the obstacle.(`ultraSound.c` and `lutraSound.h`)

**4.control:**

using Pid algorithm to let the car in the right way.(`control.c` and `control.h`)

here are details
---
## oled
|GND|VDD|D0|D1|RES|DC|CS|
|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|
|GND|VCC|1.3|1.4|1.5|3.0|1.6|

`OLED.h` and `OLED.c` are codes about controling oled

`void Ins_trans(unsigned char command);`
is the function to send command to oled.

`void Initial(void);`
is the function to initialization the oled. (having been put in `void startCartoon(void);`)

`void startCartoon(void);`
the function is used in the begining when the program start, put "新北とラふ店（自家用＄1�7" in oled.

`font.h` and `font.c` are about word mold of **ASCII** and word mold of **新北とラふ店（自家用＄1�7**

## ultra sound
|VCC|TRIG|ECHO|OUT|GND|
|:-----:|:-----:|:-----:|:-----:|:-----:|
|VCC|0.5|3.2|suspend|GND|

using ultra sound to measure the distance between car and the obstacle

`un16 ULsound_diatance(void)` return the distance (cm)

## motor
using pwm to control the speed of car motor.

||Enable|M0|M1|
|:------:|:-----------:|:--------:|:--------:|
|left|2.0|3.5|5.1|
|right|2.2|5.0|3.4|

Enable left and right receive pwm to control the speed.

m0 and m1 control the work mode of motor
|m0|m1|mode|
|:----:|:----:|:--------:|
|0|0|braking|
|0|1|run forward|
|1|0|run opposite|
|1|1|braking|

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

## beep
|beep|
|:-----:|
|0.4|

## 5 keys
define up, down, left, right, mid

|COM|UP|DOWN|LEFT|RIGHT|MID|SET|RESET|
|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|:-------:|
|GND|2.4|2.3|2.1|3.6|3.7|suspend|suspend|

`#define NO_HaveKeyBeenPressed (key_down | key_up | key_mid | key_left | key_right)`

this defination means none of these keys have been pressed.

## menu

## control

## main
