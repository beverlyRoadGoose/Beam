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

#include <iostream>
#include "podcasts_panel.h"

PodcastsPanel::PodcastsPanel(wxWindow * parent) : wxPanel(parent) {
    panelSizer = new wxBoxSizer(wxHORIZONTAL);

    podcastsListPanel = new PodcastsListPanel(this);
    podcastsListPanel->SetBackgroundColour(wxColour(wxT("#ffffff")));
    panelSizer->Add(podcastsListPanel, 1, wxALL | wxEXPAND, 4);

    episodesListPanel = new wxPanel(this);
    episodesListPanel->SetBackgroundColour(wxColour(wxT("#ffffff")));
    panelSizer->Add(episodesListPanel, 5, wxALL | wxEXPAND, 4);

    this->SetSizer(panelSizer);
}
