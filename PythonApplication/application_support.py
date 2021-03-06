#! /usr/bin/env python
#  -*- coding: utf-8 -*-
#
# Support module generated by PAGE version 4.26
#  in conjunction with Tcl version 8.6
#    Feb 18, 2020 08:13:39 PM CET  platform: Windows NT

import sys
import pygame_support
import pygame
import time
import threading
import uart

try:
    import Tkinter as tk
except ImportError:
    import tkinter as tk

try:
    import ttk
    py3 = False
except ImportError:
    import tkinter.ttk as ttk
    py3 = True

def set_Tk_var():
    global CbScrollEnabled
    # CbScrollEnabled = tk.StringVar()
    CbScrollEnabled = tk.BooleanVar()
    # global LblScrollDirection
    # LblScrollDirection = tk.StringVar()

def CallbackLoadPattern(p1):
    print('GUI_Listbox_support.CallbackLoadPattern')
    index = w.LbPatterns.curselection()[0]
    pattern = w.LbPatterns.get(index)
    pygame_support.grid.loadPattern(pattern)
    sys.stdout.flush()

def CallbackMoveGridDown(p1):
    print('GUI_Listbox_support.CallbackMoveGridDown')
    pygame_support.grid.setScrollDirection('DOWN')
    w.LblScrollDirection.config(text='Down')
    sys.stdout.flush()

def CallbackMoveGridLeft(p1):
    print('GUI_Listbox_support.CallbackMoveGridLeft')
    pygame_support.grid.setScrollDirection('LEFT')
    w.LblScrollDirection.config(text='Left')
    sys.stdout.flush()

def CallbackMoveGridRight(p1):
    print('GUI_Listbox_support.CallbackMoveGridRight')
    pygame_support.grid.setScrollDirection('RIGHT')
    w.LblScrollDirection.config(text='Right')
    sys.stdout.flush()

def CallbackMoveGridUp(p1):
    print('GUI_Listbox_support.CallbackMoveGridUp')
    pygame_support.grid.setScrollDirection('UP')
    w.LblScrollDirection.config(text='Up')
    sys.stdout.flush()

def CallbackOpenGrid(p1):
    print('GUI_Listbox_support.CallbackOpenGrid')
    sys.stdout.flush()

def CallbackQuit(p1):
    print('GUI_Listbox_support.CallbackQuit')
    CloseRequest()
    sys.stdout.flush()

def CallbackSavePattern(p1):
    print('GUI_Listbox_support.CallbackSavePattern')
    # w.TbPatterName.insert(INSERT,'Ello')
    text = w.TbPatterName.get("1.0", "end-1c")
    if pygame_support.grid.savePattern(text):
        w.LbPatterns.insert(0,text)
    sys.stdout.flush()

def CallbackScrollChange(p1):
    print('GUI_Listbox_support.CallbackScrollChange')
    if not CbScrollEnabled.get() == True:
        pygame_support.grid.enableScrolling() 
    else:
        pygame_support.grid.disableScrolling()
    sys.stdout.flush()

def CallbackSpeedChange(p1):
    print('GUI_Listbox_support.CallbackSpeedChange')
    pygame_support.grid.setScrollSpeed((w.ScSpeed.get()))
    sys.stdout.flush()
    
# Gets executed when pressing close button on window
def CloseRequest():
    print('GUI_Listbox_support.CloseRequest')
    pygame_support.closePygame()
    destroy_window()

def init(top, gui, *args, **kwargs):
    global w, top_level, root, t1, t2
    w = gui
    top_level = top
    root = top
    pygame_support.init()
    uart.init()
    t1 = threading.Thread(target=updateGrid)
    t1.start()
    t2 = threading.Thread(target=shiftGridOut)
    t2.start()
    w.LblScrollDirection.config(text='Right')
    
def destroy_window():
    # Function which closes the window.
    print("Destroying Window...")
    uart.close()
    global top_level
    t1.join()
    t2.join()
    top_level.destroy()
    top_level = None
    print("Window Destroyed")
    
def updateGrid():
    while pygame_support.IsPygameRunning():
        pygame_support.main()
        time.sleep(0.01)
        
def shiftGridOut():
    while pygame_support.IsPygameRunning():
        uart.main()
        time.sleep(0.05)
        
def testcallback():
    print("testcallback called...")

if __name__ == '__main__':
    import application
    application.vp_start_gui()




