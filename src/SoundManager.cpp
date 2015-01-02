#include "SoundManager.h"
#include <iostream>
#include <cstring>

SoundManager* SoundManager::m_soundManager = nullptr;

SoundManager::SoundManager()
{
    m_isInitialized = false;
    m_isSoundOn = false;
    m_soundDevice = 0;
    m_soundContext = 0;

    // Initial listener position of the listener
    m_position[0] = 0.0;
    m_position[1] = 0.0;
    m_position[2] = 0.0;

    // Initial velocity of the listener
    m_velocity[0] = 0.0;
    m_velocity[1] = 0.0;
    m_velocity[2] = 0.0;

    // Initial orientation of the listener
    m_orientation[0] = 0.0;
    m_orientation[1] = 0.0;
    m_orientation[2] = -1.0;
    m_orientation[3] = 0.0;
    m_orientation[4] = 1.0;
    m_orientation[5] = 0.0;

    m_audioBuffersCount = 0;
    m_audioSourcesCount = 0;

    memset(m_audioBuffers, 0, sizeof(m_audioBuffers));
    memset(m_audioSources, 0, sizeof(m_audioSources));
}

SoundManager::~SoundManager()
{
    // Delete the sources and buffers
    alDeleteSources(MAX_AUDIO_SOURCES, m_audioSources);
    alDeleteBuffers(MAX_AUDIO_BUFFERS, m_audioBuffers);

    // Destroy the sound context and device
    m_soundContext = alcGetCurrentContext();
    m_soundDevice = alcGetContextsDevice(m_soundContext);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(m_soundContext);

    if(m_soundDevice)
    {
        alcCloseDevice(m_soundDevice);
    }
}

SoundManager* SoundManager::Instance()
{
    if(m_soundManager == nullptr)
    {
        m_soundManager = new SoundManager();
    }

    return m_soundManager;
}

bool SoundManager::Initialize()
{
    if(m_isInitialized)
    {
        return true;
    }

    // Initialize device
    m_soundDevice = alcOpenDevice(NULL);

    if(!m_soundDevice)
    {
        std::cout << "SoundManager::Initialize error : No sound device." << std::endl;
        return false;
    }

    // Initialize context
    m_soundContext = alcCreateContext(m_soundDevice, NULL);

    if(!m_soundContext)
    {
        std::cout << "SoundManager::Initialize error : No sound context." << std::endl;
        return false;
    }

    // Make context current and active
    alcMakeContextCurrent(m_soundContext);

    if(CheckALError())
    {
        std::cout << "SoundManager::Initialize error : Could not make sound context current and active." << std::endl;
        return false;
    }

    // Initialize audio buffers
    alGenBuffers(MAX_AUDIO_BUFFERS, m_audioBuffers);
    if(CheckALError("Initialize::alGenBuffers"))
    {
        return false;
    }

    // Initialize audio sources
    alGenSources(MAX_AUDIO_SOURCES, m_audioSources);
    if(CheckALError("Initialize::alGenSources"))
    {
        return false;
    }

    // Initialize listener position
    alListenerfv(AL_POSITION, m_position);

    // Initialize listener velocity
    alListenerfv(AL_VELOCITY, m_velocity);

    // Initialize listener orientation
    alListenerfv(AL_ORIENTATION, m_orientation);

    // Initialize Doppler
    alDopplerFactor( 1.0 );
    alDopplerVelocity( 343.0f );

    m_isInitialized = true;
    m_isSoundOn = true;

    return true;
}

