//
// Created by lyzzerg on 22.11.18.
//

#include "Circle.h"

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawEllipse(QPoint(static_cast<int>(points[0].first), static_cast<int>(points[0].second)),
                         static_cast<int>(rad), static_cast<int>(rad));
}

bool Circle::isIntersection(const SimObject *object) const {
    if(object->getPoints().size()==1){ //CIRCLE + CIRCLE
        double distance = sqrt(pow((points[0].first-object->getPoints()[0].first),2)+
                               pow((points[0].second-object->getPoints()[0].second),2));
        return distance<=(this->get_rad()+ dynamic_cast<const Circle*>(object)->get_rad());
    } else {
        return object->isIntersection(this);
    }
}

Points Circle::getProjection(const Point *normal) const {
    Points projection;
    for(auto& point: convexHull){
        double tmp = PointsOperations::dot(point,*normal)/PointsOperations::length_squared(point);
        projection.push_back(Point(point.first*tmp-rad, point.second*tmp-rad));
        projection.push_back(Point(point.first*tmp+rad, point.second*tmp+rad));
    }
    return projection;
}

void Circle::impulseBehavior(SimObject *object) {
    if(object->reveal()== typeid(Circle).name()){
        double speed1 = PointsOperations::euclidianNorm(acceleration);
        double speed2 = PointsOperations::euclidianNorm(object->getAcceleration());

        auto speeds_new = countNewSpeeds(speed1,speed2,weight,object->getWeight());

        Points obj_points = object->getPoints();
        double speed3;

        Point norm1 = Point(points[0].first-obj_points[0].first,points[0].second-obj_points[0].second);
        speed3 = sqrt(pow(norm1.first,2)+pow(norm1.second,2));
        norm1 = Point(norm1.first/speed3, norm1.second/speed3);
        Point norm2 = Point(-points[0].first+obj_points[0].first,-points[0].second+obj_points[0].second);
        speed3 = sqrt(pow(norm2.first,2)+pow(norm2.second,2));
        norm2 = Point(norm2.first/speed3, norm2.second/speed3);


        if (this->weight != INT8_MAX && object->getWeight() != INT8_MAX) {
            this->setNewAcceleration(Point((norm1.first * speeds_new.first), (norm1.second * speeds_new.first)));
            object->setNewAcceleration(Point((norm2.first * speeds_new.second), (norm2.second * speeds_new.second)));
        } else if (this->weight == INT8_MAX) {
            object->setNewAcceleration(Point((norm2.first * speed2), (norm2.second * speed2)));
        } else if (object->getWeight() == INT8_MAX) {
            this->setNewAcceleration(Point((norm1.first * speed1), (norm1.second * speed1)));
        }
        this->defaultBehavior(10);
        object->defaultBehavior(10);
    } else{
        object->impulseBehavior(this);
    }
}

Circle::Circle(const Point &center, const double &rad_, const Point &acceleration_, const double &weight_) {
    points.push_back(center);
    convexHull.push_back(Point(center.first-rad_,center.second-rad_));
    convexHull.push_back(Point(center.first+rad_,center.second-rad_));
    convexHull.push_back(Point(center.first-rad_,center.second+rad_));
    convexHull.push_back(Point(center.first+rad_,center.second+rad_));
    acceleration = acceleration_;
    weight = weight_;
    rad=rad_;
    setFlag(ItemIsMovable);
}

QRectF Circle::boundingRect() const {
    qreal penWidth = 1;
    return QRectF(QRect(QPoint(static_cast<int>(points[0].first - rad - penWidth/2),
                               static_cast<int>(points[0].second - rad - penWidth/2)),
                        QSize(static_cast<int>(rad * 2+penWidth/2), static_cast<int>(rad * 2+penWidth/2))));
}
