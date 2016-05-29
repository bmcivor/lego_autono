# Autonomous Lego Car
Autonomous Lego Mindstorms / Arduino / Raspberry Pi

Working Repository for Autonomous Lego Car Build using the Lego Mindstorms
platform with micro-controllers to perform the Autonomous Tasks.

Current setup is for a Nexus 6 Android Platform router. Power saving mode on
Raspberry Pi Wi Pi must be disabled for continuous connection between Raspberry Pi
and Controller.

### Dependencies
* Arduino:
  - Lego Mindstorms
    - Motors
    - Sensors
  - MindSensors Shield
* Raspberry Pi: 
  - Picamera
  - HCSR04 Ultrasonic sensor
* Controller:
  - pip install <module>
    - PySerial (pyserial)
    - Numpy (numpy, as an alias np)
    - OpenCV (cv2)
    - Pygame
* Testing:
  - ***drive_by_keyboard.py***: small testing for control by keypress over serial connection
  
### About
- raspberry_pi/ 
  - ***stream_client.py***: stream video frames in jpeg format to the host computer
  - ***ultrasonic_client.py***: send distance data measured by ultrasonic sensor to the controller
- arduino/
  - ***derp.ino***: to be finalized
- controller/
  - cascade_xml/ 
    - trained cascade classifiers xml files
  - calibration_test_images/ 
    - images for calibration, supplied by opencv samples
  - training_data/ 
    - training image data for neural network in npz format
  - testing_data/ 
    - testing image data for neural network in npz format
  - training_images/ 
    - saved video frames during image training data collection stage (optional)
  - mlp_xml/ 
    - trained neural network parameters in a xml file

    To be added and adapted 
    -----------------------

  - ***picam_calibration.py***: pi camera calibration, returns camera matrix
  - ***collect_training_data.py***: receive streamed video frames and label frames for later training
  - ***mlp_training.py***: neural network training
  - ***mlp_predict_test.py***: test trained neural network with testing data
  - ***rc_driver.py***: a multithread server program receives video frames and sensor data, and allows RC car drives by itself 


# Special Notes:
--------------
removed power saving on wifi adapter to limit dropping while adapter is idle

sudo nano /etc/modprobe.d/8192cu.conf
and paste this:

# Disable power saving
-----------------------

options 8192cu rtw_power_mgnt=0 rtw_enusbss=1 rtw_ips_mode=1
then reboot

sudo reboot
