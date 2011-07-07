#include "FlowMashEngine.h"

FlowMashEngine::FlowMashEngine(DataHub &h)
{
    dataHub = &h;
    bDebug = true;
}

FlowMashEngine::~FlowMashEngine()
{
    //dtor
}

void FlowMashEngine::setup()
{
    /* on startup set the rows of each message to the one that row
        was occupying, if the row is already occupied by a message,
        use another */
    vector<int> takenRows;
    Message *m = NULL;
    Word *w = NULL;
    for(int i = 0; i < dataHub->messages->size(); i++) {
        m = (*dataHub->messages)[i];
        // find a free row to put this message on
        int first_word_row = m->words[0]->letters[0]->row;
        int cur_row = first_word_row;
        if(takenRows.size() == *(dataHub->rows))
            break; // no more free rows
        while(find(takenRows.begin(), takenRows.end(), cur_row) != takenRows.end()) {
            if(cur_row > *(dataHub->rows)) {
                cur_row = 0;
            }
            cur_row++;
        }
        cout << "free row: " << cur_row << "/" << *(dataHub->rows) << endl;
        takenRows.push_back(cur_row);

        int spacing = 0;
        int letter_index = 0;
        for(int wi = 0; wi < m->words.size(); wi++) {
            w = m->words[wi];
            for(int li = 0; li < w->letters.size(); li++)
            {
                w->letters[li]->row = cur_row;
                w->letters[li]->col = letter_index + spacing;
                letter_index++;
            }
            spacing++;
        }
    }
    lastUpdateTime = ofGetElapsedTimef();
}

void FlowMashEngine::update()
{
    // control refresh rate
    float now = ofGetElapsedTimef();
    if(now - lastUpdateTime < 0.15) {
        return;
    }
    lastUpdateTime = now;

    /* update the locations of the letters */
    Message *m = NULL;
    Word *w = NULL;
    for(int i = 0; i < dataHub->messages->size(); i++)
    {
        m = (*dataHub->messages)[i];
        for(int wi = 0; wi < m->words.size(); wi++)
        {
            w = m->words[wi];
            for(int li = 0; li < w->letters.size(); li++)
            {
                // w->letters[li]->row = row;
                w->letters[li]->col -= 1;
            }
        }

        /*  test from the last letter if the whole message has gone out,
            if so reset all the word locations to the other end */
        w = m->words[m->words.size() - 1];
        if(w->letters[w->letters.size() - 1]->col < 0)
        {
            int letter_index = 0;
            for(int wi = 0; wi < m->words.size(); wi++)
            {
                w = m->words[wi];
                for(int rli = 0; rli < w->letters.size(); rli++)
                {
                    w->letters[rli]->col = *(dataHub->cols) + 1 + letter_index;
                    letter_index++;
                }
                letter_index++; // spaces
            }
        }
    }
}

void FlowMashEngine::draw()
{

    if(bDebug) {
        // tempImg.draw(400, 10);
    }
}


