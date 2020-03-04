import bbbmaxdriver
import numpy as np

# # Max tests:
# print("----------------MAX1----------------")
# mymax1 = bbbmaxdriver.MAX(10,20,35,4)
# print("----------------MAX2----------------")
# mymax = bbbmaxdriver.MAX(99,88,77,4)
# x = np.arange(0,256,1,dtype = np.uint8)
# x = np.reshape(x,(8,32))
# mymax.shiftBufferOut(x)
# mymax.clearDisplay()

# write Pin tests:
myPin = bbbmaxdriver.Pin(8,14,1)
myPin.setPin_high()
bbbmaxdriver.delay_ms(1000)
bbbmaxdriver.delay_ms(999)
bbbmaxdriver.delay_us(1000)
print(myPin.getPin_state())
myPin.setPin_low()
bbbmaxdriver.delay_ms(999)
bbbmaxdriver.delay_us(1000)
myPin.setPin_low()
print(myPin.getPin_state())

myPin2 = bbbmaxdriver.Pin(8,14,0)
myPin2.setPin_high()
myPin2.getPin_state()

# def setPin_high(self):
# def setPin_low(self):
# def setPin_state(self, state):
# def getPin_state(self):
# def freePin(self):
# def delay_ms(self, ms):
# def delay_us(self, us):
