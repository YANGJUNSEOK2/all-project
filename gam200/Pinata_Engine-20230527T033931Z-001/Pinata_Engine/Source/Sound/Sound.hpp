#pragma once
#include <SDL_mixer.h>


class BackgroundSound
{
public:
    BackgroundSound() : buffer_size(2048), loop(-1), volume(20), name() {}
    ~BackgroundSound() {}

    void BGSound_Init(const char* soundPath);

    void  BGSound_Play();

    void  BGSound_Pause();

    void  BGSound_Resum();

    void  BGSound_Free();

    void  BGSound_Volume(int volume);

    Mix_Music* BGSound_Name() { return name; }

private:
    int buffer_size;
    int loop;
    int volume;
    Mix_Music* name;
};

class SoundEffect
{
public:
    SoundEffect() : buffer_size(2048), channel(-1), repeat_once(0), volume(10), name(nullptr) {}
    ~SoundEffect() {}

    void SoundEffect_Init(const char* soundPath);

    void SoundEffect_Play();

    void SoundEffect_Pause();

    void SoundEffect_Resum();

    void SoundEffect_Free();

    void SoundEffect_Volume(int volume);

    Mix_Chunk* SoundEffect_Name() { return name; }

private:
    int buffer_size;
    int channel;
    int repeat_once;
    int volume;
    Mix_Chunk* name;
};
