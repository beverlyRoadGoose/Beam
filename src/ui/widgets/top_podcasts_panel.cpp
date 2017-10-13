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

#include "top_podcasts_panel.h"
#include "discover_item_panel.h"

TopPodcastsPanel::TopPodcastsPanel(wxWindow * parent, DiscoveryPanelManager & panelManager) : wxScrolledWindow(parent) {
    mainSizer = new wxBoxSizer(wxVERTICAL);
    topPodcasts = panelManager.getTopPodcasts();

    setupSectionHeader();
    setupFirstRow();
    setupSecondRow();

    this->SetBackgroundColour(wxColour(wxT("#ffffff")));
    this->SetSizer(mainSizer);

    // this part makes the scrollbars show up
    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(5, 5);

}

void TopPodcastsPanel::setupSectionHeader() {
    auto * titlePanel = new wxPanel(this);
    titlePanel->SetBackgroundColour(wxColour(wxT("#ffffff")));

    auto * sectionTitle = new wxStaticText(titlePanel, wxID_ANY, wxT("Top Podcasts"));
    wxFont sectionTitleFont = sectionTitle->GetFont();
    sectionTitleFont.SetPointSize(16);
    sectionTitle->SetFont(sectionTitleFont);

    mainSizer->Add(titlePanel, 0, wxLEFT | wxBOTTOM, 5);
}

void TopPodcastsPanel::setupFirstRow() {
    auto * rowPanel = new wxPanel(this);
    auto * rowPanelSizer = new wxBoxSizer(wxHORIZONTAL);

    for (std::vector<int>::size_type i = 0; i != topPodcasts.size()/2; i++) {
        Podcast podcast = topPodcasts[i];
        auto * itemPanel = new DiscoverItemPanel(rowPanel, podcast);
        rowPanelSizer->Add(itemPanel, wxID_ANY, wxRIGHT | wxEXPAND, 10);
    }

    rowPanel->SetSizer(rowPanelSizer);
    mainSizer->Add(rowPanel, 1, wxALL | wxEXPAND, 5);
}

void TopPodcastsPanel::setupSecondRow() {
    auto * rowPanel = new wxPanel(this);
    auto * rowPanelSizer = new wxBoxSizer(wxHORIZONTAL);

    for (std::vector<int>::size_type i = 24; i != topPodcasts.size(); i++) {
        Podcast podcast = topPodcasts[i];
        auto * itemPanel = new DiscoverItemPanel(rowPanel, podcast);
        rowPanelSizer->Add(itemPanel, wxID_ANY, wxRIGHT | wxEXPAND, 10);
    }

    rowPanel->SetSizer(rowPanelSizer);
    mainSizer->Add(rowPanel, 1, wxALL | wxEXPAND, 5);
}
