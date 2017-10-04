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

#include <iostream>
#include "podcast.h"

Podcast::Podcast(const std::string & name) : name(name) {}

Podcast::Podcast(const boost::uuids::uuid & id, std::string & name) : id(id), name(name) { }

Podcast::~Podcast() = default;

boost::uuids::uuid Podcast::getId() {
    return this->id;
}

std::string Podcast::getName() {
    return this->name;
}

void Podcast::setName(std::string & name) {
    this->name = name;
}
