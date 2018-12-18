#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	ofSetBackgroundColor(0);

	gui = new ofxDatGui(ofxDatGuiAnchor::TOP_LEFT);
	spawnSurfaceButton = gui->addButton("Spawn Surface");
	gui->onButtonEvent(this, &ofApp::onButtonPressed);
	gui->onTextInputEvent(this, &ofApp::onTextInputEvent);

	blackAlpha.load("blackAlphaShader/blackAlpha");
	
	oscReceiver.setup(OSCPORT);
}

//--------------------------------------------------------------
void ofApp::onButtonPressed(ofxDatGuiButtonEvent e) {
	if (e.target == spawnSurfaceButton) {
		spawnSurface();
	}
	for (int i = 0; i < surfaces.size(); i++) {
		if (e.target == surfaces[i].surfaceToggleButton) {
			surfaces[i].drawing = !surfaces[i].drawing;
		}
		if (e.target == surfaces[i].surfaceSelectorButton) {
			spoutReceivers[i].showSenders();
		}
	}
}
//--------------------------------------------------------------
void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e) {
	for (int i = 0; i < surfaces.size(); i++) {
		if (e.target == surfaces[i].surfaceTagInput) {
			surfaces[i].tag = e.text;
			ofLogNotice("Surface " + std::to_string(i) + " tag", surfaces[i].tag);
		}
	}
}

//--------------------------------------------------------------
void ofApp::spawnSurface() {
	Surface sfce;
	sfce.corners.push_back(ofPoint(300, 100));
	sfce.corners.push_back(ofPoint(100, 100));
	sfce.corners.push_back(ofPoint(100, 200));
	sfce.corners.push_back(ofPoint(300, 200));
	sfce.surfaceToggleButton = gui->addButton("Toggle Surface " + std::to_string(surfaces.size()));
	sfce.surfaceSelectorButton = gui->addButton("Select Surface " + std::to_string(surfaces.size()) + " Receiver");
	sfce.surfaceTagInput = gui->addTextInput("Surface " + std::to_string(surfaces.size()) + " Tag");
	surfaces.push_back(sfce);

	ofxSpout2::Receiver rcvr;
	rcvr.setup();
	spoutReceivers.push_back(rcvr);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (spoutReceivers.size() != surfaces.size()) {
		assert("spoutReceivers.size() != surfaces.size()");
	}
	while (oscReceiver.hasWaitingMessages()) {
		ofxOscMessage msg;
		oscReceiver.getNextMessage(msg);
		if (msg.getAddress() == "/disableDrawSurface") {
			for (auto &surface : surfaces) {
				if (surface.tag == msg.getArgAsString(0)) {
					surface.drawing = false;
					ofLogNotice(std::to_string(surface.drawing));
				}
			}
		}
		if (msg.getAddress() == "/enableDrawSurface") {
			for (auto &surface : surfaces) {
				if (surface.tag == msg.getArgAsString(0))
					surface.drawing = true;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//blackAlpha.begin();
	for (int i = 0; i < surfaces.size(); i++) {
		if (surfaces[i].drawing) {
			std::cout << surfaces[i].drawing << std::endl;
			spoutReceivers[i].updateTexture();
			surfaces[i].texture = spoutReceivers[i].getTexture();
			surfaces[i].texture.draw(surfaces[i].corners[0], surfaces[i].corners[1], surfaces[i].corners[2], surfaces[i].corners[3]);
		}
	}
	//blackAlpha.end();
	if (editMode) {
		for (auto surface : surfaces) {
			for (auto corner : surface.corners) {
				ofDrawCircle(corner, 25);
				ofPushStyle();
				ofSetColor(255, 0, 0);
				ofDrawCircle(corner, 1);
				ofPopStyle();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case 'e':
		editMode = !editMode;
		break;
	case 'f':
		ofToggleFullscreen();
		break;
	case ' ':
	case 'h':
		guiDrawing = !guiDrawing;
		gui->setAutoDraw(guiDrawing);
	default:
		break;
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
	if (editMode) {
		for (int i = 0; i < surfaces.size(); i++) {
			for (int q = 0; q < surfaces[i].corners.size(); q++) {
				ofVec2f mouse = ofVec2f(x, y);
				if (surfaces[i].corners[q].distance(mouse) < 25) {
					surfaces[i].corners[q] = mouse;
				}
			}
		}
	}
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
