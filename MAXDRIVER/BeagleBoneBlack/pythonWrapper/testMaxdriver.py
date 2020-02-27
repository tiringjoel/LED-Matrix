import bbbmaxdriver
import numpy as np

print("----------------MAX1----------------")
# mymax1 = bbbmaxdriver.MAX(10,20,35,4)
print("----------------MAX2----------------")
mymax = bbbmaxdriver.MAX(99,88,77,4)
x = np.arange(0,256,1,dtype = np.uint8)
x = np.reshape(x,(8,32))
mymax.shiftBufferOut(x)
# mymax.clearDisplay()