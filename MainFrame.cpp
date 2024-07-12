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
    setupItemsMenu();
    bindEventHandlers();

    setupFrameSizers();

    // start with showing user menu

    listsPanel->Hide();
    itemsPanel->Hide();
}

void MainFrame::setupFrameSizers() {
    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(userPanel, wxSizerFlags().Proportion(1).Expand());
    frameSizer->Add(listsPanel, wxSizerFlags().Proportion(1).Expand());
    frameSizer->Add(itemsPanel, wxSizerFlags().Proportion(1).Expand());

    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(frameSizer,wxSizerFlags().Border(wxALL, 75).Expand());
    this->SetSizer(outerSizer);
    outerSizer->SetSizeHints(this);
}

void MainFrame::setupUserMenu() {
    userPanel = new wxPanel(this);

    newUserLabel = new wxStaticText(userPanel, wxID_ANY, "Add a new user");
    newUserLabel->SetFont(wxFontInfo(wxSize(0, 24)).Bold());

    userInputField = new wxTextCtrl(userPanel, wxID_ANY, "",
                                    wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    userInputField->SetFont(wxFontInfo(wxSize(0,18)));
    addUserButton = new wxButton(userPanel, wxID_ANY, "Add");

    selectUserLabel = new wxStaticText(userPanel, wxID_ANY, "Select a user");
    selectUserLabel->SetFont(wxFontInfo(wxSize(0, 24)).Bold());

    userListBox = new wxListBox(userPanel, wxID_ANY);

    setupUserMenuSizers();
}

void MainFrame::setupUserMenuSizers() {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(newUserLabel, wxSizerFlags().CenterHorizontal());

    mainSizer->AddSpacer(25);

    wxBoxSizer* inputFieldSizer = new wxBoxSizer(wxHORIZONTAL);
    inputFieldSizer->Add(userInputField, wxSizerFlags().Proportion(1));
    inputFieldSizer->AddSpacer(10);
    inputFieldSizer->Add(addUserButton,
                         wxSizerFlags().Proportion(0).Expand());

    mainSizer->Add(inputFieldSizer, wxSizerFlags().Expand());

    mainSizer->AddSpacer(25);

    mainSizer->Add(selectUserLabel, wxSizerFlags().CenterHorizontal());

    mainSizer->AddSpacer(25);

    mainSizer->Add(userListBox, wxSizerFlags().Proportion(1).Expand());

    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(mainSizer, wxSizerFlags().Expand());

    userPanel->SetSizer(outerSizer);
}

void MainFrame::setupListsMenu() {
    wxFont headlineFont(wxFontInfo(wxSize(0,36)).Bold());
    wxFont inputFont(wxFontInfo(wxSize(0,18)));
    wxFont buttonFont(wxFontInfo(wxSize(0,14)));

    listsPanel = new wxPanel(this);

    backListsButton = new wxButton(listsPanel, wxID_ANY, "Back", wxDefaultPosition, wxDefaultSize);
    backListsButton->SetFont(buttonFont);

    headlineLabel = new wxStaticText(listsPanel, wxID_ANY, "Shopping Lists");
    headlineLabel->SetFont(headlineFont);

    newListLabel = new wxStaticText(listsPanel, wxID_ANY, "New List");
    newListLabel->SetFont(wxFontInfo(wxSize(0, 20)).Bold());

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

    mainSizer->Add(backListsButton, wxSizerFlags().Align(wxLEFT | wxTOP));

    mainSizer->Add(headlineLabel, wxSizerFlags().CenterHorizontal());

    mainSizer->AddSpacer(25);

    wxBoxSizer* inputFieldSizer = new wxBoxSizer(wxHORIZONTAL);
    inputFieldSizer->Add(newListLabel,
                         wxSizerFlags().Proportion(0).Expand().Border(wxTOP, 5));

    inputFieldSizer->AddSpacer(10);

    inputFieldSizer->Add(listInputField, wxSizerFlags().Proportion(1));

    inputFieldSizer->AddSpacer(10);

    inputFieldSizer->Add(addListButton,
                         wxSizerFlags().Proportion(0).Expand());

    mainSizer->Add(inputFieldSizer, wxSizerFlags().Expand());

    mainSizer->AddSpacer(25);

    mainSizer->Add(listBox, wxSizerFlags().Proportion(1).Expand());

    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(mainSizer, wxSizerFlags().Expand());

    listsPanel->SetSizer(outerSizer);

}

void MainFrame::setupItemsMenu() {
    wxFont headlineFont(wxFontInfo(wxSize(0,36)).Bold());
    wxFont inputFont(wxFontInfo(wxSize(0,18)));
    wxFont buttonFont(wxFontInfo(wxSize(0,14)));

    itemsPanel = new wxPanel(this);

    backItemsButton = new wxButton(itemsPanel, wxID_ANY, "Back");
    backItemsButton->SetFont(buttonFont);

    shareListButton = new wxButton(itemsPanel, wxID_ANY, "Share List");
    shareListButton->SetFont(buttonFont);

    headlineItemsLabel = new wxStaticText(itemsPanel, wxID_ANY, "Add or Delete Items");
    headlineItemsLabel->SetFont(headlineFont);

    newItemLabel = new wxStaticText(itemsPanel, wxID_ANY, "New Item");
    newItemLabel->SetFont(wxFontInfo(wxSize(0, 20)).Bold());

    itemInputField = new wxTextCtrl(itemsPanel, wxID_ANY, "",
                                    wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    itemInputField->SetFont(inputFont);

    spinCtrl = new wxSpinCtrl(itemsPanel, wxID_ANY, "",wxDefaultPosition,wxDefaultSize,
                              wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER, 1, 100, 1);
    spinCtrl->SetFont(inputFont);

    addItemButton = new wxButton(itemsPanel, wxID_ANY, "Add");
    addItemButton->SetFont(buttonFont);

    itemCheckListBox = new wxCheckListBox(itemsPanel, wxID_ANY,
                                          wxDefaultPosition, wxSize(-1, 400));
    quantityListBox = new wxListBox(itemsPanel, wxID_ANY,
                                    wxDefaultPosition, wxSize(40,400));

    setupItemsMenuSizers();
}

void MainFrame::setupItemsMenuSizers() {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

    topSizer->Add(backItemsButton, wxSizerFlags().Align(wxLEFT));

    topSizer->AddSpacer(685);

    topSizer->Add(shareListButton, wxSizerFlags().Align(wxRIGHT));

    mainSizer->Add(topSizer, wxSizerFlags().Align(wxTOP).Expand());

    mainSizer->AddSpacer(25);

    mainSizer->Add(headlineItemsLabel, wxSizerFlags().CenterHorizontal());

    mainSizer->AddSpacer(25);

    wxBoxSizer* inputFieldSizer = new wxBoxSizer(wxHORIZONTAL);

    inputFieldSizer->Add(newItemLabel,
                         wxSizerFlags().Proportion(0).Expand().Border(wxTOP, 5));

    inputFieldSizer->AddSpacer(10);

    inputFieldSizer->Add(itemInputField, wxSizerFlags().Proportion(1));

    inputFieldSizer->AddSpacer(10);

    inputFieldSizer->Add(spinCtrl,
                         wxSizerFlags().Proportion(0).Expand());

    inputFieldSizer->AddSpacer(10);

    inputFieldSizer->Add(addItemButton,
                         wxSizerFlags().Proportion(0).Expand());

    mainSizer->Add(inputFieldSizer, wxSizerFlags().Expand());

    mainSizer->AddSpacer(25);

    wxBoxSizer* listSizer = new wxBoxSizer(wxHORIZONTAL);

    listSizer->Add(itemCheckListBox, wxSizerFlags().Proportion(1));

    listSizer->AddSpacer(10);

    listSizer->Add(quantityListBox, wxSizerFlags().Proportion(0));

    mainSizer->Add(listSizer, wxSizerFlags().Expand());

    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(mainSizer, wxSizerFlags().Expand());

    itemsPanel->SetSizer(outerSizer);
}

void MainFrame::bindEventHandlers() {
    // user menu controls binds
    addUserButton->Bind(wxEVT_BUTTON, &MainFrame::onAddUserButtonClicked, this);
    userInputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::onUserInputEnter, this);
    userListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::onUserListKeyDown, this);
    userListBox->Bind(wxEVT_LEFT_DCLICK, &MainFrame::onUserListDoubleClick, this);

    //shopping lists menu control binds
    addListButton->Bind(wxEVT_BUTTON, &MainFrame::onAddListButtonClicked, this);
    listInputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::onListInputEnter, this);
    listBox->Bind(wxEVT_KEY_DOWN, &MainFrame::onListKeyDown, this);
    listBox->Bind(wxEVT_LEFT_DCLICK, &MainFrame::onListDoubleClick, this);
    backListsButton->Bind(wxEVT_BUTTON, &MainFrame::onBackListsButtonClicked, this);

    // items menu control binds
    backItemsButton->Bind(wxEVT_BUTTON, &MainFrame::onBackItemsButtonClicked, this);
    addItemButton->Bind(wxEVT_BUTTON, &MainFrame::onAddItemButtonClicked, this);
    shareListButton->Bind(wxEVT_BUTTON, &MainFrame::onShareListButtonClicked, this);
    itemInputField->Bind(wxEVT_TEXT_ENTER, &MainFrame::onItemInputEnter, this);
    spinCtrl->Bind(wxEVT_TEXT_ENTER, &MainFrame::onItemInputEnter, this);
    itemCheckListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::onItemCheckListKeyDown, this);
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
                auto it = getUser(username);
                users.erase(it);
                userListBox->Delete(index);
            }
            break;
    }
}

