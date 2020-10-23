#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <assert.h>
#include "Singleton.hpp"

//AssetInterface
class Asset
{
public:
  Asset(const char *key) : m_key(key) {}
  const char *getKey() { return m_key; }

  //returns true if load successfull, false otherwise
  virtual bool load() = 0;
  virtual ~Asset()=0;

protected:
  const char *m_key;
};
Asset::~Asset(){}

//AssetLoader with template instantiated maps to take any data type
class AssetLoader : public Singleton<AssetLoader>
{
public:
  AssetLoader()
      : m_totalAssets(0), m_assetsLoaded(0)
  {
  }

  //pass data type and key to get asset pointer
  template <typename T>
  T *findAssetByKey(const char *key)
  {
    auto &asset = getAssetMap<T>()[key];

    if (!asset)
    {
      std::cout << "Asset by the name of " << key << " not found in asset map, check type of map being used" << std::endl;
      asset = getAssetMap<T>()["default"]; // get default asset if available
    }

    return asset;
  }

  //to be called by derived asset classes load functions
  template <typename T>
  void addAssetToMap(const char *key, T *asset)
  {
    assert(asset);
    getAssetMap<T>()[key] = asset;
  }

  //this adds assets to be loaded at a later time, just for polymorphism
  void addAssetToLoadQueue(Asset *asset)
  {
    m_loadQueue.push_back(asset);
  }

  //loads all in loadqueue, blocking
  void loadAll()
  {
    for (auto &asset : m_loadQueue)
    {
      if (asset->load())
      {
        delete asset;

        m_assetsLoaded++;
      }
      else
      {
        std::cout << "Error loading asset " << asset->getKey() << std::endl;
        delete asset;
      }
    }
    m_loadQueue.clear();
  }

  //get the number of assets loaded so far, and the total number to load respectively
  std::pair<int, int> getAssetsLoaded()
  {
    std::pair<int, int> returnValue;
    returnValue.first = m_assetsLoaded;
    returnValue.second = m_totalAssets;

    return returnValue;
  }

protected:
  //templated instance creation
  template <typename T>
  std::map<const char *, T *> &getAssetMap()
  {
    static std::map<const char *, T *> instances;
    return instances;
  }

  //list of assets to load when loadAll is called
  std::vector<Asset *> m_loadQueue;
  int m_totalAssets;
  int m_assetsLoaded;
};