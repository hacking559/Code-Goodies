#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#pragma one
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

const double eps = 1e-14;
const double INFI = 1e14;

struct Point {
	double x, y;
};

inline double distance (const Point& A, const Point& B) {
	return sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
}

inline bool isVertical (const Point& A, const Point& B) {
	return fabs(A.x - B.x) < eps;
}

inline bool isHorizontal (const Point& A, const Point& B) {
	return fabs(A.y - B.y) < eps;
}
inline double slope(const Point& A, const Point& B) {
	if (isVertical(A, B))
		return INFI;
	return (B.y - A.y) / (B.x - A.x);
}

inline double crossProduct (const Point& A, const Point& B, const Point& C) {
	return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x);
}

inline int orientation (const Point& A, const Point& B, const Point& C) {

	// 0 - collinear
	// 1 - trigonometrical order: A, B, C
	// -1 - clockwise order: A, B, C

	double cp = crossProduct(A, B, C);

	if(fabs(cp) < eps)
		return 0;

	if (cp >= eps)
		return 1;

	return -1;
}

inline double area (const Point& A, const Point& B, const Point& C) {

	double cp = fabs(crossProduct(A, B, C));
	return cp * 0.5;
}

inline bool point_in_box(const Point& A, const Point& B, const Point& C) {

	Point left, right;

	left.x = min(A.x, B.x);
	left.y = min(A.y, B.y);

	right.x = max(A.x, B.x);
	right.y = max(A.y, B.y);

	return ( (C.x >= left.x and C.x <= right.x) and (C.y >= left.y and C.y <= right.y) );
}



inline int straightIntersection (const Point& p1, const Point& p2, const Point& p3, const Point& p4, Point& I ) {

	// -1 same line
	// 0 parallel
	// 1 concurente

	double a1, a2, b1, b2, c1, c2;

	// coeficients
	a1 = p1.y - p2.y;
	b1 = p2.x - p1.x;
	c1 = p1.x * p2.y - p2.x * p1.y;

	a2 = p3.y - p4.y;
	b2 = p4.x - p3.x;
	c2 = p3.x * p4.y - p4.x * p3.y;

	if (fabs(a1 * b2 - a2 * b1) < eps) {
		if (fabs(a1 * c2 - a2 * c1) < eps and fabs(b1 * c2 - b2 * c1) < eps) {
			return -1;
		}  
		return 0;
	}

	I.x =  (-c1 * b2 + c2 * b1) / (a1 * b2 - a2 * b1);
	I.y =  (-a1 * c2 + a2 * c1) / (a1 * b2 - a2 * b1);

	return 1;
}

#endif
