import socket
import struct
import time
import threading
import queue

TIME_ADD = 'p'
TIME_SUB = 'o'
TIME_DELTA = 60.0
MAX_TIME_STEP = 3600.0
MIN_TIME_STEP = 1.0

def read_input(input_queue):
    while True:
        user_input = input()
        input_queue.put(user_input)

def run_datetime_server():
    time_step = MIN_TIME_STEP
    current_time = time.time()

    input_queue = queue.Queue()
    input_thread = threading.Thread(target=read_input, args=(input_queue,), daemon=True)
    input_thread.start()

    while True:
        if input_queue.qsize()>0:
            user_input = input_queue.get()

            if user_input == TIME_ADD: 
                print('add')
                time_step = max(min(time_step + TIME_DELTA, MAX_TIME_STEP), MIN_TIME_STEP) 
            elif user_input == TIME_SUB:
                print('sub')
                time_step = max(min(time_step - TIME_DELTA, MAX_TIME_STEP), MIN_TIME_STEP)               
        
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        t = time.localtime(current_time)

        s.sendto(struct.pack('IIIIIII', t.tm_hour, t.tm_min, t.tm_sec, t.tm_wday, t.tm_mday, t.tm_mon, t.tm_year),
                ('127.0.0.1', 12345))    

        time.sleep(1.0)
        current_time += time_step

run_datetime_server()