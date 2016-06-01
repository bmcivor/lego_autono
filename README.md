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
  - MindSensors Shield (www.mindsensors.com)
* Raspberry Pi: 
  - Picamera
  - HCSR04 Ultrasonic sensor
* Controller:
  - pip install <module>
    - PySerial (pyserial)
    - Numpy (numpy, as an alias np)
    - OpenCV (cv2)
    - Pygame (pygame)
* Testing:
  - ***drive_by_keyboard.py***: small testing for control by keypress over serial connection
  - ***ultrasonic_server_test.py***: runs a server with a socket for communication over a network, strips the data for display and correct use within the system
  - ***video_server_test.py***: runs a server with socket communication over a network to recieve a video stream using the module OpenCV to handle recieving the frames, and display. Terminates on keypress 'x'.

### About
- rasp_pi/
  - ***test_sensor_mac.py***: original setup and implementation of dual ultrasonic sensor testing
  - ***stream_camera.py***: stream video frames in jpeg format to the host computer
  - ***ultrasonic_stream.py***: send distance data measured by ultrasonic sensor to the controller
- arduino/
  - preliminary implementation in parent directory
  - lib/
    - ***BaseI2CDevice.h***: Base I2C functionality with Arduino Boards, The Arduino Due has two I2C / TWI interfaces SDA1 and SCL1, pin 20, 21.
    - ***EVShield.h***: Provides functionality to Lego Mindstorm Sensors and Motors with EVShield.
    - ***EVShieldI2C.h***: Implements I2C interfaces used by EVShield.
    - ***MsTimer2.h***: Timer controller implementing interrupts with Arduino Boards.
    - ***SHDefines.h***: Common constants for the library.
    - ***Softi2cMaster.h***: Software I2C interface used by EVShield on Arduino.
  /arduino
    - ***arduino.ino**: Main output from the Arduino to the physical motors and sensors. Reads from usb tty serial connection the desired output to write to encoders/decoders.
- controller/
  - cascade_xml/
    - trained cascade classifiers xml files, containing provided data for a stop sign
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

# Special Notes:
removed power saving on wifi adapter to limit dropping while adapter is idle

sudo nano /etc/modprobe.d/8192cu.conf
options 8192cu rtw_power_mgnt=0 rtw_enusbss=1 rtw_ips_mode=1
sudo reboot

#References
Structural build is based on the design provided by Laurens Valk in <http://robotsquare.com/books/ev3discovery/companion-page/>

***OpenCV documentation***
- <http://docs.opencv.org/2.4/modules/ml/doc/neural_networks.html#cvann-mlp-predict>
- <http://docs.opencv.org/2.4/doc/user_guide/ug_traincascade.html>
- <http://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_calib3d/py_calibration/py_calibration.html>

***Zheng Wang Blog Post***
- <https://zhengludwig.wordpress.com/projects/self-driving-rc-car/>

***David Singleton Blog Post***
- <http://blog.davidsingleton.org/nnrccar/>

***PiCamera documentation***
- <http://picamera.readthedocs.io/en/release-1.10/recipes1.html>
