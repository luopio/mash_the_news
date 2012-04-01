#include "CameraMaskViewer.h"



CameraMaskViewer::CameraMaskViewer(DataHub * h, LetterBuffer * p)
{
   dataHub = h;
//    pango = p;

    string ascii_art[] = {"#","$","O","k","=","+","|","-","^","."};

    cout << sizeof(ascii_art) << "!!!!!" << endl;
    letterSize = sizeof(ascii_art)/4;

    letters = new Letter * [letterSize];

    for (int i = 0; i < letterSize; i++) {
    //    letters[i] = new Letter(ascii_art[i]);
//        letters[i]->prerender(p);
//        dataHub->asciiArts.push_back(letters[i]);
    }

 //cout  << "ofxFBOTexture" << sizeof(letters) << endl;

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
    //ofSetColor(255, 255, 255, 255);

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
            if (res < sizeof(letters)) {
                ofColor c = dataHub->colorMap->getColor(x, y);
//                if (c.r > c.g && c.r > c.b)
//                    c.r = 255;
//                else if (c.g > c.r && c.g > c.b)
//                    c.g = 255;
//                else if (c.b > c.g && c.b > c.r)
//                    c.b = 255;
                int g = pixels[x + y * dataHub->roCoImg->width]; //(c.r + c.g + c.b)/3;
                g = g/(255/(dataHub->asciiGrayScales->size()-1));
                //cout << "GGGG " << g << " " << sizeof(letters) << " " << (int)c.r << " " << (int)c.g << " " << (int)c.b << endl;
                //letters[g]->draw(x * FONT_W, y * FONT_H, 255,255,255);//, c.r, c.g, c.b);
                //letters[g]->draw(x * FONT_W, y * FONT_H, c.r, c.g, c.b);
                dataHub->asciiGrayScales->at(g)->draw(x * FONT_W, y * FONT_H, c.r, c.g, c.b);
            }
                //letters[res]->draw(x * FONT_W, y * FONT_H,dataHub->colorMap->getPixels()[x*y+y],0,0);
        }

    }


}

CameraMaskViewer::~CameraMaskViewer()
{
    //dtor
}
