#ifndef BOX2DMASHENGINE_H
#define BOX2DMASHENGINE_H

#include "MashEngine.h"
#include "ofxBox2d.h"

class Box2dMashEngine: public MashEngine
{
    public:
        Box2dMashEngine(DataHub &h);
        virtual ~Box2dMashEngine();

        void setup();
        void update();
        void draw();

        DataHub* dataHub;

        ofxBox2d box2d;
        vector<ofxBox2dCircle> circles;

        bool bDebug;
        bool bMouseForce;

    protected:
    private:
};

#endif // BOX2DMASHENGINE_H
