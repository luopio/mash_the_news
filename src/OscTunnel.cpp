#include "OscTunnel.h"

OscTunnel::OscTunnel()
{
    sender.setup( DEFAULT_HOST, DEFAULT_PORT );
    sendStartMessage();
}

OscTunnel::OscTunnel(char * ip, int port, MashScreen * ms) {
    screen = ms;
    sender.setup(ip, port);
    cout << "sending osc messages to port " << DEFAULT_PORT << " at " << ip << endl;

    // listen on the given port
	receiver.setup( port );
	cout << "listening for osc messages on port " << DEFAULT_PORT << "\n";

    kThreshold = 0;
    kFarThreshold = 0;
    kinect = NULL;
    kDebug = true;

    bgString = "";

    sendStartMessage();
}

OscTunnel::~OscTunnel()
{
    sendStopMessage();
}

void OscTunnel::update() {
    while( receiver.hasWaitingMessages() )
	{
        // get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );

		// check for mouse moved message
		if ( m.getAddress() == "/testmessage" )
		{
			// both the arguments are int32's
			cout << "Test Received!!!" << endl;
			//screen->messages.push_back( new Message(string("kokko")));
		}
		else if ( m.getAddress() == "/sms" )
		{
			// both the arguments are int32's
			cout << "SMS: " << m.getArgAsString( 0 ) << endl;
			//screen->messages.push_back( new Message(m.getArgAsString(0)));

		} else if ( m.getAddress() == "/oscmidi" )
		{
            if (m.getArgAsString(0)== "noteoff") {
                cout << "oscmidi noteoff: ch: " << m.getArgAsInt32(1) << " note: " << m.getArgAsInt32(2) << " velocity: " << m.getArgAsInt32(3) << endl;
                 if (m.getArgAsInt32(2)==40) {
                    screen->hilightMessage(-10);
                }
            } else if (m.getArgAsString(0)== "noteon") {
                cout << "oscmidi noteon:  ch: " << m.getArgAsInt32(1) << " note: " << m.getArgAsInt32(2) << " velocity: " << m.getArgAsInt32(3) << endl;
                switch (m.getArgAsInt32(2)) {
                    case 40:
                        screen->hilightMessage(0);
                        break;
                    case 39:
                        screen->currentEngine->debug = !screen->currentEngine->debug;
                        break;
                    case 38:
                        kDebug = !kDebug;
                        break;
                }
            } else if (m.getArgAsString(0)== "cc") {

                switch (m.getArgAsInt32(2)) {
                    case 1:
                        screen->currentEngine->strength = m.getArgAsInt32(3) / 60.0;
                        cout << screen->currentEngine->strength << " is new strength!" << endl;
                        break;
                    case 2:
                        screen->currentEngine->damping = m.getArgAsInt32(3) / 120.0;
                        cout << screen->currentEngine->damping << " is new damping!" << endl;
                        break;
                    case 3:
                        screen->currentEngine->minDis = m.getArgAsInt32(3) * 10.0;
                        cout << screen->currentEngine->minDis << " is new minimum distance!" << endl;
                        break;
                    case 5:
                        updateBgString(m.getArgAsInt32(3)+33);
                        //cout << kFarThreshold << " is new far threshold value" << endl;
                        break;
                    case 6:
                        if (kinect != NULL) {
                            kinect->setCameraTiltAngle((m.getArgAsInt32(3)/(127 / 60.0)) -30);
                            cout << (m.getArgAsInt32(3)/(127 / 60.0)) -30 << " is new near threshold value" << endl;
                        }
                        break;
                    case 7:
                        kThreshold = 254 - (m.getArgAsInt32(3) * 2);
                        cout << kThreshold << " is new near threshold value" << endl;
                        break;
                    case 8:
                        kFarThreshold = 254 - (m.getArgAsInt32(3) * 2);
                        cout << kFarThreshold << " is new far threshold value" << endl;
                        break;
                    default:
                        cout << "oscmidi cc:      ch: " << m.getArgAsInt32(1) << " param: " << m.getArgAsInt32(2) << " value: " << m.getArgAsInt32(3) << endl;
                }
            }

            else {
                cout << "oscmidi message received!!!" << endl;
            }
		} else {
            cout << "unknown osc message received!!!" << endl;
		}
	}
}

void OscTunnel::addOscListener(string address, void (*callback) (ofxOscMessage)) {
    OscListener o;
    o.address = address;
    o.callback = callback;
    oscListeners.push_back(&o);
}

void OscTunnel::sendTestMessage() {
    ofxOscMessage m;
    m.setAddress( "/testmessage" );
	m.addIntArg( 1 );
	m.addFloatArg( 3.5f );
	m.addStringArg( "hello" );
	m.addFloatArg( ofGetElapsedTimef() );
	sender.sendMessage( m );
}

void OscTunnel::sendStartMessage() {
    ofxOscMessage m;
    m.setAddress( "/kinectisalive" );
	m.addFloatArg( ofGetElapsedTimef() );
	sender.sendMessage( m );
}

void OscTunnel::sendStopMessage() {
    ofxOscMessage m;
    m.setAddress( "/kinectisdead" );
	m.addFloatArg( ofGetElapsedTimef() );
	sender.sendMessage( m );
}

void OscTunnel::addKinect(ofxKinect * k) {
    kinect = k;
}

void OscTunnel::updateBgString(char c) {
    bgString = "";
    /*for (int i = 0; i < 40; i++) {
        string tmp = "";
        for (int j = 0; j < 80; j++) {
            tmp += c;
        }
        bgString += tmp;
        bgString += "\n";
    }*/
    for (int i = 0; i < 40; i++) {
        string tmp = "";
        for (int j = 0; j < 90; j++) {
            //rand
            tmp += (rand()*1.0/RAND_MAX)*5+33;
            //tmp += c;
        }
        bgString += tmp;
        bgString += "\n";
    }
}
