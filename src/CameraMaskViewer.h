#ifndef CAMERAMASKVIEWER_H
#define CAMERAMASKVIEWER_H

#include "DataHub.h"

#include "settings.h"

#ifdef _USE_OFFBO
    #define FBO ofxFbo
#else
    #include "ofxFBOTexture.h"
    #define FBO ofxFBOTexture
#endif

class CameraMaskViewer
{
    public:
        CameraMaskViewer(DataHub * h, ofxPango * p);
        virtual ~CameraMaskViewer();

        void draw();

        DataHub * dataHub;
        ofxPango * pango;

        FBO *tex1;
        FBO *tex2;
        FBO *tex3;

    protected:
        void setSign(string s, FBO * tex);
    private:
};

#endif // CAMERAMASKVIEWER_H
