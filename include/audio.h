#include"graphics.h"
#include"alut.h"
#include"efx.h"
#include"alext.h"
#include"efx-creative.h"
#include"EFX-Util.h"
#include"efx-creative.h"
#include"efx-presets.h"
class Sound
{
public:
    Sound();
    ~Sound();
    void play();
    void set(std::string path);
private:
    ALuint source;
    ALuint buffer;
};

class Audio
{
public:
    Audio();
    ~Audio();
    //void set();
private:
    ALCdevice* device;
    ALCcontext* context;
};