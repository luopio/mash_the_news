#ifndef CAMERAMASKVIEWER_H
#define CAMERAMASKVIEWER_H

#include "DataHub.h"

#include "settings.h"

#ifdef _USE_OFFBO
#define ofxFBOTexture ofFbo
#endif

class CameraMaskViewer
{
    public:
        CameraMaskViewer(DataHub * h, ofxPango * p);
        virtual ~CameraMaskViewer();

        void setSign(string s);

        void draw();

        DataHub * dataHub;
        ofxPango * pango;
        ofxCvGrayscaleImage tempImg;

        ofxFBOTexture *tex;

    protected:
    private:
};

#endif // CAMERAMASKVIEWER_H
