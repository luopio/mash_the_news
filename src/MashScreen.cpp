#include "MashScreen.h"

MashScreen::MashScreen(DataHub &h)
{
    dataHub = &h;
    dataHub->messages = &messages;
    hilightedMessageIndex = -5;
}

MashScreen::~MashScreen()
{
    //dtor
}

void MashScreen::setup()
{
    // load the font slightly smaller to fit it completely on the FBO (adjust for font change!)
    font.loadFont("Irma-Light.otf", FONT_SIZE - 4, true, true, true);
    cols = ofGetWidth()  / FONT_SIZE;
    rows = ofGetHeight() / FONT_SIZE;

    messages.push_back( new Message(string("moro mitas jatka")));
    messages.push_back( new Message(string("no huh,huh")));
    messages.push_back( new Message(string("meno on joskus vahan villia! mutta ei semittan!")));
    messages.push_back( new Message(string("Tervetuloa Göteborgiin. Meillä on viiniä!")));
    messages.push_back( new Message(string("Nyt jos koskaan kannattaa mennä Ruisrockkiin!")));

    for(vector<Message *>::iterator mi = messages.begin();
        mi != messages.end(); ++mi) {
        (*mi)->prerender(font);
    }

    Box2dMashEngine *box2dME = new Box2dMashEngine(*dataHub);
    currentEngine = box2dME;
    currentEngine->setup();

    ofBackground(0, 0, 0);
}


void MashScreen::update()
{
    currentEngine->update();

    /*for(vector<Message *>::iterator i = messages.begin();
        i != messages.end(); ++i)
    {
        (*i)->row = ofRandom(0, rows);
        (*i)->col = ofRandom(0, cols);
    }*/
}


void MashScreen::draw()
{
    Message *m = NULL;
    Word *w = NULL;
    int tint = 255;
    int word_index = 0;
    for(int i = 0; i < messages.size(); i++) {
        m = messages[i];
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

    currentEngine->draw();
}

void MashScreen::hilightMessage(int msgindex)
{
    cout << "HILIGHT:" << msgindex << endl;
    hilightedMessageIndex = msgindex;
}
