#include "Pongalong.h"

Pongalong::Pongalong(DataHub * d, ofxPango * p) {
    tex = NULL;
    pango = NULL;
    dataHub = d;
    pango = p;
    addFrame("XXXXXXXX\nX@@@@@@X\nX@@@@@@X\nXXXXXXXX");
    x = ofGetWidth()-1; //ofGetWidth() / 2;
    y = ofGetHeight()-1; //ofGetHeight() / 2;

    dataHub->pongSpeed = 1.8;

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

    //layout->color4f(1.0f, 1.0f, 1.0f, 1.0f);



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

    //tex->clear();

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

       // control refresh rate
    float now = ofGetElapsedTimef();
    if(now - lastUpdateTime > 0.01) {
        lastUpdateTime = now;
        x+=dx;
        y+=dy;
    }

   // bool cd = false;

    if (x>ofGetWidth()-FONT_SIZE*8) dx = abs(dx)*-1;
    if (x < 0) dx = abs(dx);
    if (y>ofGetWidth()-FONT_SIZE*8) dy = abs(dy)*-1;
    if (y < 0) dy = abs(dy);


    unsigned char *pixels = dataHub->roCoImg->getPixels();


    for (int xx = 0; xx < 8 ; xx++) {
        if (pixels[(xx+(int)x/FONT_SIZE) + ((int)y/(FONT_SIZE*2)) * (*(dataHub->cols))]) {
            //cout << "high" << endl;
            dy = abs(dy);
        }

    }

    for (int xx = 0; xx < 8 ; xx++) {
        if (pixels[(xx+(int)x/FONT_SIZE) + ((int)y/(FONT_SIZE*2)+4) * (*(dataHub->cols))]) {
            //cout << "low" << endl;
            dy = abs(dy)*-1;
        }

    }

    for (int xx = 0; xx < 4 ; xx++) {
        if (pixels[((int)x/FONT_SIZE) + ((int)y/(FONT_SIZE*2)+xx) * (*(dataHub->cols))]) {
            //cout << "left" << endl;
            dx = abs(dx);
        }

    }

      for (int xx = 0; xx < 4 ; xx++) {
        if (pixels[(8+(int)x/FONT_SIZE) + ((int)y/(FONT_SIZE*2)+xx) * (*(dataHub->cols))]) {
           // cout << "right" << endl;
            dx = abs(dx)*-1;
        }

    }


    if (x < 0) x = 0;
    if (x > ofGetWidth()-FONT_SIZE*8) x = ofGetWidth()-FONT_SIZE*8;
    if (y < 0) y = 0;
    if (y > ofGetHeight()-FONT_SIZE*8) y = ofGetHeight()-FONT_SIZE*8;




//tex->d
}

void Pongalong::reset() {
    x = 100;
    y = 100;

}
