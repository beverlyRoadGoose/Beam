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

#include "podcasts_panel.h"

PodcastsPanel::PodcastsPanel(wxWindow * parent) : wxPanel(parent) {
    panelSizer = new wxBoxSizer(wxHORIZONTAL);

    podcastsListBox = new wxListBox(this, ID_PODCASTS_LISTBOX, wxPoint(-1, -1), wxSize(-1, -1));
    panelSizer->Add(podcastsListBox, 1, wxALL | wxEXPAND, 2);

    episodesListPanel = new wxPanel(this);
    panelSizer->Add(episodesListPanel, 5, wxALL | wxEXPAND, 2);

    this->SetSizer(panelSizer);
}
