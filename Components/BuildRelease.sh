#!/bin/sh
cd `dirname $0`
sh AccAndMagnSensor_LSM303DLHC/BuildRelease.sh
sh AccelerationSensor_KXR94_2050/BuildRelease.sh
sh AccelerationSensor_KXSC7_2050/BuildRelease.sh
sh Adafruit_PWMServoDriver_Edison/BuildRelease.sh
sh ADC_Edison/BuildRelease.sh
sh ADC_MCP3002/BuildRelease.sh
sh ADC_MCP3208/BuildRelease.sh
sh CrawlerControllerPWM2/BuildRelease.sh
sh DigitalOutput_Edison/BuildRelease.sh
sh GyroSensor_ENC_03R/BuildRelease.sh
sh GyroSensor_L3GD20_I2C/BuildRelease.sh
sh MotorDriver_TA7291P/BuildRelease.sh
sh MotorDriver_TA8428K/BuildRelease.sh
sh NineAxisSensor_LSM9DS0_I2C/BuildRelease.sh
sh PWM_Edison/BuildRelease.sh
sh RangeSensor_GP2Y0A21YK/BuildRelease.sh
sh temperatureSensor_ADT7410/BuildRelease.sh
sh CrawlerController/BuildRelease.sh
sh RobotArmController/BuildRelease.sh
