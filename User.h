//
// Created by Elia Awad on 06/07/24.
//

#ifndef SHOPPINGLISTAPP_USER_H
#define SHOPPINGLISTAPP_USER_H


#include <iostream>
#include "ShoppingList.h"
#include <list>
#include <memory>
#include <algorithm>

class User {
public:
    User(std::string  username, int ID = 1) : username(std::move(username)), ID(ID) {}

    void addShoppingList(const std::shared_ptr<ShoppingList>& list);

    void removeShoppingList(const std::string& name);
    void removeShoppingListOnID(int num);

    bool isInShoppingLists(const std::string& name);

    std::list<std::shared_ptr<ShoppingList>>::iterator findShoppingList(const std::string& listName);
    std::list<std::shared_ptr<ShoppingList>>::iterator findShoppingListOnID(int num);

    std::string getName() const {return username;}
    int getID() const {return ID;}
    void setID(int num) { ID = num;}
    std::list<std::shared_ptr<ShoppingList>> getShoppingLists() const {return shoppinglists;}

private:
    int ID;
    std::string username;
    std::list<std::shared_ptr<ShoppingList>> shoppinglists;
};


#endif //SHOPPINGLISTAPP_USER_H
