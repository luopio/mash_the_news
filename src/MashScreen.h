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

        vector<Letter *> letters;
        ofTrueTypeFont font;
        MashEngine *currentEngine;

        DataHub *dataHub;
        unsigned int rows, cols;

        void setup();
        void update();
        void draw();

    protected:

    private:
};

#endif // MashScreen_H
