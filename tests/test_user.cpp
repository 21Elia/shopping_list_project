//
// Created by Elia Awad on 24/08/24.
//

#include <gtest/gtest.h>
#include "../ShoppingList.h"
#include "../Item.h"
#include "../User.h"

class UserTest : public ::testing::Test {
protected:

    void SetUp() override {
        user = std::make_unique<User>(("Elia"));
    }

    void TearDown() override {
        user.reset();
    }

    std::unique_ptr<User> user;
};

TEST_F(UserTest, addShoppingList) {
    std::shared_ptr<ShoppingList> shoppingList(new ShoppingList("Test List"));
    user->addShoppingList(shoppingList);
    std::list<std::shared_ptr<ShoppingList>> shoppinglists = user->getShoppingLists();
    ASSERT_EQ(shoppinglists.size(), 1);

    auto it = shoppinglists.begin();
    ASSERT_EQ((*it)->getName(), "Test List");
}

TEST_F(UserTest, addAlreadyExistingShoppingList) {
    std::shared_ptr<ShoppingList> shoppingList(new ShoppingList("Test List"));
    user->addShoppingList(shoppingList);
    ASSERT_THROW(user->addShoppingList(shoppingList), std::invalid_argument);
}

TEST_F(UserTest, removeShoppingList) {
    std::shared_ptr<ShoppingList> shoppingList(new ShoppingList("Test List"));
    user->addShoppingList(shoppingList);
    user->removeShoppingList("Test List");

    auto shoppinglists = user->getShoppingLists();
    ASSERT_EQ(shoppinglists.size(), 0);
}

TEST_F(UserTest, removeShoppingListNotFound) {
    ASSERT_THROW(user->removeShoppingList("NonExistingShoppingList"), std::invalid_argument);
}

TEST_F(UserTest, removeShoppingListOnID) {
    std::shared_ptr<ShoppingList> shoppingList(new ShoppingList("Test List"));

    user->addShoppingList(shoppingList);
    user->removeShoppingListOnID(1);

    auto shoppinglists = user->getShoppingLists();

    ASSERT_EQ(shoppinglists.size(), 0);
}

TEST_F(UserTest, removeShoppingListOnIdNotFound) {
    ASSERT_THROW(user->removeShoppingListOnID(-1), std::invalid_argument);
}

TEST_F(UserTest, isInShoppingLists) {
    std::shared_ptr<ShoppingList> shoppingList(new ShoppingList("Test List"));
    user->addShoppingList(shoppingList);

    ASSERT_TRUE(user->isInShoppingLists("Test List"));

    user->removeShoppingList("Test List");

    ASSERT_FALSE(user->isInShoppingLists("Test List"));
}

TEST_F(UserTest, findShoppingList) {
    std::shared_ptr<ShoppingList> shoppingList1(new ShoppingList("Test List 1"));
    std::shared_ptr<ShoppingList> shoppingList2(new ShoppingList("Test List 2"));
    user->addShoppingList(shoppingList1);
    user->addShoppingList(shoppingList2);

    auto it = user->findShoppingList("Test List 1");
    ASSERT_EQ((*it)->getName(), "Test List 1");

    it = user->findShoppingList("Test List 2");
    ASSERT_EQ((*it)->getName(), "Test List 2");

    it = user->findShoppingListOnID(1);
    ASSERT_EQ((*it)->getName(), "Test List 1");

    ASSERT_THROW(user->findShoppingList("NonExistingShoppingList"), std::invalid_argument);
    ASSERT_THROW(user->findShoppingListOnID(-1), std::invalid_argument);
}


