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
        FBO * maskPingPongFBO;
        ofPixels pixels;
        //ofxPango pango;
        //ofxPCPangoFontDescription font;
        ofTrueTypeFont tFont;
        ofTrueTypeFont mFont;
        bool startAgain;
        int drawOffset;

        ofImage image1;
        ofImage image2;
        ofImage image3;
        ofImage image4;
        ofImage image5;
        ofImage image6;
        ofImage image7;
        ofImage image8;
        ofImage image9;
        ofImage image10;
        ofImage image11;

        void hilight(char letter);
        void renderChar(string s, FBO * tex);
        void renderImage(ofImage &i);
};
