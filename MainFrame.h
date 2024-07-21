//
// Created by Elia Awad on 05/07/24.
//

#ifndef SHOPPINGLISTAPP_MAINFRAME_H
#define SHOPPINGLISTAPP_MAINFRAME_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>
#include <list>
#include "User.h"
#include "ShoppingList.h"
#include <fstream>
#include <filesystem>
#include <map>

class MainFrame : public wxFrame {
public:
    explicit MainFrame(const wxString &title);

private:
    void setupUserMenu();
    void setupListsMenu();
    void setupItemsMenu();

    void setupUserMenuSizers();
    void setupListsMenuSizers();
    void setupItemsMenuSizers();
    void setupFrameSizers();
    void bindEventHandlers();
    void loadDataToUI();

    void onAddUserButtonClicked(wxCommandEvent& evt);
    void onUserInputEnter(wxCommandEvent& evt);
    void onUserListKeyDown(wxKeyEvent& evt);
    void onUserListDoubleClick(wxMouseEvent& evt);

    void onAddListButtonClicked(wxCommandEvent& evt);
    void onListKeyDown(wxKeyEvent& evt);
    void onListInputEnter(wxCommandEvent& evt);
    void onListDoubleClick(wxMouseEvent& evt);
    void onBackListsButtonClicked(wxCommandEvent& evt);

    void onAddItemButtonClicked(wxCommandEvent& evt);
    void onBackItemsButtonClicked(wxCommandEvent& evt);
    void onShareListButtonClicked(wxCommandEvent& evt);
    void onItemInputEnter(wxCommandEvent& evt);
    void onItemCheckListKeyDown(wxKeyEvent& evt);
    void onItemChecked(wxCommandEvent& evt);

    void onWindowClosed(wxCloseEvent& evt);

    void addUserFromInput();
    void addListFromInput();
    void addItemFromInput();
    bool isInUsers(const std::string& username);
    void updateLists(User* user);
    void updateItems(const std::shared_ptr<ShoppingList> &shoppingList);
    void setItemCheckStatus();
    std::vector<User>::iterator findUser(const std::string& username);
    std::vector<User>::iterator findUserOnID(int num);
    std::shared_ptr<ShoppingList> findShoppingListByID(int listID);

    void saveData(const std::string& fileName);
    void loadData(const std::string& fileName);

    int nextListID;
    int nextUserID;
    std::map<int, std::list<User>> shareMap; // list ID -> sharedUsers
    std::map<int, std::list<int>> usersListsMap; // user ID -> list ID
    std::vector<User> users;
    User* currentUser;
    std::shared_ptr<ShoppingList> currentList;

    // User Menu //
    wxPanel* userPanel;
    wxStaticText* newUserLabel;
    wxTextCtrl* userInputField;
    wxButton* addUserButton;
    wxStaticText* selectUserLabel;
    wxListBox* userListBox;


    // Lists Menu //
    wxPanel* listsPanel;
    wxStaticText* headlineLabel;
    wxStaticText* newListLabel;
    wxTextCtrl* listInputField;
    wxButton* addListButton;
    wxButton* backListsButton;
    wxListBox* listBox;

    // Items Menu //
    wxPanel* itemsPanel;
    wxStaticText* headlineItemsLabel;
    wxStaticText* newItemLabel;
    wxTextCtrl* itemInputField;
    wxSpinCtrl* spinCtrl;
    wxButton* addItemButton;
    wxButton* backItemsButton;
    wxButton* shareListButton;
    wxCheckListBox* itemCheckListBox;
    wxListBox* quantityListBox;
};


#endif //SHOPPINGLISTAPP_MAINFRAME_H