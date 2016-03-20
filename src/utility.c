

/************************************************************************************
	Utility functions for our Geometric Cube Rotation problem
	Author:             Ashis Kumar Das
	ID:                 11301002
	Email:              akd.bracu@gmail.com
*************************************************************************************/



#include <math.h>



struct cube_ {
	
	float x0, y0;
	float x1, y1;
	float x2, y2;
	float x3, y3;
	
	float x4, y4;
	float x5, y5;
	float x6, y6;
	float x7, y7;
	
};


void util_calculateCoordinates(struct cube_ *pCube);

void util_rotateCoordinates(struct cube_ *pCube, float fAngle);







void util_calculateCoordinates(struct cube_ *pCube) {
	
	pCube->x4 = pCube->x2;
	pCube->y4 = pCube->y0;
	pCube->x5 = pCube->x0;
	pCube->y5 = pCube->y2;
	pCube->x6 = pCube->x3;
	pCube->y6 = pCube->y1;
	pCube->x7 = pCube->x1;
	pCube->y7 = pCube->y3;
	
	return;
}


void util_rotateCoordinates(struct cube_ *pCube, float fAngle) {
	
	float x0, y0, x1, y1, x2, y2, x3, y3;
	float x4, y4, x5, y5, x6, y6, x7, y7;
	
	x0 = pCube->x0;
	y0 = pCube->y0;
	x1 = pCube->x1;
	y1 = pCube->y1;
	
	x2 = pCube->x2;
	y2 = pCube->y2;
	x3 = pCube->x3;
	y3 = pCube->y3;
	
	x4 = pCube->x4;
	y4 = pCube->y4;
	x5 = pCube->x5;
	y5 = pCube->y5;
	
	x6 = pCube->x6;
	y6 = pCube->y6;
	x7 = pCube->x7;
	y7 = pCube->y7;
	
	pCube->x0 = (x0 * cosf(fAngle) - y0 * sinf(fAngle));
	pCube->y0 = (x0 * sinf(fAngle) + y0 * cosf(fAngle));
	pCube->x1 = (x1 * cosf(fAngle) - y1 * sinf(fAngle));
	pCube->y1 = (x1 * sinf(fAngle) + y1 * cosf(fAngle));
	
	pCube->x2 = (x2 * cosf(fAngle) - y2 * sinf(fAngle));
	pCube->y2 = (x2 * sinf(fAngle) + y2 * cosf(fAngle));
	pCube->x3 = (x3 * cosf(fAngle) - y3 * sinf(fAngle));
	pCube->y3 = (x3 * sinf(fAngle) + y3 * cosf(fAngle));
	
	pCube->x4 = (x4 * cosf(fAngle) - y4 * sinf(fAngle));
	pCube->y4 = (x4 * sinf(fAngle) + y4 * cosf(fAngle));
	pCube->x5 = (x5 * cosf(fAngle) - y5 * sinf(fAngle));
	pCube->y5 = (x5 * sinf(fAngle) + y5 * cosf(fAngle));
	
	pCube->x6 = (x6 * cosf(fAngle) - y6 * sinf(fAngle));
	pCube->y6 = (x6 * sinf(fAngle) + y6 * cosf(fAngle));
	pCube->x7 = (x7 * cosf(fAngle) - y7 * sinf(fAngle));
	pCube->y7 = (x7 * sinf(fAngle) + y7 * cosf(fAngle));
	
	return;
}
