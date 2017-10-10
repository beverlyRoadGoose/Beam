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

MainFrame::MainFrame(const wxString & title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 800)) {
    menuBar = new wxMenuBar;

    podcastsMenu = new wxMenu;
    subscriptionsMenu = new wxMenu;

    quitMenuItem = new wxMenuItem(podcastsMenu, wxID_EXIT, wxT("Quit"));
    discoverPodcastsMenuItem = new wxMenuItem(podcastsMenu, ID_DISCOVER_PODCASTS, wxT("Discover podcasts"));
    podcastsMenu->Append(discoverPodcastsMenuItem);
    menuBar->Append(podcastsMenu, wxT("Podcasts"));

    checkNewEpisodesMenuItem = new wxMenuItem(subscriptionsMenu, ID_CHECK_NEW_EPISODES, wxT("Check for new episodes"));
    subscriptionsMenu->Append(checkNewEpisodesMenuItem);
    menuBar->Append(subscriptionsMenu, wxT("Subscriptions"));

    tabsManager = new wxNotebook(this, -1, wxPoint(-1, -1), wxSize(-1, -1), wxNB_TOP);

    discoveryTabPanel = new DiscoveryPanel(tabsManager);
    tabsManager->AddPage(discoveryTabPanel, wxT("Discover Podcasts"));

    podcastsTabPanel = new PodcastsPanel(tabsManager);
    tabsManager->AddPage(podcastsTabPanel, wxT("Subscriptions"));
    
    this->SetMenuBar(menuBar);
    this->SetMinSize(wxSize(500, 500));
    this->Centre();
}

void MainFrame::quit(wxCommandEvent & event) {
    this->Close(true);
}

void MainFrame::displayDiscoverPodcastsInterface(wxCommandEvent &event) {
    // TODO discover podcasts
}

void MainFrame::displayCheckNewEpisodesInterface(wxCommandEvent &event) {
    // TODO check for new episodes
}

wxMenuBar * MainFrame::getMenuBar() {
    return menuBar;
}

wxMenu * MainFrame::getPodcastsMenu() {
    return podcastsMenu;
}

wxMenu * MainFrame::getSubscriptionsMenu() {
    return subscriptionsMenu;
}

wxMenuItem * MainFrame::getQuitMenuItem() {
    return quitMenuItem;
}

wxMenuItem * MainFrame::getDiscoverPodcastsMenuItem() {
    return discoverPodcastsMenuItem;
}

wxMenuItem * MainFrame::getCheckNewEpisodesMenuItem() {
    return checkNewEpisodesMenuItem;
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(wxID_EXIT,  MainFrame::quit)
    EVT_MENU(ID_DISCOVER_PODCASTS, MainFrame::displayDiscoverPodcastsInterface)
    EVT_MENU(ID_CHECK_NEW_EPISODES, MainFrame::displayCheckNewEpisodesInterface)
END_EVENT_TABLE()