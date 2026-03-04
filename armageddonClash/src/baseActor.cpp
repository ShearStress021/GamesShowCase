#include "baseActor.hpp"


namespace game 
{

    BaseActor::BaseActor(){}

    BaseActor::~BaseActor(){}


    bool BaseActor::update(bool onGround)
    {
        return true;
    }


    void BaseActor::draw()
    {
        DrawText("Base Actor",0,0,40,RED);
    }

    Rectangle BaseActor::getBoundingBox()
    {
        return Rectangle(position.x, position.y);
    }


     

}


