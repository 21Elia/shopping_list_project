//
// Created by Elia Awad on 07/09/24.
//

#ifndef SHOPPINGLISTAPP_DATAMANAGER_H
#define SHOPPINGLISTAPP_DATAMANAGER_H
#include <wx/wx.h>
#include "ShoppingList.h"
#include "User.h"
#include <map>
#include <list>
#include <filesystem>
#include <fstream>


class DataManager {
public:
    void saveData(const std::string& fileName,
                  const std::vector<User>& users,
                  const std::map<int, std::list<int>>& usersListsMap,
                  const std::map<int, std::list<User>>& shareMap,
                  int nextUserID,
                  int nextListID);


    void loadData(const std::string& fileName,
                  std::vector<User>& users,
                  std::map<int, std::list<int>>& usersListsMap,
                  std::map<int, std::list<User>>& shareMap,
                  int& nextUserID,
                  int& nextListID);

private:
    std::shared_ptr<ShoppingList> findShoppingListInUsers(int listID, const std::vector<User>& users);
};


#endif //SHOPPINGLISTAPP_DATAMANAGER_H
