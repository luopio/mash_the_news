#ifndef OSCTUNNEL_H
#define OSCTUNNEL_H

#include <vector>
#include "ofxOsc.h"
#include "MashScreen.h"
#include "ofxKinect.h"
#include "DataHub.h"

#define DEFAULT_HOST "192.168.10.12"
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
        MashScreen * screen;
        ofxKinect * kinect;

        OscTunnel();
        OscTunnel(char * ip, int port, MashScreen * ms);
        virtual ~OscTunnel();

        //void sendCoordinates(vector<Coordinate> &coords);
        //void sendAttractionPoints(vector<Coordinate> &coords);
        //void sendImageData(vector<Coordinate> & coords);
        void sendTestMessage();
        void update();
        void addOscListener(string address, void (*callback)(ofxOscMessage));
        void toggleMute();

        void addDataHub(DataHub * d);

        void addKinect(ofxKinect * k);

        void updateBgString(char c);

        bool kDebug;
        bool muteOn;


        string bgString;
        DataHub * dataHub;

    protected:
    private:
        ofxOscSender * sender;
        vector<OscListener*> oscListeners;

        ofxOscReceiver * receiver;
        void sendStartMessage();
        void sendStopMessage();

        bool bRGBTune1Pressed;
        bool bRGBTune2Pressed;
        bool bRGBTune3Pressed;
        bool bRGBTune4Pressed;
        bool bRGBTune5Pressed;
        bool bRGBTune6Pressed;
        bool bRGBTune7Pressed;
        bool bRGBTune8Pressed;


};

#endif // OSCTUNNEL_H
