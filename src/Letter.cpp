#include "Letter.h"

Letter::Letter(const char let)
{
    letter = string(1, let);
    col = 0;
    row = 0;
    // cout << let << ",";
}

void Letter::prerender(ofTrueTypeFont &f)
{
    font = &f;


    cout << letter << " " << (int)letter[0] << " ! " << endl;

    tex = new ofxFBOTexture();
    tex->allocate(font->stringWidth(letter), font->stringHeight(letter) * 2, false);
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
        ofColor c;
        c.r = 255; c.g = 255; c.b = 255;
        l->color = c;
        letters.push_back(l);
    }
}

Message::Message(string message, ofTrueTypeFont &font)
{
    // vector<string> swords = split(message, ' ');
    StringTokenizer t(message, ", ", StringTokenizer::TOK_TRIM);
    StringTokenizer::Iterator ti = t.begin();
    for(; ti != t.end(); ++ti) {
        Word *w = new Word((string)(*ti));
        words.push_back(w);
    }

    prerender(font);
    setPosition(30, 30);

    msg = message;

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

void Message::setPosition(int col, int row)
{
    int spacing = 0;
    int letter_index = 0;
    for(vector<Word *>::iterator i = words.begin();
        i != words.end(); ++i) {
        for(vector<Letter *>::iterator ii = (*i)->letters.begin();
            ii != (*i)->letters.end(); ++ii) {
            (*ii)->col = col + spacing + letter_index;
            (*ii)->row = row;
            letter_index++;
        }
        spacing++;
    }
}
