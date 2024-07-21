//
// Created by Elia Awad on 04/07/24.
//

#ifndef SHOPPINGLISTAPP_ITEM_H
#define SHOPPINGLISTAPP_ITEM_H

#include <iostream>
#include <utility>

class Item {
public:

    explicit Item(std::string name, std::string category, int num = 1, bool check = false) :
            name(std::move(name)), category(std::move(category)), quantity(num), checked(check) {}

    void setName(std::string n) {name = n;}
    void setCategory(std::string category) {category = category;}
    void setQuantity(int num) {quantity = num;}
    void setCheck(bool check) {checked = check;}

    std::string getName() const {return name;}
    std::string getCategory() const {return category;}
    int getQuantity() const {return quantity;}
    bool isChecked() const {return checked;}

private:
    std::string name;
    std::string category;
    int quantity;
    bool checked;
};


#endif //SHOPPINGLISTAPP_ITEM_H
