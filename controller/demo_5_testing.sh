#!/bin/bash

clear

echo "Starting demo"
echo ""
echo ""
echo ""
echo -e "\033[93mEnsure multi layer perception training has been run and data is in mlp_xml folder"
echo ""
echo ""
echo ""
echo -e "\033[91mStart multi_layer_perc_predict.py"
python multi_layer_perc_predict.py
sleep 5
echo "Script completed... closing"
echo -e "\033[0m"
exit
