#include "soundfilecache.hpp"

SoundFileCache::SoundFileCache(void)
{
}

SoundFileCache::~SoundFileCache(void)
{
  std::for_each(_sounds.begin(), _sounds.end(), Deallocator<sf::SoundBuffer*>());
  std::for_each(_music.begin(), _music.end(), Deallocator<sf::Music*>());
}

sf::Sound SoundFileCache::GetSound(std::string soundName) const
{
  std::map<std::string, sf::SoundBuffer*>::iterator itr = _sounds.find(soundName);
  if(_sounds.end() == itr)
  {
    sf::SoundBuffer *soundBuffer = new sf::SoundBuffer();
    if(!soundBuffer->LoadFromFile(soundName))
    {
      delete soundBuffer;
      throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache::GetSound");
    }
    
    std::map<std::string, sf::SoundBuffer*>::iterator result = _sounds.insert(std::pair<std::string, sf::SoundBuffer*>(soundName, soundBuffer)).first;
    
    sf::Sound sound;
    sound.SetBuffer(*result->second);
    return sound;
  }
  else
  {
    sf::Sound sound;
    sound.SetBuffer(*itr->second);
    return sound;
  }

  throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache::GetSound");
}

sf::Music* SoundFileCache::GetSong(std::string soundName) const
{
  std::map<std::string, sf::Music*>::iterator itr = _music.find(soundName);
  if(_music.end() == itr)
  {
    sf::Music *song = new sf::Music();
    if(!song->OpenFromFile(soundName))
    {
      delete song;
      throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache::GetSong");
    }
    else
    {
      std::map<std::string, sf::Music*>::iterator result = _music.insert(std::pair<std::string, sf::Music*>(soundName, song)).first;
      return result->second;
    }
  }
  else
  {
    return itr->second;
  }

  throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache::GetSong");
}

std::map<std::string, sf::SoundBuffer*> SoundFileCache::_sounds;
std::map<std::string, sf::Music*> SoundFileCache::_music;
