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

PodcastsListPanel::PodcastsListPanel(wxWindow * parent) : wxScrolledWindow(parent, wxID_ANY) {
    sizer = new wxBoxSizer(wxVERTICAL);

    this->SetSizer(sizer);
    this->SetWindowStyleFlag(wxBORDER_SUNKEN);

    // this part makes the scrollbars show up
    this->SetScrollRate(5, 5);
}
