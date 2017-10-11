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
#include "discovery_panel.h"

DiscoveryPanel::DiscoveryPanel(wxWindow * parent) : wxPanel(parent) {
    panelManager = DiscoveryPanelManager();
    panelSizer = new wxBoxSizer(wxHORIZONTAL);
    wxImage::AddHandler(new wxJPEGHandler);

    std::vector<Podcast> dashPodcasts = panelManager.getDashPodcasts();
    gridSizer = new wxGridSizer(7, 5, 5);

    for(std::vector<int>::size_type i = 0; i != dashPodcasts.size(); i++) {
        Podcast p = dashPodcasts[i];
        wxString title = p.getTitle();
        wxString imageDir = p.getLocalImageDir();
        wxBitmap bitmap(imageDir, wxBITMAP_TYPE_JPEG);

        wxPanel * imagePanel = new wxPanel(this);
        imagePanel->SetSize(500, 500);

        wxStaticBitmap * sb = new wxStaticBitmap(imagePanel, -1, bitmap);
        sb->SetSize(500, 500);

        gridSizer->Add(imagePanel, 0, wxEXPAND);
    }

    panelSizer->Add(gridSizer, 1);
    this->SetSizer(panelSizer);
}
