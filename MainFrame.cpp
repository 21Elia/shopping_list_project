//
// Created by Elia Awad on 05/07/24.
//

#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <memory>
#include "User.h"
#include "ShoppingList.h"
#include <fstream>
#include <algorithm>
#include <filesystem>

enum IDs {
    WXK_MACOS_DELETE = 8
};

static int nextUserID = 1;
static int nextListID = 1;

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title){
    setupUserMenu();
    setupListsMenu();
    setupItemsMenu();
    bindEventHandlers();
    loadDataToUI();

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

    //on close
    this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onWindowClosed, this);
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
    }else if(isInUsers(username.ToStdString())) {
        wxMessageBox("User already existing!", "Error", wxICON_ERROR);
        return;
    }

    // adding the new user

    User addedUser(username.ToStdString());
    addedUser.setID(++nextUserID);

    users.push_back(addedUser);
    userListBox->Insert(addedUser.getName(), userListBox->GetCount());
    userInputField->Clear();
    userInputField->SetFocus();
}

void MainFrame::onUserListKeyDown(wxKeyEvent &evt) {
    int index = userListBox->GetSelection();
    switch( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if (index != wxNOT_FOUND) {
                std::string username = userListBox->GetString(index).ToStdString();
                auto selectedUser = findUser(username);

                // updating usersListsMap
                int userID = selectedUser->getID();
                usersListsMap.erase(userID);

                // updating shareMap
                auto shoppingLists = selectedUser->getShoppingLists();
                for(const auto& shoppingList : shoppingLists) {
                    std::list<User>& sharedUsers = shareMap[shoppingList->getID()];
                    for(auto itr = sharedUsers.begin(); itr != sharedUsers.end(); ) {
                        if(itr->getName() == selectedUser->getName())
                            itr = sharedUsers.erase(itr);
                        else
                            ++itr;
                    }
                }

                // case for when the sharedUsers size is 1 -> MEANING THE USER HAS A LIST AND THAT LIST IS SHARED WITH HIMSELF
                for(const auto& shoppingList : shoppingLists) {
                    std::list<User>& sharedUsers = shareMap[shoppingList->getID()];
                    if(sharedUsers.size() == 1)
                        sharedUsers.clear();
                }

                // removing the user from users
                users.erase(selectedUser);
                userListBox->Delete(index);
            }
            break;
    }
}

std::vector<User>::iterator MainFrame::findUser(const std::string &username) {
    auto it = users.begin();
    while(it != users.end()) {
        if((*it).getName() == username)
            break;
        it++;
    }
    if(it != users.end())
        return it;
    else
        throw std::runtime_error("User not found.");
}

