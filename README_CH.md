# 智能车
|作者|使用芯片|车队|
|:---------|:---------:|:--------------:|
|万游|STC-8H8K64U|万游|
|||王文扬|
|||印杰|

|模块|
|:---------:|
|OLED|
|超声波|
|蜂鸣器|


以下为各模块(各模块连接的管脚见英文自述文件(readme.md))
---

## OLED屏幕

使用函数`void Initial(void)`对oled屏幕进行初始化操作

`void startCartoon(void)`
在屏幕上显示开机动画“新北とラふ店（自家用）”**此函数已包含初始化函数**

`void OLED_print(char* str);`
在oled上显示字符串

## 超声波

## 五项按键

## 电机驱动

## 电感
