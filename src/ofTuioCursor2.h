#pragma once

#include "ofxTuio.h"

class ofTuioCursor2 : public ofxTuioCursor {
public:
	ofTuioCursor2() : ofxTuioCursor(0, 0, 0.0, 0.0) {}
	void setFrom(ofxTuioCursor& cur);
	void draw();

	void update(float _xpos, float _ypos, float _xspeed, float _yspeed, float _maccel);

private:
	list<ofPoint>			path;
	ofColor					color;
};
