#pragma once
#include "../utility/AssetLoader.hpp"
#include "../utility/IOHelperFunctions.hpp"
#include <SDL_image.h>

class ImageAsset : public Asset
{
public:
  ImageAsset(const char *key, const char *assetPath, SDL_Renderer *renderer)
      : Asset(key), m_assetPath(assetPath), m_renderer(renderer)
  {
  }
  ~ImageAsset() {}

  virtual bool load() override
  {
    if (!fileExists(m_assetPath))
    {
      return false;
    }
    SDL_Surface *surface;
    surface = IMG_Load(m_assetPath);

    if (!surface)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s\n", SDL_GetError());
      return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (!texture)
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s\n", SDL_GetError());
      return false;
    }
    SDL_FreeSurface(surface);

    SINGLETON(AssetLoader)->addAssetToMap<SDL_Texture>(getKey(), texture);
    return true;
  }

private:
  const char *m_assetPath;
  SDL_Renderer *m_renderer;
};