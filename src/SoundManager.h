#ifndef __SOUNDMANAGER_H_
#define __SOUNDMANAGER_H_

#include <string>

#include "LOpenAL.h"

const int MAX_AUDIO_BUFFERS = 64;
const int MAX_AUDIO_SOURCES = 16;

class SoundManager
{
    public:
        virtual ~SoundManager();

        static SoundManager* Instance();
        static void Close();
        bool Initialize();

        bool LoadAudio(const std::string filename, unsigned int *audioId, bool loop = false);
        bool ReleaseAudio(unsigned int audioId);
        int LoadAudioBuffer(const std::string filename);
        int FindAudioInBuffer(const std::string filename);

        bool Play(unsigned int audioId, bool forceRestart = false);

        bool Stop(unsigned int audioId);
        bool StopAll();

        bool Pause(unsigned int audioId);
        bool PauseAll();
        bool Resume(unsigned int audioId);
        bool ResumeAll();

        bool SetSoundPosition(unsigned int audioId, ALfloat x, ALfloat y, ALfloat z);
        bool SetSoundVelocity(unsigned int audioId, ALfloat x, ALfloat y, ALfloat z);
        bool SetSoundDirection(unsigned int audioId, ALfloat x, ALfloat y, ALfloat z);

        bool SetListenerPosition(
            unsigned int audioId,
            ALfloat xPos, ALfloat yPos, ALfloat zPos,
            ALfloat xVel, ALfloat yVel, ALfloat zVel,
            ALfloat yaw, ALfloat pitch, ALfloat roll
        );

    private:
        // TODO: (Pavel) LoadOGG
        // TODO: (Pavel) LoadWAV
        // TODO: (Pavel) LoadAU

        SoundManager();

        static SoundManager* m_soundManager;

        bool m_isInitialized;
        bool m_isSoundOn;

        ALCdevice* m_soundDevice;
        ALCcontext* m_soundContext;

        ALfloat m_position[3];
        ALfloat m_velocity[3];
        ALfloat m_orientation[6];

        unsigned int m_audioSourcesCount;
        unsigned int m_audioSources[MAX_AUDIO_SOURCES];

        unsigned int m_audioBuffersCount;
        unsigned int m_audioBuffers[MAX_AUDIO_BUFFERS];
        std::string m_audioBuffersFilename[MAX_AUDIO_BUFFERS];

        bool CheckALError();
        bool CheckALError(const std::string &errorMsg);
};


#endif //__SOUNDMANAGER_H_