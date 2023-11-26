//
//  FlowField.hpp
//  flow field
//
//  Created by Tobias Arndt on 21.11.23.
//

#ifndef FlowField_hpp
#define FlowField_hpp
#include <stdio.h>
#include "ofMain.h"
class FlowField {
public:
    FlowField(int r);
    ~FlowField();
    void setup();
    void display();
    ofVec2f getVectorInterpolated(ofVec2f pos);
private:
    int cols, rows;
    int resolution;
    float xoff, yoff;
    std::vector<std::vector<ofVec2f>> field;
};
#endif /* FlowField_hpp */
