from socket import *
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

timeout = 0.020

SENSOR_ONE_SIG = 17

SENSOR_TWO_TRIG = 23
SENSOR_TWO_ECHO = 24

# create a socker and bind the given socket to the host
# for communication of data
client_socket = socket(AF_INET, SOCK_STREAM)
client_socket.connect(('192.168.43.178', 8002))

def setup():
    print "Setup of Ultrasonic Sensors - Start"

    GPIO.setup(SENSOR_ONE_SIG, GPIO.OUT)            # Signal Output
    GPIO.output(SENSOR_ONE_SIG, False)              # Wait for Settle
    print "Waiting for Sensor One to Settle"
    time.sleep(2)

    GPIO.setup(SENSOR_TWO_TRIG, GPIO.OUT)           # Trigger Output
    GPIO.setup(SENSOR_TWO_ECHO, GPIO.IN)            # Echo Input
    GPIO.output(SENSOR_TWO_TRIG, False)             # Wait for Settle

    print "Waiting for Sensor Two to Settle"
    time.sleep(2)

setup()

def sensor_one_read():
    GPIO.setup(SENSOR_ONE_SIG, GPIO.OUT)
    GPIO.output(SENSOR_ONE_SIG, True)

    time.sleep(0.02)

    GPIO.output(SENSOR_ONE_SIG, False)

    GPIO.setup(SENSOR_ONE_SIG, GPIO.IN)
    goodread = True
    watchtime = time.time()
    while GPIO.input(SENSOR_ONE_SIG) == 0 and goodread:
            starttime = time.time()
            if (starttime - watchtime > timeout):
                    goodread = False

    if goodread:
            watchtime = time.time()
            while GPIO.input(SENSOR_ONE_SIG) == 1 and goodread:
                    endtime = time.time()
                    if (endtime-watchtime > timeout):
                            goodread = False

    if goodread:
            duration = endtime - starttime
            distance1 = round((duration * 34000 / 2), 2)
            print "Distance 1:", distance1, "cm"
            client_socket.send(str(distance1))

def sensor_two_read():
    GPIO.output(SENSOR_TWO_TRIG, True)
    time.sleep(0.1)
    GPIO.output(SENSOR_TWO_TRIG, False)

    while GPIO.input(SENSOR_TWO_ECHO) == 0:
        pulse_start = time.time()

    while GPIO.input(SENSOR_TWO_ECHO) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start

    distance2 = pulse_duration * 17150

    distance2 = round(distance2, 2)
    print "Distance 2:", distance2, "cm"
    client_socket.send(str(distance2))
    

while(1):
    sensor_one_read()
    sensor_two_read()

