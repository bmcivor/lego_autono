

import numpy as np
import cv2
import socket


class VideoStreamingTest(object):
    def __init__(self):

        self.server_socket = socket.socket()
        self.server_socket.bind(('192.168.43.178', 8000))
        self.server_socket.listen(0)
        self.connection, self.client_address = self.server_socket.accept()
        self.connection = self.connection.makefile('rb')
        self.video_streaming()

    def video_streaming(self):

        try:
            print "Connection from: ", self.client_address
            print "Streaming video to controller..."
            print "Press 'x' to exit"

            vid_stream_bytes = ' '
            while True:
                vid_stream_bytes += self.connection.read(1024)
                # find boundaries of image data
                first = vid_stream_bytes.find('\xff\xd8')
                last = vid_stream_bytes.find('\xff\xd9')
                if first != -1 and last != -1:
                    jpg = vid_stream_bytes[first:last + 2]
                    vid_stream_bytes = vid_stream_bytes[last + 2:]
                    # change to test filtering of image data
                    image = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8), cv2.CV_LOAD_IMAGE_GRAYSCALE)
                    # image = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8), cv2.CV_LOAD_IMAGE_UNCHANGED)
                    cv2.flip(image, flipCode = -1)
                    cv2.imshow('image', image)

                    # wait for q keypress
                    if cv2.waitKey(1) & 0xFF == ord('x'):
                        break
        finally:
            self.connection.close()
            self.server_socket.close()

if __name__ == '__main__':
    VideoStreamingTest()