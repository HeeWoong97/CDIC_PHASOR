import requests
import boto3
import datetime
import uuid

GPS_FILENAME = './fifo-gps.txt'
IMG_FILENAME = './pictures/*.jpg'

def upload_image(local_image_name):
    region = 'ap-northeast-2'
    bucket_name = 'phasor-image'
    image_name = 'image/' + datetime.datetime.now().strftime(
        '%Y-Tm-Td-%H:%m:%S') + uuid.uuid4().__str__() + '.png'

    s3_resource = boto3.resource(
        's3',
        aws_access_key_id='AKIA3JEQAY5425YOG3GO',
        aws_secret_access_key='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',
        region_name=region,
    )


    # get image file
    data = open(local_image_name, 'rb')

    # save image to S3 bucket as public
    s3_resource.Bucket(bucket_name).put_object(
        Body=data, Key=image_name, ACL='public-read')

    # get public image url
    image_url = "https://s3-%s.amazonaws.com/%s/%s" % (
        region, bucket_name, image_name)

    print('uploaded image : ' + image_url)

    return image_url

def send_data_to_db(latitude, longitude, magnitude, image_link):
    url = "https://gif1x88844.execute-api.ap-northeast-2.amazonaws.com/dev/roadData"

    payload = {
        'latitude': latitude,
        'longitude': longitude,
        'magnitude': magnitude,
        'imageLink': image_url
    }

    headers = {
        'Content-Type': 'application/x-www-form-urlencoded'
    }

    response = requests.request("POST", url, headers=headers, data=payload)

    print(response.text.encode('utf8'))


'''
while True:
    if os.path.exists(GPS_FILENAME) && os.path.exists(IMG_FILENAME):
        print("detect file")
        # send image
        image_url = upload_image(IMG_FILENAME) 
        fp_fifo = open(GPS_FILENAME, 'r')
        while True:
            line = fp_fifo.readline()
            if not line:
                break
            # send gps
            send_data_to_db(line.split(' ')[0], line.split(' ')[1], '1', image_url)
        fp_fifo.close()
        os.system('rm %s' % GPS_FILENAME)
        os.system('rm %s' % IMG_FILENAME)
    else:
        continue
'''
