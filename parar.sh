#!/bin/bash
#Parar las ruedas
gpio -g mode 18 pwm
gpio -g mode 13 pwm
gpio pwm-ms 
gpio pwmc 96
gpio pwmr 4300
gpio -g pwm 13 320
gpio -g pwm 18 320

