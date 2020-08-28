from module.controller import upload_image, send_data_to_db
from module.get_gps import save_gps
from detect.camera.takePicture import save_picture 

# gps값 가져오기
print("GPS 값 요청 시작")
lat, lng = save_gps()

if lat is None or lng is None:
    print("GPS가 안되네요ㅎ..")

# 사진 가져오기
image_name = save_picture()
print('사진 이름 : ' + image_name)

# 저장하기
image_url =  upload_image(image_name)
print(image_url)
send_data_to_db(lat, lng, '1',  image_url)

