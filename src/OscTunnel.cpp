#include "OscTunnel.h"

OscTunnel::OscTunnel()
{
    sender = NULL;
    receiver = NULL;
    // sender = new ofxOscSender();
    receiver = new ofxOscReceiver();
    sender->setup( DEFAULT_HOST, DEFAULT_PORT );
    sendStartMessage();
    bRGBTune1Pressed = bRGBTune2Pressed = bRGBTune3Pressed = bRGBTune4Pressed = bRGBTune5Pressed = false;
}

OscTunnel::OscTunnel(char * ip, int port, MashScreen * ms) {
    muteOn = false;
    screen = ms;
    sender = new ofxOscSender();
    receiver = new ofxOscReceiver();
    try {
        if (sender!=NULL)
            sender->setup(ip, port);
        cout << "sending osc messages to port " << DEFAULT_PORT << " at " << ip << endl;
    } catch ( ... ) {
        cout << "can't send osc!";
        sender = NULL;
    }


    // listen on the given port
    try {
        receiver->setup( port );
        cout << "listening for osc messages on port " << DEFAULT_PORT << "\n";
    } catch ( ... ) {
        cout << "can't receive osc!";
        receiver = NULL;
    }
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
    if (receiver==NULL) return;
    while( receiver->hasWaitingMessages() ) {
	    try {

            // get the next message
            ofxOscMessage m;
            receiver->getNextMessage( &m );

            if (muteOn)
                continue;

            // check for mouse moved message
            if ( m.getAddress() == "/testmessage" )
            {
                // both the arguments are int32's
                cout << "Test Received!!!" << endl;
                //screen->messages.push_back( new Message(string("kokko")));
            }
            else if ( m.getAddress() == "/sms" )
            {
                cout << "SMS: " << m.getArgAsString( 0 ) << endl;
                screen->addMessage(m.getArgAsString(0));

            }
            else if ( m.getAddress() == "/ascii" )  {
                cout << "ascii: " << m.getArgAsString( 1 ) << endl;
                if (m.getArgAsInt32(0)) {
                    bgString = m.getArgAsString(1);
                } else {
                    bgString += m.getArgAsString(1);
                }
                //screen->messages.push_back( new Message(m.getArgAsString(0)));

            }
            else if ( m.getAddress() == "/oscmidi" ) {

                if (m.getArgAsString(0)== "noteoff") {
                    cout << "oscmidi noteoff: ch: " << m.getArgAsInt32(1) << " note: " << m.getArgAsInt32(2) << " velocity: " << m.getArgAsInt32(3) << endl;

                    switch (m.getArgAsInt32(1)) {

                        case 2:
                            switch (m.getArgAsInt32(2)) {
                                case 67:
                                    bRGBTune1Pressed = false;
                                    break;
                                case 69:
                                    bRGBTune2Pressed = false;
                                    break;
                                case 71:
                                    bRGBTune3Pressed = false;
                                    break;
                                case 72:
                                    bRGBTune4Pressed = false;
                                    break;
                                case 60:
                                    bRGBTune5Pressed = false;
                                    break;
                            }
                            break;
                    }
                }
                else if (m.getArgAsString(0)== "noteon") {
                    //cout << "oscmidi noteon:  ch: " << m.getArgAsInt32(1) << " note: " << m.getArgAsInt32(2) << " velocity: " << m.getArgAsInt32(3) << endl;
                    // corresponds to the midi channel (0-3)
                    switch (m.getArgAsInt32(1)) {
                        case 0:
                            break;
                        case 1:
                            switch (m.getArgAsInt32(2)) {
                                case 37: // first button
                                    screen->hilightWordAt(ofRandom(0, 3));
                                    break;
                            }

                            break;
                        case 2:
                            switch (m.getArgAsInt32(2)) {
                                case 67:
                                    bRGBTune1Pressed = true;
                                    break;
                                case 69:
                                    bRGBTune2Pressed = true;
                                    break;
                                case 71:
                                    bRGBTune3Pressed = true;
                                    break;
                                case 72:
                                    bRGBTune4Pressed = true;
                                    break;
                                case 60:
                                    bRGBTune5Pressed = true;
                                    break;
                            }
                            break;
                        case 3:
                            switch (m.getArgAsInt32(2)) {
                                case 36:
                                    screen->messages.push_back( new Message(string("no huh,huh"), screen->pango, dataHub->font));
                                    break;
                                case 40:
                                    // redoing...
                                    //screen->hilightMessage(0);
                                    break;
                                case 39:
                                    // no more cur engine, removed debug
                                    break;
                                case 41:
                                    dataHub->bDebug = !dataHub->bDebug;
                                    //kDebug = !kDebug;
                                    //cout << "bDebug toggle!" << endl;
                                    break;
                            }
                            break;
                    }




                }
                else if (m.getArgAsString(0)== "cc") {
                    int newAlpha = 0;
                    /* Which channel from 0 - 3 */
                    switch (m.getArgAsInt32(1)) {

                        /* Channel 0 is for spaghetti!  */
                        case 0:
                            switch (m.getArgAsInt32(2)) {
                                case 1:
                                    dataHub->damping = m.getArgAsInt32(3) / 25.0;
                                    cout << dataHub->damping << " is new damping!" << endl;
                                    break;
                                case 2:
                                    dataHub->strength = m.getArgAsInt32(3) / 25.0;
                                    cout << dataHub->strength << " is new strength!" << endl;
                                    break;
                                case 3:
                                   // dataHub->   screen->currentEngine->minDis = m.getArgAsInt32(3) * 10.0;
                  //                  cout << screen->currentEngine->minDis << " is new minimum distance!" << endl;
                                    break;
                                case 5:
                                    updateBgString(m.getArgAsInt32(3)+33);
                                    //cout << kFarThreshold << " is new far threshold value" << endl;
                                    break;

                            }
                            break;

                        /* modify alpha values of the layers */
                        case 1:
                            newAlpha = m.getArgAsInt32(3) * 2;
                            switch (m.getArgAsInt32(2)) {
                                case 1:
                                    dataHub->box2dColor.a = newAlpha;
                                    cout << (int)dataHub->box2dColor.a << " box2d alpha" << endl;
                                    break;
                                case 2:
                                    dataHub->flowColor.a = newAlpha;
                                    cout << (int)dataHub->flowColor.a << " flow alpha" << endl;
                                    break;
                                case 3:
                                    dataHub->pongColor.a = newAlpha;
                                    cout << (int)(dataHub->pongColor.a) << " pong alpha" << endl;
                                    break;
                                case 4:
                                    dataHub->asciiBackgroundColor.a = newAlpha;
                                    cout << (int)dataHub->asciiBackgroundColor.a << " asciibg alpha" << endl;
                                    break;

                                case 5:
                                    dataHub->CMVColor.a = newAlpha;
                                    cout << (int)dataHub->CMVColor.a << " asciibg alpha" << endl;
                                    break;
                            }
                            break;

                        case 2:
                            switch (m.getArgAsInt32(2)) {
                                /*  Tuning the colors of the layers, one nob per channel, button
                                    state determines */
                                case 1:
                                    //dataHub->pongSpeed = m.getArgAsInt32(3)/20;
                                    //cout << "pong speed is now " << (dataHub->pongSpeed) << endl;
                                    if(bRGBTune1Pressed) {
                                        dataHub->box2dColor.r = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune2Pressed) {
                                        dataHub->flowColor.r = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune3Pressed) {
                                        dataHub->pongColor.r = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune4Pressed) {
                                        dataHub->asciiBackgroundColor.r = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune5Pressed) {
                                        dataHub->CMVColor.r = m.getArgAsInt32(3) * 2;
                                    }

                                    break;

                                case 2:
                                    //dataHub->pongSpeed = m.getArgAsInt32(3)/20;
                                    //cout << "pong speed is now " << (dataHub->pongSpeed) << endl;
                                    if(bRGBTune1Pressed) {
                                        dataHub->box2dColor.g = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune2Pressed) {
                                        dataHub->flowColor.g = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune3Pressed) {
                                        dataHub->pongColor.g = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune4Pressed) {
                                        dataHub->asciiBackgroundColor.g = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune5Pressed) {
                                        dataHub->CMVColor.g = m.getArgAsInt32(3) * 2;
                                    }

                                    break;

                                case 3:
                                    //dataHub->pongSpeed = m.getArgAsInt32(3)/20;
                                    //cout << "pong speed is now " << (dataHub->pongSpeed) << endl;
                                    if(bRGBTune1Pressed) {
                                        dataHub->box2dColor.b = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune2Pressed) {
                                        dataHub->flowColor.b = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune3Pressed) {
                                        dataHub->pongColor.b = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune4Pressed) {
                                        dataHub->asciiBackgroundColor.b = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune5Pressed) {
                                        dataHub->CMVColor.b = m.getArgAsInt32(3) * 2;
                                    }

                                    break;

                                case 4:
                                    //dataHub->pongSpeed = m.getArgAsInt32(3)/20;
                                    //cout << "pong speed is now " << (dataHub->pongSpeed) << endl;
                                    if(bRGBTune1Pressed) {
                                        dataHub->box2dColor.a = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune2Pressed) {
                                        dataHub->flowColor.a = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune3Pressed) {
                                        dataHub->pongColor.a = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune4Pressed) {
                                        dataHub->asciiBackgroundColor.a = m.getArgAsInt32(3) * 2;
                                    }
                                    if(bRGBTune5Pressed) {
                                        dataHub->CMVColor.a = m.getArgAsInt32(3) * 2;
                                    }

                                    break;
                            }
                            break;

                        /* Channel 3 is for calibrating stuff */
                        case 3:
                            switch (m.getArgAsInt32(2)) {
                                case 5:
                                    //screen->messages.push_back( new Message(string("no huh,huh"), screen->pango, dataHub->font));
                                    break;
                                case 6:
                                    if (kinect != NULL) {
                                        kinect->setCameraTiltAngle((m.getArgAsInt32(3)/(127 / 60.0)) -30);
                                        cout << (m.getArgAsInt32(3)/(127 / 60.0)) -30 << " is new near threshold value" << endl;
                                    }
                                    break;

                                case 7:
                                    if (kinect != NULL) {
                                        dataHub->kThreshold = 254 - (m.getArgAsInt32(3) * 2);
                                        cout << dataHub->kThreshold << " is new near threshold value" << endl;
                                    }
                                    break;
                                case 8:
                                    if (kinect != NULL) {
                                        dataHub->kFarThreshold = 254 - (m.getArgAsInt32(3) * 2);
                                        cout << dataHub->kFarThreshold << " is new far threshold value" << endl;
                                    }
                                break;

                            }
                        break;
                    }
                }
            }
            else if ( m.getAddress() == "/hilite" )
            {
                int wordIndex = m.getArgAsInt32(0);
                cout << "HILITE: " << m.getArgAsInt32(0) << endl;
                screen->hilightWordAt(wordIndex);

            }
            else {
                cout << "unknown osc message received: " << m.getAddress() << endl;
            }
        } catch ( ... ) {
            cout << "problematic osc message gone to dev/null!" << endl;
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
    if (sender==NULL) return;
    ofxOscMessage m;
    m.setAddress( "/testmessage" );
	m.addIntArg( 1 );
	m.addFloatArg( 3.5f );
	m.addStringArg( "hello" );
	m.addFloatArg( ofGetElapsedTimef() );
	sender->sendMessage( m );
}

void OscTunnel::sendStartMessage() {
    if (sender==NULL) return;
    ofxOscMessage m;
    m.setAddress( "/kinectisalive" );
	m.addFloatArg( ofGetElapsedTimef() );
	sender->sendMessage( m );
}

void OscTunnel::sendStopMessage() {
    if (sender==NULL) return;
    ofxOscMessage m;
    m.setAddress( "/kinectisdead" );
	m.addFloatArg( ofGetElapsedTimef() );
	sender->sendMessage( m );
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
    for (int i = 0; i < 1000; i++) {

        bgString += (rand()*1.0/RAND_MAX)*300+33;

    }
}

void OscTunnel::addDataHub(DataHub * d) {
    dataHub = d;
}

void OscTunnel::toggleMute() {
    muteOn = !muteOn;
    if (muteOn) cout << "OSC traffic is sent to /dev/null!" << endl;
    else cout << "OSC traffic is back online!" << endl;
}
