#include "CameraMaskViewer.h"

CameraMaskViewer::CameraMaskViewer(DataHub * h, ofxPango * p)
{
    dataHub = h;
    pango = p;
    tex1 = new FBO();
    tex2 = new FBO();
    tex3 = new FBO();
    setSign("@", tex1);
    setSign("*", tex2);
    setSign(".", tex3);
}

void CameraMaskViewer::setSign (string s, FBO * tex) {

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
    // tex = new FBO();
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

    unsigned char *pixels = dataHub->roCoImg->getPixels();
    ofSetColor(255, 255, 255, 255);

    for (int x = 0; x < dataHub->roCoImg->width; ++x) {
        for(int y = 0; y < dataHub->roCoImg->height; ++y) {
//            if (y == 0)
//                tex->draw(x * FONT_SIZE, y * FONT_SIZE * 2);
            unsigned int val = pixels[x + y * dataHub->roCoImg->width];
            if(val > 220) {
                tex3->draw(x * FONT_W, y * FONT_H);
            } else if(val > 150) {
                tex2->draw(x * FONT_W, y * FONT_H);
            } else if(val){
                tex1->draw(x * FONT_W, y * FONT_H);
            }
        }

    }


}

CameraMaskViewer::~CameraMaskViewer()
{
    //dtor
}
