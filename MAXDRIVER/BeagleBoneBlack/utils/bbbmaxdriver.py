import ctypes as ct
import numpy as np
import numpy.ctypeslib as npct
import os

# To Do: 	declare PinState in class Pin private or make restype as fun variable
#		Check for inputcondition in getPin_state

# Get library path
suffix = "bin/libmaxdriver.so"
libpath = os.path.join(os.path.dirname(os.getcwd()), suffix)

# Import
try:
    maxdriverlib = ct.cdll.LoadLibrary(libpath)
except OSError:
    print('cannot open', suffix)

array_1d_uint8 = npct.ndpointer(dtype=np.uint8, ndim=2, flags='CONTIGUOUS')

def wrap_function(funcname, restype, argtypes):
    """Simplify wrapping ctypes functions"""
    func = maxdriverlib.__getattr__(funcname)
    func.restype = restype
    func.argtypes = argtypes
    return func

class Max(ct.Structure):
    _fields_ = [
        ("clkpin",ct.c_uint8),
        ("cspin",ct.c_uint8),
        ("datapin",ct.c_uint8),
        ("nrmax",ct.c_uint8)
    ]

    def __init__(self, clkpin, cspin, datapin, nrmax):
        self.clkpin = clkpin
        self.cspin = cspin
        self.datapin = datapin
        self.nrmax = nrmax
        self.initMax = wrap_function('initMax',None,[ct.Pointer(Max), ct.c_uint8, ct.c_uint8, ct.c_uint8, ct.c_uint8])
        self.initMax(self,clkpin, cspin, datapin, nrmax)
        self.shiftBufferOut_func = wrap_function('shiftBufferOut',None,[ct.Pointer(Max), array_1d_uint8])
        self.clearDisplay_func = wrap_function('clearDisplay',None, [ct.Pointer(Max)])

    def shiftBufferOut(self, buffer):
        self.shiftBufferOut_func(self, buffer)

    def clearDisplay(self):
        self.clearDisplay_func(self)

class Pin:
    def __init__(self, connector, pin, output):
        self.connector = connector
        self.pin = pin
        self.output = output
        self.PinState = 0
        # Load functions from dynamic library
        self.iolib_init_func = wrap_function("iolib_init",ct.c_int,None)
        self.iolib_setdir_func = wrap_function("iolib_setdir",ct.c_int,[ct.c_int,ct.c_int,ct.c_int])
        self.iolib_free_func = wrap_function("iolib_free",ct.c_int,None)
        self.iolib_pin_high_func = wrap_function("pin_high",None,[ct.c_int,ct.c_int])
        self.iolib_pin_low_func = wrap_function("pin_low",None,[ct.c_int,ct.c_int])
        self.iolib_is_high_func = wrap_function("is_high",ct.c_int,[ct.c_int,ct.c_int])
        self.iolib_is_low_func = wrap_function("is_low",ct.c_int,[ct.c_int,ct.c_int])

        # Init Pin and set direction
        self.iolib_init_func()
        self.iolib_setdir_func(self.connector, self.pin, self.output)

    def setPin_high(self):
        if self.output == 1:
            self.iolib_pin_high_func(self.connector, self.pin)
        else: 
            print('Cannot change pin State, Pin declared as Input')

    def setPin_low(self):
        if self.output == 1:
            self.iolib_pin_low_func(self.connector, self.pin)
        else: 
            print('Cannot change pin State, Pin declared as Input')

    def setPin_state(self, state):
        if state != 0 or state == True:
            setPin_high(self)
        else:
            setPin_low(self)

    def getPin_state(self):
        if self.iolib_is_high_func(self.connector, self.pin) == 1:
            self.PinState == 1
        elif self.iolib_is_low_func(self.connector, self.pin) == 1:
            self.PinState == 0
        else:
            self.PinState == None
        return self.PinState

    def freePin(self):
        self.iolib_free_func()

 
# Delay functions       
def delay_ms(ms):
    if ms > 999:
        print('delay value needs to be less than 999')
    elif ms < 0:
        print ('no negative numbers allowed')
    else:
        iolib_delay_ms_func = wrap_function("iolib_delay_ms",ct.c_int,[ct.c_uint])
        # iolib_BBBIO_sys_delay_ms_func = wrap_function("BBBIO_sys_delay_ms",ct.c_int,[ct.c_ulong])
        iolib_delay_ms_func(ms)

def delay_us(us):
    if us < 0:
        print ('no negative numbers allowed')
    else:
        iolib_BBBIO_sys_delay_us_func = wrap_function("BBBIO_sys_delay_us",ct.c_int,[ct.c_ulong])
        iolib_BBBIO_sys_delay_us_func(us) 




