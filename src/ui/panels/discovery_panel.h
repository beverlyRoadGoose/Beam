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

#ifndef BEAM_DISCOVERY_PANEL_H
#define BEAM_DISCOVERY_PANEL_H

#include <ui/widgets/comedy_panel.h>
#include <ui/widgets/top_podcasts_panel.h>
#include <ui/widgets/news_and_politics_panel.h>
#include <ui/widgets/society_and_culture_panel.h>
#include <modules/discovery_panel_manager.h>

class DiscoveryPanel : public wxScrolledWindow {
private:
    DiscoveryPanelManager panelManager;

    wxBoxSizer * panelSizer;
    wxPanel * wrapperPanel;
    wxBoxSizer * wrapperPanelSizer;

    TopPodcastsPanel * topPodcastsPanel;
    SocietyAndCulturePanel * societyAndCulturePanel;
    NewsAndPoliticsPanel * newsAndPoliticsPanel;
    ComedyPanel * comedyPanel;

    void setupTopPodcastsSection();
    void setupSocietyAndCultureSection();
    void setupNewsAndPoliticsSection();
    void setupComedySection();
public:
    explicit DiscoveryPanel(wxWindow * parent);
};


#endif //BEAM_DISCOVERY_PANEL_H
