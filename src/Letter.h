#ifndef LETTER_H
#define LETTER_H

#define FONT_SIZE 11
#define FONT_W 9
#define FONT_H 18

#include "ofMain.h"
#include "Poco/StringTokenizer.h"

#include "settings.h"
#ifndef _USE_OFFBO
    #include "ofxFBOTexture.h"
#endif

#include "ofxPango.h"

#include "settings.h"

#ifdef _USE_OFFBO
    #define ofxFBOTexture ofFbo
#endif

#include "Poco/UTF8Encoding.h"
#include "Poco/TextIterator.h"

using Poco::StringTokenizer;

class Letter
{
    public:
        Letter(string letter);
        virtual ~Letter();

        void prerender(ofxPango * p, ofxPCPangoFontDescription* font);
        void prerender(ofTrueTypeFont *font);
        void draw();
        void draw(int x, int y);

        string letter;

        ofxFBOTexture *tex;

        ofTrueTypeFont *font;
        ofColor color;
        int row, col;

    protected:
    private:
};

#endif // LETTER_H
