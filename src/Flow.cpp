#include "Flow.h"

Flow::Flow(DataHub &h)
{
    dataHub = &h;
    bDebug = true;
    tempImg.allocate(*(dataHub->cols), *(dataHub->rows));
}

Flow::~Flow()
{
    //dtor
}

void Flow::setup()
{
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

void Flow::update()
{
    tempImg.scaleIntoMe(*(dataHub->grayDiff));
    for(int i = 0; i < words.size(); i++) {
        FlowingWord * fw = words[i];
        int centerPixelX = fw->col * FONT_W + fw->pixelWidth / 2;
        int centerPixelY = fw->row * FONT_H + FONT_H / 2;

        int smallCenterX = centerPixelX / (ofGetWidth()  / (float)tempImg.width);
        int smallCenterY = centerPixelY / (ofGetHeight() / (float)tempImg.height);

        int centerPixelIndex = smallCenterX + smallCenterY * tempImg.width;

        if(tempImg.getPixels()[centerPixelIndex] > 0) {
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
        tempImg.draw(ofGetWidth() - 325, 5);
    }

}
