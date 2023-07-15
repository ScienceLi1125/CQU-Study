import serial
import threading

CURR_DETECT_TEXT = "当前避障模块是否有障碍物：无"
CURR_LED_TEXT = "当前LED状态：灭"
CURR_LED_STATE = '0'

def read_serial_data(ser):
    global CURR_DETECT_TEXT
    while True:
        data = ser.read().decode()  # 读取单个字节的数据
        CURR_DETECT_TEXT = f"当前避障模块是否有障碍物：{'有' if data == '1' else '无'}"

def write_serial_data(ser):
    for i in range(100000):
        ser.write(b'')
    global CURR_LED_STATE
    while True:
        ser.write(CURR_LED_STATE.encode(encoding='ascii'))

def print_curr_text():
    global CURR_DETECT_TEXT,CURR_LED_TEXT
    while True:
        print(f"\r{CURR_DETECT_TEXT},{CURR_LED_TEXT}", end='', flush=True)
# 打开串口
ser = serial.Serial('COM3', 9600)  # 串口名称和波特率
# 创建后台线程读取数据,写入数据,并打印当前系统状态
read_thread = threading.Thread(target=read_serial_data, args=(ser,))
read_thread.start()
write_thread = threading.Thread(target=write_serial_data, args=(ser,))
write_thread.start()
print_thread = threading.Thread(target=print_curr_text)
print_thread.start()

# 主线程执行其他操作
while True:
    user_input = input()
    CURR_LED_STATE = user_input
    CURR_LED_TEXT = f"当前LED状态：{'亮' if user_input == '1' else '灭'}"
