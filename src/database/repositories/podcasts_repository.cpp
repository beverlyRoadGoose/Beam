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

#include <sstream>
#include <iostream>
#include "podcasts_repository.h"

PodcastsRepository::PodcastsRepository() = default;

PodcastsRepository::~PodcastsRepository() = default;

void PodcastsRepository::insert(Podcast podcast) {
    sqlite3 * database;
    char * errorMessage = 0;
    std::stringstream ss;
    int resultCode;

    ss << "VALUES ('" << podcast.getId() << "', '" << podcast.getName() << "');";
    std::string sql = "INSERT INTO podcasts (ID,NAME) " + ss.str();

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    resultCode = sqlite3_exec(database, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error inserting podcast: " << errorMessage << " (error code " << resultCode << ")";
        throw ss.str();
    }
    databaseManager.closeDatabase();
}

Podcast PodcastsRepository::getById(boost::uuids::uuid id) {
    // TODO
}

std::vector<Podcast> PodcastsRepository::getAll() {
    // TODO
}

void PodcastsRepository::deleteById(boost::uuids::uuid id) {
    // TODO
}

void PodcastsRepository::deleteAll() {
    // TODO
}
