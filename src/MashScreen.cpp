#include "MashScreen.h"

#include "settings.h"

#ifdef _USE_OFFBO
#define ofxFBOTexture ofFbo
#endif

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
    // font.loadFont("DroidSansMono.ttf", FONT_SIZE, true, true);

    cols = ofGetWidth()  / 9; //FONT_SIZE;
    rows = ofGetHeight() / 18; //FONT_SIZE;
    dataHub->rows = &rows;
    dataHub->cols = &cols;
    cout << "cols&rows" << cols << "," << rows << "w&h " << ofGetWidth() << "," << ofGetHeight() << endl;

    /* Pango stuff */
    pango = new ofxPango();
    dataHub->font = new ofxPCPangoFontDescription();
    //fd->createFromString("Arial Unicode MS 11");
    dataHub->font->createFromString("Courier 11");

    messages.push_back( new Message(string("moro mitas jatkä"), pango, dataHub->font));
    messages.push_back( new Message(string("no huh,huh"), pango, dataHub->font));
    messages.push_back( new Message(string("Tervetuloa Göteborgiin. Meillä on viiniä!"), pango, dataHub->font));

    box2d = new Box2dMashEngine(*dataHub);
    flow = new Flow(*dataHub);
    // box2d->setup();
    flow->setup();

    ofBackground(0, 0, 0);

    asciiBG.addDatahub(dataHub);

    cmv = new CameraMaskViewer(dataHub, pango);
    cmv->setSign("@");

    asciiBG.setOfxPango(pango);
    //asciiBG.setupFBO(context, layout);
    randomBG();
   //    asciiBG.setBackground(q);
    // shader.load("shaders/noise.vert", "shaders/noise.frag");
    // cout << "binding tex0 to " << asciiBG.tex->getTextureReference().texData.textureID << endl;
    // shader.setUniform1i("tex0", fbo.getTextureReference().texData.textureID); //send which texture to the shader
    // shader.setUniformTexture("tex0", fbo, fbo.getTextureReference().texData.textureID); //send which texture to the shader
    pong = new Pongalong(dataHub,pango);

    dataHub->box2dColor             = ofColor(255, 255, 255, 0);
    dataHub->flowColor              = ofColor(255, 255, 255, 255);
    dataHub->pongColor              = ofColor(255, 255, 255, 0);
    dataHub->asciiBackgroundColor   = ofColor(255, 255, 255, 0);

    dataHub->roCoImg = new ofxCvGrayscaleImage(); // This is kinect image scaled to row/col-space

    dataHub->roCoImg->allocate(*(dataHub->cols), *(dataHub->rows));

    flowFbo.allocate(ofGetWidth(), ofGetHeight());
    box2dFbo.allocate(ofGetWidth(), ofGetHeight());
    pongFbo.allocate(ofGetWidth(), ofGetHeight());
    asciiBackgroundFbo.allocate(ofGetWidth(), ofGetHeight());

    ofEnableAlphaBlending();
}


void MashScreen::update()
{
    dataHub->roCoImg->scaleIntoMe(*(dataHub->grayDiff));

    if(dataHub->flowColor.a) {
        flow->update();
    }

    if(dataHub->box2dColor.a) {
        box2d->update();
    }
}


void MashScreen::draw()
{


    ofSetColor(255);

 /*   if(dataHub->asciiBackgroundColor.a) {
        asciiBackgroundFbo.begin();
            asciiBG.draw();
        asciiBackgroundFbo.end();
        ofSetColor(dataHub->asciiBackgroundColor);
        asciiBackgroundFbo.draw(0, 0);
    }
*/
    cmv->draw();

 /*   if(dataHub->flowColor.a) {
        flowFbo.begin();
            flow->draw();
        flowFbo.end();
        ofSetColor(dataHub->flowColor);
        flowFbo.draw(0, 0);
    }

    if(dataHub->box2dColor.a) {
        box2dFbo.begin();
            box2d->draw();
        box2dFbo.end();
        ofSetColor(dataHub->box2dColor);
        box2dFbo.draw(0, 0);
    }

    if(dataHub->pongColor.a) {
        pongFbo.clear();
        pongFbo.begin();
            pong->draw();
        pongFbo.end();
        ofSetColor(dataHub->pongColor);
        pongFbo.draw(0, 0);
    }*/

    pong->draw();
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

    asciiBG.setBackground(tmps);

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
    Message *m = new Message(msg, pango, dataHub->font);
    messages.push_back(m);
    flow->addMessage(m);
}
