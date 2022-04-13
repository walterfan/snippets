import matplotlib.pyplot as plt
import numpy as np
import wave
import sys

file = "simple_music.wav"
spf = wave.open(file,'r')
param = spf.getparams()
print("nchannels=%d, sampwidth=%d, framerate=%d, nframes=%d, comptype=%s, compname=%s" 
	% (param[0], param[1], param[2], param[3], param[4], param[5]));
#Extract Raw Audio from Wav File
signal = spf.readframes(-1)
signal = np.fromstring(signal, 'Int16')


#If Stereo
if spf.getnchannels() == 2:
    print 'Just mono files'
    sys.exit(0)

plt.figure(1)
plt.title('Signal Wave...')
plt.plot(signal)
plt.show()