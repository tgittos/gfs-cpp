#include "gameobjectmanager.hpp"
GameObjectManager::GameObjectManager()
{
}
GameObjectManager::~GameObjectManager()
{
  std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}
void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
  _gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}
VisibleGameObject* GameObjectManager::Get(std::string name) const
{
  std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
  if(_gameObjects.end() == results)
  {
    return NULL;
  }
  return results->second;
}
void GameObjectManager::Remove(std::string name)
{
  std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
  if(_gameObjects.end() != results)
  {
    delete results->second;
    _gameObjects.erase(results);
  }
}
int GameObjectManager::GetObjectCount() const
{
  return _gameObjects.size();
}
void GameObjectManager::DrawAll(sf::RenderWindow& window)
{
  std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
  while(_gameObjects.end() != itr)
  {
    itr->second->Draw(window);
    itr++;
  }
}
