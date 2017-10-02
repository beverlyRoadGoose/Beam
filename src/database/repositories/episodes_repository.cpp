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

#include "episodes_repository.h"

EpisodesRepository::EpisodesRepository() = default;

EpisodesRepository::~EpisodesRepository() = default;

void EpisodesRepository::insert(Episode episode) {
    // TODO
}

Episode EpisodesRepository::getById(boost::uuids::uuid id) {
    // TODO
}

std::vector<Episode> EpisodesRepository::getAll() {
    // TODO
}

void EpisodesRepository::deleteById(boost::uuids::uuid id) {
    // TODO
}

void EpisodesRepository::deleteAll() {
    // TODO
}
