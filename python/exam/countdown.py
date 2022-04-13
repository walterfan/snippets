import sys
import time
import os

def countdown(seconds):
    while seconds > 0:
        print(seconds, end=' ')
        time.sleep(1)
        seconds = seconds -1
    return

if __name__ == '__main__':

    if len(sys.argv) < 3:
        print('usage: python countdown seconds wavfile - countdown according the specified seconds')
        sys.exit(1)

    seconds = int(sys.argv[1])
    wavfile = sys.argv[2]
    countdown(seconds)
    os.system("play " + wavfile)
