#ifndef BOX2DMASHENGINE_H
#define BOX2DMASHENGINE_H

#include "DataHub.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"

class LetterCircle: public ofxBox2dRect
{
    public:
        int letterInWordIndex;
        Letter *letter;
};

class Box2dMashEngine
{
    public:
        Box2dMashEngine(DataHub &h);
        virtual ~Box2dMashEngine();

        void setup();
        void update();
        void draw();
        void keyPressed(ofKeyEventArgs& args);
		void keyReleased(ofKeyEventArgs& args);

        DataHub* dataHub;
        ofxCvGrayscaleImage tempImg;

        ofxBox2d box2d;
        vector<LetterCircle> circles;
        vector<ofxBox2dJoint *> joints;

        bool bMouseForce;
        bool bJediForce;

    protected:
    private:
};

#endif // BOX2DMASHENGINE_H
