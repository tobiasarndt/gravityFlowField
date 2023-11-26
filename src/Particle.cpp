//
//  Particle.cpp
//  flow field
//
//  Created by Tobias Arndt on 21.11.23.
//

#include "Particle.hpp"
#include <glm/gtx/string_cast.hpp>

Particle::Particle(std::vector<ofVec3f> nodes, int start, ofColor color):start_idx(start), color(color){
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::bernoulli_distribution d(0.3);
    for(int i=0; i<nodes.size(); i++) {
        bool x = d(gen);
        if(i == start_idx){
            isAttracted.push_back(true);
        } else {
            isAttracted.push_back(x);
        }
    }
    pos = nodes[start_idx];
    pos += ofVec3f(0.5, 0, 0).rotate(ofRandom(360), ofVec3f(0,0,1));
    direction = ofVec3f(0, 0, 0);
    duration = 0;
    path.curveTo(pos);
}

Particle::Particle(ofVec3f pos, ofVec3f direction, int start) :
    start_idx(start), pos(pos), direction(direction){
    path.curveTo(pos);
}

void Particle::move(std::vector<ofVec3f> nodes, unique_ptr<FlowField> &flow){//glm::vec2 dir){
    if (dead) return;
    ofVec3f force(0, 0, 0);
    int i=0;
    for (ofVec3f &node: nodes)
    {
        if (isAttracted[i]) {
            int sign = i == start_idx ? -0.8 : 1;
            double distance = node.distance(pos);
            if (distance < 5 && sign > 0) {
                dead = true;
                path.curveTo(node);
                path.curveTo(node);
                path.curveTo(node);
                path.simplify(0.001);
                path = path.getSmoothed(5);
                return;
            }
            if (distance < 30 && sign > 0) {
                direction *= 1;
            }
            ofVec3f dir = node - pos;
            dir.normalize();
            force += 10000 * (dir)/(std::pow(distance,3)+0.1) * sign;
        }
        i++;
    }
    ofVec2f random_force = flow->getVectorInterpolated(pos);
    random_force.limit(0.15*force.length());
    force.x += random_force.x;
    force.y += random_force.y;
    
    force.normalize();
    
    double stepsize = 1 - abs(direction.angle(force) / 180);
    direction += force;
    direction.limit(5);
    pos += direction/15; //* (stepsize + 0.1)/10;
    path.curveTo(pos.x, pos.y);
    if (isOffScreen()) stayOnScreen();
}

void Particle::draw(){
    duration ++;
    ofSetColor(color);
    path.draw();
}

void Particle::stayOnScreen(){
    dead = true;
}

bool Particle::isOffScreen(){
    return !dead && (pos.x < 0 || pos.x >= ofGetWidth() || pos.y < 0 || pos.y >= ofGetHeight());
}

bool Particle::isDead(){
    return duration >= 10000;
}

int Particle::getStartIdx(){
    return(start_idx);    
}

ofColor Particle::getColor(){
    return(color);
}
