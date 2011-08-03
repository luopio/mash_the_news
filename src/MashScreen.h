#pragma once

#include "DataHub.h"
#include "Flow.h"
#include "Box2dMashEngine.h"
#include "AsciiBackground.h"
#include "ofxPango.h"
#include "CameraMaskViewer.h"
#include "Pongalong.h"

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
        void randomBG();

        AsciiBackground asciiBG;
        CameraMaskViewer * cmv;
        Pongalong * pong;

        ofImage text_image;

        ofxPango* pango;
        ofxPCContext* context;
        ofxPCPangoLayout* layout;

        ofFbo flowFbo;
        ofFbo box2dFbo;
        ofFbo pongFbo;
        ofFbo asciiBackgroundFbo;

        // ofShader shader;

    protected:

    private:
};
