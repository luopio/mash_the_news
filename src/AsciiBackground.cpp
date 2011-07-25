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
    tex = new ofxFBOTexture();
    tex->allocate(ofGetWidth()+300, ofGetHeight()+300, false);
    tex->begin();
        // ofFill();
        // ofSetColor(255, 0, 0);
        // ofRect(0, 0, 100, 100);
        ofSetColor(255, 255, 255);
        f.drawString(s, 0, FONT_SIZE);
        //ofRect(0,0,ofGetWidth(), ofGetHeight());
    tex->end();
}

void AsciiBackground::draw() {
    tex->draw(0,0);
}

