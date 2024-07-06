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

class User {
public:
    User(std::string  username) : username(std::move(username)) {}

    void addShoppingList(const std::shared_ptr<ShoppingList>& list);

    void removeShoppingList(const std::string& name);
private:
    std::string username;
    std::list<std::shared_ptr<ShoppingList>> shoppinglists;
};


#endif //SHOPPINGLISTAPP_USER_H
