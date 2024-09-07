//
// Created by Elia Awad on 07/09/24.
//

#include "DataManager.h"
#include "MainController.h"

void DataManager::saveData(const std::string &fileName,
                           const std::vector<User> &users,
                           const std::map<int, std::list<int>> &usersListMap,
                           const std::map<int, std::list<User>> &shareMap,
                           int nextUserID,
                           int nextListID) {
    std::ofstream outFile;
    outFile.open(fileName);
    if(!outFile.is_open()) {
        wxLogError("Error writing into file %s", fileName);
        return;
    }

    if(users.empty()) {
        outFile << 0 << std::endl << 0 << std::endl << 0;
        return;
    }

    outFile << nextUserID << std::endl; // max user ID
    outFile << nextListID << std::endl; // max list ID
    outFile << users.size() << std::endl; // num of users saved
    outFile << "===" << std::endl;

    for(const auto& user : users) {
        std::string username = user.getName();
        std::replace(username.begin(), username.end(), ' ', '_');
        outFile << username << " " << user.getID() << std::endl;

        auto shoppingLists = user.getShoppingLists();
        outFile << shoppingLists.size() << std::endl;
        for(const auto& shoppingList : shoppingLists) {
            std::string listName = shoppingList->getName();
            std::replace(listName.begin(), listName.end(), ' ', '_');
            outFile << listName << " " << shoppingList->getID() << std::endl; // listName , listID

            auto items = shoppingList->getItems();
            outFile << items.size() << std::endl;
            for(const auto& item : items) {
                std::string itemName = item.getName();
                std::replace(itemName.begin(), itemName.end(), ' ', '_');
                outFile << itemName << " " << item.getQuantity() << " " << item.isChecked() << std::endl;
            }
            outFile << "---" << std::endl; // divider between lists
        }
        outFile << "===" << std::endl; // divider between users
    }

    // Printing list's IDs and the users the lists are shared with

    outFile << "USERS_SHARING_THE_ID" << std::endl;
    outFile << shareMap.size() << std::endl;
    for (const auto& pair : shareMap) {
        auto sharedUsers = pair.second;
        auto ID = pair.first;
        outFile << ID << " " << sharedUsers.size(); // listID & number of users who share the list
        for (const auto& sharedUser : sharedUsers) {
            std::string sharedUsername;
            sharedUsername = sharedUser.getName();
            std::replace(sharedUsername.begin(), sharedUsername.end(), ' ', '_');
            outFile << " " << sharedUsername;
        }
        outFile << std::endl;
    }
    outFile.close();
}

void DataManager::loadData(const std::string &fileName,
                           std::vector<User> &users,
                           std::map<int, std::list<int>> &usersListsMap, std::map<int,
                           std::list<User>> &shareMap,
                           int &nextUserID,
                           int &nextListID) {
    std::ifstream inFile;
    if(!std::filesystem::exists(fileName) || std::filesystem::is_empty(fileName)) {
        wxLogMessage("Not able to read %s: file is empty or doesn't exist", fileName, "Error");
        return;
    }
    inFile.open(fileName);
    if(!inFile.is_open()) {
        wxLogMessage("Failed to open %s", fileName, "Error");
        return;
    }

    // making sure users and map are empty
    users.clear();
    shareMap.clear();

    int userCount, listCount, itemCount;
    std::string line; // string to skip dividers

    inFile >> nextUserID;
    inFile >> nextListID;
    inFile >> userCount;
    if(userCount <= 0) {
        return;
    }

    for(int i = 0; i < userCount; i++) {
        inFile >> line; // ignoring user divider

        std::string username;
        int userID;

        inFile >> username;
        inFile >> userID;

        std::replace(username.begin(), username.end(), '_', ' ');
        User user(username, userID);
        users.push_back(user);
        User& newUser = users.back();

        inFile >> listCount;
        std::list<int> listIDs; // temporary list to store list IDs for the user to rebuild usersListsMap
        for(int j = 0; j < listCount; j++) {
            std::string listName;
            int listID;

            inFile >> listName;
            std::replace(listName.begin(), listName.end(), '_', ' ');
            inFile >> listID;

            std::shared_ptr<ShoppingList> shoppingList (new ShoppingList(listName, listID));
            newUser.addShoppingList(shoppingList);
            listIDs.push_back(listID); // Collect list IDs

            inFile >> itemCount;
            for(int k = 0; k < itemCount; k++) {
                std::string itemName;
                int quantity;
                bool check;
                inFile >> itemName;
                std::replace(itemName.begin(), itemName.end(), '_', ' ');
                inFile >> quantity;
                inFile >> check;

                Item item(itemName, "", quantity, check);
                shoppingList->addItem(item);
            }
            inFile >> line;
        }
        usersListsMap[userID] = listIDs; // Update the map with user ID and list IDs
    }

    // reading the shared information

    inFile >> line; // skips the last "===" before USERS_SHARING_THE_ID
    inFile >> line; // skips "USERS_SHARING_THE_ID"

    if(line != "USERS_SHARING_THE_ID") {
        wxMessageBox(wxString::Format("Expected USERS_SHARING_THE_ID while reading %s but got something else",
                                      fileName), "Loading Error", wxICON_ERROR);
        return;
    }

    int sharedListCount, sharedUserCount;
    inFile >> sharedListCount;

    for(int i = 0; i < sharedListCount; i++) {
        int listID;
        std::list<User> sharedUsers;

        inFile >> listID;
        inFile >> sharedUserCount;
        for(int j = 0; j < sharedUserCount; j++) {
            std::string username;
            inFile >> username;
            std::replace(username.begin(), username.end(), '_', ' ');
            try {

                User& sharedUser = *MainController::findUser(username, users); // throws exception if not found (shouldn't throw any exception tho!!)
                sharedUsers.push_back(sharedUser);

                sharedUser.removeShoppingListOnID(listID);
                sharedUser.addShoppingList(findShoppingListInUsers(listID, users));

            }catch(std::exception& e) {
                wxLogMessage(e.what(), "Error");
                return;
            }
        }
        shareMap[listID] = sharedUsers;
    }
    inFile.close();
}


std::shared_ptr<ShoppingList> DataManager::findShoppingListInUsers(int listID, const std::vector<User>& users) {
    for (const auto& user : users) {
        auto lists = user.getShoppingLists();
        for (const auto& list : lists) {
            if (list->getID() == listID) {
                return list;
            }
        }
    }
    throw std::runtime_error("List not found.");
}
