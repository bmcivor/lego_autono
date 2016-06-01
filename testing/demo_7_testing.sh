#!/bin/bash

clear

echo "Starting demo"
echo ""
echo ""
echo ""
echo -e "\033[93mEnsure ultrasonic sensors are connected and in correct position on car"
echo ""
echo ""
echo ""
echo -e "\033[91mStart ultrasonic_server_test.py"
python ultrasonic_server_test.py &
echo "Script running"
sleep 5
echo "trying ultrasonic_stream.py on raspberry pi"
ssh pi@192.168.43.45 nohup sudo python /home/pi/Desktop/vision_testing/ultrasonic_stream.py &
echo -e "\033[0m"
