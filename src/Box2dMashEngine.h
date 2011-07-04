#ifndef BOX2DMASHENGINE_H
#define BOX2DMASHENGINE_H

#include "MashEngine.h"
#include "ofxBox2d.h"

class Box2dMashEngine: public MashEngine
{
    public:
        Box2dMashEngine();
        virtual ~Box2dMashEngine();

        void setup(vector<Letter *> &v);
        void update();

        vector<Letter> *letters;

        ofxBox2d box2d;
        vector<ofxBox2dCircle> circles;

    protected:
    private:
};

#endif // BOX2DMASHENGINE_H
