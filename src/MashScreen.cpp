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
    // font.loadFont("DroidSansMono.ttf", FONT_SIZE, true, true);

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

    messages.push_back( new Message(string("moro mitas jatkä"), pango, dataHub->font));
    messages.push_back( new Message(string("no huh,huh"), pango, dataHub->font));
    messages.push_back( new Message(string("Tervetuloa Göteborgiin. Meillä on viiniä!"), pango, dataHub->font));
    messages.push_back( new Message(string("moro mitas jatkä"), pango, dataHub->font));
    messages.push_back( new Message(string("no huh,huh"), pango, dataHub->font));
    messages.push_back( new Message(string("Tervetuloa Göteborgiin. Meillä on viiniä!"), pango, dataHub->font));

    Box2dMashEngine *box2dME = new Box2dMashEngine(*dataHub);
    FlowMashEngine *flowME = new FlowMashEngine(*dataHub);

    engines.push_back(flowME);
    engines.push_back(box2dME);

    currentEngineIndex = 0;
    bJustChangedEngine = true;

    ofBackground(0, 0, 0);

    asciiBG.addDatahub(dataHub);

    cmv = new CameraMaskViewer(dataHub, pango);
    cmv->setSign("@");

    string tmps;
    for (int i = 0; i < 40; i++) {
        string tmp = "";
        for (int j = 0; j < 120; j++) {
            //rand
            tmp += (rand()*1.0/RAND_MAX)*5+33;
            //tmp += c;
        }
        tmps += tmp;
        tmps += "\n";
    }

    //asciiBG.setBackground(tmps, font);
    //asciiBG.setOfxPango(pango);
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
    //asciiBG.draw();

    //cmv->draw();

    engines[currentEngineIndex]->draw();
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
