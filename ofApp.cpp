#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofSetCircleResolution(36);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->locations.clear();
	this->colors.clear();

	ofColor color;
	for (int i = 0; i < 100; i++) {

		glm::vec2 location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 0, ofGetHeight()));
		this->locations.push_back(location);
		
		color.setHsb(ofRandom(255), 255, 230);
		this->colors.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	float radius = 30;
	for (int i = 0; i < this->locations.size(); i++) {

		ofFill();
		ofSetColor(239);
		ofDrawCircle(this->locations[i], radius);

		ofNoFill();
		ofSetColor(this->colors[i]);
		ofDrawCircle(this->locations[i], radius);

		vector<glm::vec2> near_locations;
		for (int j = 0; j < this->locations.size(); j++) {

			if (i == j) { continue; }

			glm::vec2 distance = this->locations[i] - this->locations[j];
			float distance_lenght = glm::length(distance);
			if (distance_lenght < radius * 2) {

				ofSetColor(this->colors[j]);
				ofDrawCircle(this->locations[i], ofMap(distance_lenght, 0, radius * 2, radius, 0));
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}