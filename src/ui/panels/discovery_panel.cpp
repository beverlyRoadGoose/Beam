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
#include <networking/network_utils.h>
#include <ui/widgets/discover_item_panel.h>
#include "discovery_panel.h"

DiscoveryPanel::DiscoveryPanel(wxWindow * parent) : wxScrolledWindow(parent) {
    panelManager = DiscoveryPanelManager();
    panelSizer = new wxBoxSizer(wxVERTICAL);

    std::vector<Podcast> dashPodcasts = panelManager.getDashPodcasts();

    for(std::vector<int>::size_type i = 0; i != dashPodcasts.size(); i++) {
        Podcast p = dashPodcasts[i];
        DiscoverItemPanel * itemPanel = new DiscoverItemPanel(this, p);
        panelSizer->Add(itemPanel, 1, wxALL | wxEXPAND, 4);
    }

    this->FitInside(); // ask the sizer about the needed size
    this->SetScrollRate(5, 5);

    this->SetSizer(panelSizer);
}
