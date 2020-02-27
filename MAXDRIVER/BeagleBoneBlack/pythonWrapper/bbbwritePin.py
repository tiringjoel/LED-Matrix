import ctypes
import os

maxdriverlib = ctypes.cdll.LoadLibrary(os.path.abspath("libmaxdriver.so"))

def wrap_function(funcname, restype, argtypes):
    """Simplify wrapping ctypes functions"""
    func = maxdriverlib.__getattr__(funcname)
    func.restype = restype
    func.argtypes = argtypes
    return func

# Load needed function:
iolib_init_func = wrap_function("iolib_init",ctypes.c_int,None)
iolib_setdir_func = wrap_function("iolib_setdir",ctypes.c_int,[ctypes.c_int,ctypes.c_int,ctypes.c_int])
iolib_free_func = wrap_function("iolib_free",ctypes.c_int,None)
iolib_delay_ms_func = wrap_function("iolib_delay_ms",ctypes.c_int,ctypes.c_uint)
iolib_BBBIO_sys_delay_ms_func = wrap_function("BBBIO_sys_delay_ms",ctypes.c_int,ctypes.c_ulong)
iolib_BBBIO_sys_delay_us_func = wrap_function("BBBIO_sys_delay_us",ctypes.c_int,ctypes.c_ulong)
iolib_pin_high_func = wrap_function("pin_high",None,[ctypes.c_int,ctypes.c_int])
iolib_pin_low_func = wrap_function("pin_low",None,[ctypes.c_int,ctypes.c_int])

def shiftBufferOut(self, buffer):
    self.shiftBufferOut_func(self, buffer)

def clearDisplay(self):
    self.clearDisplay_func(self)