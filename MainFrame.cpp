//
// Created by Elia Awad on 05/07/24.
//

#include "MainFrame.h"
#include <wx/wx.h>
#include <memory>
#include "MainController.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title){
    controller = new MainController(this);
    setupUserMenu();
    setupListsMenu();
    setupItemsMenu();
    bindEventHandlers();

    controller->loadData();

    // start with showing user menu

    setupFrameSizers();
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
                              wxSP_ARROW_KEYS | wxTE_PROCESS_ENTER, 0, 100, 0);
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
    addUserButton->Bind(wxEVT_BUTTON, &MainController::onAddUserButtonClicked, controller);
    userInputField->Bind(wxEVT_TEXT_ENTER, &MainController::onUserInputEnter, controller);
    userListBox->Bind(wxEVT_KEY_DOWN, &MainController::onUserListKeyDown, controller);
    userListBox->Bind(wxEVT_LEFT_DCLICK, &MainController::onUserListDoubleClick, controller);

    //shopping lists menu control binds
    addListButton->Bind(wxEVT_BUTTON, &MainController::onAddListButtonClicked, controller);
    listInputField->Bind(wxEVT_TEXT_ENTER, &MainController::onListInputEnter, controller);
    listBox->Bind(wxEVT_KEY_DOWN, &MainController::onListKeyDown, controller);
    listBox->Bind(wxEVT_LEFT_DCLICK, &MainController::onListDoubleClick, controller);
    backListsButton->Bind(wxEVT_BUTTON, &MainController::onBackListsButtonClicked, controller);

    // items menu control binds
    backItemsButton->Bind(wxEVT_BUTTON, &MainController::onBackItemsButtonClicked, controller);
    addItemButton->Bind(wxEVT_BUTTON, &MainController::onAddItemButtonClicked, controller);
    shareListButton->Bind(wxEVT_BUTTON, &MainController::onShareListButtonClicked, controller);
    itemInputField->Bind(wxEVT_TEXT_ENTER, &MainController::onItemInputEnter, controller);
    spinCtrl->Bind(wxEVT_TEXT_ENTER, &MainController::onItemInputEnter, controller);
    itemCheckListBox->Bind(wxEVT_KEY_DOWN, &MainController::onItemCheckListKeyDown, controller);
    itemCheckListBox->Bind(wxEVT_CHECKLISTBOX, &MainController::onItemChecked, controller);

    //on close
    this->Bind(wxEVT_CLOSE_WINDOW, &MainController::onWindowClosed, controller);
}

wxPanel *MainFrame::getUserPanel() const {
    return userPanel;
}

wxTextCtrl *MainFrame::getUserInputField() const {
    return userInputField;
}

wxListBox *MainFrame::getUserListBox() const {
    return userListBox;
}

wxPanel *MainFrame::getListsPanel() const {
    return listsPanel;
}

wxTextCtrl *MainFrame::getListInputField() const {
    return listInputField;
}

wxListBox *MainFrame::getListBox() const {
    return listBox;
}

wxPanel *MainFrame::getItemsPanel() const {
    return itemsPanel;
}

wxTextCtrl *MainFrame::getItemInputField() const {
    return itemInputField;
}

wxSpinCtrl *MainFrame::getSpinCtrl() const {
    return spinCtrl;
}

wxCheckListBox *MainFrame::getItemCheckListBox() const {
    return itemCheckListBox;
}

wxListBox *MainFrame::getQuantityListBox() const {
    return quantityListBox;
}



