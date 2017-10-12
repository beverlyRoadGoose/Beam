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

TopPodcastsPanel::TopPodcastsPanel(wxWindow * parent) : wxScrolledWindow(parent) {
    mainSizer = new wxBoxSizer(wxVERTICAL);

    setupSectionHeader();

    this->SetBackgroundColour(wxColour(wxT("#ffffff")));
    this->SetSizer(mainSizer);

    // this part makes the scrollbars show up
    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(5, 5);
}

void TopPodcastsPanel::setupSectionHeader() {
    auto * titlePanel = new wxPanel(this);
    auto * titlePanelSizer = new wxBoxSizer(wxHORIZONTAL);
    auto * sectionTitle = new wxStaticText(titlePanel, wxID_ANY, wxT("Top Podcasts"));

    wxFont sectionTitleFont = sectionTitle->GetFont();
    sectionTitleFont.SetPointSize(17);
    sectionTitle->SetFont(sectionTitleFont);

    titlePanel->SetBackgroundColour(wxColour(wxT("#ffffff")));
    titlePanelSizer->Add(sectionTitle, 1, wxALL | wxEXPAND, 5);
    titlePanel->SetSizer(titlePanelSizer);

    mainSizer->Add(titlePanel, 1, wxBOTTOM | wxEXPAND, 4);
}
