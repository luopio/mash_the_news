#ifndef MashScreen_H
#define MashScreen_H

#include "Letter.h"
#include "MashEngine.h"
#include "FlowMashEngine.h"
#include "Box2dMashEngine.h"
#include "DataHub.h"
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

        vector<MashEngine *> engines;
        MashEngine *currentEngine;

        int hilightedMessageIndex;
        int currentEngineIndex;
        bool bJustChangedEngine;

        DataHub *dataHub;
        unsigned int rows, cols;

        void setup();
        void update();
        void draw();
        void hilightMessage(int messageIndex);
        void changeEngine();

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

#endif // MashScreen_H
