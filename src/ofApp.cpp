#include "ofApp.h"
#include "ofxXmlSettings.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableSmoothing();
	loadSettings();
	tuioClient.start(settings.nPort);

	ofAddListener(tuioClient.cursorAdded, this, &ofApp::tuioAdded);
	ofAddListener(tuioClient.cursorRemoved, this, &ofApp::tuioRemoved);
	ofAddListener(tuioClient.cursorUpdated, this, &ofApp::tuioUpdated);
}

//--------------------------------------------------------------
void ofApp::update(){
	tuioClient.getMessage();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(ofColor::black);
	ofSetColor(ofColor::yellow);
	ofDrawBitmapString("TUIO Player, port " + ofToString(settings.nPort), ofPoint(20, 20));

	for (auto tit = lsCursors.begin(); tit != lsCursors.end(); tit++) {
		ofTuioCursor2 blob = *tit;
		blob.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r' || key == 'R') {
		lsCursors.clear();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::tuioAdded(ofxTuioCursor &tuioCursor) {
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(), tuioCursor.getY()*ofGetHeight());
	cout << "Point n" << tuioCursor.getSessionId() << " add at " << loc << endl;

	// Add to our list
	ofTuioCursor2 cursor;
	cursor.setFrom(tuioCursor);
	lsCursors.push_back(cursor);
}

void ofApp::tuioUpdated(ofxTuioCursor &tuioCursor) {
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(), tuioCursor.getY()*ofGetHeight());
	cout << "Point n" << tuioCursor.getSessionId() << " updated at " << loc << endl;

	auto it = std::find_if(lsCursors.begin(), lsCursors.end(), [&tuioCursor](ofTuioCursor2& cur) {
		return cur.getSessionId() == tuioCursor.getSessionId();
	});
	if (it != lsCursors.end())
	{
		it->update(tuioCursor.getX(), tuioCursor.getY(), tuioCursor.getXSpeed(), tuioCursor.getYSpeed(), tuioCursor.getMotionAccel());
	}
}

void ofApp::tuioRemoved(ofxTuioCursor &tuioCursor) {
	ofPoint loc = ofPoint(tuioCursor.getX()*ofGetWidth(), tuioCursor.getY()*ofGetHeight());
	cout << "Point n" << tuioCursor.getSessionId() << " remove at " << loc << endl;

	// Remove from our list
	auto new_end = std::remove_if(lsCursors.begin(), lsCursors.end(), [&tuioCursor](ofTuioCursor2& cur) {
		return cur.getSessionId() == tuioCursor.getSessionId();
	});
	lsCursors.erase(new_end, lsCursors.end());
}

void ofApp::loadSettings()
{
	ofxXmlSettings s;
	s.loadFile("settings.xml");
	settings.nPort = s.getValue("settings:tuio:port", 3333);
}

void ofApp::saveSettings()
{
	ofxXmlSettings s;
	s.setValue("settings:tuio:port", settings.nPort);
	s.saveFile("settings.xml");
}