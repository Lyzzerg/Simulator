#include <iostream>
#include "Simulator/Simulator.h"
#include "SimObjects/Circle.h"
#include "SimObjects/Rectangle.h"
#include <thread>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QObject>
#include <QThread>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    auto *scene = new QGraphicsScene();

    Simulator *simulator = new Simulator();

    simulator->add_object_to_simulation(new Circle(Point(100,100),15, Point(1,0),15));
    simulator->add_object_to_simulation(new Circle(Point(150,110),10, Point(0,1),10));
    simulator->add_object_to_simulation(new Circle(Point(200,120),5, Point(1,0),5));
    simulator->add_object_to_simulation(new Circle(Point(250,130),15, Point(1,1),15));
    simulator->add_object_to_simulation(new Circle(Point(300,140),10, Point(0,-1),10));
    simulator->add_object_to_simulation(new Circle(Point(350,150),5, Point(-1,0),5));

    simulator->add_object_to_simulation(new Rectangle(Point(200,340),40,40,Point(1,1),20));
   simulator->add_object_to_simulation(new Rectangle(Point(400,360),40,40,Point(-1, 0),10));
    simulator->add_object_to_simulation(new Rectangle(Point(400,300),5,5,Point(0, -1),5));

   // simulator->add_object_to_simulation(new Circle(Point(400,160),15, Point(-1,-1),15));
  //  simulator->add_object_to_simulation(new Circle(Point(450,170),10, Point(1,2),10));
   // simulator->add_object_to_simulation(new Circle(Point(50,180),5, Point(2,1),5));

    simulator->add_object_to_simulation(new Rectangle(Point(200,200),5,5,Point(0,-1),5));
    simulator->add_object_to_simulation(new Rectangle(Point(200,250),10,10,Point(0, 1),10));
    simulator->add_object_to_simulation(new Rectangle(Point(200,300),15,15,Point(0, 1),15));


    for(auto& wall:simulator->getField()){
        scene->addItem(wall);
    }
    for(auto& object:simulator->getObjects()){
        scene->addItem(object);
    }
    auto * view = new QGraphicsView(scene);
    QTimer *timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),simulator,SLOT(simulate()));
    view->show();
    timer->start(1);
    QObject::connect(simulator,SIGNAL(objects_moved()),scene,SLOT(update()));
    //Circle *circle2 = new Circle(Point(3,3),1, Point(4,4),10);
    //Rectangle *rectangle1 = new Rectangle();
    //simulator->add_object_to_simulation(circle2);
    //simulator->add_object_to_simulation(rectangle1);
    //simulator->start_simulation();
    //simulator->remove_object_from_simulation(rectangle1);
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //simulator->stop_simulation();
    return a.exec();
}