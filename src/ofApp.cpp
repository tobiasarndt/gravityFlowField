#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grid.load("images/bitmap.png");
    leftMouseButtonPressed = false;
    minDistance = 10.0;
    isSavingPDF = false;
    isInitializingParticles = false;
    
    nNodes = 50;
    nPartNode = 5;
    setupNodes(nNodes);
    ff = make_unique<FlowField>(ofGetHeight()/4);
    ff->setup();
    ff->display();
}

//--------------------------------------------------------------
void ofApp::update(){
    if (isInitializingParticles) {
        isInitializingParticles = false;
        for (int i=0; i<nodes.size()*nPartNode; i++) {
            ofColor left(upLeft);
            left.lerp(downLeft, nodes[i % nodes.size()].y / ofGetHeight());
            ofColor right(upRight);
            right.lerp(downRight, nodes[i % nodes.size()].y / ofGetHeight());
            left.lerp(right, nodes[i % nodes.size()].x / ofGetWidth());
            
            particles.push_back(Particle(nodes, i % nodes.size(), left));
        }
    }
    for(Particle &particle: particles) {
        particle.move(nodes, ff);
        
    }
}

void ofApp::setupNodes(int n){
    int nLeft = n / 2;
    ofVec3f centerRight(ofGetWidth()/4*3, ofGetHeight()/2, 0);
    for (int i=0; i<n; i++) {
        // front
        float r = ofGetHeight()*0.25 * sqrt(ofRandom(1));
        float theta = ofRandom(2 * 3.141);
        ofVec3f offset(r * cos(theta), r * sin(theta), 0);
        nodes.push_back(centerRight + offset);
        // back
        nodes.push_back(ofVec3f(ofRandom(ofGetWidth()/20,
                                         ofGetWidth()/20*9),
                                ofRandom(ofGetHeight()/10,
                                         ofGetHeight()/10*9),
                                0));
        nodes.push_back(ofVec3f(ofRandom(ofGetWidth()/20,
                                         ofGetWidth()/20*9),
                                ofRandom(ofGetHeight()/10,
                                         ofGetHeight()/10*9),
                                0));
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(52, 58, 64);//(255, 250, 224);
    ofSetColor(ofColor::white);
    grid.draw(0, 0);
    
//    ofEnableAlphaBlending();
//    // turn on alpha blending
//    // If isSavingPDF is true (i.e. the s key has been pressed), then
//    // anything in between ofBeginSaveScreenAsPDF(...) and ofEndSaveScreenAsPDF()
//    // Note: anything after ofBeginSaveScreenAsPDF(...) has been called
//    // is not drawn to the screen, it is instead rendered into a PDF file
    if (isSavingPDF) {
        ofBeginSaveScreenAsPDF("savedScreenshot_"+ofGetTimestampString()+".pdf");
    }
    
    for(Particle &particle: particles) {
        //ofSetColor(colorPallete[particle.getStartIdx() % colorPallete.size()],100);
        ofSetLineWidth(2);
        particle.draw();
    }
    
    for(int i=0; i<nodes.size(); i++) {
        ofColor left(upLeft);
        left.lerp(downLeft, nodes[i].y / ofGetHeight());
        ofColor right(upRight);
        right.lerp(downRight, nodes[i].y / ofGetHeight());
        left.lerp(right, nodes[i].x / ofGetWidth());
        //ofSetColor(colorPallete[i % colorPallete.size()]);
        ofSetColor(left);
        ofFill();
        ofDrawCircle(nodes[i].x, nodes[i].y, 5);
    }
//    ff->display();
//
//    // Finish saving the PDF and reset the isSavingPDF flag to false
//    // Ending the PDF tells openFrameworks to resume drawing to the screen.
    if (isSavingPDF) {
        ofEndSaveScreenAsPDF();
        isSavingPDF = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        // isSavingPDF is a flag that lets us know whether or not save a PDF
        isSavingPDF = true;
    }
    if (key == 'i') {
        // isSavingPDF is a flag that lets us know whether or not save a PDF
        isInitializingParticles = true;
    }
    if (key == 'r') {
        particles.clear();
    }
    if (key == 'x') {
        particles.clear();
        nodes.clear();
        setupNodes(nNodes);
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
    ofPoint mousePos(ofGetMouseX(), ofGetMouseY(), 0);
    if (! nodes.back().match(mousePos, 0.4)) {
        nodes.push_back(mousePos);
    }
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
