#include "CameraMaskViewer.h"



CameraMaskViewer::CameraMaskViewer(DataHub * h, LetterBuffer * p)
{
   dataHub = h;
//    pango = p;

    string ascii_art[] = {"#","$","O","k","=","+","|","-","^","."};

    cout << sizeof(ascii_art) << "!!!!!" << endl;

    letters = new Letter * [sizeof(ascii_art)/4];

   cout  << "ofxFBOTexture" << sizeof(letters) << endl;


    for (int i = 0; i < sizeof(ascii_art)/4; i++) {
        letters[i] = new Letter(ascii_art[i]);
        letters[i]->prerender(p);
    }



    //letters[0] = new FBO();
    //setSign("@", letters[0]);
}

void CameraMaskViewer::setSign (string s, FBO * tex) {

    ofxPCContext * context = pango->createContextWithSurface(FONT_W, FONT_H);
    context->color4f(1.0f, 1.0f, 1.0f, 0.0f);
    //context->paint();
    ofxPCPangoLayout * layout = context->createPangoLayout();

    layout->fill(0.0f,0.0f,0.0f,1.0f);
    layout->setTextColor(1.0f,1.0f,1.0f,1.0f);
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
            int res = 0;
            while ( res < 255/(sizeof(letters))) {
                if (val > 255 - (255 / (sizeof(letters))*(res+1))) {
                    break;
                }
                res++;
            }
            if (res < sizeof(letters))
                letters[res]->draw(x * FONT_W, y * FONT_H);
        }

    }


}

CameraMaskViewer::~CameraMaskViewer()
{
    //dtor
}
