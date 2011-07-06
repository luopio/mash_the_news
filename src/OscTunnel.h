#ifndef OSCTUNNEL_H
#define OSCTUNNEL_H

#include <vector>
#include "ofxOsc.h"

#define DEFAULT_HOST "192.168.1.101"
#define DEFAULT_PORT 7000

using namespace std;

struct OscListener
{
    string address;
    void (*callback)(ofxOscMessage);
};

class OscTunnel
{
    public:
        OscTunnel();
        OscTunnel(char * ip, int port);
        virtual ~OscTunnel();

        //void sendCoordinates(vector<Coordinate> &coords);
        //void sendAttractionPoints(vector<Coordinate> &coords);
        //void sendImageData(vector<Coordinate> & coords);
        void sendTestMessage();
        void update();
        void addOscListener(string address, void (*callback)(ofxOscMessage));

    protected:
    private:
        ofxOscSender sender;
        vector<OscListener*> oscListeners;

        ofxOscReceiver receiver;
        void sendStartMessage();
        void sendStopMessage();

};

#endif // OSCTUNNEL_H
