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

#ifndef BEAM_EPISODES_REPOSITORY_H
#define BEAM_EPISODES_REPOSITORY_H

#include <vector>
#include <entities/episode.h>
#include <database/databasemanager.h>

class EpisodesRepository {
private:
    DatabaseManager databaseManager;

    static bool verifyPodcastExists(long & id);
    static int getListCallback(void *data, int argc, char **argv, char **columnName);
    static int getSingleCallback(void *data, int argc, char **argv, char **columnName);
public:
    EpisodesRepository();
    ~EpisodesRepository();
    void insert(Episode episode);
    Episode getById(boost::uuids::uuid & id);
    std::vector<Episode> getByPodcastId(long & id);
    std::vector<Episode> getAll();
    void deleteById(boost::uuids::uuid & id);
    void deleteByPodcastId(long & id);
    void deleteAll();
};

#endif //BEAM_EPISODES_REPOSITORY_H
