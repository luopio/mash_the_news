#ifndef LETTER_H
#define LETTER_H

#define FONT_SIZE 14

#include "ofMain.h"
#include "ofxFBOTexture.h"

class Letter
{
    public:
        Letter(const char letter, ofTrueTypeFont &of);
        virtual ~Letter();

        void draw();

        string letter;
        ofxFBOTexture *tex;
        ofTrueTypeFont *font;
        int row, col;

    protected:
    private:
};

#endif // LETTER_H
