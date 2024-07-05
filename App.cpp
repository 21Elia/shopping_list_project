//
// Created by Elia Awad on 05/07/24.
//

#include "App.h"

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("Title Test");
    mainFrame->Show();
    return true;
}
