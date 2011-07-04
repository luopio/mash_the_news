#include "Letter.h"

Letter::Letter(char let, ofTrueTypeFont &f)
{
    letter = let;
    font = &f;
    x = ofRandom(0, ofGetWidth());
    y = ofRandom(0, ofGetHeight());
}

Letter::~Letter()
{
    //dtor
}


void Letter::setup()
{

}

void Letter::update()
{
    x = ofRandom(0, ofGetWidth());
    y = ofRandom(0, ofGetHeight());
}

void Letter::draw()
{
    font->drawString("a", x, y);
}

