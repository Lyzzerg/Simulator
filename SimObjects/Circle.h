//
// Created by lyzzerg on 15.11.18.
//

#ifndef SIMPLEPHYSICSSIMULATION_CIRCLE_H
#define SIMPLEPHYSICSSIMULATION_CIRCLE_H

#include "SimObject.h"
#include <typeinfo>
#define DEFAULT_RAD 2

class Circle: public SimObject{
protected:
    double rad;
public:

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


    bool isIntersection(const SimObject* object) const override;

    Points getProjection(const Point* normal) const override;

    double get_rad() const { return rad; }

    void impulseBehavior(SimObject* object) override;

    explicit Circle(const Point& center, const double& rad_ = DEFAULT_RAD,
                    const Point& acceleration_=Point(0,0),
                    const double& weight_=DEFAULT_WEIGHT);
};
#endif //SIMPLEPHYSICSSIMULATION_CIRCLE_H