std::vector<User>::iterator MainFrame::findUserOnID(int num) {
    auto it = users.begin();
    while(it != users.end()) {
        if((*it).getID() == num)
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
    myShoppingList->setID(++nextListID);

    //updating the usersListsMap
    usersListsMap[currentUser->getID()].push_back(myShoppingList->getID());

    try {
        currentUser->addShoppingList(myShoppingList);
    }
    catch(std::invalid_argument& e) {
        wxLogMessage(e.what(), "Error");
        listInputField->Clear();
        return;
    }
    //adding the listName to the listBox
    listBox->Append(listName);
    listInputField->Clear();
    listInputField->SetFocus();
}

void MainFrame::onListKeyDown(wxKeyEvent &evt) {
    int index = listBox->GetSelection();
    switch ( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if(index != wxNOT_FOUND && index >= 0 && index < listBox->GetCount()) {
                std::string listName = listBox->GetString(index).ToStdString();
                currentList = *currentUser->findShoppingList(listName);

                // update usersListsMap
                int listID = currentList->getID();
                auto& listIDs = usersListsMap[currentUser->getID()];
                listIDs.remove(listID);

                // update shareMap
                std::list<User>& currentListSharedUsers = shareMap[listID];
                for(auto it = currentListSharedUsers.begin(); it != currentListSharedUsers.end(); ++it) {
                    if(it->getName() == currentUser->getName()) {
                        it = currentListSharedUsers.erase(it); // erase function removes the element it points to and
                                                        // also returns an iterator to the next element to avoid it pointing to null
                        break;
                    }
                }

                //case for when the sharedUsers size is 1 -> MEANING THE USER HAS A LIST AND THAT LIST IS SHARED WITH HIMSELF
                auto shoppingLists = currentUser->getShoppingLists();
                for(const auto& shoppingList : shoppingLists) {
                    std::list<User>& sharedUsers = shareMap[shoppingList->getID()];
                    if(sharedUsers.size() == 1)
                        sharedUsers.clear();
                }


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
        currentList = ( *(currentUser->findShoppingList(listName)) );
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
    for(auto const& shoppingList : shoppinglists) {
        listBox->Append(shoppingList->getName());
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
    updateLists(currentUser);
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
        if (index >= 0 && index < itemCheckListBox->GetCount()) {
            itemCheckListBox->Check(index, item.isChecked());
        }
        quantityListBox->Append(itemQuantity);
    }
}

void MainFrame::onItemCheckListKeyDown(wxKeyEvent &evt) {
    int itemIndex = itemCheckListBox->GetSelection();
    switch( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if(itemIndex != wxNOT_FOUND && itemIndex >= 0 && itemIndex < itemCheckListBox->GetCount()) {
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
                      wxT("Enter the username you want to share the list with:"), wxT("Share"));
    if (dialog.ShowModal() == wxID_OK) {
        std::string username = dialog.GetValue().ToStdString();
        try {
            auto otherUser = findUser(username); // throws exception if not found
            int listIndex = listBox->GetSelection();
            wxString listName = listBox->GetString(listIndex);

            if ( otherUser->isInShoppingLists(listName.ToStdString()) ) {
                wxMessageBox(wxString::Format("%s already has a list with this name!", username),
                             "Error", wxICON_ERROR);
                return;
            }

            if(currentList->isShared()) {
                auto& sharedUsers = shareMap[currentList->getID()];
                sharedUsers.push_back(*otherUser);
                otherUser->addShoppingList(currentList);
                wxMessageBox(wxString::Format("%s shared with %s!", listName, username));
            }else {
                currentList->setShared(true);
                shareMap[currentList->getID()].push_back(*otherUser); //adding otherUser in the empty vector of sharedUsers
                otherUser->addShoppingList(currentList);
                wxMessageBox(wxString::Format("%s shared with %s", listName, username));
            }
        }catch(std::exception& e) {
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
    if(index == wxNOT_FOUND || index < 0 || index >= itemCheckListBox->GetCount())
        return;
    wxString itemName = itemCheckListBox->GetString(index);
    Item& currentItem = currentList->getItem(itemName.ToStdString());
    currentItem.setCheck(itemCheckListBox->IsChecked(index));
}

bool MainFrame::isInUsers(const std::string &username) {
    bool found = false;
    auto it = users.begin();
    while(it != users.end()) {
        if (username == (*it).getName()) {
            found = true;
            break;
        }
        it++;
    }
    return found;
}

void MainFrame::onWindowClosed(wxCloseEvent &evt) {
    saveData("data.txt");
    evt.Skip();
}

void MainFrame::saveData(const std::string& fileName) {
    std::ofstream outFile;
    outFile.open("data.txt");
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


void MainFrame::loadDataToUI() {
    loadData("data.txt");
    for(const auto& user : users) {
        userListBox->Append(user.getName());
        auto lists = user.getShoppingLists();
        for (const auto& list : lists) {
            listBox->Append(list->getName());
            auto items = list->getItems();
            for (const auto& item : items) {
                itemCheckListBox->Append(item.getName());
                itemCheckListBox->Check(itemCheckListBox->GetCount() -1, item.isChecked());
                wxString quantityStr = wxString::Format("%d", item.getQuantity());
                quantityListBox->Append(quantityStr);
            }
        }
    }
}

void MainFrame::loadData(const std::string &fileName) {
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

                User& sharedUser = *findUser(username); // throws exception if not found (shouldn't throw any exception tho!!)
                sharedUsers.push_back(sharedUser);

                sharedUser.removeShoppingListOnID(listID);
                sharedUser.addShoppingList(findShoppingListByID(listID));

            }catch(std::exception& e) {
                wxLogMessage(e.what(), "Error");
                return;
            }
        }
        shareMap[listID] = sharedUsers;
    }
    inFile.close();
}

std::shared_ptr<ShoppingList> MainFrame::findShoppingListByID(int listID) {
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



