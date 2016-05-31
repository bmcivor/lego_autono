#!/bin/bash

clear

echo "Starting demo"
echo ""
echo ""
echo ""
echo -e "\033[93mEnsure camera is connected and chess calibration images are included in calibration_chess_frame folder"
echo ""
echo ""
echo ""
echo -e "\033[91mStart camera_calibration.py"
echo -e "\033[0m"

python camera_calibration.py
