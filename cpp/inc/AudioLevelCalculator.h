#ifndef __AUDIO_LEVEL_CALCULATOR_H__
#define __AUDIO_LEVEL_CALCULATOR_H__

#include <cstdint>
#include <string>

class AudioLevelCalculator
{
public:
    int calculateAudioLevel(uint8_t* samples, int offset, int length, int overload);
};

#endif