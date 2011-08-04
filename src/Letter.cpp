#include "Letter.h"

#include "settings.h"
#ifdef _USE_OFFBO
#define ofxFBOTexture ofFbo
#endif

using namespace Poco;

Letter::Letter(string let)
{
    letter = let;
    col = 0;
    row = 0;
    //cout << let << ",";
}


void Letter::prerender(ofxPango *p, ofxPCPangoFontDescription* font)
{
    ofSetColor(255, 255, 255, 255);
    ofxPCContext * context = p->createContextWithSurface(FONT_W, FONT_H);

    context->color4f(1.0f, 0.0f, 0.0f, 1.0f);
    ofxPCPangoLayout* layout = context->createPangoLayout();
    layout = context->createPangoLayout();
    layout->fill(0.0f,0.0f,0.0f,1.0f);
    layout->setTextColor(1.0f,1.0,1.0f,1.0f);
    layout->setFontDescription(*font);
    layout->setText(letter);
    layout->show();

    /* Hopefully this will be useless step. It has to be!!! */
    ofImage text_image;
    text_image.allocate(context->getSurface()->getWidth(), context->getSurface()->getHeight(), OF_IMAGE_COLOR_ALPHA);
    text_image.setFromPixels(context->getSurface()->getPixels(), text_image.width, text_image.height, OF_IMAGE_COLOR_ALPHA, true);

    //tex = new ofFbo();
    tex = new ofxFBOTexture();
    //tex->allocate(font->stringWidth(letter), font->getLineHeight());
    tex->allocate(FONT_W, FONT_H);
    tex->begin();
        text_image.draw(0,0);
    tex->end();
}

void Letter::prerender(ofTrueTypeFont * font)
{
    tex = new ofxFBOTexture();
    tex->allocate(FONT_W, FONT_H);
    tex->begin();
        font->drawString(letter, 0,0);
    tex->end();
}

Letter::~Letter()
{
    //dtor
}

void Letter::draw()
{
    draw(col * FONT_W, row * FONT_H);
}

void Letter::draw(int x, int y)
{
    tex->draw(x, y);
}
