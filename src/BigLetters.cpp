#include "BigLetters.h"

BigLetters::BigLetters(DataHub &dh)
{
    dataHub = &dh;
    curFBO = NULL;
    fontSize = *(dataHub->rows) / 5 * 4;
    tFont.loadFont("DroidSansMono.ttf", fontSize, true, true);
    mFont.loadFont("Fixedsys500c.ttf", 11, true, true);

    image1.loadImage("co.png");
    image2.loadImage("arcane1.png");
    image3.loadImage("hnml-113x42.png");

    curFBO = new FBO();
    curFBO->allocate(*(dataHub->cols), *(dataHub->rows));
    maskFBO = new FBO();
    maskFBO->allocate(ofGetWidth(), ofGetHeight());
    pixels.allocate(*(dataHub->cols), *(dataHub->rows), OF_IMAGE_COLOR_ALPHA);
}


void BigLetters::hilight(char letter)
{
    impulse = 255;

    if(letter == '1') {
        renderImage(image1);
    } else if(letter == '2') {
        renderImage(image2);
    } else if(letter == '3') {
        renderImage(image3);
    } else {

        curFBO->begin();
            ofClear(0, 0, 0, 0);
            ofFill();
            ofSetColor(255, 255, 255, 255);
            tFont.drawString(ofToString(letter),
                             *(dataHub->cols) / 2 - fontSize / 2,
                             *(dataHub->rows) / 2 + fontSize / 2);
        curFBO->end();
        curFBO->readToPixels(pixels);

    }

    maskFBO->begin();
        ofClear(255, 255, 255, 10);
        int w = curFBO->getWidth();
        for(int y = 0; y < curFBO->getHeight(); y++) {
            for(int x = 0; x < curFBO->getWidth(); x++) {
                int index = (x + y * w) * 4;
                if(pixels[index] > 0) {
                    ofSetColor(0, 0, 0, 255);
                    ofRect(x * FONT_W, y * FONT_H,
                           FONT_W, FONT_H);
                    ofSetColor(pixels[index],
                               pixels[index + 1],
                               pixels[index + 2],
                               255);
                    mFont.drawString("@", x * FONT_W, y * FONT_H - 4);
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
    if(maskFBO != NULL && impulse > 0) {
        ofSetColor(dataHub->bigLetterColor.r,
                   dataHub->bigLetterColor.g,
                   dataHub->bigLetterColor.b,
                   impulse);
        maskFBO->draw(0, 0, ofGetWidth(), ofGetHeight());
    }
}


void BigLetters::renderImage(ofImage &i)
{
    curFBO->begin();
        ofClear(0, 0, 0, 0);
        ofSetColor(255, 255, 255, 255);
        i.draw(0, 0);
    curFBO->end();
    curFBO->readToPixels(pixels);
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
