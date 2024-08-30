//
// Created by Elia Awad on 04/07/24.
//

#include "Item.h"

void Item::setQuantity(int num) {
    if(num < 0)
        throw std::invalid_argument("Quantity must be zero or a positive number.");
    quantity = num;
}