void SoundManager::PrintAvailableDevices() {
    std::cout << "Sound devices available : " << '\n';
    if (alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT") == AL_TRUE)
    {
        std::cout << "List of devices : " << '\n';
        std::cout << (char*) alcGetString(NULL, ALC_DEVICE_SPECIFIER);
        std::cout << '\n';
    }
    else
    {
        std::cout << "Enumeration error" << '\n';
    }
}

bool SoundManager::LoadAudio(const std::string filename, unsigned int *audioId, bool loop)
{
    if(filename.empty())
    {
        return false;
    }

    if(m_audioSourcesCount >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    // Clear errors code
    alGetError();

    int bufferId = -1;

    bufferId = FindAudioInBuffer(filename);
    // Audio is not yet loaded
    if(bufferId < 0)
    {
        bufferId = LoadAudioBuffer(filename);
        if(bufferId < 0)
        {
            // Buffer is full
            return false;
        }
    }

    int sourceId = m_audioSourcesCount;
    *audioId = sourceId;
    m_audioSourcesCount++;

    alSourcei(m_audioSources[sourceId], AL_BUFFER, m_audioBuffers[bufferId]);
    alSourcei(m_audioSources[sourceId], AL_LOOPING, loop);

    if(CheckALError("LoadAudio::alSourcei"))
    {
        return false;
    }

    return true;
}

int SoundManager::LoadAudioBuffer(const std::string filename)
{
    if(filename.empty())
    {
        return -1;
    }

    if(m_audioBuffersCount >= MAX_AUDIO_BUFFERS)
    {
        return -1;
    }

    int bufferId = m_audioBuffersCount;

    alGetError();

    LoadWAV(filename, bufferId);

    if (CheckALError( "LoadAudioBuffer()::alutCreateBufferFromFile" ))
    {
        return false;
    }

    m_audioBuffersFilename[bufferId] = filename;
    m_audioBuffersCount++;

    return bufferId;
}

void SoundManager::LoadWAV(const std::string &filename, unsigned int bufferId)
{
    m_audioBuffers[bufferId] = alutCreateBufferFromFile(filename.c_str());
}

int SoundManager::FindAudioInBuffer(const std::string filename)
{
    for(int bufferId = 0; bufferId < MAX_AUDIO_BUFFERS; ++bufferId)
    {
        if(filename == m_audioBuffersFilename[bufferId])
        {
            return bufferId;
        }
    }
    return -1;
}

bool SoundManager::ReleaseAudio(unsigned int audioId)
{
    if(audioId >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    alSourceStop(m_audioSources[audioId]);
    m_audioBuffersCount--;

    return false;
}

bool SoundManager::Play(unsigned int audioId, bool forceRestart)
{
    if(audioId >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    int sourceAudioState = 0;

    alGetError();

    alGetSourcei(m_audioSources[audioId], AL_SOURCE_STATE, &sourceAudioState);

    if(sourceAudioState == AL_PLAYING)
    {
        if(forceRestart)
        {
            Stop(audioId);
        }
        else
        {
            return false;
        }
    }

    alSourcePlay(m_audioSources[audioId]);

    if(CheckALError("Play::alSourcePlay"))
    {
        return false;
    }

    return true;
}

bool SoundManager::Stop(unsigned int audioId)
{
    if(audioId >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    alGetError();

    alSourceStop(m_audioSources[audioId]);

    if(CheckALError("Stop::alSourceStop"))
    {
        return false;
    }

    return true;
}

bool SoundManager::StopAll()
{
    if(m_audioSourcesCount >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    alGetError();

    for(int i = 0; i < (int)m_audioSourcesCount; ++i)
    {
        Stop(i);
    }

    if(CheckALError("StopAll::alSourceStop"))
    {
        return false;
    }

    return true;
}

bool SoundManager::Pause(unsigned int audioId)
{
    if(audioId >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    alGetError();

    alSourcePause(m_audioSources[audioId]);

    if(CheckALError("Pause::alSourceStop"))
    {
        return false;
    }

    return true;
}

bool SoundManager::PauseAll()
{
    if(m_audioSourcesCount >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    alGetError();

    alSourcePausev(m_audioSourcesCount, m_audioSources);

    if(CheckALError("PauseAll::alSourcePausev"))
    {
        return false;
    }

    return true;
}

bool SoundManager::Resume(unsigned int audioId)
{
    return false;
}

bool SoundManager::ResumeAll()
{
    return false;
}

bool SoundManager::SetSoundPosition(unsigned int audioId, ALfloat x, ALfloat y, ALfloat z)
{
    if (audioId >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    ALfloat pos[] = {x, y, z};
    alSourcefv(m_audioSources[audioId], AL_POSITION, pos);

    if (CheckALError("SetSoundPosition::alSourcefv:AL_POSITION"))
    {
        return false;
    }

    return true;
}

bool SoundManager::SetSoundVelocity(unsigned int audioId, ALfloat x, ALfloat y, ALfloat z)
{
    if (audioId >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    ALfloat vel[] = {x, y, z};
    alSourcefv(m_audioSources[audioId], AL_VELOCITY, vel);

    if (CheckALError("SetSoundPosition::alSourcefv:AL_VELOCITY"))
    {
        return false;
    }

    return true;
}

bool SoundManager::SetSoundDirection(unsigned int audioId, ALfloat x, ALfloat y, ALfloat z)
{
    if (audioId >= MAX_AUDIO_SOURCES)
    {
        return false;
    }

    ALfloat dir[] = {x, y, z};
    alSourcefv(m_audioSources[audioId], AL_DIRECTION, dir);

    if (CheckALError("SetSoundPosition::alSourcefv:AL_DIRECTION"))
    {
        return false;
    }

    return true;
}

bool SoundManager::SetListenerPosition(unsigned int audioId,
    ALfloat xPos, ALfloat yPos, ALfloat zPos,
    ALfloat xVel, ALfloat yVel, ALfloat zVel,
    ALfloat yaw, ALfloat pitch, ALfloat roll
)
{

    // Position
    ALfloat pos[] = {xPos, yPos, zPos};
    alListenerfv(AL_POSITION, pos);

    if (CheckALError("SetListenerPosition::alListenerfv:AL_POSITION")) {
        return false;
    }

    // Velocity
    ALfloat vel[] = {xVel, yVel, zVel};
    alListenerfv(AL_VELOCITY, vel);

    if (CheckALError("SetListenerPosition::alListenerfv:AL_VELOCITY")) {
        return false;
    }

    // Direction
    ALfloat dir[] = {yaw, pitch, roll};
    alListenerfv(AL_ORIENTATION, dir);

    if (CheckALError("SetListenerPosition::alListenerfv:AL_DIRECTION"))
    {
        return false;
    }

    //alListenerf(AL_MAX_DISTANCE, 10000.0f);
    //alListenerf(AL_MIN_GAIN, 0.0f);
    //alListenerf(AL_MAX_GAIN, 1.0f);
    //alListenerf(AL_GAIN, 1.0f);

    return true;
}

bool SoundManager::CheckALError()
{
    ALenum errorCode;
    if((errorCode = alGetError()) != AL_NO_ERROR)
    {
        std::string errorMsg = "ERROR SoundManager::OpenAL : ";
        errorMsg += (char *) alGetString(errorCode);
        std::cout << errorMsg << std::endl;
        return true;
    }

    return false;
}

bool SoundManager::CheckALError(const std::string& errorMsg)
{
    ALenum errorCode;
    if((errorCode = alGetError()) == AL_NO_ERROR)
    {
        return false;
    }

    switch(errorCode)
    {
        case AL_INVALID_NAME:
            std::cout << "ERROR SoundManager::OpenAL : " << errorMsg << " Invalid Name" << std::endl;
            break;
        case AL_INVALID_ENUM:
            std::cout << "ERROR SoundManager::OpenAL : " << errorMsg << " Invalid Enum" << std::endl;
            break;
        case AL_INVALID_VALUE:
            std::cout << "ERROR SoundManager::OpenAL : " << errorMsg << " Invalid Value" << std::endl;
            break;
        case AL_INVALID_OPERATION:
            std::cout << "ERROR SoundManager::OpenAL : " << errorMsg << " Invalid Operation" << std::endl;
            break;
        case AL_OUT_OF_MEMORY:
            std::cout << "ERROR SoundManager::OpenAL : " << errorMsg << " Out Of Memory" << std::endl;
            break;
        default:
            std::cout << "ERROR SoundManager::OpenAL : " << errorMsg << " Unknown Error" << std::endl;
            break;
    }
    return false;
}
