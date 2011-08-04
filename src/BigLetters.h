#pragma once

#include "settings.h"
#include "DataHub.h"
#include "ofxPango.h"

#ifdef _USE_OFFBO
    #define FBO ofFbo
#else
    #define FBO ofxFBOTexture
#endif

class BigLetters
{
    public:
        BigLetters(DataHub &dataHub);
        void update();
        void draw();

        DataHub *dataHub;
        int impulse;
        map<char, FBO *> letters;
        FBO * curFBO;
        ofxPango pango;
        ofxPCPangoFontDescription font;

        void hilight(char letter);
        void renderChar(string s, FBO * tex);
};
