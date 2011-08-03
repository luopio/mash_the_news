#include "Flow.h"

Flow::Flow(DataHub &h)
{
    dataHub = &h;
    bDebug = true;
}

Flow::~Flow()
{
    //dtor
}

void Flow::setup()
{
    words.clear();
    Message *m = NULL;
    int filledRows = 0;
    while(filledRows < *(dataHub->rows)) {
        for(int i = 0; i < dataHub->messages->size(); i++) {
            int filledCols = 0;
            m = (*dataHub->messages)[i];
            float speed = ofRandom(-2, 2);
            while(filledCols < (*dataHub->cols)) {
                for(vector<Word *>::iterator wi = m->words.begin();
                    wi != m->words.end(); ++wi) {
                    FlowingWord * fw = new FlowingWord();
                    fw->msg = m;
                    fw->word = *wi;
                    fw->col = filledCols;
                    if(fw->col + fw->word->letters.size() > *(dataHub->cols)) {
                        filledCols = *(dataHub->cols);
                        break;
                    }
                    fw->row = filledRows;
                    fw->speed = speed;
                    fw->impulse = 0;
                    words.push_back(fw);
                    filledCols += (*wi)->letters.size() + 1; // + space
                    fw->pixelWidth = (*wi)->letters.size() * FONT_W;
                }
                filledCols += 4;
            }
        filledRows++;
        }
    }
}

void Flow::addMessage(Message *m)
{
    int desiredRandomRow = ofRandom(0, *(dataHub->rows));

    for(vector<FlowingWord *>::iterator i = words.begin(); i != words.end(); ++i)
    {
        FlowingWord * fw = *(i);
        if(fw->row == desiredRandomRow) {
            words.erase(i);
        }
    }

    int filledCols = 0;

    float speed = ofRandom(-2, 2);

    while(filledCols < (*dataHub->cols)) {
        for(vector<Word *>::iterator wi = m->words.begin();
                wi != m->words.end(); ++wi) {
            FlowingWord * fw = new FlowingWord();
            fw->msg = m;
            fw->word = *wi;
            fw->col = filledCols;
            if(fw->col + fw->word->letters.size() > *(dataHub->cols)) {
                filledCols = *(dataHub->cols);
                break;
            }
            fw->row = desiredRandomRow;
            filledCols += (*wi)->letters.size() + 1; // + space
            fw->speed = speed;
            fw->impulse = 255; // hilight on add
            words.push_back(fw);
        }
        filledCols += 4;
    }
}

void Flow::update()
{
    for(int i = 0; i < words.size(); i++) {
        FlowingWord * fw = words[i];
        int centerPixelX = fw->col * FONT_W + fw->pixelWidth / 2;
        int centerPixelY = fw->row * FONT_H + FONT_H / 2;

        int smallCenterX = centerPixelX / (ofGetWidth()  / (float)dataHub->roCoImg->width);
        int smallCenterY = centerPixelY / (ofGetHeight() / (float)dataHub->roCoImg->height);

        int centerPixelIndex = smallCenterX + smallCenterY * dataHub->roCoImg->width;

        if(dataHub->roCoImg->getPixels()[centerPixelIndex] > 0) {
            fw->impulse = 255;
        }
    }

    // control refresh rate
    float now = ofGetElapsedTimef();
    if(now - lastUpdateTime < 0.15) {
        return;
    }
    lastUpdateTime = now;

    for(int i = 0; i < words.size(); i++)
    {
        FlowingWord * fw = words[i];
        fw->col += fw->speed;

        int letterAmount = -fw->word->letters.size();
        if(fw->col > *(dataHub->cols)) {
            fw->col = -letterAmount;
        } else if(fw->col < -letterAmount) {
            fw->col = *(dataHub->cols);
        }

        if(fw->impulse > 0) fw->impulse -= 20;

    }
}

void Flow::draw()
{
    for(int i = 0; i < words.size(); i++)
    {
        FlowingWord * fw = words[i];
        //if(!(int)fw->impulse)
        //    continue;
        fw->word->draw(fw->col * FONT_W, fw->row * FONT_H,
                       (int)fw->impulse + 40, (int)fw->impulse + 40, (int)fw->impulse + 10);
    }

    if(dataHub->bDebug) {
        dataHub->roCoImg->draw(ofGetWidth() - 325, 5);
    }

}

void Flow::hilightFirstWord(Word *w)
{
    for(int i = 0; i < words.size(); i++) {
        FlowingWord * fw = words[i];
        if(fw->word == w) {
            fw->impulse = 255;
            return;
        }
    }
}
