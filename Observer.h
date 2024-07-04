//
// Created by Elia Awad on 04/07/24.
//

#ifndef SHOPPINGLISTAPP_OBSERVER_H
#define SHOPPINGLISTAPP_OBSERVER_H


class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};


#endif //SHOPPINGLISTAPP_OBSERVER_H
