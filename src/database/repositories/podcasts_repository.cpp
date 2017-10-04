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
#include <boost/lexical_cast.hpp>
#include "podcasts_repository.h"

std::vector<Podcast> allPodcasts;
Podcast * podcastRetrievedById = nullptr;

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
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();
}

void PodcastsRepository::update(Podcast podcast) {

}

Podcast PodcastsRepository::getById(boost::uuids::uuid id) {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;

    std::stringstream ss;
    ss << "SELECT * FROM podcasts WHERE id='" << id << "'";

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    allPodcasts = std::vector<Podcast>();

    resultCode = sqlite3_exec(database, ss.str().c_str(), getByIdCallback, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error retrieving podcast by id: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();

    boost::uuids::uuid retrievedId = podcastRetrievedById->getId();
    std::string retrievedName = podcastRetrievedById->getName();
    Podcast p = Podcast(retrievedId, retrievedName);

    delete podcastRetrievedById;
    podcastRetrievedById = nullptr;

    return p;
}

std::vector<Podcast> PodcastsRepository::getAll() {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;
    char * sql = const_cast<char *>("SELECT * FROM podcasts");

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    allPodcasts = std::vector<Podcast>();

    resultCode = sqlite3_exec(database, sql, getAllCallback, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error reading all podcasts from db: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();

    return allPodcasts;
}

void PodcastsRepository::deleteById(boost::uuids::uuid id) {
    // TODO
}

void PodcastsRepository::deleteAll() {
    // TODO
}

int PodcastsRepository::getAllCallback(void * data, int argc, char **argv, char **columnName) {
    boost::uuids::uuid podcastId = boost::lexical_cast<boost::uuids::uuid>(argv[0]);
    std::string podcastName = argv[1];
    Podcast podcast = Podcast(podcastId, podcastName);
    allPodcasts.push_back(podcast);

    return 0;
}

int PodcastsRepository::getByIdCallback(void *data, int argc, char **argv, char **columnName) {
    boost::uuids::uuid podcastId = boost::lexical_cast<boost::uuids::uuid>(argv[0]);
    std::string podcastName = argv[1];
    podcastRetrievedById = new Podcast(podcastId, podcastName);

    return 0;
}
