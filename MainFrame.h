//
// Created by Elia Awad on 05/07/24.
//

#ifndef SHOPPINGLISTAPP_MAINFRAME_H
#define SHOPPINGLISTAPP_MAINFRAME_H

#include "MainController.h"
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

    wxPanel* getUserPanel() const;

    wxTextCtrl* getUserInputField() const;

    wxListBox* getUserListBox() const;

    wxPanel* getListsPanel() const;

    wxTextCtrl* getListInputField() const;

    wxListBox* getListBox() const;

    wxPanel* getItemsPanel() const;

    wxTextCtrl* getItemInputField() const;

    wxSpinCtrl* getSpinCtrl() const;

    wxCheckListBox* getItemCheckListBox() const;

    wxListBox* getQuantityListBox() const;

private:

    MainController* controller;

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


    void setupUserMenu();
    void setupListsMenu();
    void setupItemsMenu();

    void setupUserMenuSizers();
    void setupListsMenuSizers();
    void setupItemsMenuSizers();
    void setupFrameSizers();

    void bindEventHandlers();
};


#endif //SHOPPINGLISTAPP_MAINFRAME_H