import os

#libpath = os.path.abspath("libmaxdirver.so")
#print("libpath: \n", libpath)
suffix = "bin/libmaxdriver.so"
#dirname = os.getcwd()
#print("cwd: \n", dirname)
prefix = os.path.dirname(os.getcwd())
libpath = os.path.join(prefix, suffix)
print(libpath)
print(os.path.isfile(libpath))
