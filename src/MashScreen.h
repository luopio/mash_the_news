#pragma once

#include "DataHub.h"
#include "Flow.h"
#include "Box2dMashEngine.h"
#include "AsciiBackground.h"
#include "ofxPango.h"
#include "CameraMaskViewer.h"

class MashScreen
{
    public:
        MashScreen(DataHub &h);
        virtual ~MashScreen();

        vector<Message *> messages;
        ofTrueTypeFont font;

        Flow *flow;
        Box2dMashEngine *box2d;
        bool bFlowActive;
        bool bBox2dActive;

        DataHub *dataHub;
        unsigned int rows, cols;

        void setup();
        void update();
        void draw();

        void randomBG();

        AsciiBackground asciiBG;
        CameraMaskViewer * cmv;

        ofImage text_image;

        ofxPango* pango;
        ofxPCContext* context;
        ofxPCPangoLayout* layout;

        // ofShader shader;

    protected:

    private:
};