std::vector<User>::iterator MainFrame::getUser(const std::string &username) {
    auto it = users.begin();
    while(it != users.end()) {
        if((*it).getUsername() == username)
            break;
        it++;
    }
    if(it != users.end())
        return it;
    else
        throw std::runtime_error("User not found.");
}

void MainFrame::onUserListDoubleClick(wxMouseEvent &evt) {
    int index = userListBox->GetSelection();
    if(index != wxNOT_FOUND) {
        std::string username = userListBox->GetString(index).ToStdString();
        selectedUser = &( *(getUser(username)) );
        fillListBox(selectedUser);

        userPanel->Hide();
        listsPanel->Show();
        Layout();
        listInputField->SetFocus();
    }
    evt.Skip();
}

void MainFrame::onAddListButtonClicked(wxCommandEvent &evt) {
    addListFromInput();
}

void MainFrame::onListInputEnter(wxCommandEvent &evt) {
    addListFromInput();
}

void MainFrame::addListFromInput() {
    wxString listName = listInputField->GetValue();
    int index = userListBox->GetSelection();
    if(!listName.IsEmpty()){
        std::string username = userListBox->GetString(index).ToStdString();

        //creating shopping list and adding it to the corresponding user
        std::shared_ptr<ShoppingList> myShoppingList(new ShoppingList(listName.ToStdString()));
        auto it = getUser(username);
        try {
            (*it).addShoppingList(myShoppingList);
        }
        catch(std::invalid_argument& e) {
            wxLogError(e.what());
            listInputField->Clear();
            return;
        }

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
            if(index != wxNOT_FOUND) {
                std::string listName = listBox->GetString(index).ToStdString();
                (*selectedUser).removeShoppingList(listName);

                listBox->Delete(index);
            }
            break;
    }
}

