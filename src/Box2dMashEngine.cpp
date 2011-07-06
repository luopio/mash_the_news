#include "Box2dMashEngine.h"

Box2dMashEngine::Box2dMashEngine(DataHub &h)
{
    dataHub = &h;
}

Box2dMashEngine::~Box2dMashEngine()
{
    //dtor
}

void Box2dMashEngine::setup()
{

    box2d.init();
    box2d.setGravity(0, 1);
    // box2d.createFloor();
    box2d.createBounds();
    box2d.checkBounds(true);
    box2d.setFPS(30.0);

    for(int i = 0; i < ofGetWidth(); i+=20) {
        ofxBox2dCircle circle;
        circle.setPhysics(1.5, 0.53, 0.1);
        circle.setup(box2d.getWorld(), i, 10, ofRandom(5, 15));
        circles.push_back(circle);
    }

    bDebug = true;
    bMouseForce = true;

}

void Box2dMashEngine::update()
{
    box2d.update();


    if(bMouseForce) {
        float strength = 1.0f;
        float damping  = 0.7f;
        float minDis   = 100;
        for(int i=0; i<circles.size(); i++) {
            circles[i].addAttractionPoint(ofPoint(*(dataHub->mouseX), *(dataHub->mouseY)), strength, minDis);
            circles[i].addDamping(damping, damping);
        }
    }
}

void Box2dMashEngine::draw()
{
    if(bDebug) {
        for(int i=0; i<circles.size(); i++) {
            circles[i].draw();
        }
        // ofDrawBitmapString(10, ofGetHeight() - 100, "")
    }
}
