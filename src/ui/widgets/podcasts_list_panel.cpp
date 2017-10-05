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

#include "podcasts_list_panel.h"

PodcastsListPanel::PodcastsListPanel(wxWindow * parent) : wxPanel(parent) {
    sizer = new wxBoxSizer(wxVERTICAL);

    titleBar = new wxStaticText(this, wxID_ANY, wxT("Subscriptions"));
    wxFont titleBarFont = titleBar->GetFont();
    titleBarFont.SetPointSize(12);
    titleBarFont.SetWeight(wxFONTWEIGHT_BOLD);
    titleBar->SetFont(titleBarFont);
    sizer->Add(titleBar, 0, wxALIGN_CENTER_HORIZONTAL);

    this->SetSizer(sizer);
    this->SetWindowStyleFlag(wxBORDER_SUNKEN);
}
