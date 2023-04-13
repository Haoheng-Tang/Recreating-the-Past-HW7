#pragma once

#include "ofMain.h"
#include "ofxCv.h"

using namespace ofxCv;

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

		ofVideoGrabber grabber;
		ofImage bgGray;
		ofImage camGray;
		ofImage threshImg;
		ofImage prevGray;
		ofImage diffImg;
		ContourFinder finder;
		vector < ofPoint > pts;
		float nWhiteSmoothed = 0;
		ofPolyline history;


		bool bFlip;
		
};
