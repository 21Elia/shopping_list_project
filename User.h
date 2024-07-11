//
// Created by Elia Awad on 06/07/24.
//

#ifndef SHOPPINGLISTAPP_USER_H
#define SHOPPINGLISTAPP_USER_H


#include <iostream>
#include "ShoppingList.h"
#include <list>
#include <memory>
#include <utility>
#include <algorithm>

class User {
public:
    User(std::string  username) : username(std::move(username)) {}

    void addShoppingList(const std::shared_ptr<ShoppingList>& list);

    void removeShoppingList(const std::string& name);

    bool isInShoppingLists(const std::string& name);

    std::list<std::shared_ptr<ShoppingList>>::iterator findShoppingList(const std::string& listName);

    std::string getUsername() const {return username;}
    std::list<std::shared_ptr<ShoppingList>> getShoppingLists() const {return shoppinglists;}

private:
    std::string username;
    std::list<std::shared_ptr<ShoppingList>> shoppinglists;
};


#endif //SHOPPINGLISTAPP_USER_H
