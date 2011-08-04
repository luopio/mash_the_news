#include "BigLetters.h"

BigLetters::BigLetters(DataHub &dh)
{
    dataHub = &dh;
    curFBO = NULL;
    fontSize = *(dataHub->rows) / 4 * 3;
    tFont.loadFont("DroidSansMono.ttf", fontSize, true, true);
    mFont.loadFont("DroidSansMono.ttf", FONT_SIZE, true, true);

    curFBO = new FBO();
    curFBO->allocate(*(dataHub->cols), *(dataHub->rows));
    maskFBO = new FBO();
    maskFBO->allocate(ofGetWidth(), ofGetHeight());
    pixels.allocate(*(dataHub->cols), *(dataHub->rows), OF_IMAGE_COLOR_ALPHA);
}


void BigLetters::hilight(char letter)
{
    impulse = 255;
    // curFBO = letters[letter];

    curFBO->begin();
        ofClear(0, 0, 0, 0);
        ofFill();
        ofSetColor(255, 255, 255, 255);
        tFont.drawString(ofToString(letter),
                         *(dataHub->cols) / 2 - fontSize,
                         *(dataHub->rows) / 2 + fontSize / 2);
    curFBO->end();
    curFBO->readToPixels(pixels);

    maskFBO->begin();
        ofClear(255, 255, 255, 60);
        int w = curFBO->getWidth();
        //int scaledFontWidth = FONT_W * (curFBO->getWidth() / (float)ofGetWidth());
        //int scaledFontHeight = FONT_H * (curFBO->getHeight() / (float)ofGetHeight());
        for(int y = 0; y < curFBO->getHeight(); y++) {
            for(int x = 0; x < curFBO->getWidth(); x++) {
                if(pixels[(x + y * w) * 4] > 0) {
                    mFont.drawString("@", x * FONT_W, y * FONT_H);
                    // ofCircle(x, y, 1);
                }
            }
        }
    maskFBO->end();

}

void BigLetters::update()
{
    if(impulse > 0)
        impulse -= 20;
}

void BigLetters::draw()
{
    if(curFBO != NULL && impulse > 0) {
        // cout << "draw big letter " << impulse << endl;
        ofSetColor(255, 255, 255, impulse);
        maskFBO->draw(0, 0, ofGetWidth(), ofGetHeight());
        // curFBO->draw(0, 0, ofGetWidth(), ofGetHeight());
    }
}


void BigLetters::renderChar(string s, FBO * tex) {
/*
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
*/
}
