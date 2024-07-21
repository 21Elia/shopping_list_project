//
// Created by Elia Awad on 06/07/24.
//

#include "User.h"

void User::addShoppingList(const std::shared_ptr<ShoppingList>& list) {
    if( !isInShoppingLists(list->getName()) )
        shoppinglists.push_back(list);
    else
        throw std::invalid_argument(list->getName() + " already exists. Use a different name.");
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

std::list<std::shared_ptr<ShoppingList>>::iterator User::findShoppingList(const std::string &listName) {
    auto it = shoppinglists.begin();
    while (it != shoppinglists.end()) {
        if (listName == (*it)->getName())
            break;
        it++;
    }
    if (it != shoppinglists.end())
        return it;
    else
        throw std::invalid_argument("List not found");
}

bool User::isInShoppingLists(const std::string &name) {
    bool found = false;
    auto it = shoppinglists.begin();
    while (it != shoppinglists.end() && !found) {
        if ( name == (*it)->getName() )
            found = true;
        it++;
    }
    return found;
}

void User::removeShoppingListOnID(int num) {
    auto it = shoppinglists.begin();
    while(it != shoppinglists.end()) {
        if(num == (*it)->getID()) {
            break;
        }
        it++;
    }
    if(it != shoppinglists.end())
        shoppinglists.erase(it);
    else
        throw std::invalid_argument("Shopping list not found. Try again.");
}

std::list<std::shared_ptr<ShoppingList>>::iterator User::findShoppingListOnID(int num) {
    auto it = shoppinglists.begin();
    while (it != shoppinglists.end()) {
        if (num == (*it)->getID())
            break;
        it++;
    }
    if (it != shoppinglists.end())
        return it;
    else
        throw std::invalid_argument("List not found");
}