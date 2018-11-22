//
// Created by lyzzerg on 22.11.18.
//

#include "Simulator.h"

Simulator::Simulator(const unsigned int &fieldsizex_, const unsigned int &fieldsizey_) {
    field.push_back(new Rectangle(Point(fieldsizex_/2,-1),fieldsizex_,1));
    field.push_back(new Rectangle(Point(fieldsizex_/2,fieldsizey_+1),fieldsizex_,1));
    field.push_back(new Rectangle(Point(-1,fieldsizey_/2),1,fieldsizey_));
    field.push_back(new Rectangle(Point(fieldsizex_+1,fieldsizey_/2),1,fieldsizey_));
}

void Simulator::simulate() {
    for(auto& object:objects){
        for(auto& wall:field){
            if((object)->isIntersection(wall)){
                (object)->impulseBehavior(wall);
            }
        }
        for(auto& object2: objects){
            if(object==object2){
                continue;
            } else if((object)->isIntersection(object2)){
                (object)->impulseBehavior(object2);
            }
        }
        (object)->defaultBehavior(DEFAULT_SIMULATION_SPEED);
    }
    emit objects_moved();
}
