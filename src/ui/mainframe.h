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

#ifndef BEAM_MAINFRAME_H
#define BEAM_MAINFRAME_H

class MainFrame : public wxFrame {
private:
    wxMenuBar * menuBar;
    wxMenu * fileMenu;
    wxMenu * podcastsMenu;
    wxMenuItem * quitMenuItem;
    DECLARE_EVENT_TABLE()
public:
    explicit MainFrame(const wxString & title);
    void quit(wxCommandEvent & event);
    wxMenuBar * getMenuBar();
    wxMenu * getFileMenu();
    wxMenu * getPodcastsMenu();
    wxMenuItem * getQuitMenuItem();
};

#endif
