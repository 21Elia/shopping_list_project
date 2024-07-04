//
// Created by Elia Awad on 04/07/24.
//

#ifndef SHOPPINGLISTAPP_SUBJECT_H
#define SHOPPINGLISTAPP_SUBJECT_H

#include "Observer.h"

class Subject {
public:
    virtual void notify() = 0;
    virtual void subscribe(Observer* o) = 0;
    virtual void unsubscribe(Observer* o) = 0;
};


#endif //SHOPPINGLISTAPP_SUBJECT_H
