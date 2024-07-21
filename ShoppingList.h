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
    explicit ShoppingList(std::string name, int ID = 1) : name(std::move(name)), ID(ID), shared(false){}

    void addItem(const Item& item);
    void removeItem(const std::string& itemName);
    int getNumItems() const;
    void printDetails();

    bool isInItems(const Item& givenItem);

    void notify() override;
    void subscribe(Observer* o) override;
    void unsubscribe(Observer* o) override;

    std::string getName() const {return name;}
    std::vector<Item> getItems() const{return items;}
    Item& getItem(std::string itemName);
    int getID() const {return ID;}
    void setID(int num) { ID = num;}
    bool isShared() const {return shared;}
    void setShared(bool value) { shared = value;}

private:
    int ID;
    bool shared;
    std::string name;
    std::vector<Item> items;
    std::list<Observer*> observers;
};


#endif //SHOPPINGLISTAPP_SHOPPINGLIST_H
