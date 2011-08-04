#pragma once

#include "DataHub.h"
#include "Flow.h"
#include "Box2dMashEngine.h"
#include "AsciiBackground.h"
#include "ofxPango.h"
#include "CameraMaskViewer.h"
#include "Pongalong.h"

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
        Box2dMashEngine *box2d;

        DataHub *dataHub;
        unsigned int rows, cols;

        void setup();
        void update();
        void draw();

        void hilightWordAt(int wordIndex);
        void addMessage(string msg);
        void freezeFrame();
        void randomBG();

        AsciiBackground asciiBG;
        CameraMaskViewer * cmv;
        Pongalong * pong;

        ofImage text_image;

        ofxPango* pango;
        ofxPCContext* context;
        ofxPCPangoLayout* layout;

        FBO flowFbo;
        FBO box2dFbo;
        FBO pongFbo;
        FBO asciiBackgroundFbo;
        FBO CMVFbo;

        vector<FBO *> freezes;
        vector<int> freezeOpacities;
        int curFreezeFrame;
        // ofShader shader;
        float lastUpdateTime;

    protected:

    private:
};
