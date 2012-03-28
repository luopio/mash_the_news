#pragma once

#include "DataHub.h"
#include "Flow.h"
#include "AsciiBackground.h"
#include "ofxPango.h"
#include "CameraMaskViewer.h"
#include "LetterBuffer.h"

#include "settings.h"

#ifdef _USE_OFFBO
    #define FBO ofFbo
#else
    #define FBO ofxFBOTexture
#endif

class MashScreen
{
    public:
        MashScreen(DataHub &h);
        virtual ~MashScreen();

        vector<Message *> messages;
        ofTrueTypeFont font;

        Flow *flow;
        LetterBuffer *letterBuffer;

        DataHub *dataHub;
        unsigned int rows, cols;

        void setup();
        void update();
        void draw();

        void hilightWordAt(int wordIndex);
        void addMessage(string msg);
        void randomBG();

        AsciiBackground asciiBG;
        CameraMaskViewer * cmv;

        ofImage text_image;

        ofxPango* pango;
        ofxPCContext* context;
        ofxPCPangoLayout* layout;

        FBO flowFbo;
        FBO asciiBackgroundFbo;
        FBO CMVFbo;

        float lastUpdateTime;

    protected:

    private:
};
