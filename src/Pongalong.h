#ifndef PONGALONG_H
#define PONGALONG_H

#include "DataHub.h"

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

        float x, y, dx, dy;

        float lastUpdateTime;

    protected:
    private:
};

#endif // PONGALONG_H
