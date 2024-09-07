//
// Created by Elia Awad on 04/09/24.
//

#include "MainController.h"
#include "MainFrame.h"
#include <list>
#include "User.h"
#include "ShoppingList.h"
#include <wx/wx.h>
#include <map>

enum IDs {
    WXK_MACOS_DELETE = 8
};

MainController::MainController(MainFrame *view) : view(view), nextUserID(0), nextListID(0), dataManager() {
    fileName = "data.txt";
    //loadData();
}

void MainController::onAddUserButtonClicked(wxCommandEvent &evt) {
    addUserFromInput();
}

void MainController::onUserInputEnter(wxCommandEvent &evt) {
    addUserFromInput();
}

void MainController::addUserFromInput() {
    wxString username = view->getUserInputField()->GetValue();
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
    unsigned int pos = view->getUserListBox()->GetCount();
    view->getUserListBox()->Insert(addedUser.getName(), pos);
    view->getUserInputField()->Clear();
    view->getUserInputField()->SetFocus();
}

void MainController::onUserListKeyDown(wxKeyEvent &evt) {
    int index = view->getUserListBox()->GetSelection();
    switch( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if (index != wxNOT_FOUND) {
                std::string username = view->getUserListBox()->GetString(index).ToStdString();
                auto selectedUser = findUser(username, users);

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
                view->getUserListBox()->Delete(index);
            }
            break;
    }
}

void MainController::onUserListDoubleClick(wxMouseEvent &evt) {
    int index = view->getUserListBox()->GetSelection();
    if(index != wxNOT_FOUND) {
        std::string username = view->getUserListBox()->GetString(index).ToStdString();
        currentUser = &( *findUser(username, users) );
        updateLists(currentUser);

        view->getUserPanel()->Hide();
        view->getListsPanel()->Show();
        view->Layout();
        view->getListInputField()->SetFocus();
    }
    evt.Skip();
}

void MainController::onAddListButtonClicked(wxCommandEvent &evt) {
    addListFromInput();
}
void MainController::onListInputEnter(wxCommandEvent &evt) {
    addListFromInput();
}

void MainController::addListFromInput() {
    wxString listName = view->getListInputField()->GetValue();
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
        view->getListInputField()->Clear();
        return;
    }
    //adding the listName to the listBox
    view->getListBox()->Append(listName);
    view->getListInputField()->Clear();
    view->getListInputField()->SetFocus();
}

void MainController::onListDoubleClick(wxMouseEvent &evt) {
    int index = view->getListBox()->GetSelection();
    if(index != wxNOT_FOUND) {
        std::string listName = view->getListBox()->GetString(index).ToStdString();
        currentList = ( *(currentUser->findShoppingList(listName)) );
        updateItems(currentList);
        view->getItemInputField()->Clear();
        view->getListsPanel()->Hide();
        view->getItemsPanel()->Show();
        view->Layout();
    }
    evt.Skip();
}

void MainController::onBackListsButtonClicked(wxCommandEvent &evt) {
    view->getListsPanel()->Hide();
    view->getUserPanel()->Show();
    view->Layout();
}

void MainController::onAddItemButtonClicked(wxCommandEvent &evt) {
    addItemFromInput();
}

void MainController::onItemInputEnter(wxCommandEvent &evt) {
    addItemFromInput();
}

void MainController::addItemFromInput() {
    wxString itemName = view->getItemInputField()->GetValue();
    if (itemName.IsEmpty()) {
        wxMessageBox("Item name cannot be empty!", "Error", wxICON_ERROR);
        return;
    }
    //create the item
    int quantity = view->getSpinCtrl()->GetValue();
    Item myItem(itemName.ToStdString(), "", quantity);
    currentList->addItem(myItem);

    // update the itemListBox
    updateItems(currentList);

    //reset controls
    view->getSpinCtrl()->SetValue(0);
    view->getItemInputField()->Clear();
    view->getItemInputField()->SetFocus();
}

void MainController::onBackItemsButtonClicked(wxCommandEvent &evt) {
    updateLists(currentUser);
    view->getItemsPanel()->Hide();
    view->getListsPanel()->Show();
    view->Layout();
}

