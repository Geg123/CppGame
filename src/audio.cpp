#include"../include/audio.h"
void checkOpenALImplementation() {
    ALCdevice* device = alcOpenDevice(nullptr);
    
    // Проверяем реализацию
    const ALCchar* vendor = alcGetString(device, ALC_DEVICE_SPECIFIER);
    const ALCchar* version = alGetString(AL_VERSION);
    const ALCchar* renderer = alGetString(AL_RENDERER);
    const ALCchar* extensions = alGetString(AL_EXTENSIONS);
    
    std::cout << "OpenAL Vendor: " << (vendor ? vendor : "Unknown") << std::endl;
    std::cout << "OpenAL Version: " << (version ? version : "Unknown") << std::endl;
    std::cout << "OpenAL Renderer: " << (renderer ? renderer : "Unknown") << std::endl;
    std::cout << "OpenAL Extensions: " << (extensions ? extensions : "None") << std::endl;
    
    // Проверяем EFX поддержку
    const ALCchar* alcExtensions = alcGetString(device, ALC_EXTENSIONS);
    std::string alcExtStr(alcExtensions ? alcExtensions : "");
    
    if (alcExtStr.find("ALC_EXT_EFX") != std::string::npos) {
        std::cout << "EFX extension IS supported" << std::endl;
        
        // Пробуем разные имена функций
        void* func1 = alGetProcAddress("alGenEffects");
        void* func2 = alGetProcAddress("ALGENEFFECTS"); // Верхний регистр
        void* func3 = alGetProcAddress("alGenEffectsEXT"); // С суффиксом
        
        std::cout << "alGenEffects: " << func1 << std::endl;
        std::cout << "ALGENEFFECTS: " << func2 << std::endl;
        std::cout << "alGenEffectsEXT: " << func3 << std::endl;
    } else {
        std::cout << "EFX extension NOT supported" << std::endl;
    }
    
    alcCloseDevice(device);
}
// Глобальные указатели на функции

bool checkALError(const std::string& message) {
    ALenum error = alGetError();
    if (error != AL_NO_ERROR) {
        std::cerr << "OpenAL Error (" << message << "): " << alGetString(error) << std::endl;
        return false;
    }
    return true;
}

Sound::Sound()
{
    // 3. Создание и настройка источника звука
    alGenSources(1, &source);
    
    if (!checkALError("Source generation")) {
        //return -1;
    }
    
    // Устанавливаем параметры источника
    alSourcef(source, AL_PITCH, 1.0f);     // Высота тона
    alSourcef(source, AL_GAIN, 1.0f);      // Громкость
    alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f); // Позиция в 3D пространстве
    alSource3f(source, AL_VELOCITY, 0.0f, 0.0f, 0.0f); // Скорость
    alSourcei(source, AL_LOOPING, AL_FALSE); // Без зацикливания
    alSource3f(source, AL_DIRECTION, 0.0f, 0.0f, 0.0f);

    /*ALuint effect;

    alGenEffects(1, &effect);
    alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
    
    // Настройка параметров реверберации
    alEffectf(effect, AL_REVERB_DENSITY, 0.5f);
    alEffectf(effect, AL_REVERB_DIFFUSION, 0.5f);
    alEffectf(effect, AL_REVERB_GAIN, 0.32f);
    alEffectf(effect, AL_REVERB_GAINHF, 0.89f);
    alEffectf(effect, AL_REVERB_DECAY_TIME, 1.49f);
    alEffectf(effect, AL_REVERB_DECAY_HFRATIO, 0.83f);
    alEffectf(effect, AL_REVERB_REFLECTIONS_GAIN, 0.05f);
    alEffectf(effect, AL_REVERB_REFLECTIONS_DELAY, 0.007f);
    alEffectf(effect, AL_REVERB_LATE_REVERB_GAIN, 1.26f);
    alEffectf(effect, AL_REVERB_LATE_REVERB_DELAY, 0.011f);
    alEffectf(effect, AL_REVERB_AIR_ABSORPTION_GAINHF, 0.994f);
    alEffectf(effect, AL_REVERB_ROOM_ROLLOFF_FACTOR, 0.0f);
    
    // Создание слотов для эффектов
    ALuint slot;
    alGenAuxiliaryEffectSlots(1, &slot);
    alAuxiliaryEffectSloti(slot, AL_EFFECTSLOT_EFFECT, effect);
    
    // Привязка к источнику звука
    alSource3i(source, AL_AUXILIARY_SEND_FILTER, slot, 0, AL_FILTER_NULL);*/
}

void Sound::set(std::string path)
{
    buffer = alutCreateBufferFromFile(path.c_str());

    ALenum error = alutGetError();
    if (error != ALUT_ERROR_NO_ERROR) {
        printf("Error: %s\n", alutGetErrorString(error));
    }
    alSourcei(source, AL_BUFFER, buffer);
}

void Sound::play()
{
    alSourcePlay(source);
}


Sound::~Sound()
{
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
}

Audio::Audio()
{
    //checkOpenALImplementation();
    
    alutInitWithoutContext(NULL, NULL);
    device = alcOpenDevice(nullptr);
    //std::cout << !!alcIsExtensionPresent(device, "ALC_EXT_EFX");
    if (!device) {
        std::cerr << "Failed to open audio device" << std::endl;
        //return -1;
    }

    context = alcCreateContext(device, nullptr);
    if (!context || !alcMakeContextCurrent(context)) {
        std::cerr << "Failed to create audio context" << std::endl;
        alcCloseDevice(device);
        //return -1;
    }

    // Проверяем наличие ошибок после инициализации
    if (!checkALError("Initialization")) {
        alcDestroyContext(context);
        alcCloseDevice(device);
        //return -1;
    }
    
    
    
    
}

Audio::~Audio()
{
      // 9. Завершение работы OpenAL
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
    alutExit();
}