#include "Letter.h"

Letter::Letter(const char let)
{
    letter = string(1, let);
    cout << let << ",";
    row = 10 + ofRandom(1, 100);
    col = 10 + ofRandom(1, 100);
}

void Letter::prerender(ofTrueTypeFont &f)
{
    font = &f;
    tex = new ofxFBOTexture();
    tex->allocate(FONT_SIZE + 3, FONT_SIZE + 3, false);
    tex->begin();
        // ofFill();
        // ofSetColor(255, 0, 0);
        // ofRect(0, 0, 100, 100);
        ofSetColor(255, 255, 255);
        font->drawString(letter, 0, FONT_SIZE);
    tex->end();
}

Letter::~Letter()
{
    //dtor
}

void Letter::draw()
{
    tex->draw(col * FONT_SIZE, row * FONT_SIZE);
}

Word::Word(string word)
{
    string::iterator i;
    for(i = word.begin(); i != word.end(); i++) {
        Letter *l = new Letter((*i));
        letters.push_back(l);
    }
}

Message::Message(string message)
{
    // vector<string> swords = split(message, ' ');
    StringTokenizer t(message, ", ", StringTokenizer::TOK_TRIM);
    StringTokenizer::Iterator ti = t.begin();
    for(; ti != t.end(); ++ti) {
        Word *w = new Word((string)(*ti));
        words.push_back(w);
    }
}

void Message::prerender(ofTrueTypeFont &f)
{
    for(vector<Word *>::iterator i = words.begin();
        i != words.end(); ++i) {

        for(vector<Letter *>::iterator ii = (*i)->letters.begin();
            ii != (*i)->letters.end(); ++ii) {

            (*ii)->prerender(f);

        }
    }
}
