#ifndef MashScreen_H
#define MashScreen_H

#include "Letter.h"
#include "MashEngine.h"
#include "Box2dMashEngine.h"
#include "DataHub.h"

class MashScreen
{
    public:
        MashScreen(DataHub &h);
        virtual ~MashScreen();

        vector<Letter *>    letters;
        vector<Message *>   messages;
        ofTrueTypeFont font;
        MashEngine *currentEngine;
        int hilightedMessageIndex;

        DataHub *dataHub;
        unsigned int rows, cols;

        void setup();
        void update();
        void draw();
        void hilightMessage(int messageIndex);

    protected:

    private:
};

#endif // MashScreen_H
