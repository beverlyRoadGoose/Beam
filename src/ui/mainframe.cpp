/*
 *  Copyright 2017 Oluwatobi Adeyinka
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "mainframe.h"

MainFrame::MainFrame(const wxString & title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 500)) {
    menuBar = new wxMenuBar;
    fileMenu = new wxMenu;
    podcastsMenu = new wxMenu;

    quitMenuItem = new wxMenuItem(fileMenu, wxID_EXIT, wxT("&Quit\tCtrl+W"));
    fileMenu->Append(quitMenuItem);

    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(podcastsMenu, wxT("&Podcasts"));

    this->SetMenuBar(menuBar);
    this->Centre();
}

void MainFrame::quit(wxCommandEvent & event) {
    this->Close(true);
}

wxMenuBar * MainFrame::getMenuBar() {
    return menuBar;
}

wxMenu * MainFrame::getFileMenu() {
    return fileMenu;
}

wxMenu * MainFrame::getPodcastsMenu() {
    return podcastsMenu;
}

wxMenuItem * MainFrame::getQuitMenuItem() {
    return quitMenuItem;
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(wxID_EXIT,  MainFrame::quit)
END_EVENT_TABLE()