#include "MashScreen.h"

MashScreen::MashScreen(DataHub &h)
{
    dataHub = &h;
    dataHub->messages = &messages;
    dataHub->currentEngine = &currentEngineIndex;
    hilightedMessageIndex = -5;

}

MashScreen::~MashScreen()
{
    cout << "mashscreen being destroyed" << endl;
}

void MashScreen::setup()
{
    // load the font slightly smaller to fit it completely on the FBO (adjust for font change!)
    font.loadFont("DroidSansMono.ttf", FONT_SIZE, true, true);

    cols = ofGetWidth()  / 9; //FONT_SIZE;
    rows = ofGetHeight() / 18; //FONT_SIZE;
    dataHub->rows = &rows;
    dataHub->cols = &cols;
    cout << "cols&rows" << cols << "," << rows << "w&h " << ofGetWidth() << "," << ofGetHeight() << endl;

   /* int row_index = 0;
    for(vector<Message *>::iterator mi = messages.begin(); mi != messages.end(); ++mi) {
        (*mi)->prerender(&font);
        (*mi)->setPosition(0, row_index);
        row_index++;
    }*/

      /* Pango stuff */

    pango = new ofxPango();
    dataHub->font = new ofxPCPangoFontDescription();
    //fd->createFromString("Arial Unicode MS 11");
    dataHub->font->createFromString("Courier 11");

    messages.push_back( new Message(string("ämoro mitas jatkä"), pango, dataHub->font));
    messages.push_back( new Message(string("no huh,huh"), pango, dataHub->font));
    messages.push_back( new Message(string("öTervetuloa Göteborgiin. Meillä on viiniä!"), pango, dataHub->font));


    Box2dMashEngine *box2dME = new Box2dMashEngine(*dataHub);
    FlowMashEngine *flowME = new FlowMashEngine(*dataHub);

    engines.push_back(box2dME);
    engines.push_back(flowME);

    currentEngineIndex = 0;
    bJustChangedEngine = true;

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

}


void MashScreen::update()
{
    if(bJustChangedEngine) {
        engines[currentEngineIndex]->setup();
        bJustChangedEngine = false;
    }

    engines[currentEngineIndex]->update();
}


void MashScreen::draw()
{
    asciiBG.draw();

    cmv->draw();

    //text_image.draw(0,0);

    // note that the engine should not normally draw anything but debug
    // stuff
    engines[currentEngineIndex]->draw();

    /*
    shader.begin();

    ofSetColor(255, 0, 0);
    ofFill();
    ofRect(ofGetElapsedTimef() * 10, 0, ofGetWidth() / 3, ofGetHeight());
    ofNoFill();
    ofSetColor(255);

    shader.end();
    */

    Message *m = NULL;
    Word *w = NULL;
    int tint = 255;
    int word_index = 0;
    for(int i = 0; i < messages.size(); i++) {
        m = messages[i];
        for(vector<Word *>::iterator wi = m->words.begin();
            wi != m->words.end(); ++wi)
        {
            Word * word = *wi;
            for(int lindex = 0; lindex < word->letters.size(); lindex++)
            {
                Letter * c = word->letters[lindex];
                if(hilightedMessageIndex >= 0) {
                    //cout << "+" << hilightedMessageIndex << endl;
                    if(i == hilightedMessageIndex) {
                        c->color.r = MIN(c->color.r + 5, 255);
                        c->color.g = MIN(c->color.g + 5, 255);
                        c->color.b = MIN(c->color.b + 5, 255);
                    } else {
                        c->color.r = MAX(c->color.r - 5, 0);
                        c->color.g = MAX(c->color.g - 5, 0);
                        c->color.b = MAX(c->color.b - 5, 0);
                    }
                } else if(hilightedMessageIndex < -5) {
                    //cout << "-" << hilightedMessageIndex << endl;
                    c->color.r = MIN(c->color.r + 5, 255);
                    c->color.g = MIN(c->color.g + 5, 255);
                    c->color.b = MIN(c->color.b + 5, 255);
                    if(c->color.b > 255)
                        hilightedMessageIndex = -1;
                }
                ofSetColor(c->color.r, c->color.g, c->color.b);
                c->draw();
//                if(lindex != 0) {
//                    Letter * prevLetter = word->letters[lindex - 1];
//                    ofLine(prevLetter->col * FONT_SIZE - FONT_SIZE / 2,
//                           prevLetter->row * FONT_SIZE - FONT_SIZE / 2,
//                           c->col * FONT_SIZE - FONT_SIZE / 2,
//                           c->row * FONT_SIZE - FONT_SIZE / 2);
//                }
            }
        }

        word_index++;
        ofSetColor(255, tint, word_index % 3 * 100);
        tint -= 30;
    }


    if(dataHub->bDebug) {
        ofDrawBitmapString("Current engine: "+ofToString(currentEngineIndex), 10, ofGetHeight() - 100);
    }
}

void MashScreen::hilightMessage(int msgindex)
{
    cout << "HILIGHT:" << msgindex << endl;
    hilightedMessageIndex = msgindex;
}

void MashScreen::changeEngine()
{
    if(currentEngineIndex < engines.size()) {
        currentEngineIndex++;
        bJustChangedEngine = true;
    } else {
        currentEngineIndex = 0;
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

    asciiBG.setBackground(tmps);

}
