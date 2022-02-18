
# U8g2 for arm/x86-linux

<!-- [![Build Status](https://travis-ci.com/wuhanstudio/u8g2-arm-linux.svg?branch=master)](https://travis-ci.com/wuhanstudio/u8g2-arm-linux) -->

[![CircleCI](https://circleci.com/gh/wuhanstudio/u8g2-arm-linux.svg?style=svg)](https://circleci.com/gh/wuhanstudio/u8g2-arm-linux)

## Quick Start

``` 
$ cd u8g2-arm-linux
$ make
$ ls bin/
``` 

## 针对 MZ-1FXS-CBC09-XXX 主板 三种i2c控制方式
1. userspace软件模拟i2c
	- 确认SCL: 447, SDA: 446, RST: 376 作为普通GPIO配置
	- Userspace 可通过/sys/class/gpio/接口控制
	- `$ sudo ./bin/u8g2_sw_i2c`

2. 内核i2c-gpio模拟hw-i2c
	- 修改BIOS配置, 将i2c-2关闭(使得PIN脚被定义为普通GPIO)
	- 取消GPIO应用层导出:	`echo 446,447 > /sys/class/gpio/unexport`
	- 加载i2c-gpio驱动:		`modprobe i2c-gpio`
	- 加载自定义pin脚的i2c-gpio驱动: `insmod i2c-gpio-custom.ko bus0=12,446,447,[5/50]`
	- `$ sudo ./bin/u8g2_hw_i2c`

3. 硬件designware-i2c驱动
	- 修改BIOS的ACPI开启i2c-2位designware硬件i2c
	- `ls /dev/i2c*` 能看到 /dev/i2c-2
	- `ls /sys/class/i2c-adapter/ -l` 能看到 i2c_designware.N/i2c-N 的适配器
	- `$ sudo ./bin/u8g2_hw_i2c`


Check wiki [here](https://github.com/wuhanstudio/u8g2-arm-linux/wiki) for set-up

<!-- TOC -->

- [U8g2 for arm-linux](#u8g2-for-arm-linux)
    - [Introduction](#introduction)
    - [Todo list](#todo-list)
    - [Gallery](#gallery)
    - [How to compile](#how-to-compile)
    - [How to run](#how-to-run)
    - [Related Projects](#related-projects)
	- [Contact](#contact)
	- [Wiki](https://github.com/wuhanstudio/u8g2-arm-linux/wiki)

<!-- /TOC -->

## Introduction

U8g2 is a monochrome graphics library for embedded devices, and I ported it onto arm linux.

It should work fine on virtually all devices running linux with i2c, spi support, since no libraries pertaining to specific platforms has been used, yet you need to choose right compilers for your devices. 

## Todo list

[●] Hardware I2C  
[●] Hardware SPI  
[●] Software I2C  
[●] Software SPI  
[●] 8080 mode  
[●] Add C++ wrapper  
[●] Faster GPIO by tracking fd  
[●] Better build system  
[●] Upstream the port  
[&nbsp; ] Replace sysfs with gpiod  
[&nbsp; ] Benchmark

## Gallery 

Nanopi  
[http://wiki.friendlyarm.com/wiki/index.php/NanoPi](http://wiki.friendlyarm.com/wiki/index.php/NanoPi)  

<img src="img/nanopi-i2c-spi.jpg" alt="Nanopi" width=400>	

<br />

<img src="img/nanopi.jpg" alt="Nanopi" width=400>	

Nanopi NEO  
[http://wiki.friendlyarm.com/wiki/index.php/NanoPi_NEO](http://wiki.friendlyarm.com/wiki/index.php/NanoPi_NEO)  

<img src="img/nanopi-neo.jpg" alt="Nanopi-Neo" width=400>	

Raspberry Pi ZERO  
[https://www.raspberrypi.org/products/raspberry-pi-zero/](https://www.raspberrypi.org/products/raspberry-pi-zero/)  

<img src="img/raspi-zero.jpg" alt="Raspi-Zero" width=400>		

Raspberry Pi 2 B+  
[https://www.raspberrypi.org/products/raspberry-pi-2-model-b/](https://www.raspberrypi.org/products/raspberry-pi-2-model-b/)  

<img src="img/raspi2.jpg" alt="Raspi2-B+" width=400>	

Orange Pi ZERO  
[http://www.orangepi.org/orangepizero/](http://www.orangepi.org/orangepizero/)  

<img src="img/orangepi-zero.jpg" alt="orangepi-zero" width=400>	

Lichee Pi NANO  
[http://nano.lichee.pro/](http://nano.lichee.pro/)  

<img src="img/licheepi-nano.jpg" alt="licheepi-nano" width=400>	

C-SKY  
[https://c-sky.github.io/docs/gx6605s.html](https://c-sky.github.io/docs/gx6605s.html)  

<img src="img/csky-ck610.jpg" alt="csky-ck610" width=400>	

## How to compile

First, clone this repo:  

`$ git clone https://github.com/wuhanstudio/u8g2-arm-linux.git`

`$ cd u8g2-arm-linux`

Change cross-compiler in Makefile under each example directory according to your board.

	# Chosse proper compiler for your PI
	# NanoPi:             arm-linux-gnueabi-gcc
	# Raspberry Pi Zero:  arm-linux-gnueabi-gcc

	# Raspberry Pi 2:     arm-linux-gnueabihf-gcc
	# OrangePi Zero:      arm-linux-gnueabihf-gcc
	# NanoPi NEO:         arm-linux-gnueabihf-gcc
	# NanoPi NEO Plus 2:  arm-linux-gnueabihf-gcc
	# C-SKY:              csky-linux-gcc	
	CC = arm-linux-gnueabihf-gcc

For cross-compile:

	arm-linux-gnueabi-gcc   for armv6  
	arm-linux-gnueabihf-gcc for armv7

For native-compile (compile on your board), simply use:
	
	CC = gcc

Finally, time to compile:

`$ make`

## How to run

Before running, you can check your I2C graphic devices using i2c-tools: 

`$ sudo apt-get install i2c-tools`  

List your devices:

`$ ls /dev/i2c*`  
`/dev/i2c-0  /dev/i2c-1`

Probe your devices on bus 0:

`$ i2cdetect -y -r 0`

-----

For cross-compile, you can change ip address in Makefile:

	# IP Address of your PI	
	PI=pi@10.1.1.232

Then upload generated binary file onto your board:

`$ make upload`

## Related Projects

- U8g2: https://github.com/olikraus/u8g2
- U8glib: https://github.com/olikraus/u8glib


## Contact

* Author：Wu Han
* Homepage：http://wuhanstudio.cc
* Contact：https://github.com/wuhanstudio/u8g2-arm-linux/issues
