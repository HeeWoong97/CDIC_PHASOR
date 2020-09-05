import picamera
import time
import datetime
import os
import sys

def save_picture():
    # now = datetime.datetime.now()
    # filename = now.strftime('%Y-%m-%d %H:%M:%S')
    # filename = 'images/' + filename + '.jpg'
    # with picamera.PiCamera() as camera:
        # camera.resolution = (1024, 768)
        # camera.start_preview()
        # time.sleep(2)
        # camera.stop_preview()
        # camera.capture(filename)
        # os.system('cp ' + '\'' + filename + '\'.jpg images/')
    filename = sys.argv[1:]

    return filename
