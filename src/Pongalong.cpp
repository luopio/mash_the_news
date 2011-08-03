#include "Pongalong.h"

Pongalong::Pongalong(DataHub * d, ofxPango * p) {
    tex = NULL;
    pango = NULL;
    dataHub = d;
    pango = p;
    addFrame("XXXXXXXX\nXXXXXXXX\nXXXXXXXX\nXXXXXXXX");
    x = ofGetWidth() / 2;
    y = ofGetHeight() / 2;

    dataHub->pongSpeed = 0.8;

    dx = dataHub->pongSpeed;
    dy = dataHub->pongSpeed;
}

Pongalong::~Pongalong()
{
    //dtor
}

void Pongalong::addFrame(string s) {
     if (pango==NULL || dataHub==NULL) return;

    ofxPCContext* context = pango->createContextWithSurface(FONT_SIZE*8, FONT_SIZE*8);
    context->color4f(1.0f, 1.0f, 1.0f, 1.0f);

    ofxPCPangoLayout* layout = context->createPangoLayout();

    layout->setText(s);
    layout->setFontDescription(*(dataHub->font));

    layout->setWidth(ofGetWidth());

    layout->show();

    ofImage text_image;
    text_image.allocate(context->getSurface()->getWidth(), context->getSurface()->getHeight(), OF_IMAGE_COLOR_ALPHA);
    text_image.setFromPixels(context->getSurface()->getPixels(), text_image.width, text_image.height, OF_IMAGE_COLOR_ALPHA, true);

    tex = new ofxFBOTexture();
    tex->allocate(text_image.width, text_image.height);
    tex->begin();
        text_image.draw(0,0);
    tex->end();
    //tex->setupScreenForMe();
}

void Pongalong::draw() {
    if (tex==NULL) return;
   // tex->

    if (dx < 0) {
        dx = (dataHub->pongSpeed)*-1;
    } else {
        dx = (dataHub->pongSpeed);
    }

    if (dy < 0) {
        dy = (dataHub->pongSpeed)*-1;
    } else {
        dy = (dataHub->pongSpeed);
    }

   ofColor c;
        c.r = 255; c.g = 255; c.b = 0;
   ofSetColor(c);
    tex->draw((((int)x)/FONT_SIZE)*FONT_SIZE,(((int)y/(FONT_SIZE*2))*FONT_SIZE*2));
    x+=dx;
    y+=dy;
   // bool cd = false;

    unsigned char *pixels = dataHub->roCoImg->getPixels();







    if (x>ofGetWidth()-FONT_SIZE*8 || x < 0)
        dx *= -1;
    if (y>ofGetHeight()-FONT_SIZE*8 || y < 0)
        dy *= -1;

//tex->d
}
