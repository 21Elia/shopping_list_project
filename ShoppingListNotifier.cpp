//
// Created by Elia Awad on 11/07/24.
//

#include "ShoppingListNotifier.h"

ShoppingListNotifier::ShoppingListNotifier(ShoppingList *shoppingList) : myShoppingList(shoppingList) {
    myShoppingList->subscribe(this);
}

void ShoppingListNotifier::update() {
    std::cout << "User's list " << myShoppingList->getName() << "has been updated." << std::endl;
    myShoppingList->printDetails();
}

ShoppingListNotifier::~ShoppingListNotifier() {
    myShoppingList->unsubscribe(this);
}
