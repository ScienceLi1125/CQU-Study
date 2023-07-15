import serial
import threading

class CarReader:
    def __init__(self, serial) -> None:
        self.curr_cnt = 0
        self.serial = serial
    
    def read_serial_data(self):
        while True:
            data = self.serial.read().decode()
            if data == '1':
                self.curr_cnt += 1

    def start(self):
        read_thread = threading.Thread(target=self.read_serial_data)
        read_thread.start()

    def harvest(self) -> int:
        cnt = self.curr_cnt
        self.curr_cnt = 0
        return cnt

class LEDController:
    def __init__(self, serial) -> None:
        self.state = '' # 0——南北为红灯，东西为绿灯；1——南北为绿灯，东西为红灯
        self.serial = serial
    
    def write_serial_data(self):
        for i in range(10000000):
            self.serial.write(b'')
        while True:
            self.serial.write(self.state.encode(encoding='ascii'))

    def start(self):
        write_thread = threading.Thread(target=self.write_serial_data)
        write_thread.start()