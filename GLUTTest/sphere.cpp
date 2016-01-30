//
//  sphere.cpp
//  freegluttest
//
//  Created by Adam Hunter on 1/13/16.
//  Copyright © 2016 Adam Hunter. All rights reserved.
//

#include "sphere.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

const float DegreesToRadians = M_PI / 180.0;

point3 one;
point3  two;
point3  three;

point3 quad_data[684];

point3 *getSphere() {
    return &quad_data[0];
}

int getSphereCount() {
    return 684;
}

//Need duplicates of the vertices
void buildSphere() {
    int k = 0;
	//float x;
	//float y;
	//float z;
	//x = 2.0; y = 2.0; z = 2.0;
	//for (int i = 0; i < 10; i++) {
	//	quad_data[0] = { x,y,z};
	//	quad_data[1] = { 0,4,0};
	//	quad_data[2] = { 0,0,0};

	//	quad_data[3] = { 4,0,0 };
	//	quad_data[4] = { 0,0,0 };
	//	quad_data[5] = { 2,2,2 };

	//	quad_data[6] = { x,y,z };
	//	quad_data[7] = { 0,4,0 };
	//	quad_data[8] = { 0,4,4 };

	//	//quad_data[2] = { 4,0,0 };
	//	x+=2.0; 
	//	y+=2.0; 
	//	z+=2.0;

	//}
    for(float phi = -240.0; phi <= 240.0; phi += 60.0) {
        float phir = phi * DegreesToRadians;
        float phir20 = (phi + 20.0) * DegreesToRadians;
		float phir40 = (phi + 40.0) * DegreesToRadians;
		float phir60 = (phi + 60.0) * DegreesToRadians;
        for(float theta = -540.0; theta <= 540.0; theta += 20.0) {
            float thetar = theta * DegreesToRadians;
            quad_data[k] = point3(sin(thetar) * cos(phir),
                                  cos(thetar) * cos(phir),
                                  sin(phir));
            k++;
            quad_data[k] = point3(sin(thetar) * cos(phir20),
                                  cos(thetar) * cos(phir20),
                                  sin(phir20));
            k++;

			quad_data[k] = point3(sin(thetar) * cos(phir),
				cos(thetar) * cos(phir),
				sin(phir));
			one = quad_data[k];
			k++;
			quad_data[k] = point3(sin(thetar) * cos(phir20),
				cos(thetar) * cos(phir20),
				sin(phir20));
			k++;
			quad_data[k] = point3(sin(thetar) * cos(phir40),
				cos(thetar) * cos(phir40),
				sin(phir40));
			k++;
			quad_data[k] = point3(sin(thetar) * cos(phir60),
				cos(thetar) * cos(phir60),
				sin(phir60));
			three = quad_data[k];
			k++;
        }
    }



}

