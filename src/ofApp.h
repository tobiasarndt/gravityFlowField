#pragma once

#include "ofMain.h"
#include "Particle.hpp"
#include "FlowField.hpp"

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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void setupNodes(int n);
    bool isSavingPDF;
    bool isInitializingParticles;
    std::vector<Particle> particles;
    std::vector<ofVec3f> nodes;
    int nPartNode;
    int nNodes;
    unique_ptr<FlowField> ff;
    ofColor upLeft = ofColor::fromHex(0xF72585);
    ofColor upRight = ofColor::fromHex(0x4CC9F0);
    ofColor downLeft = ofColor::fromHex(0x4361EE);
    ofColor downRight = ofColor::fromHex(0x7209B7);
    
    ofImage grid;
};
