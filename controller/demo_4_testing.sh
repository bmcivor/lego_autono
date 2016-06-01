#!/bin/bash

clear

echo "Starting demo"
echo ""
echo ""
echo ""
echo -e "\033[93mEnsure data has been collected and sample frames stored in training_images folder"
echo ""
echo ""
echo ""
echo -e "\033[91mStart multi_layer_perc_training.py"
python multi_layer_perc_training.py
sleep 5
echo "Script completed... closing"
echo -e "\033[0m"
exit
