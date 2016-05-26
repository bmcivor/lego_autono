# Autonomous Lego Car
Autonomous Lego Mindstorms / Arduino / Raspberry Pi

Working Repository for Autonomous Lego Car Build using the Lego Mindstorms
platform with microcontrollers to perform the Autonomous Tasks.

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
  - Numpy
  - OpenCV
  - Pygame
  - PiSerial
  
### About
- raspberry_pi/ 
  - ***stream_client.py***: stream video frames in jpeg format to the host computer
  - ***ultrasonic_client.py***: send distance data measured by ultrasonic sensor to the controller
- arduino/
  - ***derp.ino***: to be finalized
- controller/
  - cascade_xml/ 
    - trained cascade classifiers xml files
  - chess_board/ 
    - images for calibration, captured by pi camera 
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
  - ***rc_control_test.py***: drive RC car with keyboard (testing purpose)
  - ***picam_calibration.py***: pi camera calibration, returns camera matrix
  - ***collect_training_data.py***: receive streamed video frames and label frames for later training
  - ***mlp_training.py***: neural network training
  - ***mlp_predict_test.py***: test trained neural network with testing data
  - ***rc_driver.py***: a multithread server program receives video frames and sensor data, and allows RC car drives by itself 
