//
// Created by Elia Awad on 05/07/24.
//

#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <memory>
#include "User.h"
#include "ShoppingList.h"

enum IDs {
    WXK_MACOS_DELETE = 8
};

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title){
    setupUserMenu();
    setupListsMenu();
    setupEditMenu();
    bindEventHandlers();

    // Setup the frame sizer

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(userPanel, wxSizerFlags().Proportion(1).Expand());
    frameSizer->Add(listsPanel, wxSizerFlags().Proportion(1).Expand());
    frameSizer->Add(editPanel, wxSizerFlags().Proportion(1).Expand());
    //SetSizerAndFit(frameSizer);
    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(frameSizer,wxSizerFlags().Border(wxALL, 75).Expand());
    SetSizerAndFit(outerSizer);

    listsPanel->Hide();
    editPanel->Hide();
}

void MainFrame::setupUserMenu() {
    userPanel = new wxPanel(this);

    newUserText = new wxStaticText(userPanel, wxID_ANY, "Add a new user");
    newUserText->SetFont(wxFontInfo(wxSize(0,18)).Bold());

    userInputField = new wxTextCtrl(userPanel, wxID_ANY, "",
                                    wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    addUserButton = new wxButton(userPanel, wxID_ANY, "Add");

    selectUserText = new wxStaticText(userPanel, wxID_ANY,"Select a user");
    selectUserText->SetFont(wxFontInfo(wxSize(0,20)).Bold());

    userListBox = new wxListBox(userPanel, wxID_ANY);

    setupUserMenuSizers();
}

void MainFrame::setupUserMenuSizers() {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(newUserText, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(25);

    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    inputSizer->Add(userInputField, wxSizerFlags().Proportion(1));
    inputSizer->AddSpacer(10);
    inputSizer->Add(addUserButton, wxSizerFlags().Proportion(0));

    mainSizer->Add(inputSizer, wxSizerFlags().Expand());
    mainSizer->AddSpacer(50);
    mainSizer->Add(selectUserText, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(25);
    mainSizer->Add(userListBox, wxSizerFlags().Expand().Proportion(1));

    userPanel->SetSizer(mainSizer);
}

void MainFrame::setupListsMenu() {
    wxFont headlineFont(wxFontInfo(wxSize(0,36)).Bold());
    wxFont inputFont(wxFontInfo(wxSize(0,20)));
    wxFont buttonFont(wxFontInfo(wxSize(0,14)));

    listsPanel = new wxPanel(this);

    backListsButton = new wxButton(listsPanel, wxID_ANY, "Back");
    backListsButton->SetFont(buttonFont);

    headlineText = new wxStaticText(listsPanel, wxID_ANY, "Shopping Lists");
    headlineText->SetFont(headlineFont);

    newListText = new wxStaticText(listsPanel, wxID_ANY, "New List");
    newListText->SetFont(wxFontInfo(wxSize(0, 20)).Bold());

    listInputField = new wxTextCtrl(listsPanel, wxID_ANY, "",
                                    wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
                                //the style wxTE_PROCESS_ENTER is needed for wxEVT_TEXT_ENTER to work
    listInputField->SetFont(inputFont);

    addListButton = new wxButton(listsPanel, wxID_ANY, "Add");
    addListButton->SetFont(buttonFont);

    listBox = new wxListBox(listsPanel, wxID_ANY);

    setupListsMenuSizers();
}

void MainFrame::setupListsMenuSizers() {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->AddSpacer(25);
    mainSizer->Add(headlineText, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(25);


    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    inputSizer->Add(newListText, wxSizerFlags().Proportion(0));
    inputSizer->AddSpacer(10);
    inputSizer->Add(listInputField, wxSizerFlags().Proportion(1));
    inputSizer->AddSpacer(10);
    inputSizer->Add(addListButton, wxSizerFlags().Proportion(0));

    mainSizer->Add(inputSizer, wxSizerFlags().Expand());
    mainSizer->AddSpacer(10);
    mainSizer->Add(listBox, wxSizerFlags().Expand().Proportion(1));

    listsPanel->SetSizer(mainSizer);
}

void MainFrame::setupEditMenu() {
    wxFont headlineFont(wxFontInfo(wxSize(0,36)).Bold());
    wxFont inputFont(wxFontInfo(wxSize(0,20)));
    wxFont buttonFont(wxFontInfo(wxSize(0,14)));

    editPanel = new wxPanel(this);

    backItemsButton = new wxButton(editPanel, wxID_ANY, "Back");
    backItemsButton->SetFont(buttonFont);

    headlineEditMenuText = new wxStaticText(editPanel, wxID_ANY, "Add or Delete Items");
    headlineEditMenuText->SetFont(headlineFont);

    newItemText = new wxStaticText(editPanel, wxID_ANY, "New Item");
    newItemText->SetFont(wxFontInfo(wxSize(0,20)).Bold());

    itemInputField = new wxTextCtrl(editPanel, wxID_ANY, "",
                                    wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    itemInputField->SetFont(inputFont);

    addItemButton = new wxButton(editPanel, wxID_ANY, "Add");
    addItemButton->SetFont(buttonFont);

    itemCheckListBox = new wxCheckListBox(editPanel, wxID_ANY);

    setupEditMenuSizers();
    //editPanel->Hide();

}

void MainFrame::setupEditMenuSizers() {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->AddSpacer(25);
    mainSizer->Add(headlineEditMenuText, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(25);

    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    inputSizer->Add(newItemText, wxSizerFlags().Proportion(0));
    inputSizer->AddSpacer(10);
    inputSizer->Add(itemInputField, wxSizerFlags().Proportion(1));
    inputSizer->AddSpacer(10);
    inputSizer->Add(addItemButton, wxSizerFlags().Proportion(0));

    mainSizer->Add(inputSizer, wxSizerFlags().Expand());
    mainSizer->AddSpacer(10);
    mainSizer->Add(itemCheckListBox, wxSizerFlags().Expand().Proportion(1));

    editPanel->SetSizer(mainSizer);
}

void MainFrame::bindEventHandlers() {

    addUserButton->Bind(wxEVT_BUTTON, &MainFrame::onAddUserButtonClicked, this);
    userInputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::onUserInputEnter, this);
    userListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::onUserListKeyDown, this);
    userListBox->Bind(wxEVT_LEFT_DCLICK, &MainFrame::onUserListDoubleClick, this);

    addListButton->Bind(wxEVT_BUTTON, &MainFrame::onAddListButtonClicked, this);
    listInputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::onInputEnter, this);
    listBox->Bind(wxEVT_KEY_DOWN, &MainFrame::onListKeyDown, this);
    listBox->Bind(wxEVT_LEFT_DCLICK, &MainFrame::onListDoubleClick, this);
    backListsButton->Bind(wxEVT_BUTTON, &MainFrame::onBackListsButtonClicked, this);
}

void MainFrame::onAddUserButtonClicked(wxCommandEvent &evt) {
    addUserFromInput();
}

void MainFrame::onUserInputEnter(wxCommandEvent &evt) {
    addUserFromInput();
}

void MainFrame::addUserFromInput() {
    if(!userInputField->IsEmpty()) {
        std::string username = userInputField->GetValue().ToStdString();
        User myUser(username);
        users.push_back(myUser);
        userListBox->Insert(myUser.getUsername(), userListBox->GetCount());
        userInputField->Clear();
    }
    userInputField->SetFocus();
}

void MainFrame::onUserListKeyDown(wxKeyEvent &evt) {
    int index = userListBox->GetSelection();
    switch( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if (index != wxNOT_FOUND) {
                std::string username = userListBox->GetString(index).ToStdString();
                auto it = findUser(username);
                if (it != users.end()) {
                    users.erase(it);
                    userListBox->Delete(index);
                }
            }
            break;
    }
}

std::vector<User>::iterator MainFrame::findUser(const std::string &username) {
    auto it = users.begin();
    while(it != users.end()) {
        if((*it).getUsername() == username)
            break;
        it++;
    }
    return it;
}

void MainFrame::onUserListDoubleClick(wxMouseEvent &evt) {
    int index = userListBox->GetSelection();
    if(index != wxNOT_FOUND) {
        std::string username = userListBox->GetString(index).ToStdString();
        selectedUser = &( *(findUser(username)) );
        fillListBox(selectedUser);

        userPanel->Hide();
        listsPanel->Show();
        Layout();
    }
    evt.Skip();
}

void MainFrame::onAddListButtonClicked(wxCommandEvent &evt) {
    addListFromInput();
}

void MainFrame::onInputEnter(wxCommandEvent &evt) {
    addListFromInput();
}

void MainFrame::addListFromInput() {
    wxString listName = listInputField->GetValue();
    int index = userListBox->GetSelection();
    if(!listName.IsEmpty()){
        std::string username = userListBox->GetString(index).ToStdString();

        //creating shopping list and adding it to the corresponding user
        std::shared_ptr<ShoppingList> myShoppingList(new ShoppingList(listName.ToStdString()));
        auto it = findUser(username);
        (*it).addShoppingList(myShoppingList);

        //adding the listName to the listBox
        listBox->Insert(listName, listBox->GetCount()); //second parameter is the listBox index
        listInputField->Clear();
    }
    listInputField->SetFocus();
}

void MainFrame::onListKeyDown(wxKeyEvent &evt) {
    int index = listBox->GetSelection();
    switch ( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            listBox->Delete(index);
    }
}

void MainFrame::onListDoubleClick(wxMouseEvent &evt) {
    listsPanel->Hide();
    editPanel->Show();
    Layout();
    //wxLogMessage("Double clicked");
}

void MainFrame::onBackListsButtonClicked(wxCommandEvent &evt) {
    listBox->Clear();
    listsPanel->Hide();
    userPanel->Show();
    Layout();
}

void MainFrame::fillListBox(User *user) {
    std::list<std::shared_ptr<ShoppingList>> shoppinglists = user->getShoppingList();
    for(auto const& shoppinglist : shoppinglists) {
        listBox->Append(shoppinglist->getName());
    }
}





