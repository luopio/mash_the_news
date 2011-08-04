#include "BigLetters.h"

BigLetters::BigLetters(DataHub &dh)
{
    string chars = "abcdefghijklmnopqrstuvwxyz";

    // font.createFromString("FixedsysTTF 300");
    // font.createFromString("Arial 300");

    /*for(int i = 0; i < chars.size(); i++) {
        FBO * f = new FBO();
        renderChar(ofToString(chars[i]), f);
        letters[chars[i]] = f;
        cout << "created big letter " << chars[i] << endl;
    }*/

    dataHub = &dh;
    curFBO = NULL;
}


void BigLetters::hilight(char letter)
{
    impulse = 300;
    // curFBO = letters[letter];

    ofTrueTypeFont f;
    f.loadFont("DroidSansMono.ttf", 24, true, true);
    curFBO = new FBO();
    curFBO->allocate(*(dataHub->cols), *(dataHub->rows));
    curFBO->begin();
        ofClear(0, 0, 0, 0);
        ofFill();
        ofSetColor(255, 0, 255, 255);
        //text_image.draw(0,0);
        f.drawString("A", *(dataHub->cols) / 2, 24); // ofToString(letters[letter]), 0, 0);
    curFBO->end();

}

void BigLetters::update()
{
    if(impulse > 0)
        impulse -= 10;
}

void BigLetters::draw()
{
    if(curFBO != NULL && impulse > 0) {
        cout << "draw big letter " << impulse << endl;
        ofSetColor(255, 0, 255, impulse);
        curFBO->draw(0, 0, ofGetWidth(), ofGetHeight());
    }
}


void BigLetters::renderChar(string s, FBO * tex) {

    ofxPCContext * context = pango.createContextWithSurface( *(dataHub->cols), *(dataHub->rows) );
    context->color4f(1.0f, 1.0f, 1.0f, 0.0f);
    //context->paint();
    ofxPCPangoLayout * layout = context->createPangoLayout();

    layout->fill(0.0f, 0.0f, 0.0f, 1.0f);
    layout->setTextColor(1.0f, 1.0f, 1.0f, 1.0f);
    layout->setFontDescription(font);
    layout->setText(s);

    layout->show();

    ofImage text_image;
    text_image.allocate(context->getSurface()->getWidth(), context->getSurface()->getHeight(), OF_IMAGE_COLOR_ALPHA);
    text_image.setFromPixels(context->getSurface()->getPixels(), text_image.width, text_image.height, OF_IMAGE_COLOR_ALPHA, true);

    // tex->allocate( *(dataHub->cols), *(dataHub->rows) );
    tex->allocate(ofGetWidth(), ofGetHeight());
    ofEnableAlphaBlending();
    ofTrueTypeFont f;
    f.loadFont("Sans", 300, true, true);
    tex->begin();
        ofClear(0, 0, 0, 0);
        ofSetColor(255, 0, 255, 255);
        //text_image.draw(0,0);
        //ofCircle(0, 0, *(dataHub->rows) );
        f.drawString(s, 0, 0);
    tex->end();
}
