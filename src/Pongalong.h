#ifndef PONGALONG_H
#define PONGALONG_H

#include "DataHub.h"

#include "settings.h"

#ifdef _USE_OFFBO
#define ofxFBOTexture ofFbo
#endif

class Pongalong
{
    public:
        Pongalong(DataHub * d, ofxPango * p);
        virtual ~Pongalong();

        void draw();
        void addFrame(string s);

        DataHub * dataHub;
        ofxPango * pango;

        ofxFBOTexture *tex;
        vector<ofxFBOTexture*> frames;

        int animationCounter;
        float lastAnimationUpdateTime;

        float x, y, dx, dy;

        float lastUpdateTime;

        void reset();

    protected:
    private:
};

#endif // PONGALONG_H
