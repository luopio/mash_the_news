#ifndef MashScreen_H
#define MashScreen_H

#include "Letter.h"

class MashScreen
{
    public:
        MashScreen();
        virtual ~MashScreen();

        vector<Letter *> letters;

        ofTrueTypeFont font;

        unsigned int rows, cols;

        void setup();
        void update();
        void draw();

    protected:

    private:
};

#endif // MashScreen_H
