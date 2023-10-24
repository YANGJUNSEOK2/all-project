#include "Sound.hpp"


void BackgroundSound::BGSound_Init(const char* soundPath)
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, buffer_size);

    Mix_Music* sound = Mix_LoadMUS(soundPath);
    name = sound;

    Mix_VolumeMusic(volume);
}

void BackgroundSound::BGSound_Play()
{
    Mix_PlayMusic(name, loop);
}

void BackgroundSound::BGSound_Pause()
{
    Mix_PauseMusic();
}

void BackgroundSound::BGSound_Resum()
{
    Mix_ResumeMusic();
}

void BackgroundSound::BGSound_Volume(int volume)
{
    Mix_VolumeMusic(volume);
}

void BackgroundSound::BGSound_Free()
{
    Mix_FreeMusic(name);
}


void SoundEffect::SoundEffect_Init(const char* soundPath)
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, buffer_size);

    Mix_Chunk* sound = Mix_LoadWAV(soundPath);
    name = sound;

    Mix_VolumeChunk(name, volume);
}

void SoundEffect::SoundEffect_Play()
{
    Mix_PlayChannel(channel, name, repeat_once);
}

void SoundEffect::SoundEffect_Pause()
{
    Mix_Pause(channel);
}

void SoundEffect::SoundEffect_Resum()
{
    Mix_Resume(channel);
}

void SoundEffect::SoundEffect_Volume(int volume)
{
    Mix_VolumeChunk(name, volume);
}

void SoundEffect::SoundEffect_Free()
{
    Mix_FreeChunk(name);
}

