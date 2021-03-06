#pragma once

#include "ofMain.h"
#include "ofxTuio.h"
#include "ofTuioCursor2.h"

class appSettings
{
public:
	int					nPort;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		void loadSettings();
		void saveSettings();
		void tuioAdded(ofxTuioCursor & tuioCursor);
		void tuioRemoved(ofxTuioCursor & tuioCursor);
		void tuioUpdated(ofxTuioCursor & tuioCursor);

		ofxTuioClient						tuioClient;
		list<ofTuioCursor2>					lsCursors;

		appSettings							settings;
};
