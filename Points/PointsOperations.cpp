//
// Created by lyzzerg on 21.11.18.
//

#include "PointsOperations.h"

std::pair<Point, Point> PointsOperations::findMaxdistPoints(const Points &proj){
    double maxdist =0;
    std::pair<Point,Point> maxpoints(proj[0],proj[1]);
    for(int i=0; i<proj.size(); i++){
        for(int j=i+1; j<proj.size(); j++){
            double tmpdist = distSq(proj[i], proj[j]);
            if(tmpdist>maxdist){
                maxdist = tmpdist;
            }
            maxpoints.first = proj[i];
            maxpoints.second = proj[j];
        }
    }
    return maxpoints;
}

double PointsOperations::distSq(const Point &p1, const Point &p2) {
    return (p1.first - p2.first)*(p1.first - p2.first) +
           (p1.second - p2.second)*(p1.second - p2.second);
}

void PointsOperations::sortPointsByY(Points &points_) {
    std::sort(points_.begin(),points_.end(),[](const Point& a, const Point& b)->bool{
        return a.second<b.second;
    });
}

bool PointsOperations::isProjectionsIntersects(const Points &proj1, const Points &proj2) {
    auto maxdistp1 = findMaxdistPoints(proj1);
    auto maxdistp2 = findMaxdistPoints(proj2);
    return checkPointIn(maxdistp1,maxdistp2.first)||checkPointIn(maxdistp1, maxdistp2.second);
}

bool PointsOperations::checkPointIn(const std::pair<Point, Point> &vec, const Point &p) {
    double eps = 1e-3;
    return fabs((p.first - vec.first.first) * (vec.second.second - vec.first.second) -
                (p.second-vec.first.second)*(vec.second.first-vec.first.first)) <= eps;
}

double PointsOperations::dot(const Point &point1, const Point &point2) {
    return (point1.first)*(point2.first)+(point1.second)*(point2.second);
}

double PointsOperations::length_squared(const Point &point) {
    return (point.first)*(point.first)+(point.second)*(point.second);
}

double PointsOperations::square_dist(const Point &p0, const Point &p1, const Point &p2) {
    return pow((p2.second-p1.second)*p0.first-(p2.first-p1.first)*p0.second+p2.first*p1.second-p2.second*p1.first,
               2)/(pow(p2.second-p1.second,2)+pow(p2.first-p1.first,2));
}

double PointsOperations::cross(const Point &a, const Point &b) {
    return a.first*b.second-b.first*a.second;
}

turn_t PointsOperations::turn(const Point &a, const Point &b, const Point &c) {
    double det = PointsOperations::cross(Point(b.first-a.first, b.second-a.second),
                                         Point(c.first-a.first, c.second-a.second));
    if(det>0){
        return left;
    }
    if(det<0){
        return right;
    }
    return collinear;
}
