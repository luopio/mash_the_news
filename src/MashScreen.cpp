#include "MashScreen.h"

MashScreen::MashScreen(DataHub &h)
{
    dataHub = &h;
    dataHub->messages = &messages;
}

MashScreen::~MashScreen()
{
    //dtor
}

void MashScreen::setup()
{
    font.loadFont("Irma-Light.otf", FONT_SIZE, true, true, true);
    cols = ofGetWidth()  / FONT_SIZE;
    rows = ofGetHeight() / FONT_SIZE;

    messages.push_back( new Message(string("moro mitas jatka")));
    messages.push_back( new Message(string("no huh,huh")));
    messages.push_back( new Message(string("meno on joskus vahan villia! mutta ei semittan!")));

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
    for(vector<Message *>::iterator mi = messages.begin();
        mi != messages.end(); ++mi) {
        for(vector<Word *>::iterator wi = (*mi)->words.begin();
            wi != (*mi)->words.end(); ++wi)
        {
            for(vector<Letter *>::iterator li = (*wi)->letters.begin();
                li != (*wi)->letters.end(); ++li)
            {
                (*li)->draw();
            }
        }
        word_index++;
        ofSetColor(255, tint, word_index % 3 * 100);
        tint -= 30;
    }


    currentEngine->draw();

}

