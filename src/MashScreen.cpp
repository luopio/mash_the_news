#include "MashScreen.h"

MashScreen::MashScreen()
{
    //ctor
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

    Box2dMashEngine *box2dME = new Box2dMashEngine();
    currentEngine = box2dME;
    currentEngine->setup(letters);

    for(int i = 0; i < 100; i++) {
        Letter *l = new Letter('a', font);
        letters.push_back(l);
    }
    ofBackground(0, 0, 0);
}


void MashScreen::update()
{
    currentEngine->update();

    for(vector<Letter *>::iterator i = letters.begin();
        i != letters.end(); ++i)
    {
        (*i)->row = ofRandom(0, rows);
        (*i)->col = ofRandom(0, cols);
    }
}


void MashScreen::draw()
{
    for(vector<Letter *>::iterator i = letters.begin();
        i != letters.end(); ++i)
    {
        (*i)->draw();
    }
}

