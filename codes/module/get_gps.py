import serial
import time
import string
import pynmea2

def save_gps():
    port = "/dev/ttyS0"
    ser = serial.Serial(port, baudrate=9600, timeout=0.5)
    dataout = pynmea2.NMEAStreamReader()
    for i in range(100):
        newdata = ser.readline().decode('utf-8')
        if newdata[0:6]=="$GPRMC":
            print(newdata)
            newmsg = pynmea2.parse(newdata)
            lat = newmsg.latitude
            lng = newmsg.longitude
            print(str(lat) + str(lng))
            return lat, lng 

'''
def save_gps():
    FIFO_FILENAME = './fifo-gps.txt'

    f = open("detect.txt", "r")
    fp_fifo = open(FIFO_FILENAME, 'w')

    while True:
        port = "/dev/ttyS0"
        ser = serial.Serial(port, baudrate=9600, timeout=0.5)
        dataout = pynmea2.NMEAStreamReader()
    
        if f.readline() == "detect!\n":
            print("detect!")
            while True:
                newdata = ser.readline()
                if newdata[0:6]=="$GPRMC":
                    print(str(i+1) + ": " + newdata)
                    newmsg = pynmea2.parse(newdata)
                    lat = newmsg.latitude
                    lng = newmsg.longitude
                    gps = str(lat) + ' ' + str(lng)
                    print(gps)
                    fp_fifo.write(gps + '\n')
                    break
                else:
                    continue
        else:
            continue
    f.close()
    fp_fifo.close()
'''
