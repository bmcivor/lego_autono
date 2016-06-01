#!/bin/bash

clear

echo "Starting demo"
echo ""
echo ""
echo ""
echo -e "\033[93mEnsure camera is connected and motor controller ino file is flashed to Arduino, ultrasonic sensors and camera are orientated correctly"
echo ""
echo ""
echo ""
echo -e "\033[91mStart remote_auto_driving.py"
python remote_auto_driving.py &
echo "Control script running..."
sleep 5
echo "trying stream_camera.py on raspberry pi"
ssh pi@192.168.43.45 nohup python /home/pi/Desktop/vision_testing/stream_camera.py &
sleep 2
echo "trying ultrasonic_stream.py on raspberry pi"
ssh pi@192.168.43.45 nohup sudo python /home/pi/Desktop/vision_testing/ultrasonic_stream.py &
sleep 2
echo "program should be running"
echo -e "\033[0m"
