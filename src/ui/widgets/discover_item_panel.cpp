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

#include "podcasts_list_item_panel.h"

#include "discover_item_panel.h"

DiscoverItemPanel::DiscoverItemPanel(wxWindow * parent, Podcast & podcast) : wxPanel(parent), podcast(podcast) {
    panelSizer = new wxBoxSizer(wxHORIZONTAL);
    wxImage::AddHandler(new wxJPEGHandler);

    wxString title = podcast.getTitle();
    wxString imageDir = podcast.getLocalImageDir();

    wxBitmap bitmap(imageDir, wxBITMAP_TYPE_JPEG);
    bitmap.SetWidth(250);
    bitmap.SetHeight(250);

    wxPanel * imagePanel = new wxPanel(this);
    imagePanel->SetSize(250, 250);

    wxStaticBitmap * sb = new wxStaticBitmap(imagePanel, -1, bitmap);
    sb->SetSize(250, 250);

    panelSizer->Add(imagePanel);

    this->SetBackgroundColour(wxColour(wxT("#ffffff")));
    this->SetWindowStyleFlag(wxBORDER_SUNKEN);
    this->SetSizer(panelSizer);
}
