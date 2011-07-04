#ifndef LETTER_H
#define LETTER_H

#include "ofMain.h"

class Letter
{
    public:
        Letter(char letter, ofTrueTypeFont &of);
        virtual ~Letter();

        char letter;
        ofTrueTypeFont *font;
        float x, y;

        void update();
        void setup();
        void draw();

    protected:
    private:
};

#endif // LETTER_H
