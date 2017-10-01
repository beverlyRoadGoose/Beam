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

#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    createPodcastsTable();
    createEpisodesTable();
}

DatabaseManager::~DatabaseManager() = default;

void DatabaseManager::openDatabase() {
    sqlite3_open(DATABASE_FILE.c_str(), &database);
}

void DatabaseManager::closeDatabase() {
    sqlite3_close(database);
}

void DatabaseManager::createPodcastsTable() {
    openDatabase();
    closeDatabase();
}

void DatabaseManager::createEpisodesTable() {
    openDatabase();
    closeDatabase();
}
