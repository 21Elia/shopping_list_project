//
// Created by Elia Awad on 22/08/24.
//

#include <gtest/gtest.h>
#include "../Item.h"
#include "../ShoppingList.h"

class ShoppingListTest : public ::testing::Test {
protected:
    void SetUp() override {
        shoppingList = std::make_shared<ShoppingList>("Test List");
    }

    void TearDown() override {
        shoppingList.reset();
    }

    std::shared_ptr<ShoppingList> shoppingList;

};

TEST_F(ShoppingListTest, addItem) {
    Item item("Apple", "Fruit", 2);

    shoppingList->addItem(item);

    ASSERT_EQ(shoppingList->getItem("Apple").getName(), "Apple");
    ASSERT_EQ(shoppingList->getItem("Apple").getCategory(), "Fruit");
    ASSERT_EQ(shoppingList->getItem("Apple").getQuantity(), 2);
    ASSERT_FALSE(shoppingList->getItem("Apple").isChecked());

    shoppingList->addItem(item);

    ASSERT_EQ(shoppingList->getNumItems(), 4);

    // testing adding the same item on a checked item. Expecting to set the item check to false
    // (in case it was set on true) and to update the quantity correctly

    Item &gottenItem = shoppingList->getItem("Apple");
    gottenItem.setCheck(true);

    shoppingList->addItem(Item("Apple", "Fruit", 3));

    ASSERT_FALSE(shoppingList->getItem("Apple").isChecked());
    ASSERT_EQ(shoppingList->getNumItems(), 3);
}

TEST_F(ShoppingListTest, invalidQuantityItem) {
    ASSERT_THROW(Item("Apple", "Fruit", -1), std::invalid_argument);
    ASSERT_THROW(Item("Banana", "Fruit", 0), std::invalid_argument);
}

TEST_F(ShoppingListTest, removeItem) {
    Item item("Apple", "", 2);

    shoppingList->addItem(item);
    shoppingList->removeItem(item.getName());

    ASSERT_THROW(shoppingList->getItem("Apple"), std::invalid_argument);
}

TEST_F(ShoppingListTest, removeItemNotFound) {
    ASSERT_THROW(shoppingList->removeItem("NonExistingItem"), std::invalid_argument);
}

TEST_F(ShoppingListTest, getNumItems) {
    Item item1("Apple", "Fruit", 2);
    Item item2("Cereals", "Breakfast", 1);
    Item item3("Tuna", "Fish", 3);

    shoppingList->addItem(item1);
    shoppingList->addItem(item2);
    shoppingList->addItem(item3);

    shoppingList->removeItem("Cereals");

    ASSERT_EQ(shoppingList->getNumItems(), 5);
}

TEST_F(ShoppingListTest, isInItems) {
    Item item1("Apple", "Fruit", 2);
    Item item2("Cereals", "Breakfast", 1);

    shoppingList->addItem(item1);
    shoppingList->addItem(item2);

    ASSERT_TRUE(shoppingList->isInItems(item1));
    ASSERT_TRUE(shoppingList->isInItems(item2));

    shoppingList->removeItem("Cereals");

    ASSERT_FALSE(shoppingList->isInItems(item2));
}

TEST_F(ShoppingListTest, getItem) {
    Item item("Apple", "Fruit", 1);
    shoppingList->addItem(item);
    Item& gottenItem = shoppingList->getItem("Apple");
    gottenItem.setQuantity(5);
    ASSERT_EQ(shoppingList->getNumItems(), 5);
}

TEST_F(ShoppingListTest, getItemNotFound) {
    ASSERT_THROW(shoppingList->getItem("NonExistingItem"), std::invalid_argument);
}

TEST_F(ShoppingListTest, setAndIsShared) {
    ASSERT_FALSE(shoppingList->isShared());
    shoppingList->setShared(true);
    ASSERT_TRUE(shoppingList->isShared());
}