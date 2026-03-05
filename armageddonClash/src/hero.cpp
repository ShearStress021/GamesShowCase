#include "hero.hpp"


namespace game {

//    static const b2Vec2 zeroVec(0.f, 0.f);
    Hero::Hero() 

    {

        texture = LoadTexture("./data/Characters/Hero/base/Spritesheets/idle.png");
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
            position.x ,
            position.y 
        };
    }

    void Hero::draw()
    {


        Vector2 ulPosition = getUpperLeftPosition();
        


        Rectangle destRect(ulPosition.x, ulPosition.y, 
                            frameWidth * 2.f , texture.height * 2.f); 
        DrawTexturePro(texture, frameRect, destRect, Vector2{}, 0.0f, WHITE);

      //  DrawText("Here text",20,20,30,GREEN);
     //   DrawTextureRec(texture,frameRect,ulPosition,WHITE);
    }


    void Hero::update(){


        std::cout << frameIndex << '\n';
        frameDelayCounter += 1/50.f;

        if (frameDelayCounter > frameDelay)
        {
            frameDelayCounter = 0;
            ++frameIndex;
            frameIndex %= numFrames;
        }

        frameRect.x = frameIndex * frameWidth;


        //return true;

    }

    Rectangle Hero::getBoundingBox()
    {
        Vector2 ulPosition = getUpperLeftPosition();
        return Rectangle{ulPosition.x, ulPosition.y, texture.width/1.f, texture.height/1.f};
    }

}
