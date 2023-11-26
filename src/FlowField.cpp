//
//  FlowField.cpp
//  flow field
//
//  Created by Tobias Arndt on 21.11.23.
//

#include "FlowField.hpp"
FlowField::FlowField(int r)
{
    resolution = r;
    cols = ofGetWidth() / resolution + 1;
    rows = ofGetHeight() / resolution + 1;
    field.assign(cols, std::vector<ofVec2f>(rows, ofVec2f(0, 0)));
}
FlowField::~FlowField()
{
    
}
void FlowField::setup()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> d(0, 1);
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            ofVec2f dir(d(gen), d(gen));
            field[x][y] = dir.normalize();
        }
    }
}

void FlowField::display()
{
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            ofPushMatrix();
            ofTranslate(x * resolution, y * resolution);
            ofNoFill();
            ofSetColor(255);
            ofDrawRectangle(0, 0, resolution, resolution);
            
            ofVec2f c = ofVec2f(0);//ofVec2f(resolution / 2, resolution / 2);
            int len = resolution * 3 / 4;
            ofVec2f t0 = c - (field[x][y] * len / 2);
            ofVec2f t1 = c + (field[x][y] * len / 2);
            ofSetColor(255, 255, 0);
            ofDrawLine(t0.x, t0.y, t1.x, t1.y);
            ofPopMatrix();
        }
    }
    for (int x = 0; x < 11*10; x++) {
        for (int y = 0; y < 8*10; y++) {
            
            ofVec2f c = ofVec2f(x*resolution/10, y*resolution/10);
            ofVec2f t0 = c - getVectorInterpolated(c)*10;
            ofVec2f t1 = c + getVectorInterpolated(c)*10;
            ofSetColor(0, 255, 255, 20);
            ofDrawLine(t0.x, t0.y, t1.x, t1.y);
        }
    }
}

ofVec2f FlowField::getVectorInterpolated(ofVec2f pos){
    
    ofVec2f newVector(0);
    
    int col = (int)ofClamp(pos.x / resolution, 0, cols - 1);
    int row = (int)ofClamp(pos.y / resolution, 0, rows - 1);
    
    float pctX = float((int)pos.x % resolution)/resolution;
    float pctY = float((int)pos.y % resolution)/resolution;
    
    float d0 = max(0.f, 1 - sqrt(pctX*pctX + pctY*pctY)) ;
    float d1 = max(0.f, 1 - sqrt(pctX*pctX + (1-pctY)*(1-pctY)));
    float d2 = max(0.f, 1 - sqrt((1-pctX)*(1-pctX) + pctY*pctY));
    float d3 = max(0.f, 1 - sqrt((1-pctX)*(1-pctX) + (1-pctY)*(1-pctY)));
    
    float norm = d0 + d1 + d2 + d3;
    
    newVector = (d0*field[col][row] + d1*field[col][(row+1)%rows] + d2*field[(col+1)%cols][row] + d3*field[(col+1)%cols][(row+1)%rows])/norm;
    return newVector;
}
