//
//  sphere.hpp
//  freegluttest
//
//  Created by Adam Hunter on 1/13/16.
//  Copyright © 2016 Adam Hunter. All rights reserved.
//

#ifndef sphere_hpp
#define sphere_hpp

#include <stdio.h>

struct point3
{
    float x, y, z;        //Vertex
    
    point3() {}
    point3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

void buildSphere();
point3 *getSphere();
int getSphereCount();

#endif /* sphere_hpp */
