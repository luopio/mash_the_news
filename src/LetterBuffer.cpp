#include "LetterBuffer.h"

LetterBuffer::LetterBuffer(ofxPango *p, ofxPCPangoFontDescription* font)
{
    this->p = p;
    this->font = font;
}

LetterBuffer::~LetterBuffer()
{
    //dtor
}

ofxFBOTexture* LetterBuffer::getFbo(string letter)
{
    map<string, ofxFBOTexture *>::iterator iter = letters.begin();
    iter = letters.find(letter);
    if( iter == letters.end() ) {
        cout << "Letter " << letter << " not mapped. Creating.." << '\n';
        prerender(letter);
    }
    cout << "Now have " << letters.size() << " letters" << endl;
    return letters[letter];

}

void LetterBuffer::prerender(string letter)
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

    ofxFBOTexture * tex = new ofxFBOTexture();
    tex->allocate(FONT_W, FONT_H);
    tex->begin();
        text_image.draw(0,0);
    tex->end();
    letters[letter] = tex;
}
