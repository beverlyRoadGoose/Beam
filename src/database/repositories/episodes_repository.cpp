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
#include "episodes_repository.h"
#include "podcasts_repository.h"

std::vector<Episode> retrievedEpisodesList;
Episode * episodeRetrievedById = nullptr;

EpisodesRepository::EpisodesRepository() = default;

EpisodesRepository::~EpisodesRepository() = default;

void EpisodesRepository::insert(Episode episode) {
    sqlite3 * database;
    char * errorMessage = 0;
    std::stringstream ss;
    int resultCode;

    long podcastId = episode.getPodcastId();
    verifyPodcastExists(podcastId);

    ss << "VALUES ('" << episode.getId() << "', "
            "'" << episode.getPodcastId() << "', "
            "'" << episode.getTitle() << "', "
            "'" << episode.getSummary() << "', "
            "'" << episode.getPublishDate() << "', "
            "'" << episode.getEnclosureUrl() << "', "
            "'" << episode.getDuration() << "' );";
    std::string sql = "INSERT INTO episodes (id, podcastId, title, summary, publishDate, enclosureUrl, duration) " + ss.str();

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    resultCode = sqlite3_exec(database, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error inserting episode: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();
}

Episode EpisodesRepository::getById(boost::uuids::uuid & id) {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;

    std::stringstream ss;
    ss << "SELECT * FROM episodes WHERE id='" << id << "'";

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    resultCode = sqlite3_exec(database, ss.str().c_str(), getSingleCallback, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error retrieving episode by id: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();

    if (episodeRetrievedById == nullptr)
        throw "No episode with matching id found";

    boost::uuids::uuid retrievedId = episodeRetrievedById->getId();
    long retrievedPodcastId = episodeRetrievedById->getPodcastId();
    std::string retrievedTitle = episodeRetrievedById->getTitle();
    std::string retrievedSummary = episodeRetrievedById->getSummary();
    std::string retrievedPublishDate = episodeRetrievedById->getPublishDate();
    std::string retrievedEnclosureUrl = episodeRetrievedById->getEnclosureUrl();
    int retrievedDuration = episodeRetrievedById->getDuration();

    Episode e = Episode(retrievedId, retrievedPodcastId, retrievedTitle, retrievedSummary, retrievedPublishDate, retrievedEnclosureUrl, retrievedDuration);

    delete episodeRetrievedById;
    episodeRetrievedById = nullptr;

    return e;
}

std::vector<Episode> EpisodesRepository::getByPodcastId(long & id) {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;

    std::stringstream ss;
    ss << "SELECT * FROM episodes WHERE podcastId='" << id << "'";

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    retrievedEpisodesList = std::vector<Episode>();

    resultCode = sqlite3_exec(database, ss.str().c_str(), getListCallback, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error reading podcast episodes from db: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();

    return retrievedEpisodesList;
}

std::vector<Episode> EpisodesRepository::getAll() {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;
    char * sql = const_cast<char *>("SELECT * FROM episodes");

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    retrievedEpisodesList = std::vector<Episode>();

    resultCode = sqlite3_exec(database, sql, getListCallback, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error reading all episodes from db: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();

    return retrievedEpisodesList;
}

void EpisodesRepository::deleteById(boost::uuids::uuid & id) {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;

    std::stringstream ss;
    ss << "DELETE FROM episodes WHERE id='" << id << "'";

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    resultCode = sqlite3_exec(database, ss.str().c_str(), nullptr, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error deleting episode: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();
}

void EpisodesRepository::deleteByPodcastId(long & id) {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;

    std::stringstream ss;
    ss << "DELETE FROM episodes WHERE podcastId='" << id << "'";

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    resultCode = sqlite3_exec(database, ss.str().c_str(), nullptr, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error deleting podcast episodes: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();
}

void EpisodesRepository::deleteAll() {
    sqlite3 * database;
    char * errorMessage = 0;
    int resultCode;
    char * sql = const_cast<char *>("DELETE FROM episodes");

    databaseManager.openDatabase();
    database = databaseManager.getDatabase();

    resultCode = sqlite3_exec(database, sql, nullptr, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error emptying episodes table: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    databaseManager.closeDatabase();
}

int EpisodesRepository::getListCallback(void *data, int argc, char **argv, char **columnName) {
    boost::uuids::uuid episodeId = boost::lexical_cast<boost::uuids::uuid>(argv[0]);
    long podcastId = atol(argv[1]);
    std::string episodeTitle = argv[2];
    std::string episodeSummary = argv[3];
    std::string episodePublishDate = argv[4];
    std::string episodeEnclosureUrl = argv[5];
    int episodeDuration = atoi(argv[5]);

    Episode episode = Episode(episodeId, podcastId, episodeTitle, episodeSummary, episodePublishDate, episodeEnclosureUrl, episodeDuration);
    retrievedEpisodesList.push_back(episode);

    return 0;
}

int EpisodesRepository::getSingleCallback(void *data, int argc, char **argv, char **columnName) {
    boost::uuids::uuid episodeId = boost::lexical_cast<boost::uuids::uuid>(argv[0]);
    long podcastId = atol(argv[1]);
    std::string episodeTitle = argv[2];
    std::string episodeSummary = argv[3];
    std::string episodePublishDate = argv[4];
    std::string episodeEnclosureUrl = argv[5];
    int episodeDuration = atoi(argv[5]);

    episodeRetrievedById = new Episode(episodeId, podcastId, episodeTitle, episodeSummary, episodePublishDate, episodeEnclosureUrl, episodeDuration);

    return 0;
}

bool EpisodesRepository::verifyPodcastExists(long & id) {
    PodcastsRepository podcastsRepository = PodcastsRepository();

    try {
        podcastsRepository.getById(id);
    }
    catch (const std::exception & ex) {
        std::stringstream ss;
        ss << "Podcast doesn't exist: " << *ex.what();
        throw ss.str();
    }

    return true;
}

