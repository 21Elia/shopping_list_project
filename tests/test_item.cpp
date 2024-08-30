//
// Created by Elia Awad on 23/08/24.
//

#include <gtest/gtest.h>
#include "../Item.h"

class ItemTest : public ::testing::Test {
};

TEST_F(ItemTest, negativeQuantityItem) {
    EXPECT_THROW(Item("Apple", "Fruit", -1), std::invalid_argument);
}

TEST_F(ItemTest, undefinedQuantityItem) {
    Item item("Apple", "Fruit", 0);
    EXPECT_TRUE(item.isUndefinedQuantity());
}
