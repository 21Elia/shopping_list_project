//
// Created by Elia Awad on 11/07/24.
//

#ifndef SHOPPINGLISTAPP_SHOPPINGLISTNOTIFIER_H
#define SHOPPINGLISTAPP_SHOPPINGLISTNOTIFIER_H

#include "ShoppingList.h"
#include "Observer.h"


class ShoppingListNotifier : public Observer {
public:
    explicit ShoppingListNotifier(ShoppingList* shoppingList);

    void update() override;

    ~ShoppingListNotifier() override;
private:
    ShoppingList* myShoppingList;
};


#endif //SHOPPINGLISTAPP_SHOPPINGLISTNOTIFIER_H
