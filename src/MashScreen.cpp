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
    //dtor
}

void MashScreen::setup()
{
    // load the font slightly smaller to fit it completely on the FBO (adjust for font change!)
    //font.loadFont("Irma-Light.otf", FONT_SIZE - 4, true, true, true);
    font.loadFont("DroidSansMono.ttf", FONT_SIZE, false, true);
    //font.loadFont("VeraMono.ttf", FONT_SIZE, true, true, true);
    cols = ofGetWidth()  / FONT_SIZE;
    rows = ofGetHeight() / FONT_SIZE;
    dataHub->rows = &rows;
    dataHub->cols = &cols;

    messages.push_back( new Message(string("moro mitas jatka ää"),font));
    messages.push_back( new Message(string("no huh,huh öö"),font));
    //messages.push_back( new Message(string("meno on joskus vahan villia! mutta ei semittan!"),font));
    //messages.push_back( new Message(string("Tervetuloa Göteborgiin. Meillä on viiniä!"),font));
    //messages.push_back( new Message(string("Nyt jos koskaan kannattaa mennä Ruisrockkiin!"),font));

   /* int row_index = 0;
    for(vector<Message *>::iterator mi = messages.begin();
        mi != messages.end(); ++mi) {
        (*mi)->prerender(font);
        (*mi)->setPosition(0, row_index);
        row_index++;
    }*/

    Box2dMashEngine *box2dME = new Box2dMashEngine(*dataHub);
    FlowMashEngine *flowME = new FlowMashEngine(*dataHub);
    engines.push_back(box2dME);
    engines.push_back(flowME);

    currentEngineIndex = 0;
    bJustChangedEngine = true;

    ofBackground(0, 0, 0);

    asciiBG.addDatahub(dataHub);

    string tmps = "";

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

    asciiBG.setBackground(tmps, font);

}


void MashScreen::update()
{
    if(bJustChangedEngine) {
        engines[currentEngineIndex]->setup();
        bJustChangedEngine = false;
    }

    engines[currentEngineIndex]->update();

    /*for(vector<Message *>::iterator i = messages.begin();
        i != messages.end(); ++i)
    {
        (*i)->row = ofRandom(0, rows);
        (*i)->col = ofRandom(0, cols);
    }*/
}


void MashScreen::draw()
{

    asciiBG.draw();

    Message *m = NULL;
    Word *w = NULL;
    int tint = 255;
    int word_index = 0;
    for(int i = 0; i < messages.size(); i++) {
        m = messages[i];
        font.drawString(m->msg, 100, 500+i*20);
        for(vector<Word *>::iterator wi = m->words.begin();
            wi != m->words.end(); ++wi)
        {
            for(vector<Letter *>::iterator li = (*wi)->letters.begin();
                li != (*wi)->letters.end(); ++li)
            {
                Letter * c = (*li);
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
                (*li)->draw();
            }
        }
        word_index++;
        // ofSetColor(255, tint, word_index % 3 * 100);
        tint -= 30;
    }

    if(dataHub->bDebug) {
        ofDrawBitmapString("Current engine: "+ofToString(currentEngineIndex), 10, ofGetHeight() - 100);
    }

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
