#include "AsciiBackground.h"

AsciiBackground::AsciiBackground()
{
    dataHub = NULL;
    background = "";
}

AsciiBackground::~AsciiBackground() { }

void AsciiBackground::addDatahub(DataHub * d) {
    dataHub = d;
}

void AsciiBackground::setBackground(string s, ofTrueTypeFont &f) {
    background = s;
    tex = new ofFbo();
    tex->allocate(ofGetWidth(), ofGetHeight());
    tex->begin();
        ofFill();
        // ofSetColor(25, 0, 0);
        // ofRect(0, 0, tex->getWidth(), tex->getHeight());
        ofSetColor(255, 255, 255, 255);
        f.drawString(s, 0, FONT_SIZE);
        // ofCircle(ofGetWidth() / 2, ofGetHeight() / 2, ofGetHeight());
    tex->end();
}

void AsciiBackground::draw() {
    tex->draw(0,0);
}

