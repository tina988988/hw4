import time
import serial
import sys,tty,termios


# XBee setting
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)
s.write("/parking/run 15 15 west\n".encode())
s.close()