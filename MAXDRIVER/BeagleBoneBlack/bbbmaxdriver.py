from ctypes import *
import numpy as np
import numpy.ctypeslib as npct
import os

maxdriverlib = cdll.LoadLibrary(os.path.abspath("maxdriver.so"))
array_1d_uint8 = npct.ndpointer(dtype=np.uint8, ndim=2, flags='CONTIGUOUS')

def wrap_function(funcname, restype, argtypes):
    """Simplify wrapping ctypes functions"""
    func = maxdriverlib.__getattr__(funcname)
    func.restype = restype
    func.argtypes = argtypes
    return func

class MAX(Structure):
    _fields_ = [
        ("clkpin",c_uint8),
        ("cspin",c_uint8),
        ("datapin",c_uint8),
        ("nrmax",c_uint8)
    ]

    def __init__(self, clkpin, cspin, datapin, nrmax):
        self.clkpin = clkpin
        self.cspin = cspin
        self.datapin = datapin
        self.nrmax = nrmax
        self.initMax = wrap_function('initMax',None,[POINTER(MAX), c_uint8, c_uint8, c_uint8, c_uint8])
        # self = initMax(self,clkpin, cspin, datapin, nrmax)
        self.initMax(self,clkpin, cspin, datapin, nrmax)
        self.shiftBufferOut_func = wrap_function('shiftBufferOut',None,[POINTER(MAX), array_1d_uint8])
        self.clearDisplay_func = wrap_function('clearDisplay',None, [POINTER(MAX)])

    def shiftBufferOut(self, buffer):
        self.shiftBufferOut_func(self, buffer)

    def clearDisplay(self):
        self.clearDisplay_func(self)
