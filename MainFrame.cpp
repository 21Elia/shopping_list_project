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
    itemCheckListBox->Bind(wxEVT_CHECKLISTBOX, &MainFrame::onItemChecked, this);
}

void MainFrame::onAddUserButtonClicked(wxCommandEvent &evt) {
    addUserFromInput();
}

void MainFrame::onUserInputEnter(wxCommandEvent &evt) {
    addUserFromInput();
}

void MainFrame::addUserFromInput() {
    wxString username = userInputField->GetValue();
    if (username.IsEmpty()) {
        wxMessageBox("User name cannot be empty!", "Error", wxICON_ERROR);
        return;
    }else if(isInList(username.ToStdString())) {
        wxMessageBox("User already existing!", "Error", wxICON_ERROR);
        return;
    }
    User user(username.ToStdString());
    users.push_back(user);
    userListBox->Insert(user.getUsername(), userListBox->GetCount());
    userInputField->Clear();
    userInputField->SetFocus();
}

void MainFrame::onUserListKeyDown(wxKeyEvent &evt) {
    int index = userListBox->GetSelection();
    switch( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if (index != wxNOT_FOUND) {
                std::string username = userListBox->GetString(index).ToStdString();
                auto it = findUser(username);
                users.erase(it);
                userListBox->Delete(index);
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
    if(it != users.end())
        return it;
    else
        throw std::runtime_error("User not found.");
}

void MainFrame::onUserListDoubleClick(wxMouseEvent &evt) {
    int index = userListBox->GetSelection();
    if(index != wxNOT_FOUND) {
        std::string username = userListBox->GetString(index).ToStdString();
        currentUser = &( *(findUser(username)) );
        updateLists(currentUser);

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
    if (listName.IsEmpty()) {
        wxMessageBox("List name cannot be empty!", "Error", wxICON_ERROR);
        return;
    }

    //creating shopping list and adding it to the corresponding user
    std::shared_ptr<ShoppingList> myShoppingList(new ShoppingList(listName.ToStdString()));

    try {
        (*currentUser).addShoppingList(myShoppingList);
    }
    catch(std::invalid_argument& e) {
        wxLogError(e.what());
        listInputField->Clear();
        return;
    }

    //adding the listName to the listBox
    listBox->Insert(listName, listBox->GetCount()); //second parameter is the listBox index
    listInputField->Clear();
    listInputField->SetFocus();
}

void MainFrame::onListKeyDown(wxKeyEvent &evt) {
    int index = listBox->GetSelection();
    switch ( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if(index != wxNOT_FOUND) {
                std::string listName = listBox->GetString(index).ToStdString();
                (*currentUser).removeShoppingList(listName);

                listBox->Delete(index);
            }
            break;
    }
}

void MainFrame::onListDoubleClick(wxMouseEvent &evt) {
    int index = listBox->GetSelection();
    if(index != wxNOT_FOUND) {
        std::string listName = listBox->GetString(index).ToStdString();
        currentList = (* (*currentUser).findShoppingList(listName) );
        updateItems(currentList);
        itemInputField->Clear();
        listsPanel->Hide();
        itemsPanel->Show();
        Layout();
    }
    evt.Skip();
}

void MainFrame::onBackListsButtonClicked(wxCommandEvent &evt) {
    listsPanel->Hide();
    userPanel->Show();
    Layout();
}

void MainFrame::updateLists(User *user) {
    listBox->Clear();
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
    wxString itemName = itemInputField->GetValue();
    if (itemName.IsEmpty()) {
        wxMessageBox("Item name cannot be empty!", "Error", wxICON_ERROR);
        return;
    }
    //create the item
    int quantity = spinCtrl->GetValue();
    Item myItem(itemName.ToStdString(), "", quantity);
    currentList->addItem(myItem);

    // update the itemListBox
    updateItems(currentList);

    //reset controls
    spinCtrl->SetValue(1);
    itemInputField->Clear();
    itemInputField->SetFocus();
}

void MainFrame::onBackItemsButtonClicked(wxCommandEvent &evt) {
    itemsPanel->Hide();
    listsPanel->Show();
    Layout();
}

void MainFrame::updateItems(const std::shared_ptr<ShoppingList> &shoppingList) {
    itemCheckListBox->Clear();
    quantityListBox->Clear();

    std::vector<Item> items = (currentList)->getItems();

    for (const auto& item : items) {
        wxString itemName = item.getName();
        wxString itemQuantity = wxString::Format("%d", item.getQuantity());
        int index = itemCheckListBox->GetCount();

        itemCheckListBox->Append(itemName);
        itemCheckListBox->Check(index, item.isChecked());
        quantityListBox->Append(itemQuantity);
    }
}

void MainFrame::onItemCheckListKeyDown(wxKeyEvent &evt) {
    int itemIndex = itemCheckListBox->GetSelection();
    switch( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if(itemIndex != wxNOT_FOUND) {
                std::string itemName = (itemCheckListBox->GetString(itemIndex).ToStdString());
                currentList->removeItem(itemName);
                itemCheckListBox->Delete(itemIndex);
                quantityListBox->Delete(itemIndex);
            }
            break;
    }
}

void MainFrame::onShareListButtonClicked(wxCommandEvent &evt) {
    wxTextEntryDialog dialog(this,
                      wxT("Enter the username you want to share the list with."), wxT("Share"));
    if (dialog.ShowModal() == wxID_OK) {
        std::string username = dialog.GetValue().ToStdString();
        try {
            auto otherUserItr = findUser(username); // throws exception
            int listIndex = listBox->GetSelection();
            wxString listName = listBox->GetString(listIndex);

            if ( (*otherUserItr).isInShoppingLists(listName.ToStdString()) ) {
                wxMessageBox(username + " already has a list with this name!");
                return;
            }

            (*otherUserItr).addShoppingList(currentList);
            listBox->Append(listName);
            // this adds the listName to list-boxes of all users, so I have to clear and then fill again the selected user's list box
            listBox->Clear();
            updateLists(currentUser);
        }catch(std::runtime_error& e) {
            wxMessageBox(e.what(), "Error", wxICON_ERROR);
            return;
        }
    }

}

void MainFrame::onItemChecked(wxCommandEvent &evt) {
    setItemCheckStatus();
}

void MainFrame::setItemCheckStatus() {
    int index = itemCheckListBox->GetSelection();
    if(index == wxNOT_FOUND)
        return;
    wxString itemName = itemCheckListBox->GetString(index);
    Item& currentItem = currentList->getItem(itemName.ToStdString());
    currentItem.setCheck(itemCheckListBox->IsChecked(index));
}

bool MainFrame::isInList(const std::string &username) {
    bool found = false;
    auto it = users.begin();
    while(it != users.end()) {
        if (username == (*it).getUsername()) {
            found = true;
            break;
        }
        it++;
    }
    return found;
}





