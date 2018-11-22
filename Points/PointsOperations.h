//
// Created by lyzzerg on 21.11.18.
//

#ifndef SIMPLEPHYSICSSIMULATION_POINTSOPERATIONS_H
#define SIMPLEPHYSICSSIMULATION_POINTSOPERATIONS_H

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <cmath>

typedef std::pair<double, double> Point;
typedef std::vector<Point> Points;
enum turn_t {left = 1, right = -1, collinear = 0};

class PointsOperations {
public:
    static double square_dist(const Point& p0, const Point& p1, const Point& p2);
    static double length_squared(const Point& point);
    static double dot(const Point& point1, const Point& point2);
    static std::pair<Point,Point> findMaxdistPoints(const Points& proj);
    static double distSq(const Point& p1, const Point& p2);
    static void sortPointsByY(Points &points_);
    static bool isProjectionsIntersects(const Points &proj1, const Points &proj2);
    static bool checkPointIn(const std::pair<Point,Point>& vec, const Point& p);
    static double cross(const Point& a, const Point& b);
    static turn_t turn(const Point& a,const Point& b,const Point& c);
    static double euclidianNorm(const Point& vec);

    //i've already no time to make this, so.... RIP
    void countConvexHull();
};


#endif //SIMPLEPHYSICSSIMULATION_POINTSOPERATIONS_H
