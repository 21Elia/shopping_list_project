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

    // setting up the frame sizer

    wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
    frameSizer->Add(userPanel, wxSizerFlags().Proportion(1).Expand());
    frameSizer->Add(listsPanel, wxSizerFlags().Proportion(1).Expand());
    frameSizer->Add(itemsPanel, wxSizerFlags().Proportion(1).Expand());

    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(frameSizer,wxSizerFlags().Border(wxALL, 75).Expand());
    SetSizerAndFit(outerSizer);


    listsPanel->Hide();
    itemsPanel->Hide();
}

void MainFrame::setupUserMenu() {
    userPanel = new wxPanel(this);

    newUserText = new wxStaticText(userPanel, wxID_ANY, "Add a new user");
    newUserText->SetFont(wxFontInfo(wxSize(0,24)).Bold());

    userInputField = new wxTextCtrl(userPanel, wxID_ANY, "",
                                    wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    userInputField->SetFont(wxFontInfo(wxSize(0,18)));
    addUserButton = new wxButton(userPanel, wxID_ANY, "Add");

    selectUserText = new wxStaticText(userPanel, wxID_ANY,"Select a user");
    selectUserText->SetFont(wxFontInfo(wxSize(0,24)).Bold());

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
    mainSizer->AddSpacer(25);
    mainSizer->Add(selectUserText, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(25);
    mainSizer->Add(userListBox, wxSizerFlags().Expand().Proportion(1));

    userPanel->SetSizer(mainSizer);
}

void MainFrame::setupListsMenu() {
    wxFont headlineFont(wxFontInfo(wxSize(0,36)).Bold());
    wxFont inputFont(wxFontInfo(wxSize(0,18)));
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

void MainFrame::setupItemsMenu() {
    wxFont headlineFont(wxFontInfo(wxSize(0,36)).Bold());
    wxFont inputFont(wxFontInfo(wxSize(0,20)));
    wxFont buttonFont(wxFontInfo(wxSize(0,14)));

    itemsPanel = new wxPanel(this);

    backItemsButton = new wxButton(itemsPanel, wxID_ANY, "Back");
    backItemsButton->SetFont(buttonFont);

    headlineItemsMenuText = new wxStaticText(itemsPanel, wxID_ANY, "Add or Delete Items");
    headlineItemsMenuText->SetFont(headlineFont);

    newItemText = new wxStaticText(itemsPanel, wxID_ANY, "New Item");
    newItemText->SetFont(wxFontInfo(wxSize(0,20)).Bold());

    itemInputField = new wxTextCtrl(itemsPanel, wxID_ANY, "",
                                    wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    itemInputField->SetFont(inputFont);

    spinCtrl = new wxSpinCtrl(itemsPanel, wxID_ANY, "",wxDefaultPosition,wxDefaultSize,
                              wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER, 1, 100, 1);

    addItemButton = new wxButton(itemsPanel, wxID_ANY, "Add");
    addItemButton->SetFont(buttonFont);

    itemCheckListBox = new wxCheckListBox(itemsPanel, wxID_ANY,
                                          wxDefaultPosition, wxSize(-1, 400));
    quantityListBox = new wxListBox(itemsPanel, wxID_ANY,
                                    wxDefaultPosition, wxSize(40,400));

    setupItemsMenuSizers();
    //itemsPanel->Hide();

}

void MainFrame::setupItemsMenuSizers() {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->AddSpacer(25);
    mainSizer->Add(headlineItemsMenuText, wxSizerFlags().CenterHorizontal());
    mainSizer->AddSpacer(25);

    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    inputSizer->Add(newItemText, wxSizerFlags().Proportion(0));
    inputSizer->AddSpacer(10);
    inputSizer->Add(itemInputField, wxSizerFlags().Proportion(1));
    inputSizer->AddSpacer(10);
    inputSizer->Add(spinCtrl, wxSizerFlags().Proportion(0));
    inputSizer->AddSpacer(10);
    inputSizer->Add(addItemButton, wxSizerFlags().Proportion(0));

    mainSizer->Add(inputSizer, wxSizerFlags().Expand());
    mainSizer->AddSpacer(10);

    wxBoxSizer* listSizer = new wxBoxSizer(wxHORIZONTAL);
    listSizer->AddSpacer(97);
    listSizer->Add(itemCheckListBox, wxSizerFlags().Proportion(1));
    listSizer->AddSpacer(5);
    listSizer->Add(quantityListBox, wxSizerFlags().Proportion(0));
    listSizer->AddSpacer(110);
    mainSizer->Add(listSizer, wxSizerFlags().Expand());
    //mainSizer->Add(itemCheckListBox, wxSizerFlags().Expand().Proportion(1));

    itemsPanel->SetSizer(mainSizer);
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
    return it;
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





