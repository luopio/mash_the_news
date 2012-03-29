#include "MashScreen.h"

MashScreen::MashScreen(DataHub &h)
{
    dataHub = &h;
    // dataHub->messages = &messages;
}

MashScreen::~MashScreen()
{
    cout << "mashscreen being destroyed" << endl;
}

void MashScreen::setup()
{
    // load the font slightly smaller to fit it completely on the FBO (adjust for font change!)
    //font.loadFont("Sans", FONT_SIZE, true, true);

    cols = ofGetWidth()  / FONT_W;
    rows = ofGetHeight() / FONT_H;
    bShowImage = false;
    dataHub->colorMapWeight = 0.0;
    dataHub->colorMapImageWeight = 0.0;

    dataHub->currentSlideIndex = 0;
    dataHub->rows = &rows;
    dataHub->cols = &cols;
    cout << "cols&rows" << cols << "," << rows << "w&h " << ofGetWidth() << "," << ofGetHeight() << endl;

    /* Pango stuff */
    pango = new ofxPango();
    dataHub->font = new ofxPCPangoFontDescription();
    //dataHub->font->createFromString("Arial Unicode MS 11");
    // dataHub->font->createFromString("Courier 11");
    // dataHub->font->createFromString("Trebuchet MS 10");
    // dataHub->font->createFromString("Bitstream Vera Sans Mono 11");
    dataHub->font->createFromString("FixedsysTTF 11");
    // dataHub->font->setWeight(PANGO_WEIGHT_ULTRAHEAVY);

    cairo_font_options_t * co = cairo_font_options_create ();
    cairo_font_options_set_antialias(co,CAIRO_ANTIALIAS_NONE);

    letterBuffer = new LetterBuffer(pango, dataHub->font);
    flow = new Flow(*dataHub);
    // box2d->setup();

    ofBackground(0, 0, 0);

    //asciiBG.addDatahub(dataHub);
    cmv = new CameraMaskViewer(dataHub, letterBuffer);
    //asciiBG.setOfxPango(pango);

    // Initialize the slideshow images
    vector<string> msgs;
    msgs.push_back("Stars, darkness, light");
    msgs.push_back("Yeah, you would think?");
    msgs.push_back("This is how fuckit");
    msgs.push_back("a phantom, a dew drop, a bubble");
    SlideShowImage * s = new SlideShowImage(msgs, "secondimage.jpg", letterBuffer, dataHub);
    slideshow.push_back(s);

    vector<string> msgs2;
    msgs2.push_back("DORKY WORKY");
    msgs2.push_back("HUMBLE DUUD");
    //s = new SlideShowImage(msgs2, "firstimage.jpg", letterBuffer, dataHub);
    //slideshow.push_back(s);
    dataHub->messages = &(s->messages);

    flow->setup();

    randomBG();
    // asciiBG.setBackground(q);
    // shader.load("shaders/noise.vert", "shaders/noise.frag");
    // cout << "binding tex0 to " << asciiBG.tex->getTextureReference().texData.textureID << endl;
    // shader.setUniform1i("tex0", fbo.getTextureReference().texData.textureID); //send which texture to the shader
    // shader.setUniformTexture("tex0", fbo, fbo.getTextureReference().texData.textureID); //send which texture to the shader

    dataHub->box2dColor             = ofColor(255, 255, 255, 0);
    dataHub->flowColor              = ofColor(255, 25,  98,  255);
    dataHub->asciiBackgroundColor   = ofColor(25,  25,  205, 0);
    dataHub->CMVColor               = ofColor(255,  0,  178, 255);

    dataHub->flowBGbrightness       = 40;

    dataHub->roCoImg = new ofxCvGrayscaleImage(); // This is kinect image scaled to row/col-space
    dataHub->roCoImg->allocate(*(dataHub->cols), *(dataHub->rows));

    dataHub->colorMap = slideshow[0]->colorMap;
    cout << "colorMap size" << dataHub->colorMap->getWidth() << "," << dataHub->colorMap->getHeight() << endl;

    flowFbo.allocate(ofGetWidth(), ofGetHeight());
    asciiBackgroundFbo.allocate(ofGetWidth(), ofGetHeight());
    CMVFbo.allocate(ofGetWidth(), ofGetHeight());

    ofEnableAlphaBlending();
}


