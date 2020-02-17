#!/usr/bin/python3
import time
import serial
import os

#if this prints, then everything is fine
print("UART Jetson tfmini program")

os.system("echo {}|sudo -S {}".format("dlinano", "chmod 777 /dev/ttyTHS1"))

ser = serial.Serial(
    port="/dev/ttyTHS1",
    baudrate=115200,
)

def getTFminiData():
    while(True):
        time.sleep(0.1)
        count = ser.in_waiting
        if count > 8:
            recv = ser.read(9)
            ser.reset_input_buffer()
            int(recv[0])
            if recv[0] == 0x59 and recv[1] == 0x59:
                cmdistance = recv[2] + recv[3] * 256
                distance = cmdistance/2.54
                strength = recv[4] + recv[5] * 256
                print('(', distance, ',', strength, ')')
                ser.reset_input_buffer()
                return (distance, strength)
#python3                  
if __name__ == '__main__':
    getTFminiData()
    try:
        if ser.is_open == False:
            ser.open()
            getTFminiData()
    except:
        print("error, no serial port available")