void MainController::onShareListButtonClicked(wxCommandEvent &evt) {
    wxTextEntryDialog dialog(view,
                             wxT("Enter the username you want to share the list with:"), wxT("Share"));
    if (dialog.ShowModal() == wxID_OK) {
        std::string username = dialog.GetValue().ToStdString();
        try {
            auto otherUser = findUser(username, users); // throws exception if not found
            int listIndex = view->getListBox()->GetSelection();
            wxString listName = view->getListBox()->GetString(listIndex);

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

void MainController::onListKeyDown(wxKeyEvent &evt) {
    int index = view->getListBox()->GetSelection();
    switch ( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if(index != wxNOT_FOUND && index >= 0 && index < view->getListBox()->GetCount()) {
                std::string listName = view->getListBox()->GetString(index).ToStdString();
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
                view->getListBox()->Delete(index);
            }
            break;
    }
}

void MainController::onItemCheckListKeyDown(wxKeyEvent &evt) {
    int itemIndex = view->getItemCheckListBox()->GetSelection();
    switch( evt.GetKeyCode() ) {
        case WXK_MACOS_DELETE:
            if(itemIndex != wxNOT_FOUND && itemIndex >= 0 && itemIndex < view->getItemCheckListBox()->GetCount()) {
                std::string itemName = (view->getItemCheckListBox()->GetString(itemIndex).ToStdString());
                currentList->removeItem(itemName);
                view->getItemCheckListBox()->Delete(itemIndex);
                view->getQuantityListBox()->Delete(itemIndex);
            }
            break;
    }
}

void MainController::onItemChecked(wxCommandEvent &evt) {
    setItemCheckStatus();
}

void MainController::setItemCheckStatus() {
    int index = view->getItemCheckListBox()->GetSelection();
    if(index == wxNOT_FOUND || index < 0 || index >= view->getItemCheckListBox()->GetCount())
        return;
    wxString itemName = view->getItemCheckListBox()->GetString(index);
    Item& currentItem = currentList->getItem(itemName.ToStdString());
    currentItem.setCheck(view->getItemCheckListBox()->IsChecked(index));
}

void MainController::onWindowClosed(wxCloseEvent &evt) {
    saveData();
    evt.Skip();
}

void MainController::saveData(){
    dataManager.saveData(fileName, users, usersListsMap, shareMap, nextUserID, nextListID);
}

void MainController::loadData() {
    dataManager.loadData(fileName, users, usersListsMap, shareMap, nextUserID, nextListID);
    // loading data to the user interface
    for(const auto& user : users) {
        view->getUserListBox()->Append(user.getName());
        auto lists = user.getShoppingLists();
        for (const auto& list : lists) {
            view->getListBox()->Append(list->getName());
            auto items = list->getItems();
            for (const auto& item : items) {
                view->getItemCheckListBox()->Append(item.getName());
                view->getItemCheckListBox()->Check(view->getItemCheckListBox()->GetCount() -1,
                                                   item.isChecked());
                wxString quantityStr = wxString::Format("%d", item.getQuantity());
                view->getQuantityListBox()->Append(quantityStr);
            }
        }
    }
}

bool MainController::isInUsers(const std::string &username) {
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

std::vector<User>::iterator MainController::findUser(const std::string &username, std::vector<User>& users) {
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

void MainController::updateLists(User *user) {
    view->getListBox()->Clear();
    std::list<std::shared_ptr<ShoppingList>> shoppinglists = user->getShoppingLists();
    for(auto const& shoppingList : shoppinglists) {
        view->getListBox()->Append(shoppingList->getName());
    }
}

void MainController::updateItems(const std::shared_ptr<ShoppingList> &shoppingList) {
    view->getItemCheckListBox()->Clear();
    view->getQuantityListBox()->Clear();

    std::vector<Item> items = (currentList)->getItems();

    for (const auto& item : items) {
        wxString itemName = item.getName();
        wxString itemQuantity = wxString::Format("%d", item.getQuantity());
        unsigned int index = view->getItemCheckListBox()->GetCount();

        view->getItemCheckListBox()->Append(itemName);
        if (index < view->getItemCheckListBox()->GetCount()) {
            view->getItemCheckListBox()->Check(index, item.isChecked());
        }
        if(item.isUndefinedQuantity())
            view->getQuantityListBox()->Append(" ");
        else
            view->getQuantityListBox()->Append(itemQuantity);
    }
}