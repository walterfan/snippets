import ctypes
import pathlib

# refer to https://realpython.com/python-bindings-overview

if __name__ == "__main__":
    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "libtiny_util.so"
    print("load " + str(libname))
    c_lib = ctypes.CDLL(libname)

    num = 2.3
    ret = c_lib.round_to_int(ctypes.c_float(num))

    print("{} round to {} ".format(num, str(ret)))

    text = "hello world"
    wave = "hello.wav"

    b_text = text.encode("utf-8")
    b_wave = wave.encode("utf-8")

    ret2 = c_lib.text_to_wav(ctypes.c_char_p(b_text), ctypes.c_char_p(b_wave))