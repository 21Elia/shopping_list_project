//
// Created by Elia Awad on 04/07/24.
//

#ifndef SHOPPINGLISTAPP_ITEM_H
#define SHOPPINGLISTAPP_ITEM_H

#include <iostream>
#include <utility>

class Item {
public:

    explicit Item(const std::string&  name, const std::string& category, int num = 1, bool check = false) :
            name(name), category(category), quantity(num), checked(check) {
        if (quantity <= 0) {
            throw std::invalid_argument("Quantity must be a positive number.");
        }
    }

    void setName(const std::string& n) {name = n;}
    void setCategory(const std::string& cat) {category = cat;}
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
