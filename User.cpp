//
// Created by Elia Awad on 06/07/24.
//

#include "User.h"

void User::addShoppingList(const std::shared_ptr<ShoppingList>& list) {
    shoppinglists.push_back(list);
}

void User::removeShoppingList(const std::string& name) {
    auto it = shoppinglists.begin();
    while(it != shoppinglists.end()) {
        if(name == (*it)->getName()) {
            break;
        }
        it++;
    }
    if(it != shoppinglists.end())
        shoppinglists.erase(it);
    else
        throw std::invalid_argument("Shopping list not found. Try again.");
}