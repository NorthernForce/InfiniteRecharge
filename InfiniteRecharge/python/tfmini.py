#!/usr/bin/python3
import time
import serial

print("UART tfmini Jetson Nano")

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
                distance = recv[2] + recv[3] * 256
                strength = recv[4] + recv[5] * 256
                print('(', distance, ',', strength, ')')
                ser.reset_input_buffer()
#python3
                if recv[0] == 'Y' and recv[1] == 'Y': #python2
                    lowD = int(recv[2].encode('hex'), 16)
                    highD = int(recv[3].encode('hex'), 16)
                    lowS = int(recv[4].encode('hex'), 16)
                    highS = int(recv[5].encode('hex'), 16)
                    distance = lowD + highD * 256
                    strength = lowS + highS * 256
                    print(distance, strength)
               
               
if __name__ == '__main__':
    getTFminiData()
    try:
        if ser.is_open == False:
            ser.open()
            getTFminiData()
    except:
        print("error")