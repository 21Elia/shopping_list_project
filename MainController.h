//
// Created by Elia Awad on 04/09/24.
//

#ifndef SHOPPINGLISTAPP_MAINCONTROLLER_H
#define SHOPPINGLISTAPP_MAINCONTROLLER_H

class MainFrame;
// DO NOT INCLUDE "MainFrame.h" IN MainController.h
// IT CONFUSES THE COMPILER AND view->Layout(); doesn't work anymore
#include <wx/wx.h>
#include "User.h"
#include "ShoppingList.h"
#include "DataManager.h"
#include <list>
#include <map>

class MainController {
public:
    explicit MainController(MainFrame* view);

    // user methods
    void onAddUserButtonClicked(wxCommandEvent& evt);
    void onUserInputEnter(wxCommandEvent& evt);
    void onUserListKeyDown(wxKeyEvent& evt);

    void onUserListDoubleClick(wxMouseEvent& evt);
    // list methods
    void onAddListButtonClicked(wxCommandEvent& evt);

    void onListInputEnter(wxCommandEvent& evt);
    void onListKeyDown(wxKeyEvent& evt);
    void onListDoubleClick(wxMouseEvent& evt);

    void onBackListsButtonClicked(wxCommandEvent& evt);
    // item methods
    void onAddItemButtonClicked(wxCommandEvent& evt);
    void onItemInputEnter(wxCommandEvent& evt);

    void addItemFromInput();
    void onBackItemsButtonClicked(wxCommandEvent& evt);
    void onShareListButtonClicked(wxCommandEvent& evt);

    void onItemCheckListKeyDown(wxKeyEvent& evt);
    void onItemChecked(wxCommandEvent& evt);

    void onWindowClosed(wxCloseEvent& evt);
    bool isInUsers(const std::string& username);


    static std::vector<User>::iterator findUser(const std::string& username, std::vector<User>& users);
    void saveData();
    void loadData();

private:
    void updateItems(const std::shared_ptr<ShoppingList> &shoppingList);
    void updateLists(User* user);
    void setItemCheckStatus();
    void addUserFromInput();
    void addListFromInput();

private:
    MainFrame* view;
    DataManager dataManager;
    std::string fileName;

    int nextUserID;
    int nextListID;
    std::map<int, std::list<User>> shareMap; // list ID -> sharedUsers
    std::map<int, std::list<int>> usersListsMap; // user ID -> list ID
    std::vector<User> users;
    User* currentUser;
    std::shared_ptr<ShoppingList> currentList;
};


#endif //SHOPPINGLISTAPP_MAINCONTROLLER_H
