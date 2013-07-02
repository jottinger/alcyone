cmake_minimum_required(VERSION 2.7)
project(wiringPiStub)

add_library(wiringPi wiringPi.c wiringPiI2C.c wiringSerial.c)