import requests
import os
import conf
from boltiot import Email, Sms, Bolt
import json, time


mybolt = Bolt(conf.API_KEY, conf.DEVICE_ID)
sms = Sms(conf.SID, conf.AUTH_TOKEN, conf.TO_NUMBER, conf.FROM_NUMBER)
mailer = Email(conf.MAILGUN_API_KEY, conf.SANDBOX_URL, conf.SENDER_EMAIL, conf.RECIPIENT_EMAIL)

while True:
    print ("Reading sensor value")
    response1 = mybolt.digitalRead('0')
    response2 = mybolt.digitalRead('2')
    data1 = json.loads(response1)
    data2 = json.loads(response2)
    print("Value getting from Arduino : " + str(data1['value']) + "  :  " + str(data2['value']))
    try:
        ir = int(data1['value'])
        temp = int(data2['value'])
        
        if ir == 1:
            try:
                os.system('rm snap.jpg')
            except:
                pass
            print("Making request to Twilio to send a SMS")
            print("Making request to Mailgun to send an email")
            os.system('uvccapture -m')
            response = requests.post(
    'https://api.mailgun.net/v3/' +'MAILGUN SANBOX URL HERE'+ '/messages',
    auth=('api', 'MAILGUN API HERE'),
    files=[
        ('inline[0]', ('image.png', open('snap.jpg', mode='rb').read())),
      ],
    data={
        'from': 'MAILGUN EMAIL HERE',
        'to': 'RECIPIENT EMAIL HERE',
        #'bcc': [bcc_adresat],
        'subject': 'ALERT! Somebody tried to enter without sanititzing.',
        'text': 'WARNING! Somebody tried to enter without sanititzing. Check the attached image.',
        'html': '''<html><body>
            <img src="cid:image.png">
            
            </body></html>'''
    },
    timeout=5  # sec
)
            
            response = sms.send_sms("WARNING! Somebody tried to enter without sanititzing. Check mail for picture")
            print("Response received from Twilio is: " + str(response))
            print("Status of SMS at Twilio is :" + str(response.status))
            break
        
        if temp == 1:
            print("Making request to Twilio to send a SMS")
            print("Making request to Mailgun to send an email")
            
            try:
                os.system('rm snap.jpg')
            except:
                pass
            print("Making request to Twilio to send a SMS")
            print("Making request to Mailgun to send an email")
            os.system('uvccapture -m')
            response = requests.post(
    'https://api.mailgun.net/v3/' +'MAILGUN SANDBOX URL HERE'+ '/messages',
    auth=('api', 'MAILGUN API HERE'),
    files=[
        ('inline[0]', ('image.png', open('snap.jpg', mode='rb').read())),
      ],
    data={
        'from': 'MAILGUN EMAIL HERE',
        'to': 'RECIPIENT EMAIL HERE',
        #'bcc': [bcc_adresat],
        'subject': 'ALERT! Somebody has fever.',
        'text': 'WARNING! Somebody has fever. Check the attached image.',
        'html': '''<html><body>
            <img src="cid:image.png">
            
            </body></html>'''
    },
    timeout=5  # sec
)
            
            response = sms.send_sms("WARNING! Somebody has fever. Check mail for picture.")
            print("Response received from Twilio is: " + str(response))
            print("Status of SMS at Twilio is :" + str(response.status))
            break
        
    except Exception as e:
        print ("Error occured: Below are the details")
        print (e)
    time.sleep(10)
