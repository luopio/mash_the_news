#include "Letter.h"

Letter::Letter(const char let, ofTrueTypeFont &f)
{
    letter = string(1, let);
    font = &f;
    row = ofRandom(0, 10);
    col = ofRandom(0, 10);
    tex = new ofxFBOTexture();
    tex->allocate(FONT_SIZE + 3, FONT_SIZE + 3, false);
    tex->begin();
        // ofFill();
        // ofSetColor(255, 0, 0);
        // ofRect(0, 0, 100, 100);
        ofSetColor(0, 0, 255);
        font->drawString(letter, 0, FONT_SIZE);
    tex->end();
}

Letter::~Letter()
{
    //dtor
}

void Letter::draw()
{
    tex->draw(col * FONT_SIZE, row * FONT_SIZE);
}
