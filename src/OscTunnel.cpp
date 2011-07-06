#include "OscTunnel.h"

OscTunnel::OscTunnel()
{
    sender.setup( DEFAULT_HOST, DEFAULT_PORT );
    sendStartMessage();
}

OscTunnel::OscTunnel(char * ip, int port) {
    sender.setup(ip, port);
    cout << "sending osc messages to port " << DEFAULT_PORT << " at " << ip << endl;

    // listen on the given port
	receiver.setup( port );
	cout << "listening for osc messages on port " << DEFAULT_PORT << "\n";

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

        cout << "message is received! ";

		// check for mouse moved message
		if ( m.getAddress() == "/testmessage" )
		{
			// both the arguments are int32's
			cout << "Test Received!!!" << endl;
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
