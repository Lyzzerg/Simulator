//
// Created by lyzzerg on 22.11.18.
//

#ifndef SIMPLEPHYSICSSIMULATION_SIMULATORV_H
#define SIMPLEPHYSICSSIMULATION_SIMULATORV_H

#include <list>
#include "../SimObjects/SimObject.h"
#include "../SimObjects/Rectangle.h"
#include <thread>
#include <mutex>
#include <QTimer>
#include <QObject>
#include <QGraphicsView>
#define DEFAULT_SIMULATION_SPEED 10
#define DEFAULT_SIMULATION_SIZE 500

class Simulator: public QObject {
Q_OBJECT
protected:
    std::list<SimObject*> field;
    std::list<SimObject*> objects;
public:
    std::list<SimObject*> getField(){
        return field;
    }
    std::list<SimObject*> getObjects(){
        return objects;
    }

    void add_object_to_simulation(SimObject *object){
        objects.push_back(object);
    }
    void remove_object_from_simulation(SimObject *object){
        objects.remove(object);
    }

    explicit Simulator(const unsigned int& fieldsizex_ = DEFAULT_SIMULATION_SIZE,
                       const unsigned int& fieldsizey_ = DEFAULT_SIMULATION_SIZE);

signals:
    void objects_moved();
public slots:
    void simulate();
};


#endif //SIMPLEPHYSICSSIMULATION_SIMULATORV_H
