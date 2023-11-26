//
//  Particle.hpp
//  flow field
//
//  Created by Tobias Arndt on 21.11.23.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include "ofMain.h"
#include "FlowField.hpp"

class Particle {
    int start_idx;
    std::vector<bool> isAttracted;
    ofColor color;
public:
    Particle(std::vector<ofVec3f> nodes, int start, ofColor color);
    Particle(ofVec3f pos, ofVec3f direction, int start);
    void move(std::vector<ofVec3f> nodes, unique_ptr<FlowField> &flow);//glm::vec2 dir);
    void draw();
    void stayOnScreen();
    bool isOffScreen();
    bool isDead();
    int getStartIdx();
    ofColor getColor();
    
    ofVec3f pos;
    ofVec3f direction;
    int duration;
    ofPolyline path;
    bool dead = false;
};

#endif /* Particle_hpp */
