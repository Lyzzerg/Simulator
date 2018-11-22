//
// Created by lyzzerg on 15.11.18.
//

#ifndef SIMPLEPHYSICSSIMULATION_RECTANGLE_H
#define SIMPLEPHYSICSSIMULATION_RECTANGLE_H

#include "SimObject.h"
#include "Circle.h"
#define DEFAULT_SIZE 2


class Rectangle: public SimObject{
public:

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    bool isIntersection(const SimObject* object) const override;

    explicit Rectangle(const Point& center_,const double& width_ = DEFAULT_SIZE, const double& height_=DEFAULT_SIZE,
            const Point& acceleration_= Point(0,0), const double& weight_=DEFAULT_WEIGHT);
};

#endif //SIMPLEPHYSICSSIMULATION_RECTANGLE_H
