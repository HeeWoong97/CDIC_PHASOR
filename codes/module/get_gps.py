import serial
import time
import string
import pynmea2

FIFO_FILENAME = './fifo-gps.txt'

f = open("detect.txt", "r")
fp_fifo = open(FIFO_FILENAME, 'w')

while True:
    port = "/dev/ttyS0"
    ser = serial.Serial(port, baudrate=9600, timeout=0.5)
    dataout = pynmea2.NMEAStreamReader()
    
    if f.readline() == "detect!\n":
        print("detect!")
        i = 0
        while i < 10:
            newdata = ser.readline()
            if newdata[0:6]=="$GPRMC":
                print(str(i+1) + ": " + newdata)
                newmsg = pynmea2.parse(newdata)
                lat = newmsg.latitude
                lng = newmsg.longitude
                gps = "Latitude= " + str(lat) + ", Longitude= " + str(lng)
                print(gps)
                fp_fifo.write(gps + '\n')
                i += 1
            else:
                continue
    else:
        continue

f.close()
fp_fifo.close()