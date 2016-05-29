
import socket
import time


class SensorStreamingTest(object):
    def __init__(self):
        """
            Test the streaming of ultrasonic data from raspberry pi
        """
        self.server_socket = socket.socket()
        self.server_socket.bind(('192.168.43.178', 8002))
        self.server_socket.listen(0)
        self.connection, self.client_address = self.server_socket.accept()
        self.ultrasonic_stream()
    
    def ultrasonic_stream(self):
        
        try:
            print "Connection from: ", self.client_address
            start = time.time()
            
            while True:
                sensor_data = self.connection.recv(1024)
                print "Distance: %s cm" % sensor_data
                
        finally:
            self.connection.close()
            self.server_socket.close()

if __name__ == '__main__':
    SensorStreamingTest()