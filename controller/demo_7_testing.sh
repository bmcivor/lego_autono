#!/bin/bash

clear

echo "Starting demo"
echo ""
echo ""
echo ""
echo -e "\033[93mEnsure camera is connected and motor controller ino file is flashed to Arduino"
echo ""
echo ""
echo ""
echo -e "\033[91mStart collect_data.py"
python collect_data.py &
echo "script ran"
sleep 5
echo "trying stream_camera.py on raspberry pi"
ssh pi@192.168.43.45 nohup python /home/pi/Desktop/vision_testing/stream_camera.py &
echo -e "\033[0m"
