//
// Created by lyzzerg on 15.11.18.
//

#include "SimObject.h"

void SimObject::impulseBehavior(SimObject *object) {
    double speed1 = sqrt(pow(acceleration.first,2)+pow(acceleration.second,2));
    double speed2 = sqrt(pow(object->getAcceleration().first,2)+pow(object->getAcceleration().second,2));

    Point acc_norm1 = Point(acceleration.first/speed1,acceleration.second/speed1);
    Point acc_norm2 = Point(object->getAcceleration().first/speed2, object->getAcceleration().second/speed2);


    double speed1_new =  (2* object->getWeight()*speed2+speed1*(weight- object->getWeight()))
                         /
                         (weight + object->getWeight());
    double speed2_new =  (2*weight*speed1+speed2*(object->getWeight()-weight))
                         /
                         (weight + object->getWeight());



    Points obj_p = object->getPoints();
    if (this->weight == INT8_MAX && obj_p.size()==1) { //wall+circle
        if ((points[2].second < obj_p[0].second && points[3].second < obj_p[0].second) ||
            (points[0].second > obj_p[0].second && points[1].second > obj_p[0].second)) {
            acc_norm2 = Point(acc_norm2.first, -acc_norm2.second);
        } else if ((points[1].first < obj_p[0].first && points[3].first < obj_p[0].first) ||
                   (points[0].first > obj_p[0].first && points[2].first > obj_p[0].first)) {
            acc_norm2 = Point(-acc_norm2.first, acc_norm2.second);
        }
    } else if(this->weight!=INT8_MAX && obj_p.size()==1) {//rect+circle
        Point tmp = acc_norm1;
        acc_norm1 = acc_norm2;
        acc_norm2 = tmp;

    } else if(object->getWeight() == INT8_MAX && points.size()!=1){//rect+wall
        if ((points[0].first<obj_p[0].first)&&(points[2].first<obj_p[0].first)){
            acc_norm1 = Point(-acc_norm1.first, acc_norm1.second);
        } else if((points[2].second>obj_p[0].second)&&(points[3].second>obj_p[0].second)){
            acc_norm1 = Point(acc_norm1.first, -acc_norm1.second);
        }
    } else if(object->getWeight() != INT8_MAX && weight!= INT8_MAX &&
                obj_p.size()!=1 && points.size()!=1){
        Point tmp = acc_norm1;
        acc_norm1 = acc_norm2;
        acc_norm2 = tmp;
    }

    if(this->weight != INT8_MAX && object->weight!=INT8_MAX) {
        this->setNewAcceleration(Point((acc_norm1.first * speed1_new), (acc_norm1.second * speed1_new)));
        object->setNewAcceleration(Point((acc_norm2.first * speed2_new), (acc_norm2.second * speed2_new)));
    }else if(this->weight == INT8_MAX){
        object->setNewAcceleration(Point((acc_norm2.first * speed2), (acc_norm2.second * speed2)));
    } else if(object->weight == INT8_MAX){
        this->setNewAcceleration(Point((acc_norm1.first * speed1), (acc_norm1.second * speed1)));
    }
    this->defaultBehavior(10);
    object->defaultBehavior(10);


    /*
     * HOW TO FIND
     * NEW
     * FUCKING
     * ACC_NORM VECTORS?
     * DAT'S DA QUESTION
     * DO U KNOW DA WEI?
     * */
}


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
