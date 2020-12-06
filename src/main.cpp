#include <vector>

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#define OLC_PGEX_ANIMSPR
#include "olcPGEX_AnimatedSprite.h"
#include "pipe.hpp"
#include "later.hpp"
#include "rect.hpp"

// OLC ScreenWidth()/ScreenHeight() is fucked ...
int screenWidth = 140;
int screenHeight = 240;

// Override base class with your custom functionality ...
class Game : public olc::PixelGameEngine
{
public:
    bool hasGameStarted = false;
    bool hasPressedJump = false;
    float gameScale = 0.5f;

    // Timing ...
    int targetFps = 60;
    float fAccumulatedTime = 0.0f;
    float fTargetFrameTime = 1.0f / targetFps;
    int elapsedFrames = 0;
    int elapsedSeconds = elapsedFrames % targetFps;

    // Pipes ...
    std::vector<Pipe> pipes;
    int pipeGap = 50;
    int pipesOnScreen = 0;
    int pipeSpawnDelay = 2;

    // Game Variables ...
    float fallSpeed = 0.0f;
    float fallSpeedMax = 7.0f;
    float gravity = 0.25f;
    float jumpGain = 4.0f;

    olc::AnimatedSprite sprPepe;
    olc::Decal *decPipe;
    olc::vi2d pepePos = {screenWidth / 2 - 8, screenHeight / 2};

    int backgroundLayer;
    int gameLayer;
    int guiLayer;

    Game()
    {
        // Name you application ...
        sAppName = "Experimentation";
    }

    std::vector<olc::vi2d> CalcFrames(int width, int height, int col, int row = 1)
    {
        std::vector<olc::vi2d> frames;

        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < row; j++)
            {
                frames.push_back({width * i, height * j});
            }
        }

        return frames;
    }

    bool OnUserCreate() override
    {
        // Load Assets ...
        olc::Sprite *sprBackground = new olc::Sprite("./assets/background.png");

        olc::Renderable *spritesheet = new olc::Renderable();
        spritesheet->Load("./assets/pepe.png");

        olc::Sprite *sprPipe = new olc::Sprite("./assets/pipe.png");
        decPipe = new olc::Decal(sprPipe);

        // Prep Pepe sprite ...
        sprPepe.mode = olc::AnimatedSprite::SPRITE_MODE::SINGLE;
        sprPepe.type = olc::AnimatedSprite::SPRITE_TYPE::DECAL;
        sprPepe.spriteSheet = spritesheet;
        sprPepe.SetSpriteSize({32, 32});
        sprPepe.SetSpriteScale(gameScale);

        std::vector<olc::vi2d> frames = CalcFrames(sprPepe.GetSpriteSize().x, sprPepe.GetSpriteSize().y, 6);

        sprPepe.AddState("flap", frames);
        sprPepe.SetState("flap");

        // Prep pipes ...
        int numPipes = 5;
        int screenMinY = screenHeight * 0.2f;
        int screenMaxY = screenHeight * 0.8f;

        for (int i = 0; i < numPipes; i++)
        {
            const int frameW = sprPipe->width * gameScale;
            const int frameH = sprPipe->height * gameScale;
            const Geometry::Rectangle frame = {0, 0, frameW, frameH};
            Pipe p{frame, screenMinY, screenMaxY, screenWidth, 1};
            pipes.push_back(p);
        }

        // Create Layers ...
        backgroundLayer = CreateLayer();
        gameLayer = CreateLayer();

        // Draw background ...
        olc::vi2d backgroundVec = {0, 0};
        SetDrawTarget(backgroundLayer);
        DrawSprite(backgroundVec, sprBackground, 1);
        EnableLayer(backgroundLayer, true);
        SetDrawTarget(nullptr);

        // This prevents the game from starting ...
        // later pipe_spawner(2000, false, &spawnPipe);

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLANK);

        /**
         * TODO: Is there a way for me to pause the game loop
         * after I finish rendering a frame? ...
         */

        // Draw pepe ...
        sprPepe.Draw(fElapsedTime, pepePos);

        for (auto &pipe : pipes)
        {
            if (pipe.GetIsActive())
            {
                DrawDecal({pipe.position.x, pipe.position.y + pipeGap / 2}, decPipe, {gameScale, gameScale});
                DrawDecal({pipe.position.x, pipe.position.y - pipeGap / 2}, decPipe, {gameScale, -gameScale});
            }
        }

        if (GetKey(olc::Key::SPACE).bPressed)
        {
            hasGameStarted = true;
            hasPressedJump = true;
        }

        fAccumulatedTime += fElapsedTime;
        if (fAccumulatedTime >= fTargetFrameTime)
        {
            fAccumulatedTime -= fTargetFrameTime;
            fElapsedTime = fTargetFrameTime;
        }
        else
            return true; // Don't do anything this frame

        // Frame limited action ...
        elapsedFrames++;
        if (elapsedFrames % targetFps == 0)
        {
            incrementSecond();
        }

        // Move entities and do collisions here ...
        if (hasGameStarted)
        {
            // Create pipe if needed ...
            for (auto &pipe : pipes)
            {
                if (pipe.GetIsActive())
                {
                    pipe.Update();
                }
            }

            if (fallSpeed < fallSpeedMax)
                fallSpeed += gravity;

            pepePos.y += fallSpeed;

            if (hasPressedJump)
            {
                fallSpeed = -jumpGain;
                hasPressedJump = false;
            }
        }

        return true;
    }

    void spawnPipe()
    {
        for (auto &pipe : pipes)
        {
            if (!pipe.GetIsActive())
            {
                pipe.Spawn();
                break;
            }
        }
    }

    void incrementSecond()
    {
        elapsedSeconds++;

        if (hasGameStarted & elapsedSeconds % pipeSpawnDelay == 0)
        {
            spawnPipe();
        }
    }
};

int main()
{
    Game game;
    if (game.Construct(screenWidth, screenHeight, 4, 4))
        game.Start();
    return 0;
}