#ifndef SOUND_FILE_CACHE_H
#define SOUND_FILE_CACHE_H

#include <string>
#include <map>
#include <stdexcept>
#include "SFML/Audio.hpp"

class SoundFileCache
{
public:
  SoundFileCache(void);
  ~SoundFileCache(void);

  sf::Sound GetSound(std::string) const;
  sf::Music* GetSong(std::string) const;

private:
  static std::map<std::string, sf::SoundBuffer*> _sounds;
  static std::map<std::string, sf::Music*> _music;

  template <typename T>
  struct Deallocator
  {
    void operator()(const std::pair<std::string, T> &p)
    {
      delete p.second;
    }
  };
};

class SoundNotFoundException : public std::runtime_error
{
public:
  SoundNotFoundException(std::string const& msg):
    std::runtime_error(msg)
  {}
};

#endif
