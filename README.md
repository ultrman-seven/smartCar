# smartCar
this is the smart car competition

|auther|Leslie|
|:----------|:---------:|
|chip|STC-8H8K64U|
|starting date|2020/10/30|

details
---
## oled
`OLED.h` and `OLED.c` are codes about controling oled

**functions**

`void Ins_trans(unsigned char command);`
is the function to send command to oled.

`void Initial(void);`
is the function to initialization the oled. (having been put in `void startCartoon(void);`)

`void startCartoon(void);`
the function is used in the begining when the program start, put "新北とうふ店(自家用)" in oled.
