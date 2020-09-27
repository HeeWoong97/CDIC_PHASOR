from module.controller import upload_image, send_data_to_db
from module.get_gps import save_gps
# from detect.camera.takePicture import save_picture 
import sys

# gps값 가져오기
print("request GPS value...")
lat, lng = save_gps()

'''
if (lat is None or lng is None) or (lat < 30 or lng < 120):
    print("GPS is not available...")
    lat = 37.50366383333333
    lng = 126.9582585
'''

# 사진 가져오기
image_name = sys.argv[2];
print('image name : ' + image_name)

# 저장하기
image_url =  upload_image(image_name)
print(image_url)
send_data_to_db(lat, lng, sys.argv[1],  image_url)

