#include "AsciiBackground.h"

AsciiBackground::AsciiBackground()
{
    dataHub = NULL;
    background = "";
}

AsciiBackground::~AsciiBackground()
{
    //dtor
}

void AsciiBackground::addDatahub(DataHub * d) {
    dataHub = d;
}

void AsciiBackground::setBackground(string s, ofTrueTypeFont &f) {
    background = s;
    tex = new ofFbo();
    tex->allocate(ofGetWidth(), ofGetHeight(), false);
    tex->begin();
        ofFill();
        ofSetColor(25, 0, 0);
        ofRect(0, 0, tex->getWidth(), tex->getHeight());
        ofSetColor(255, 255, 255, 128);
        f.drawString(s, 0, FONT_SIZE);
    tex->end();
}

void AsciiBackground::draw() {
    // ofSetColor(40,40,40);
    tex->draw(0,0);
    // ofSetColor(255,255,255);
}

