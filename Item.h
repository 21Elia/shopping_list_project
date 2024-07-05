//
// Created by Elia Awad on 04/07/24.
//

#ifndef SHOPPINGLISTAPP_ITEM_H
#define SHOPPINGLISTAPP_ITEM_H

#include <iostream>

class Item {
public:

    explicit Item(std::string name, std::string category, int num = 1) : name(name), category(category),
                                                                       quantity(num) {}
    void setName(std::string n) {name = n;}
    void setCategory(std::string category) {category = category;}
    void setQuantity(int num) {quantity = num;}

    std::string getName() const {return name;}
    std::string getCategory() const {return category;}
    int getQuantity() const {return quantity;}

private:
    std::string name;
    std::string category;
    int quantity;

};


#endif //SHOPPINGLISTAPP_ITEM_H
