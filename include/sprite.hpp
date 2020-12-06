#pragma once

#include <string>

#define OLC_PGEX_ANIMSPR
#include "olcPGEX_AnimatedSprite.h"
#include "olcPixelGameEngine.h"
#include "rect.hpp"

namespace Util::GameObjects
{
    class Sprite : public olc::Sprite
    {
    public:
        Sprite(
            olc::vi2d pos,
            std::string assetPath);

        bool GetIsActive()
        {
            return isActive;
        }
        void Spawn();
        void Spawn(int x, int y);
        void SetScale(int scale);
        void Kill();
        void Destroy();
        void Update();
        Geometry::Rectangle GetFrame() const;

    private:
        bool isActive = false;
        olc::vi2d position;
        olc::AnimatedSprite asset;
        std::vector<olc::vi2d> animationFrames;
        Geometry::Rectangle frame;

        std::vector<olc::vi2d> CalculateFrames(int col, int row);
    };
} // namespace Util::GameObjects