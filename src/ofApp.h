#pragma once
#define OSCPORT 47893

#include "ofMain.h"
#include "ofxSpout2Receiver.h"
#include "ofxDatGui.h"
#include "ofxOsc.h"

class Surface {
public:
	ofTexture texture;
	vector<ofVec2f> corners;
	bool drawing = true;
	std::string tag = "";
	ofxDatGuiButton *surfaceToggleButton;
	ofxDatGuiButton *surfaceSelectorButton;
	ofxDatGuiTextInput *surfaceTagInput;
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
		void onButtonPressed(ofxDatGuiButtonEvent e);
		void onTextInputEvent(ofxDatGuiTextInputEvent e);

		void spawnSurface();

		ofxOscReceiver oscReceiver;

		ofxDatGui *gui;
		bool guiDrawing = true;
		ofxDatGuiButton *spawnSurfaceButton;

		bool editMode = false;

		std::string editingWall;
		vector<Surface> surfaces;
		vector<ofxSpout2::Receiver> spoutReceivers;	//Ideally this is part of the Surface class, but there was some issue I don't have time to debug

		ofShader blackAlpha;
};
