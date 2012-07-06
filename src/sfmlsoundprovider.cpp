#include "SFMLSoundProvider.hpp"
#include "SoundFileCache.hpp"

SFMLSoundProvider::SFMLSoundProvider() :
  _currentSongName("")
{
}

void SFMLSoundProvider::PlaySound(std::string filename)
{
  int availChannel = -1;
  for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
  {
    if(_currentSounds[i].GetStatus() != sf::Sound::Playing)
    {
      availChannel = i;
    }
  }

  if (availChannel != -1)
  {
    try
    {
      _currentSounds[availChannel] = _soundFileCache.GetSound(filename);
      _currentSounds[availChannel].Play();
    }
    catch(SoundNotFoundException& err)
    {
      // swallow the error for now
    }
  }
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
  sf::Music *currentSong;
  try
  {
    currentSong = _soundFileCache.GetSong(filename);
  }
  catch (SoundNotFoundException&)
  {
    // swallow the error and do nothing
    return;
  }
  if("" != _currentSongName)
  {
    try
    {
      sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
      if(sf::Sound::Stopped != priorSong->GetStatus())
      {
        priorSong->Stop();
      }
    }
    catch(SoundNotFoundException&)
    {
      //swallow the error and do nothing
    }
  }
  _currentSongName = filename;
  currentSong->SetLoop(looping);
  currentSong->Play();
}

void SFMLSoundProvider::StopAllSounds()
{
  for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
  {
    _currentSounds[i].Stop();
  }

  if("" != _currentSongName)
  {
    try
    {
      sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
      if(sf::Sound::Stopped != priorSong->GetStatus())
      {
        priorSong->Stop();
      }
    }
    catch(SoundNotFoundException&)
    {
      //swallow the error and do nothing
    }
  }
}

bool SFMLSoundProvider::IsSoundPlaying()
{
  for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
  {
    if(sf::Sound::Playing == _currentSounds[i].GetStatus())
    {
      return true;
    }
  }
  return false;
}

bool SFMLSoundProvider::IsSongPlaying()
{
  if("" != _currentSongName)
  {
    return sf::Music::Playing == _soundFileCache.GetSong(_currentSongName)->GetStatus();
  }
  return false;
}
