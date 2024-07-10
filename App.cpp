//
// Created by Elia Awad on 05/07/24.
//

#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("Shopping List App");
    mainFrame->SetClientSize(1000,600);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}
