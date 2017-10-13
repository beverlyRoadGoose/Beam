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

#include <entities/podcast.h>
#include "podcasts_list_item_panel.h"

#ifndef BEAM_DISCOVER_ITEM_PANEL_H
#define BEAM_DISCOVER_ITEM_PANEL_H


class DiscoverItemPanel : public wxPanel {
private:
    Podcast podcast;
    wxBoxSizer * panelSizer;

    void setupItemImage();
    void setupItemName();
    void setupItemAuthor();
public:
    DiscoverItemPanel(wxWindow * parent, Podcast & podcast);
};


#endif //BEAM_DISCOVER_ITEM_PANEL_H
