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
        int fontSize;
        map<char, FBO *> letters;
        FBO * curFBO;
        FBO * maskFBO;
        ofPixels pixels;
        //ofxPango pango;
        //ofxPCPangoFontDescription font;
        ofTrueTypeFont tFont;
        ofTrueTypeFont mFont;

        ofImage image1;
        ofImage image2;
        ofImage image3;

        void hilight(char letter);
        void renderChar(string s, FBO * tex);
        void renderImage(ofImage &i);
};
