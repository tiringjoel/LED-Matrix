# -*- coding: utf-8 -*-
"""
Created on Sat Jun 20 13:33:19 2020

@author: Joel
"""

import pygame_support as ps
import serial
import time
import struct
import ctypes

def init():
    global ser
    try:
        ser = serial.Serial('COM5',9600)
        time.sleep(2.5)
        return 1
    except:
        print("Port not reachable")  
        return 0          

def main():
    running = True
    while running:
        if ser.in_waiting != 0:
            s = ser.readline()
            print("Readed from Port: ",s)
            
        eingabe = input("Write to terminal:")
        if eingabe == 'quit':
            running = False
        else:
            #string = b'' + struct.pack('!B',ctypes.c_uint8(eingabe))
            #print(ctypes.c_uint8(eingabe))
            ser.write(ctypes.c_uint8(2))
            
    ser.close()
    # data = ps.grid.data.reshape(32,8)
    # for i in range(32):
    #     dataout = (-1)*data[i][0] + (-2)*data[i][1] + (-4)*data[i][2] + (-8)*data[i][3] + (-16)*data[i][4]+ (-32)*data[i][5]+ (-64)*data[i][6] + (-128)*data[i][7]

success = init()
if success:
    main()