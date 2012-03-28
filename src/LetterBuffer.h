#ifndef LETTERBUFFER_H
#define LETTERBUFFER_H

#define FONT_SIZE 11 // For courier
#define FONT_W 8
#define FONT_H 17

#ifndef _USE_OFFBO
    #include "ofxFBOTexture.h"
    #define ofxFBOTexture ofFbo
#endif

#include "ofMain.h"
#include "ofxPango.h"


class LetterBuffer
{
    public:
        LetterBuffer(ofxPango *p, ofxPCPangoFontDescription* font);
        virtual ~LetterBuffer();
        ofxFBOTexture * getFbo(string letter);
        void prerender(string letter, ofxPango *p, ofxPCPangoFontDescription* font);
        void prerender(string letter);

        map<string, ofxFBOTexture *> letters;
        ofxPango *p;
        ofxPCPangoFontDescription* font;

    protected:
    private:
};

#endif // LETTERBUFFER_H
