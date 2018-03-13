/*
 *  Copyright 2018 Oluwatobi Adeyinka
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

#ifndef BEAM_BEAM_CONFIG_H
#define BEAM_BEAM_CONFIG_H

#include <wx/filename.h>

#include "beam_config.h"

void BeamConfig::setupTempDirectory() {
    wxString _tmpDirectory = wxGetCwd() + "/.tmp";
    wxString _tmpImgDirectory = _tmpDirectory + "/img";
    wxString _tmpAudioDirectory = _tmpDirectory + "/audio";

    if (!wxDir::Exists(_tmpDirectory)) wxDir::Make(_tmpDirectory, wxS_DIR_DEFAULT);
    if (!wxDir::Exists(_tmpImgDirectory)) wxDir::Make(_tmpImgDirectory, wxS_DIR_DEFAULT);
    if (!wxDir::Exists(_tmpAudioDirectory)) wxDir::Make(_tmpAudioDirectory, wxS_DIR_DEFAULT);
}

void BeamConfig::setupPersistenceDirectory() {
    wxString _persistenceDirectory = wxGetCwd() + "/.persistence";
    wxString _persistenceImgDirectory = _persistenceDirectory + "/img";
    wxString _persistenceAudioDirectory = _persistenceDirectory + "/audio";

    if (!wxDir::Exists(_persistenceDirectory)) wxDir::Make(_persistenceDirectory, wxS_DIR_DEFAULT);
    if (!wxDir::Exists(_persistenceImgDirectory)) wxDir::Make(_persistenceImgDirectory, wxS_DIR_DEFAULT);
    if (!wxDir::Exists(_persistenceAudioDirectory)) wxDir::Make(_persistenceAudioDirectory, wxS_DIR_DEFAULT);
}

void BeamConfig::removeTempDirectory() {
    wxString _tmpDirectory = wxGetCwd() + "/.tmp";
    wxDir::Remove(_tmpDirectory, wxPATH_RMDIR_RECURSIVE);
}

#endif //BEAM_BEAM_CONFIG_H
