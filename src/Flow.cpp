#include "Flow.h"

Flow::Flow(DataHub &h)
{
    dataHub = &h;
    bDebug = true;
    dataHub->flowFadeSpeed = 23;
}

Flow::~Flow()
{
    //dtor
}

void Flow::setup()
{
    words = new vector<FlowingWord *>();
    words->clear();
    Message *m = NULL;
    int filledRows = 0;

    if(!dataHub->messages->size())
        return;

    while(filledRows < *(dataHub->rows)) {
        for(int i = 0; i < dataHub->messages->size(); i++) {
            m = (*dataHub->messages)[i];
            int totalLength = 0;
            int messageRepeatsOnThisRow = 1;
            // calculate a total length for the message, how many do we need per row?
            if(m->length > (*dataHub->cols)) {
                totalLength = m->length;
            } else {
                totalLength = m->length;
                while(totalLength < (*dataHub->cols)) {
                    totalLength += m->length + 4;
                    messageRepeatsOnThisRow++;
                }
            }
            cout << "Flow:setup() calculated total length of " << totalLength << endl;

            int colCounter = 0;
            float speed = ofRandom(-2, 2);
            while(messageRepeatsOnThisRow > 0) {
                for(vector<Word *>::iterator wi = m->words.begin(); wi != m->words.end(); ++wi) {
                    FlowingWord * fw = new FlowingWord();
                    fw->msg = m;
                    fw->word = *wi;
                    fw->col = colCounter;
                    fw->row = filledRows;
                    fw->speed = speed;
                    fw->impulse = 0;
                    fw->pixelWidth = (*wi)->letters.size() * FONT_W;
                    fw->rowTotalLength = totalLength;
                    words->push_back(fw);
                    colCounter += (*wi)->letters.size()  + 1;
                }
                messageRepeatsOnThisRow--;
                colCounter += 4;
            }
        filledRows++;
        }
    }
}

void Flow::addMessage(Message *m)
{
    int desiredRandomRow = ofRandom(0, *(dataHub->rows));

    vector<FlowingWord *> *newWords = new vector<FlowingWord *>();
    for(vector<FlowingWord *>::iterator i = words->begin(); i != words->end(); ++i)
    {
        FlowingWord * fw = *(i);
        if(fw->row == desiredRandomRow) {
            // words.erase(i);
        } else {
            newWords->push_back(fw);
        }
    }
    vector<FlowingWord *> *temp = words;
    words = newWords;
    delete(temp);

    int totalLength = 0;
    int messageRepeatsOnThisRow = 0;
    // calculate a total length for the message, how many do we need per row?
    if(m->length > (*dataHub->cols)) {
        totalLength = m->length;
        messageRepeatsOnThisRow = 1;
    } else {
        totalLength = m->length;
        messageRepeatsOnThisRow = 1;
        while(totalLength < (*dataHub->cols)) {
            totalLength += m->length + 4;
            messageRepeatsOnThisRow++;
        }
    }
    cout << "calculated total length of " << totalLength << endl;

    int colCounter = 0;
    float speed = ofRandom(-2, 2);
    while(messageRepeatsOnThisRow > 0) {
        for(vector<Word *>::iterator wi = m->words.begin(); wi != m->words.end(); ++wi) {
            FlowingWord * fw = new FlowingWord();
            fw->msg = m;
            fw->word = *wi;
            fw->col = colCounter;
            fw->row = desiredRandomRow;
            fw->speed = speed;
            fw->impulse = 355;
            fw->pixelWidth = (*wi)->letters.size() * FONT_W;
            fw->rowTotalLength = totalLength;
            words->push_back(fw);
            colCounter += (*wi)->letters.size()  + 1;
        }
        messageRepeatsOnThisRow--;
        colCounter += 4;
    }
}

void Flow::update()
{
    for(int i = 0; i < words->size(); i++)
    {
        FlowingWord * fw = (*words)[i];
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

    for(int i = 0; i < words->size(); i++)
    {
        FlowingWord * fw = (*words)[i];
        fw->col += fw->speed;

        int letterAmount = fw->word->letters.size();
        if(fw->speed > 0 && fw->col > *(dataHub->cols)) {
            fw->col -= fw->rowTotalLength;
        } else if(fw->speed < 0 && fw->col < -letterAmount) {
            fw->col += fw->rowTotalLength;
        }

        if(fw->impulse > 0) fw->impulse -= dataHub->flowFadeSpeed;
        else { fw->impulse = 0; }

    }
}

void Flow::draw()
{
    for(int i = 0; i < words->size(); i++)
    {
        FlowingWord * fw = (*words)[i];
        //if(!(int)fw->impulse)
        //    continue;
        fw->word->drawww(fw->col,
                         fw->row,
                        (int)fw->impulse + dataHub->flowBGbrightness,
                        (int)fw->impulse + dataHub->flowBGbrightness,
                        (int)fw->impulse + dataHub->flowBGbrightness,
                         //dataHub->colorMap->getPixels(),
                         //dataHub->colorMap->getWidth(),
                         //dataHub->colorMap->getHeight()
                         dataHub->colorMap,
                         // dataHub->colorMapWeight
                         fw->impulse / 255,
                         dataHub->asciiGrayScales
                         );
    }

    //if(dataHub->bDebug) {
    //    dataHub->roCoImg->draw(ofGetWidth() - 325, 5);
    //}

}

void Flow::hilightFirstWord(Word *w)
{
    for(int i = 0; i < words->size(); i++) {
        FlowingWord * fw = (*words)[i];
        if(fw->word == w) {
            fw->impulse = 255;
            return;
        }
    }
}
