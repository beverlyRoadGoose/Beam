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

#include "discover_item_panel.h"

DiscoverItemPanel::DiscoverItemPanel(wxWindow * parent, Podcast & podcast) : wxPanel(parent), podcast(podcast) {
    panelSizer = new wxBoxSizer(wxVERTICAL);

    setupItemImage();
    setupItemName();
    setupItemAuthor();

    this->SetSizer(panelSizer);
}

void DiscoverItemPanel::setupItemImage() {
    auto * imagePanel = new wxPanel(this);
    imagePanel->SetSize(120, 120);

    wxInitAllImageHandlers();
    wxBitmap bitmap(podcast.getLocalImageDir(), wxBITMAP_TYPE_ANY);
    bitmap.SetWidth(120);
    bitmap.SetHeight(120);

    auto * staticBitmap = new wxStaticBitmap(imagePanel, wxID_ANY, bitmap);
    staticBitmap->SetSize(120, 120);

    panelSizer->Add(imagePanel);
}

void DiscoverItemPanel::setupItemName() {
    auto * titlePanel = new wxPanel(this);
    auto * titlePanelSizer = new wxBoxSizer(wxHORIZONTAL);
    const char * title = podcast.getTitle().c_str();

    auto * sectionTitle = new wxStaticText(titlePanel, wxID_ANY, title, wxDefaultPosition, wxSize(120, 20), wxELLIPSIZE_END);
    sectionTitle->Wrap(120);

    wxFont sectionTitleFont = sectionTitle->GetFont();
    sectionTitleFont.SetPointSize(12);
    sectionTitle->SetFont(sectionTitleFont);

    titlePanel->SetBackgroundColour(wxColour(wxT("#ffffff")));
    titlePanelSizer->Add(sectionTitle);
    titlePanel->SetSizer(titlePanelSizer);

    panelSizer->Add(titlePanel);
}

void DiscoverItemPanel::setupItemAuthor() {
    auto * authorPanel = new wxPanel(this);
    auto * authorPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    const char * author = podcast.getPublisher().c_str();

    auto * sectionTitle = new wxStaticText(authorPanel, wxID_ANY, author, wxDefaultPosition, wxSize(120, 20), wxELLIPSIZE_END);
    sectionTitle->Wrap(120);
    sectionTitle->SetForegroundColour(wxColour(wxT("#808080")));

    wxFont sectionTitleFont = sectionTitle->GetFont();
    sectionTitleFont.SetPointSize(10);
    sectionTitle->SetFont(sectionTitleFont);

    authorPanel->SetBackgroundColour(wxColour(wxT("#ffffff")));
    authorPanelSizer->Add(sectionTitle);
    authorPanel->SetSizer(authorPanelSizer);

    panelSizer->Add(authorPanel);
}
