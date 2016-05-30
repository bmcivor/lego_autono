import socket
import pygame
from pygame.locals import *

class RCTest(object):
    """
    Testing communication from Controller, to RiPi, to Arduino, to Motor
    Removing the need when controlling by keyboard to have both Wifi and 
    Serial connected to Controller
    Only required connection is wifi from Controller to RiPi, making the car
    completely remote controlled
    """
    def __init__(self):
        pygame.init()
        self.send_inst = True
        self.server_socket = socket.socket()
        self.server_socket.bind(('192.168.43.178', 8001))
        self.server_socket.listen(0)
        self.connection, self.client_address = self.server_socket.accept()
        self.steer()

    def steer(self):
        """
        Decision maker based on button press from Controller
        No switch statement in python so elif is used
        """
        try:
            print "Connection from: ", self.client_address
            while self.send_inst:
                for event in pygame.event.get():
                    if event.type == KEYDOWN:
                        # Returns state of keys in keyboard of controller
                        key_input = pygame.key.get_pressed()
                        
                        # complex orders
                        if key_input[pygame.K_UP]:
                            print("Forward")
                            self.server_socket.send(str(1))

                        elif key_input[pygame.K_DOWN]:
                            print("Reverse")
                            self.server_socket.send(str(2))

                        elif key_input[pygame.K_RIGHT]:
                            print("Right")
                            self.server_socket.send(str(3))

                        elif key_input[pygame.K_LEFT]:
                            print("Left")
                            self.server_socket.send(str(4))

                        # exit
                        elif key_input[pygame.K_x] or key_input[pygame.K_q]:
                            print 'Exit'
                            self.send_inst = False
                            self.server_socket.send(str(0))
                            break

                    elif event.type == pygame.KEYUP:
                        self.server_socket.send(str(5))
        finally:
            self.connection.close()
            self.server_socket.close()


if __name__ == '__main__':
    RCTest()
