#!/bin/bash

clear

echo "Starting demo"
echo ""
echo ""
echo ""
echo -e "\033[93mEnsure Arduino has motor controller ino flashed, and diagnostics have completed"
echo ""
echo ""
echo ""
echo -e "\033[91mStart drive_by_keyboard.py"
echo -e "\033[0m"

python drive_by_keyboard.py &
