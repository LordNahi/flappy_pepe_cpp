#include <vector>

#include "util.hpp"
#include "sprite.hpp"
#include "rect.hpp"

using namespace Util;

namespace Util::GameObjects
{
    Sprite::Sprite(olc::vi2d pos, std::string assetPath)
    {
        position = pos;

        olc::Renderable *ren = new olc::Renderable();

        ren->Load(assetPath);

        asset.mode = olc::AnimatedSprite::SPRITE_MODE::SINGLE;
        asset.type = olc::AnimatedSprite::SPRITE_TYPE::DECAL;
        asset.spriteSheet = ren;

        const olc::vi2d assetSize = asset.GetSpriteSize();

        frame.x = pos.x;
        frame.y = pos.y;
        frame.w = assetSize.x;
        frame.h = assetSize.y;
    }

    void Sprite::SetScale(int scale)
    {
        asset.SetSpriteScale(scale);
    }

    void Sprite::Spawn()
    {
        isActive = true;
    }

    void Sprite::Spawn(int x, int y)
    {
        frame.x = x;
        frame.y = y;

        isActive = true;

        std::cout << "Sprite Spawned" << std::endl;
    };

    void Sprite::Update()
    {
        frame.x = position.x;
        frame.y = position.y;
    }

    void Sprite::Kill()
    {
        isActive = false;

        std::cout << "Sprite Spawned" << std::endl;
    }

    void Sprite::Destroy()
    {
        delete asset.spriteSheet;
    }

    Geometry::Rectangle Sprite::GetFrame() const
    {
        return frame;
    }

    std::vector<olc::vi2d> Sprite::CalculateFrames(int col, int row)
    {
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < row; j++)
            {
                animationFrames.push_back({frame.w * i, frame.h * j});
            }
        }
    }
} // namespace Util::GameObjects
