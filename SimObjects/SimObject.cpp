//
// Created by lyzzerg on 15.11.18.
//

#include "SimObject.h"

void SimObject::defaultBehavior(const int &simulation_speed) {
    for(auto& point:points){
        point.first+=acceleration.first/simulation_speed;
        point.second+=acceleration.second/simulation_speed;
    }
    //printCharacteristics();
}

bool SimObject::isIntersection(const SimObject *object) const {
    //so we gonna take both convexHulls
    //take normals from first
    bool result = true;
    for(int i=1; i<this->convexHull.size(); i++){
        Point normal(this->convexHull[i-1].second-this->convexHull[i].second,
                     this->convexHull[i].first-this->convexHull[i-1].first);
        Points projection1 = this->getProjection(&normal);
        Points projection2 = object->getProjection(&normal);
        result = PointsOperations::isProjectionsIntersects(projection1, projection2);
        if(!result){
            return result;
        }
    }
    return result;
}

Points SimObject::getProjection(const Point *normal) const {
    Points projection;
    for(auto& point: convexHull){
        double tmp = PointsOperations::dot(point,*normal)/PointsOperations::length_squared(point);
        projection.push_back(Point(point.first*tmp, point.second*tmp));
    }
    return projection;
}

std::string SimObject::reveal() const {
    return typeid(*this).name();
}

void SimObject::printCharacteristics() const {
    std::cout<<"Pos: "<<std::endl;
    for(auto& point: points){
        std::cout << point.first << " " << point.second << std::endl;
    }
    std::cout<<"Acc "<<acceleration.first<<" "<<acceleration.second<<std::endl;
    std::cout<<"Weight "<<weight<<std::endl<<std::endl;
}

std::pair<double,double> SimObject::countNewSpeeds(const double &th_speed, const double &obj_speed,
        const double& th_weight, const double& obj_weight) {
    double s1 = (2 * obj_weight * obj_speed + th_speed * (th_weight - obj_weight))
    /
    (th_weight + obj_weight);
    double s2 = (2 * th_weight * th_speed + obj_speed * (obj_weight - th_weight))
                        /
                        (th_weight + obj_weight);
    return {s1,s2};
}
