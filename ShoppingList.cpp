//
// Created by Elia Awad on 04/07/24.
//

#include "ShoppingList.h"

void ShoppingList::addItem(const Item &item) {
    if(isInList(item)) {
        Item& existingItem = getItem(item.getName());
        if(existingItem.isChecked()) {
            existingItem.setCheck(false);
            existingItem.setQuantity(item.getQuantity());
        }else
            existingItem.setQuantity(existingItem.getQuantity() + item.getQuantity());
    }
    else
        items.push_back(item);
}

void ShoppingList::removeItem(const std::string& name) {
    auto it = items.begin();
    while(it != items.end()) {
        if( (*it).getName() == name ) {
            break;
        }
        it++;
    }
    if(it != items.end()) {
        items.erase(it);
        notify();
    }else
        throw std::invalid_argument("Item not found. Try again.");
}

void ShoppingList::printDetails() {
    std::cout << "------SOPPING LIST------" << "\n"<< std::endl;
    for(const auto& item : items) {
        std::cout << item.getName() << ": " << item.getQuantity() << "\n" << std::endl;
    }
    std::cout << "Total Items: " << getNumItems() << std::endl;
}

bool ShoppingList::isInList(const Item &givenItem) {
    bool found = false;
    for(const auto& item : items) {
        if(givenItem.getName() == item.getName())
            found = true;
    }
    return found;
}

void ShoppingList::notify() {
    for(const auto& observer : observers)
        observer->update();
}

void ShoppingList::subscribe(Observer *o) {
    observers.push_back(o);
}

void ShoppingList::unsubscribe(Observer *o) {
    observers.remove(o);
}

int ShoppingList::getNumItems() const {
    int total = 0;
    for(const auto& item : items){
        total += item.getQuantity();
    }
    return total;
}

Item& ShoppingList::getItem(std::string name) {
    auto it = items.begin();
    while(it != items.end()) {
        if(name == (*it).getName()) {
            break;
        }
        it++;
    }
    if(it != items.end())
        return (*it);
    else
        throw std::invalid_argument("Item not found. Try again.");
}

