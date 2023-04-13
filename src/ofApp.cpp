#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	grabber.setDeviceID(0);
	grabber.initGrabber(640, 480);

	camGray.allocate(grabber.getWidth(),
		grabber.getHeight(),
		OF_IMAGE_GRAYSCALE);

	prevGray.allocate(grabber.getWidth(),
		grabber.getHeight(),
		OF_IMAGE_GRAYSCALE);

	diffImg.allocate(grabber.getWidth(),
		grabber.getHeight(),
		OF_IMAGE_GRAYSCALE);

	threshImg.allocate(grabber.getWidth(),
		grabber.getHeight(),
		OF_IMAGE_GRAYSCALE);

	ofBackground(120, 160, 240);

	for (int i = 0; i < 800; i++) {
		float x = ofRandom(grabber.getWidth());
		float y = ofRandom(grabber.getHeight());
		ofPoint point(x, y);
		pts.push_back(point);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	grabber.update();
	if (grabber.isFrameNew()) {
		convertColor(grabber, camGray, CV_RGB2GRAY);
		camGray.update();
		camGray.mirror(false, true);


		absdiff(camGray, prevGray, diffImg);
		diffImg.update();

		prevGray.setFromPixels(camGray.getPixels());
		prevGray.update();

		
		threshImg.setFromPixels(diffImg.getPixels());
		threshold(threshImg, 40);
		threshImg.update();

		finder.findContours(threshImg);



		for (int i = 0; i < 800; i++) {

			ofColor color = threshImg.getColor(pts[i].x, pts[i].y);
			int upy = 0;
			int downy = grabber.getHeight();

			int leftx = 0;
			int rightx = grabber.getWidth();

			if (color.getBrightness() < 127) {
				ofSeedRandom(i*mouseY);
				pts[i].y += ofRandom(-1, 1);
				ofSeedRandom(i*mouseX);
				pts[i].x += ofRandom(-1, 1);
			}
			else {
				history.addVertex(pts[i]);
				if (history.size() > 15) {
					history.getVertices().erase(history.getVertices().begin());
				}
				
				//move y
				for (int j = pts[i].y; j >= 0; j--) {
					ofColor check = threshImg.getColor(pts[i].x, j);
					if (check.getBrightness() < 127) {
						upy = j;
						break;
					}
				}
				
				for (int k = pts[i].y; k < grabber.getHeight(); k++) {
					ofColor check = threshImg.getColor(pts[i].x, k);
					if (check.getBrightness() < 127) {
						downy = k;
						break;
					}
				}
				if (abs(downy - pts[i].y)>abs(upy-pts[i].y) && downy != grabber.getHeight() && upy != 0) {
					pts[i].y = upy;
				}
				else if (abs(downy - pts[i].y) <= abs(upy - pts[i].y) && downy != grabber.getHeight() && upy != 0)
				{
					pts[i].y = downy;
				}

				/*
				//move x
				for (int j = pts[i].x; j >= 0; j--) {
					ofColor check = threshImg.getColor(j, pts[i].y);
					if (check.getBrightness() < 127) {
						leftx = j;
						break;
					}
				}
				for (int k = pts[i].x; k < grabber.getWidth(); k++) {
					ofColor check = threshImg.getColor(k, pts[i].y);
					if (check.getBrightness() < 127) {
						rightx = k;
						break;
					}
				}
				if (abs(rightx - pts[i].x) > abs(leftx - pts[i].x) && rightx != grabber.getWidth() && leftx != 0) {
					pts[i].x = leftx;
				}
				else if (abs(rightx - pts[i].x) <= abs(leftx - pts[i].x) && rightx != grabber.getWidth() && leftx != 0)
				{
					pts[i].x = rightx;
				}
				*/
			}
			if (pts[i].y >= grabber.getHeight()) {
				pts[i].y = 1;
			}
			if (pts[i].y <= 0) {
				pts[i].y = grabber.getHeight()-1;
			}

			if (pts[i].x >= grabber.getWidth()) {
				pts[i].x = 1;
			}
			if (pts[i].x <= 0) {
				pts[i].x = grabber.getWidth()-1;
			}

		}

	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofScale(0.5, 0.5);
	ofSetColor(255);
	diffImg.draw(grabber.getWidth(), 0);
	threshImg.draw(grabber.getWidth() * 2, 0);

	for (int i = 0; i < 800; i++) {
		ofSeedRandom(i);
		int r = int(ofRandom(0, i * 800)) % 255;
		int g = int(ofRandom(0, 900 * i)) % 255;
		int b = int(ofRandom(0, 1200 * i)) % 255;
		ofSetColor(r, g, b);
		ofDrawCircle(pts[i].x, pts[i].y, 2.5);
	}


	history.draw();
	if (history.size() > 2) {
		history.getVertices().erase(history.getVertices().begin());
	}

	/*
	if (finder.size() > 0) {
		ofPolyline line = finder.getPolyline(0);
		line.draw();
	}
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
