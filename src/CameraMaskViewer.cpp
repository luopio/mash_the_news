#include "CameraMaskViewer.h"

#include "settings.h"

#ifdef _USE_OFFBO
#define ofxFBOTexture ofFbo
#endif

CameraMaskViewer::CameraMaskViewer(DataHub * h, ofxPango * p)
{
    tex = NULL;

    dataHub = h;
    pango = p;

    tempImg.allocate(*(dataHub->cols), *(dataHub->rows));
}

void CameraMaskViewer::setSign (string s) {

    ofxPCContext * context = pango->createContextWithSurface(FONT_W, FONT_H);
    context->color4f(1.0f, 1.0f, 1.0f, 0.0f);
    //context->paint();
    ofxPCPangoLayout * layout = context->createPangoLayout();

    layout->fill(0.0f,0.0f,0.0f,1.0f);
    layout->setTextColor(1.0f,1.0,1.0f,1.0f);
    layout->setFontDescription(*(dataHub->font));
    layout->setText(s);

    // layout->setWidth(ofGetWidth());

    //layout->show

    //layout->setJustify(true);
    //context->color4f(1.0f, 1.0f, 1.0f, 1.0f);

    layout->show();

    //ofFill();
    ofImage text_image;
    //text_image.clear();
    text_image.allocate(context->getSurface()->getWidth(), context->getSurface()->getHeight(), OF_IMAGE_COLOR_ALPHA);
    text_image.setFromPixels(context->getSurface()->getPixels(), text_image.width, text_image.height, OF_IMAGE_COLOR_ALPHA, true);

    //tex = new ofFbo();
    tex = new ofxFBOTexture();
    //tex->allocate(font->stringWidth(letter), font->getLineHeight());
    tex->allocate(FONT_W, FONT_H);
    tex->begin();
        //ofFill();
        //ofSetColor(0, 0, 0);
        //ofRect(0, 0, tex->getWidth(), tex->getHeight());
        //ofSetColor(255, 255, 255);
        text_image.draw(0,0);
//        font->drawString(letter, 0, FONT_SIZE);
    tex->end();

}

void CameraMaskViewer::draw() {
    if (tex==NULL) return;

   // tempImg.scaleIntoMe(*(dataHub->grayDiff));
    unsigned char *pixels = dataHub->roCoImg->getPixels();

    for (int x = 0; x < tempImg.width; ++x) {
        for(int y = 0; y < tempImg.height; ++y) {
//            if (y == 0)
//                tex->draw(x * FONT_SIZE, y * FONT_SIZE * 2);
            if(pixels[x + y * tempImg.width]) {
                tex->draw(x * FONT_W, y * FONT_H);
            }
        }

    }


}

CameraMaskViewer::~CameraMaskViewer()
{
    //dtor
}
