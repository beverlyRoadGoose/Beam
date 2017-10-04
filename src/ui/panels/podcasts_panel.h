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

#include <wx/wx.h>

#ifndef BEAM_PODCASTS_PANEL_H
#define BEAM_PODCASTS_PANEL_H

class PodcastsPanel : public wxPanel {
private:
    wxBoxSizer * panelSizer;
    wxListBox * podcastsListBox;
    wxPanel * episodesListPanel;
public:
    explicit PodcastsPanel(wxWindow * parent);
};

const int ID_PODCASTS_LISTBOX = 1;
const int ID_EPISODES_LISTPANEL = 2;

#endif //BEAM_PODCASTS_PANEL_H
