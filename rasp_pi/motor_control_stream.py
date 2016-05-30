
import serial
from socket import *

class FinalRCDrive(object):
    """
    Testing communication from Controller, to RiPi, to Arduino, to Motor
    Removing the need when controlling by keyboard to have both Wifi and 
    Serial connected to Controller
    Only required connection is wifi from Controller to RiPi, making the car
    completely remote controlled
    """
    def __init__(self):
        self.ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
        self.send_inst = True
        client_socket = socket(AF_INET, SOCK_STREAM)
        client_socket.connect(('192.168.43.178', 8001))
        self.read_send_comms()

    def read_send_comms(self):
        try:            
            while self.send_inst:
                # read socket
                # write to serial
                button_data = client_socket.recv(2)
                print "Button pressed: %s" % button_data

        finally:
            pass

if __name__ == '__main__':
    FinalRCDrive()
