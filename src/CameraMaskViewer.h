#ifndef CAMERAMASKVIEWER_H
#define CAMERAMASKVIEWER_H

#include "DataHub.h"

#include "settings.h"

#include "Letter.h"

#ifdef _USE_OFFBO
    #define FBO ofFbo
#else
    #include "ofxFBOTexture.h"
    #define FBO ofxFBOTexture
#endif

class CameraMaskViewer
{
    public:
        CameraMaskViewer(DataHub * h, LetterBuffer * p);
        virtual ~CameraMaskViewer();

        void draw();

        DataHub * dataHub;
        ofxPango * pango;

        Letter ** letters;

    protected:
        void setSign(string s, ofxFBOTexture * tex);
    private:
};

#endif // CAMERAMASKVIEWER_H
