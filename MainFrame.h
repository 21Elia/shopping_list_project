//
// Created by Elia Awad on 05/07/24.
//

#ifndef SHOPPINGLISTAPP_MAINFRAME_H
#define SHOPPINGLISTAPP_MAINFRAME_H

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <vector>
#include "User.h"
#include "ShoppingList.h"

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

    void addUserFromInput();
    void addListFromInput();
    void addItemFromInput();
    void fillListBox(User* user);
    void fillItemListBox(User* user);
    std::vector<User>::iterator getUser(const std::string& username);

    User* selectedUser;

    // User Menu //
    wxPanel* userPanel;
    wxStaticText* newUserLabel;
    wxTextCtrl* userInputField;
    wxButton* addUserButton;
    wxStaticText* selectUserLabel;
    wxListBox* userListBox;
    std::vector<User> users;


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
