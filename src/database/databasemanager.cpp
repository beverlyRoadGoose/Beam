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
#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    createPodcastsTable();
    createEpisodesTable();
}

DatabaseManager::~DatabaseManager() = default;

void DatabaseManager::openDatabase() {
    int resultCode = sqlite3_open_v2(DATABASE_FILE.c_str(), &database, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
    if (resultCode != SQLITE_OK) {
        std::stringstream ss;
        ss << "Error opening database: " << sqlite3_errmsg(database) << " (error code " << resultCode << ")";
        throw ss.str();
    }
}

void DatabaseManager::closeDatabase() {
    sqlite3_close(database);
}

void DatabaseManager::createPodcastsTable() {
    int resultCode;
    char * errorMessage = 0;

    std::string sql =
            "CREATE TABLE IF NOT EXISTS podcasts("
            "id TEXT PRIMARY KEY NOT NULL,"
            "title TEXT NOT NULL,"
            "link TEXT NOT NULL,"
            "feedUrl TEXT NOT NULL,"
            "description TEXT NOT NULL,"
            "imageUrl TEXT NOT NULL,"
            "url TEXT NOT NULL);";

    openDatabase();
    resultCode = sqlite3_exec(database, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error creating podcasts table: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    closeDatabase();
}

void DatabaseManager::createEpisodesTable() {
    int resultCode;
    char * errorMessage = 0;

    std::string sql =
            "CREATE TABLE IF NOT EXISTS episodes("
            "id TEXT PRIMARY KEY NOT NULL,"
            "podcastId TEXT NOT NULL,"
            "title TEXT NOT NULL,"
            "summary TEXT NOT NULL,"
            "publishDate TEXT NOT NULL,"
            "enclosureUrl TEXT NOT NULL,"
            "duration TEXT NOT NULL);";

    openDatabase();
    resultCode = sqlite3_exec(database, sql.c_str(), nullptr, nullptr, &errorMessage);
    if (resultCode != SQLITE_OK){
        std::stringstream ss;
        ss << "Error creating episodes table: " << errorMessage << " (error code " << resultCode << ")";
        sqlite3_free(errorMessage);
        throw ss.str();
    }
    closeDatabase();
}

sqlite3 * DatabaseManager::getDatabase() {
    return database;
}
