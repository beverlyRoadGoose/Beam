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

#include <vector>
#include <wx/wx.h>
#include "discovery_panel.h"

DiscoveryPanel::DiscoveryPanel(wxWindow * parent) : wxScrolledWindow(parent) {
    panelManager = DiscoveryPanelManager();
    panelSizer = new wxBoxSizer(wxVERTICAL);

    wrapperPanel = new wxPanel(this);
    wrapperPanelSizer = new wxBoxSizer(wxVERTICAL);

    wrapperPanel->SetWindowStyleFlag(wxBORDER_SUNKEN);
    wrapperPanel->SetBackgroundColour(wxColour(wxT("#ffffff")));

    setupTopPodcastsSection();
    setupSocietyAndCultureSection();
    setupNewsAndPoliticsSection();
    setupComedySection();

    wrapperPanel->SetSizer(wrapperPanelSizer);
    panelSizer->Add(wrapperPanel, 1, wxALL | wxEXPAND, 5);
    this->SetSizer(panelSizer);

    this->FitInside();
    this->SetScrollRate(5, 5);
}

void DiscoveryPanel::setupTopPodcastsSection() {
    auto * titlePanel = new wxPanel(this);
    titlePanel->SetBackgroundColour(wxColour(wxT("#ffffff")));

    auto * sectionTitle = new wxStaticText(titlePanel, wxID_ANY, wxT("Top Podcasts"));
    wxFont sectionTitleFont = sectionTitle->GetFont();
    sectionTitleFont.SetPointSize(16);
    sectionTitle->SetFont(sectionTitleFont);

    wrapperPanelSizer->Add(titlePanel, 0, wxLEFT | wxTOP, 15);

    topPodcastsPanel = new TopPodcastsPanel(wrapperPanel, panelManager);
    wrapperPanelSizer->Add(topPodcastsPanel, 1, wxLEFT | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
}

void DiscoveryPanel::setupSocietyAndCultureSection() {
    auto * titlePanel = new wxPanel(this);
    titlePanel->SetBackgroundColour(wxColour(wxT("#ffffff")));

    auto * sectionTitle = new wxStaticText(titlePanel, wxID_ANY, wxT("Society and Culture"));
    wxFont sectionTitleFont = sectionTitle->GetFont();
    sectionTitleFont.SetPointSize(16);
    sectionTitle->SetFont(sectionTitleFont);

    wrapperPanelSizer->Add(titlePanel, 0, wxLEFT | wxTOP, 15);

    societyAndCulturePanel = new SocietyAndCulturePanel(wrapperPanel, panelManager);
    wrapperPanelSizer->Add(societyAndCulturePanel, 1, wxLEFT | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
}

void DiscoveryPanel::setupNewsAndPoliticsSection() {
    auto * titlePanel = new wxPanel(this);
    titlePanel->SetBackgroundColour(wxColour(wxT("#ffffff")));

    auto * sectionTitle = new wxStaticText(titlePanel, wxID_ANY, wxT("News and Politics"));
    wxFont sectionTitleFont = sectionTitle->GetFont();
    sectionTitleFont.SetPointSize(16);
    sectionTitle->SetFont(sectionTitleFont);

    wrapperPanelSizer->Add(titlePanel, 0, wxLEFT | wxTOP, 15);

    newsAndPoliticsPanel = new NewsAndPoliticsPanel(wrapperPanel, panelManager);
    wrapperPanelSizer->Add(newsAndPoliticsPanel, 1, wxLEFT | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
}

void DiscoveryPanel::setupComedySection() {
    auto * titlePanel = new wxPanel(this);
    titlePanel->SetBackgroundColour(wxColour(wxT("#ffffff")));

    auto * sectionTitle = new wxStaticText(titlePanel, wxID_ANY, wxT("Comedy"));
    wxFont sectionTitleFont = sectionTitle->GetFont();
    sectionTitleFont.SetPointSize(16);
    sectionTitle->SetFont(sectionTitleFont);

    wrapperPanelSizer->Add(titlePanel, 0, wxLEFT | wxTOP, 15);

    comedyPanel = new ComedyPanel(wrapperPanel, panelManager);
    wrapperPanelSizer->Add(comedyPanel, 1, wxLEFT | wxBOTTOM | wxRIGHT | wxEXPAND, 5);
}
