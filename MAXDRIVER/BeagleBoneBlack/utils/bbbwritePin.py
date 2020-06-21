import ctypes
import os
import time

suffix = "bin/libmaxdriver.so"
libpath = os.path.join(os.path.dirname(os.getcwd()), suffix)

try:
    maxdriverlib = ctypes.cdll.LoadLibrary(libpath)
except OSError:
    print('cannot open', suffix)

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
iolib_delay_ms_func = wrap_function("iolib_delay_ms",ctypes.c_int,[ctypes.c_uint])
iolib_BBBIO_sys_delay_ms_func = wrap_function("BBBIO_sys_delay_ms",ctypes.c_int,[ctypes.c_ulong])
iolib_BBBIO_sys_delay_us_func = wrap_function("BBBIO_sys_delay_us",ctypes.c_int,[ctypes.c_ulong])
iolib_pin_high_func = wrap_function("pin_high",None,[ctypes.c_int,ctypes.c_int])
iolib_pin_low_func = wrap_function("pin_low",None,[ctypes.c_int,ctypes.c_int])
iolib_is_high_func = wrap_function("is_high",ctypes.c_int,[ctypes.c_int,ctypes.c_int])
iolib_is_low_func = wrap_function("is_low",ctypes.c,[ctypes.c_int,ctypes.c_int])

print("main routine started..")
connector = 8
pin = 14
delay = 100
output = 1

iolib_init_func()
iolib_setdir_func(connector,pin, output)
print("Direction set...")
iolib_pin_high_func(connector,pin)
print("Pin high...")
t1 = time.time()
#iolib_delay_ms_func(delay)
iolib_BBBIO_sys_delay_ms_func(delay)
iolib_BBBIO_sys_delay_us_func(1000)
t2 = time.time()
print(t2-t1)
iolib_pin_low_func(connector,pin)
print("Pin low...")
iolib_free_func()
print("freed Pin...")


