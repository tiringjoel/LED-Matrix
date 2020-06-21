# -*- coding: utf-8 -*-
"""
Created on Sat Jun 20 13:33:19 2020

@author: Joel
"""

import pygame_support as ps
import serial
import time

def init():
    global ser
    try:
        ser = serial.Serial('COM5',9600)
        time.sleep(1.5)
        return 1
    except:
        print("Port not reachable")  
        return 0          

def main():
    global ser
    if ser.in_waiting != 0:
        s = ser.readline()
        print("Readed from Port: ",s)
                
    data = ps.grid.data.reshape(32,8)
    for i in range(32):
        dataout = (-1)*data[i][0] + (-2)*data[i][1] + (-4)*data[i][2] + (-8)*data[i][3] + (-16)*data[i][4]+ (-32)*data[i][5]+ (-64)*data[i][6] + (-128)*data[i][7]
        ser.write(str.encode(str(int(dataout))))
        ser.write(str.encode(' '))

def close():
    global ser
    ser.close()
    print("Port closed")
    
if __name__ == '__main__':
    import application
    application.vp_start_gui()