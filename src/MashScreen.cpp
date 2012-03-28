#include "MashScreen.h"

MashScreen::MashScreen(DataHub &h)
{
    dataHub = &h;
    dataHub->messages = &messages;
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
    //cmv = new CameraMaskViewer(dataHub, pango);
    //asciiBG.setOfxPango(pango);

    // asciiBG.setupFBO(context, layout);

    /*
    messages.push_back( new Message(string("100 DANCERS"), pango, dataHub->font));
    messages.push_back( new Message(string("Stars, darkness, light,"), pango, dataHub->font));
    messages.push_back( new Message(string("a phantom,a dew drop,a bubble"), pango, dataHub->font));
    messages.push_back( new Message(string("a dream, lightning flash, a cloud"), pango, dataHub->font));
    messages.push_back( new Message(string("This is how all compound things should be seen."), pango, dataHub->font));
    messages.push_back( new Message(string("100 % pure magic power"), pango, dataHub->font));
    messages.push_back( new Message(string("Falling, spiraling, transformation, surfing the skin"), pango, dataHub->font));
    messages.push_back( new Message(string("Have you seen a dancing tree?"), pango, dataHub->font));
    messages.push_back( new Message(string("Zebra on the fast lane. Coughing up purple haze."), pango, dataHub->font));
    messages.push_back( new Message(string("We are the children of the sun, project of love and surrender"), pango, dataHub->font));
    messages.push_back( new Message(string("The rose smelled like raspberries."), pango, dataHub->font));
    messages.push_back( new Message(string("Invisible dance and fire ball."), pango, dataHub->font));
    messages.push_back( new Message(string("Who are we together, where, whatś happening..?"), pango, dataHub->font));
    messages.push_back( new Message(string("Mind is a muscle, grass in the wind"), pango, dataHub->font));
    messages.push_back( new Message(string("Just visiting planet Earth"), pango, dataHub->font));
    */

    messages.push_back( new Message(string("100 DANCERS"), letterBuffer));
    messages.push_back( new Message(string("Stars, darkness, light,"), letterBuffer));
    messages.push_back( new Message(string("a phantom,a dew drop,a bubble"), letterBuffer));
    messages.push_back( new Message(string("a dream, lightning flash, a cloud"), letterBuffer));
    messages.push_back( new Message(string("This is how all compound things should be seen."), letterBuffer));
    messages.push_back( new Message(string("100 % pure magic power"), letterBuffer));
    messages.push_back( new Message(string("Falling, spiraling, transformation, surfing the skin"), letterBuffer));
    messages.push_back( new Message(string("Have you seen a dancing tree?"), letterBuffer));
    messages.push_back( new Message(string("Zebra on the fast lane. Coughing up purple haze."), letterBuffer));

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
    dataHub->CMVColor               = ofColor(255,  0,  178, 0);

    dataHub->flowBGbrightness       = 40;

    dataHub->roCoImg = new ofxCvGrayscaleImage(); // This is kinect image scaled to row/col-space
    dataHub->roCoImg->allocate(*(dataHub->cols), *(dataHub->rows));

    dataHub->colorMap = new ofImage();
    dataHub->colorMap->loadImage("secondimage.jpg");
    dataHub->colorMap->resize(*dataHub->cols, *dataHub->rows);
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
    if(dataHub->colorMapImageWeight > 0.01) {
        ofSetColor(255, 255, 255, 255 * dataHub->colorMapImageWeight);
        dataHub->colorMap->draw(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(255);
    }
    if(bShowImage) {
        dataHub->colorMap->draw(0, 0, ofGetWidth(), ofGetHeight());
    }
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

void MashScreen::addMessage(string msg)
{
    Message *m = new Message(msg, letterBuffer);
    messages.push_back(m);
    flow->addMessage(m);
}