void MainFrame::onListDoubleClick(wxMouseEvent &evt) {
    int index = listBox->GetSelection();
    if(index != wxNOT_FOUND) {
        std::string listName = listBox->GetString(index).ToStdString();
        fillItemListBox(selectedUser);
        listsPanel->Hide();
        itemsPanel->Show();
        Layout();
    }
    evt.Skip();
}

void MainFrame::onBackListsButtonClicked(wxCommandEvent &evt) {
    listBox->Clear();
    listInputField->Clear();
    listsPanel->Hide();
    userPanel->Show();
    Layout();
}

void MainFrame::fillListBox(User *user) {
    std::list<std::shared_ptr<ShoppingList>> shoppinglists = user->getShoppingLists();
    for(auto const& shoppinglist : shoppinglists) {
        listBox->Append(shoppinglist->getName());
    }
}

void MainFrame::onAddItemButtonClicked(wxCommandEvent &evt) {
    addItemFromInput();
}

void MainFrame::onItemInputEnter(wxCommandEvent &evt) {
    addItemFromInput();
}

void MainFrame::addItemFromInput() {
    if(!itemInputField->IsEmpty()) {
         //create the item
         wxString itemName = itemInputField->GetValue();
         int quantity = spinCtrl->GetValue();
         Item myItem(itemName.ToStdString(), "", quantity);

         //add the item to the corresponding shopping list
         std::string shoppingListName = listBox->GetString(listBox->GetSelection()).ToStdString();
        auto selectedListItr = (*selectedUser).findShoppingList(shoppingListName);
        (*selectedListItr)->addItem(myItem);

         // update the itemListBox
         itemCheckListBox->Clear();
         quantityListBox->Clear();
         fillItemListBox(selectedUser);

        //add the item details to the checkListBox
         /*itemCheckListBox->Append(itemName);
         wxString itemQuantity = wxString::Format("%d",quantity);
         quantityListBox->Append(itemQuantity);
          */

         //reset controls
         spinCtrl->SetValue(1);
         itemInputField->Clear();
         itemInputField->SetFocus();
    }
}

