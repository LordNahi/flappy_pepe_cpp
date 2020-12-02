#pragma once

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define OLC_PGEX_ANIMSPR
#include "olcPGEX_AnimatedSprite.h"

class AssetLoader
{
public:
    static void loadAsset(std::string key, std::string path);

private:
    AssetLoader(){};
};