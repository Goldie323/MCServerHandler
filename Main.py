from ctypes import cdll

mylib = cdll.LoadLibrary("./Library-Code/build/libMCServerHandler.so")

d = mylib.math_add(5, 3)
print(f"Result of addition: {d}")