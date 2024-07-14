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
    explicit ShoppingList(std::string name) : name(std::move(name)) {}

    void addItem(const Item& item);
    void removeItem(const std::string& name);
    void printDetails();
    int getNumItems() const;
    Item& getItem(std::string name);

    bool isInList(const Item& givenItem);

    void notify() override;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;

    std::string getName() const {return name;}
    std::vector<Item> getItems() const{return items;}

private:
    std::string name;
    std::vector<Item> items;
    std::list<Observer*> observers;
};


#endif //SHOPPINGLISTAPP_SHOPPINGLIST_H
