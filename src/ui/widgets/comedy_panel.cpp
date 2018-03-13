/*
 *  Copyright 2018 Oluwatobi Adeyinka
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

#include "comedy_panel.h"
#include "discover_item_panel.h"

ComedyPanel::ComedyPanel(wxWindow *parent, DiscoveryPanelManager &panelManager) : wxScrolledWindow(parent){
    mainSizer = new wxBoxSizer(wxVERTICAL);
    podcasts = panelManager.getComedyPodcasts();

    setupFirstRow();
    setupSecondRow();

    this->SetBackgroundColour(wxColour(wxT("#ffffff")));
    this->SetSizer(mainSizer);
    this->FitInside();
    this->SetScrollRate(5, 5);
    this->SetMinSize(wxSize(-1, 380));
}

void ComedyPanel::setupFirstRow() {
    auto * rowPanel = new wxPanel(this);
    auto * rowPanelSizer = new wxBoxSizer(wxHORIZONTAL);

    for (std::vector<int>::size_type i = 0; i != (podcasts.size()/2); i++) {
        Podcast podcast = podcasts[i];
        auto * itemPanel = new DiscoverItemPanel(rowPanel, podcast);
        rowPanelSizer->Add(itemPanel, 0, wxRIGHT | wxEXPAND, 10);
    }

    rowPanel->SetSizer(rowPanelSizer);
    mainSizer->Add(rowPanel, 0, wxALL | wxEXPAND, 5);
}

void ComedyPanel::setupSecondRow() {
    auto * rowPanel = new wxPanel(this);
    auto * rowPanelSizer = new wxBoxSizer(wxHORIZONTAL);

    for (std::vector<int>::size_type i = 50; i != podcasts.size(); i++) {
        Podcast podcast = podcasts[i];
        auto * itemPanel = new DiscoverItemPanel(rowPanel, podcast);
        rowPanelSizer->Add(itemPanel, 0, wxRIGHT | wxEXPAND, 10);
    }

    rowPanel->SetSizer(rowPanelSizer);
    mainSizer->Add(rowPanel, 0, wxALL | wxEXPAND, 5);
}
