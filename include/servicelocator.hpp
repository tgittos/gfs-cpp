#ifndef SERVICE_LOCATOR_H
#define SERVICE_LOCATOR_H

#include "IAudioProvider.hpp"

class ServiceLocator
{
public:
  static IAudioProvider* GetAudio() { return _audioProvider; } const

  static void RegisterAudioService(IAudioProvider *provider)
  {
    _audioProvider = provider;
  }

private:
  static IAudioProvider* _audioProvider;
};

#endif