void MashScreen::update()
{
    if(dataHub->flowColor.a) {
        flow->update();
    }

    // control refresh rate for the rest
    float now = ofGetElapsedTimef();
    if(now - lastUpdateTime < 0.15) {
        return;
    }
    lastUpdateTime = now;
}


void MashScreen::draw()
{

    ofSetColor(255, 255, 255, 255);

    /*
    if(dataHub->asciiBackgroundColor.a) {
        asciiBackgroundFbo.begin();
            ofClear(0, 0, 0, 0);
            asciiBG.draw();
        asciiBackgroundFbo.end();
        ofSetColor(dataHub->asciiBackgroundColor);
        asciiBackgroundFbo.draw(0, 0);
    }
    */

    if(dataHub->flowColor.a) {
        flowFbo.begin();
            ofSetColor(255, 255, 255, 255);
            ofClear(0, 0, 0, 0);
            flow->draw();
        flowFbo.end();
        //ofSetColor(dataHub->flowColor);
        flowFbo.draw(0, 0);
    }



    if(dataHub->colorMapImageWeight > 0.01) {
        ofSetColor(255, 255, 255, 255 * dataHub->colorMapImageWeight);
        dataHub->colorMap->draw(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(255);
    }
    if(bShowImage) {
        dataHub->colorMap->draw(0, 0, ofGetWidth(), ofGetHeight());
    }

/*
    if(dataHub->CMVColor.a) {
        CMVFbo.begin();
        ofSetColor(255, 255, 255, 255);
        ofClear(0, 0, 0, 0);
        cmv->draw();
        CMVFbo.end();
        ofSetColor(dataHub->CMVColor);
        CMVFbo.draw(0, 0);
    }
    */
}

void MashScreen::randomBG() {
    string tmps = "";

    for (int i = 0; i < rows -1; i++) {
        string tmp = "";
        for (int j = 0; j < cols; j++) {
            tmp += (rand()*1.0/RAND_MAX)*60+33;
            //tmp += "*";
        }
        tmp += "\n";
        tmps += tmp;
    }

    tmps += "ÖÄöÖÄÖÄÄÄÖ***************";

    // asciiBG.setBackground(tmps);

}

void MashScreen::hilightWordAt(int wordIndex)
{
    Message *m = NULL;
    Word *w = NULL;
    Word *wantedWord = NULL;
    int curIndex = 0;
    for(int i = 0; i < dataHub->messages->size(); i++) {
        m = (*dataHub->messages)[i];
        for(vector<Word *>::iterator wi = m->words.begin();
            wi != m->words.end(); ++wi) {
            if(curIndex == wordIndex) {
                wantedWord = *wi;
                flow->hilightFirstWord(wantedWord);
                return;
            }
            curIndex++;
        }
    }
}


void MashScreen::nextSlide()
{
    dataHub->currentSlideIndex++;
    if(dataHub->currentSlideIndex > slideshow.size() - 1) {
        dataHub->currentSlideIndex = 0;
    }
    cout << "moved to slide " << dataHub->currentSlideIndex << endl;
    dataHub->messages = &(slideshow[dataHub->currentSlideIndex]->messages);
}


SlideShowImage::SlideShowImage(vector<string> msgs, string imagePath, LetterBuffer * letterBuffer, DataHub * dataHub)
{
    string m;
    for(int i = 0; i < msgs.size(); i++) {
        m = msgs[i];
        messages.push_back( new Message(m, letterBuffer) );
    }
    image = new ofImage();
    image->loadImage(imagePath);
    colorMap = new ofImage();
    colorMap->loadImage(imagePath);
    colorMap->resize(*(dataHub->cols), *(dataHub->rows));
}
