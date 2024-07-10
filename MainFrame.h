//
// Created by Elia Awad on 05/07/24.
//

#ifndef SHOPPINGLISTAPP_MAINFRAME_H
#define SHOPPINGLISTAPP_MAINFRAME_H

#include <wx/wx.h>
#include <vector>
#include "User.h"
#include "ShoppingList.h"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString &title);

private:
    void setupUserMenu();
    void setupListsMenu();
    void setupEditMenu();

    void setupUserMenuSizers();
    void setupListsMenuSizers();
    void setupEditMenuSizers();

    void bindEventHandlers();

    void onAddUserButtonClicked(wxCommandEvent& evt);
    void onUserInputEnter(wxCommandEvent& evt);
    void onUserListKeyDown(wxKeyEvent& evt);
    void onUserListDoubleClick(wxMouseEvent& evt);
    void addUserFromInput();


    void onAddListButtonClicked(wxCommandEvent& evt);
    void onListKeyDown(wxKeyEvent& evt);
    void onInputEnter(wxCommandEvent& evt);
    void onListDoubleClick(wxMouseEvent& evt);
    void onBackListsButtonClicked(wxCommandEvent& evt);

    void addListFromInput();
    void fillListBox(User* user);
    std::vector<User>::iterator findUser(const std::string& username);

    User* selectedUser;

    // User Menu //
    wxPanel* userPanel;
    wxStaticText* newUserText;
    wxTextCtrl* userInputField;
    wxButton* addUserButton;
    wxStaticText* selectUserText;
    wxListBox* userListBox;
    std::vector<User> users;


    // Lists Menu //
    wxPanel* listsPanel;
    wxStaticText* headlineText;
    wxStaticText* newListText;
    wxTextCtrl* listInputField;
    wxButton* addListButton;
    wxButton* backListsButton;
    wxListBox* listBox;

    // Edit Menu //
    wxPanel* editPanel;
    wxStaticText* headlineEditMenuText;
    wxStaticText* newItemText;
    wxTextCtrl* itemInputField;
    wxButton* addItemButton;
    wxButton* backItemsButton;
    wxCheckListBox* itemCheckListBox;
};


#endif //SHOPPINGLISTAPP_MAINFRAME_H
