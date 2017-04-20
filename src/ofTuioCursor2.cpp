#include "ofTuioCursor2.h"
#include "ofPolyline.h"

void ofTuioCursor2::setFrom(ofxTuioCursor& cur) {
	sessionId = cur.getSessionId();
	fingerId = cur.getFingerId();
	update(cur.getPosition().getX(), cur.getPosition().getY(), cur.getXSpeed(), cur.getYSpeed(), cur.getMotionAccel());
	color = ofColor(255.f * ofRandomuf(), 255.f * ofRandomuf(), 255.f * ofRandomuf());
}

void ofTuioCursor2::draw() {
	ofSetColor(color);

	// Draw the path
	ofPolyline pathDraw;
	for (auto &p : path)
	{
		ofPoint ptScaled(p.x * ofGetWidth(), p.y * ofGetHeight());
		pathDraw.addVertex(ptScaled);
	}
	pathDraw.draw();

	// Draw the blob and its info
	ofEllipse(getX()*ofGetWidth(), getY()*ofGetHeight(), 10.0, 10.0);
	string str = "SessionId: " + ofToString((int)(getSessionId()));
	ofDrawBitmapString(str, getX()*ofGetWidth() - 10.0, getY()*ofGetHeight() + 25.0);
}

void ofTuioCursor2::update(float _xpos, float _ypos, float _xspeed, float _yspeed, float _maccel) {
	ofxTuioCursor::update(_xpos, _ypos, _xspeed, _yspeed, _maccel);
	// Add the new position to the path
	path.push_back(ofPoint(_xpos, _ypos));
};