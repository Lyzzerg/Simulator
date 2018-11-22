//
// Created by lyzzerg on 15.11.18.
//

#ifndef SIMPLEPHYSICSSIMULATION_SIMOBJECT_H
#define SIMPLEPHYSICSSIMULATION_SIMOBJECT_H

#include "../Points/PointsOperations.h"

#define DEFAULT_WEIGHT INT8_MAX


/*
 * IDEA:
 * find minimal convex hull
 * find all normals
 * find all perpendiculars to normals
 * find all projections to perpendiculars (in 2d it's lines)
 * if projection without intersections exists -> objects do not intersect;
 * */


#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QObject>

class SimObject: public QObject, public QGraphicsItem{
    Q_OBJECT
protected:
    Points points;
    Points convexHull;
    Point acceleration;
    double weight;

public:

    void defaultBehavior(const int &simulation_speed);
    virtual void impulseBehavior(SimObject *object)=0;

    virtual Points getProjection(const Point* normal) const;

    virtual bool isIntersection(const SimObject* object) const;
    virtual std::string reveal() const;

    Points getPoints() const { return points; }
    Points getConvexHull() const { return convexHull; }
    Point getAcceleration() const { return acceleration; }
    void setNewAcceleration(const Point& new_acc){acceleration=new_acc;}
    double getWeight() const { return weight; }

    void printCharacteristics() const;

public slots:
};


#endif //SIMPLEPHYSICSSIMULATION_SIMOBJECT_H
