//
// Created by lyzzerg on 22.11.18.
//

#include "Rectangle.h"

QRectF Rectangle::boundingRect() const {
    qreal penWidth = 1;
    return QRectF(QRect(QPoint(static_cast<int>(points[0].first-penWidth/2),
                               static_cast<int>(points[0].second-penWidth/2)),
                        QPoint(static_cast<int>(points[3].first+penWidth/2),
                               static_cast<int>(points[3].second+penWidth/2))));
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawRect(QRect(QPoint(static_cast<int>(points[0].first), static_cast<int>(points[0].second)),
                            QPoint(static_cast<int>(points[3].first), static_cast<int>(points[3].second))));
}

Rectangle::Rectangle(const Point &center_, const double &width_, const double &height_, const Point &acceleration_,
                     const double &weight_) {
    points.push_back(Point(center_.first-width_/2,center_.second-height_/2)); //[0] ax
    points.push_back(Point(center_.first+width_/2,center_.second-height_/2)); // [1]
    points.push_back(Point(center_.first-width_/2,center_.second+height_/2)); // [2]
    points.push_back(Point(center_.first+width_/2,center_.second+height_/2)); //[3] ax1

    convexHull.push_back(points[0]);
    convexHull.push_back(points[1]);
    convexHull.push_back(points[2]);
    convexHull.push_back(points[3]);

    acceleration = acceleration_;
    weight = weight_;
    setFlag(ItemIsMovable);
}

bool Rectangle::isIntersection(const SimObject *object) const {
    //RectRect
    if(object->reveal() == typeid(Rectangle).name()){
        Points obj_points = object->getPoints();
        Point fp0,fp1;
        fp0=fp1=points[0];
        Point sp0,sp1;
        sp0=sp1=obj_points[0];

        for(int i=0; i<4; i++){
            if(points[i].first<=fp0.first && points[i].second<=fp0.second){
                fp0=points[i];
            }
            if(points[i].first>=fp1.first && points[i].second>=fp1.second){
                fp1=points[i];
            }
            if(obj_points[i].first<=sp0.first && obj_points[i].second<=sp0.second){
                sp0=obj_points[i];
            }
            if(obj_points[i].first>=sp1.first && obj_points[i].second>=sp1.second){
                sp1=obj_points[i];
            }
        }
        return(
                      (
                              (
                                      ( fp0.first>=sp0.first && fp0.first<=sp1.first )||( fp1.first>=sp0.first && fp1.first<=sp1.first  )
                              ) && (
                                      ( fp0.second>=sp0.second && fp0.second<=sp1.second )||( fp1.second>=sp0.second && fp1.second<=sp1.second )
                              )
                      )||(
                              (
                                      ( sp0.first>=fp0.first && sp0.first<=fp1.first )||( sp1.first>=fp0.first && sp1.first<=fp1.first  )
                              ) && (
                                      ( sp0.second>=fp0.second && sp0.second<=fp1.second )||( sp1.second>=fp0.second && sp1.second<=fp1.second )
                              )
                      )
              )||(
                      (
                              (
                                      ( fp0.first>=sp0.first && fp0.first<=sp1.first )||( fp1.first>=sp0.first && fp1.first<=sp1.first  )
                              ) && (
                                      ( sp0.second>=fp0.second && sp0.second<=fp1.second )||( sp1.second>=fp0.second && sp1.second<=fp1.second )
                              )
                      )||(
                              (
                                      ( sp0.first>=fp0.first && sp0.first<=fp1.first )||( sp1.first>=fp0.first && sp1.first<=fp1.first  )
                              ) && (
                                      ( fp0.second>=sp0.second && fp0.second<=sp1.second )||( fp1.second>=sp0.second && fp1.second<=sp1.second )
                              )
                      )
              );

    } else{
        //RectCircle
        bool res = true;
        Point p0=object->getPoints()[0];
        double rad = dynamic_cast<const Circle*>(object)->get_rad();


        //find ON X projection
        double rect_x0 = points[0].first;
        double rect_x1 = points[1].first;
        double circle_x0 = p0.first-rad;
        double circle_x1 = p0.first+rad;

        if((circle_x0<rect_x0 && circle_x1<rect_x0)||(circle_x0>rect_x1 && circle_x1>rect_x1)){
            res = false;
        }

        //find ON Y projection
        double rect_y0 = points[0].second;
        double rect_y1 = points[2].second;
        double circle_y0 = p0.second-rad;
        double circle_y1 = p0.second+rad;

        if((circle_y0<rect_y0 && circle_y1<rect_y0)||(circle_y0>rect_y1 && circle_y1>rect_y1)){
            res = false;
        }
        return res;
    }

}