void MainFrame::onBackItemsButtonClicked(wxCommandEvent &evt) {
    itemCheckListBox->Clear();
    quantityListBox->Clear();
    itemInputField->Clear();
    itemsPanel->Hide();
    listsPanel->Show();
    Layout();
}

void MainFrame::fillItemListBox(User* user) {
    std::string listName = listBox->GetString(listBox->GetSelection()).ToStdString();
    auto selectedList = (*selectedUser).findShoppingList(listName);
    std::vector<Item> items = (*selectedList)->getItems();
    for (const auto& item : items) {
        wxString itemName = item.getName();
        itemCheckListBox->Append(itemName);
        wxString itemQuantity = wxString::Format("%d", item.getQuantity());
        quantityListBox->Append(itemQuantity);
    }
}

void MainFrame::onItemCheckListKeyDown(wxKeyEvent &evt) {
    int itemIndex = itemCheckListBox->GetSelection();
    switch( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if(itemIndex != wxNOT_FOUND) {
                std::string listName = listBox->GetString(listBox->GetSelection()).ToStdString();
                auto selectedListItr = (*selectedUser).findShoppingList(listName);
                std::string itemName = (itemCheckListBox->GetString(itemIndex).ToStdString());
                (*selectedListItr)->removeItem(itemName);

                itemCheckListBox->Delete(itemIndex);
                quantityListBox->Delete(itemIndex);
            }
            break;
    }
}

void MainFrame::onShareListButtonClicked(wxCommandEvent &evt) {
    wxTextEntryDialog dialog(this,
                      wxT("Enter a user you want to share the list with."), wxT("Share"));
    if (dialog.ShowModal() == wxID_OK) {
        std::string username = dialog.GetValue().ToStdString();
        try {
            auto userItr = getUser(username);
            int listIndex = listBox->GetSelection();

            wxString listName = listBox->GetString(listIndex);
            auto listItr = (*selectedUser).findShoppingList(listName.ToStdString());

            // adding the list

            (*userItr).addShoppingList(*listItr);
            listBox->Append(listName);  //this adds the listName to listboxes of all users
            // i have to clear and then fill again the selected user's list box
            listBox->Clear();
            fillListBox(selectedUser);

            wxLogMessage(listName + " shared with " + username);
        }
        catch(std::runtime_error& e) {
            wxLogError( e.what());
            return;
        }
    }

}





