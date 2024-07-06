//
// Created by Elia Awad on 05/07/24.
//

#include "App.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("Title Test");
    mainFrame->SetClientSize(800,600);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}
