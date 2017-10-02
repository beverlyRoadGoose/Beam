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

#ifndef BEAM_PODCASTS_REPOSITORY_H
#define BEAM_PODCASTS_REPOSITORY_H

#include <vector>
#include <entities/podcast.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <database/databasemanager.h>

class PodcastsRepository {
private:
    DatabaseManager databaseManager;
public:
    PodcastsRepository();
    ~PodcastsRepository();
    void insert(Podcast podcast);
    Podcast getById(boost::uuids::uuid id);
    std::vector<Podcast> getAll();
    void deleteById(boost::uuids::uuid id);
    void deleteAll();
};

#endif //BEAM_PODCASTS_REPOSITORY_H
