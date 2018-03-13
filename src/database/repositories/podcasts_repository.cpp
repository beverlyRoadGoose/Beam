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

#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

#include "podcasts_repository.h"

std::vector<Podcast> retrievedPodcastsList;
Podcast * podcastRetrievedById = nullptr;

PodcastsRepository::PodcastsRepository() = default;

PodcastsRepository::~PodcastsRepository() = default;

void PodcastsRepository::insert(Podcast podcast) {
    sqlite3 * database;
    char * errorMessage = 0;
    std::stringstream ss;
    int resultCode;

    ss << "VALUES ('" << podcast.getId() << "', "
            "'" << podcast.getTitle() << "', "
            "'" << podcast.getPublisher() << "', "
            "'" << podcast.getFeedUrl() << "', "
            "'" << podcast.getDescription() << "', "
            "'" << podcast.getImageUrl() << "', "
            "'" << podcast.getLocalImageDir() << "', "
            "'" << podcast.getUrl() <<"');";
    std::string sql = "INSERT INTO podcasts (id, title, publisher, feedUrl, description, imageUrl, localImageDir, url) " + ss.str();

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

Podcast PodcastsRepository::getById(long & id) {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;

    std::stringstream ss;
    ss << "SELECT * FROM podcasts WHERE id='" << id << "'";

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    resultCode = sqlite3_exec(database, ss.str().c_str(), getSingleCallback, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error retrieving podcast by id: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();

    if (podcastRetrievedById == nullptr)
        throw "No podcast with matching id found";

    long retrievedId = podcastRetrievedById->getId();
    std::string retrievedTitle = podcastRetrievedById->getTitle();
    std::string retrievedPublisher = podcastRetrievedById->getPublisher();
    std::string retrievedFeedUrl = podcastRetrievedById->getFeedUrl();
    std::string retrievedDescription = podcastRetrievedById->getDescription();
    std::string retrievedImageUrl = podcastRetrievedById->getImageUrl();
    std::string retrievedImageDir = podcastRetrievedById->getLocalImageDir();
    std::string retrievedUrl = podcastRetrievedById->getUrl();

    Podcast p = Podcast(retrievedId, retrievedTitle, retrievedPublisher, retrievedFeedUrl, retrievedDescription, retrievedImageUrl, retrievedUrl);
    p.setLocalImageDir(retrievedImageDir);

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

    retrievedPodcastsList = std::vector<Podcast>();

    resultCode = sqlite3_exec(database, sql, getListCallback, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error reading all podcasts from db: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();

    return retrievedPodcastsList;
}

void PodcastsRepository::deleteById(long & id) {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;

    std::stringstream ss;
    ss << "DELETE FROM podcasts WHERE id='" << id << "'";

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    resultCode = sqlite3_exec(database, ss.str().c_str(), nullptr, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error deleting podcast: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();
}

void PodcastsRepository::deleteAll() {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;
    char * sql = const_cast<char *>("DELETE FROM podcasts");

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    resultCode = sqlite3_exec(database, sql, nullptr, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error emptying podcasts table: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();
}

int PodcastsRepository::getListCallback(void *data, int argc, char **argv, char **columnName) {
    long id = atol(argv[0]);
    std::string title = argv[1];
    std::string publisher = argv[2];
    std::string feedUrl = argv[3];
    std::string description = argv[4];
    std::string imageUrl = argv[5];
    std::string localImageDir = argv[6];
    std::string url = argv[7];

    Podcast podcast = Podcast(id, title, publisher, feedUrl, description, imageUrl, url);
    podcast.setLocalImageDir(localImageDir);
    retrievedPodcastsList.push_back(podcast);

    return 0;
}

int PodcastsRepository::getSingleCallback(void *data, int argc, char **argv, char **columnName) {
    long id = atol(argv[0]);
    std::string title = argv[1];
    std::string publisher = argv[2];
    std::string feedUrl = argv[3];
    std::string description = argv[4];
    std::string imageUrl = argv[5];
    std::string localImageDir = argv[6];
    std::string url = argv[7];

    podcastRetrievedById = new Podcast(id, title, publisher, feedUrl, description, imageUrl, url);
    podcastRetrievedById->setLocalImageDir(localImageDir);

    return 0;
}
