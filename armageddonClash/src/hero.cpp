#include "hero.hpp"
#include "string"


namespace game {

//    static const b2Vec2 zeroVec(0.f, 0.f);
    Hero::Hero() :
        texture(LoadTexture("data/Characters/Bridge Heroine/Heroine base/Spritesheets/idle.png"))

    {
        numFrames = 4;
        frameWidth = texture.width / numFrames;
        frameRect = Rectangle(0.0f, 0.0f, (float)frameWidth, (float)texture.height);

        frameDelay = 5;
        frameDelayCounter = 0;
        frameIndex = 0;
        

    }

    Hero::~Hero(){};

    Vector2 Hero::getUpperLeftPosition(){
        return Vector2 {
            position.x - frameWidth / 2.0f,
            position.y - texture.height
        };
    }

    void Hero::draw()
    {

        Vector2 ulPosition = getUpperLeftPosition();

        

        DrawText("Here text",ulPosition.x, ulPosition.y,30,GREEN);
        DrawTextureRec(texture,frameRect,ulPosition,WHITE);
    }

    bool Hero::update(bool onGround){
        return 0;

    }

    Rectangle Hero::getBoundingBox()
    {
        Vector2 ulPosition = getUpperLeftPosition();
        return Rectangle{ulPosition.x, ulPosition.y, texture.width/1.f, texture.height/1.f};
    }

}
