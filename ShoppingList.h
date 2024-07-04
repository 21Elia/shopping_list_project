//
// Created by Elia Awad on 04/07/24.
//

#ifndef SHOPPINGLISTAPP_SHOPPINGLIST_H
#define SHOPPINGLISTAPP_SHOPPINGLIST_H

#include "Item.h"
#include "Subject.h"
#include <list>
#include <memory>

class ShoppingList : public Subject {
public:

    void addItem(const Item& item);
    void removeItem(const std::string& name);
    void printDetails();

    bool isInList(const Item& givenItem);

    void notify() override;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;

private:
    std::vector<Item> items;
    std::list<Observer*> observers;
};


#endif //SHOPPINGLISTAPP_SHOPPINGLIST_H
