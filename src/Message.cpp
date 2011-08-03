#include "Message.h"

Message::Message(string message, ofxPango * p, ofxPCPangoFontDescription* f)
{
    StringTokenizer t(message, ", ", StringTokenizer::TOK_TRIM);
    StringTokenizer::Iterator ti = t.begin();
    for(; ti != t.end(); ++ti) {
        Word *w = new Word((string)(*ti));
        words.push_back(w);
    }
    prerender(p, f);
    setPosition(13, 13);
}

void Message::prerender(ofxPango * p, ofxPCPangoFontDescription* f) {
  for(vector<Word *>::iterator i = words.begin();
        i != words.end(); ++i) {

        for(vector<Letter *>::iterator ii = (*i)->letters.begin();
            ii != (*i)->letters.end(); ++ii) {

            (*ii)->prerender(p, f);

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

void Message::draw()
{
    for(vector<Word *>::iterator i = words.begin();
        i != words.end(); ++i) {
        (*i)->draw();
    }
}

int Message::getCol()
{
    return words[0]->letters[0]->col;
}

int Message::getRow()
{
    return words[0]->letters[0]->row;
}
