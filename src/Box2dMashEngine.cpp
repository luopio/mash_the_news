#include "Box2dMashEngine.h"

Box2dMashEngine::Box2dMashEngine()
{
    //ctor
}

Box2dMashEngine::~Box2dMashEngine()
{
    //dtor
}

void Box2dMashEngine::setup(vector<Letter *> &v)
{
    box2d.init();
    box2d.setGravity(0, 1);
    // box2d.createFloor();
    box2d.createBounds();
    box2d.checkBounds(true);
    box2d.setFPS(30.0);
}

void Box2dMashEngine::update()
{
    box2d.update();
    /*
    if(bMouseForce) {
        float strength = 1.0f;
        float damping  = 0.7f;
        float minDis   = 100;
        for(int i=0; i<circles.size(); i++) {
            circles[i].addAttractionPoint(mouseX, mouseY, strength, minDis);
            circles[i].addDamping(damping, damping);
        }
    }
    */
}
