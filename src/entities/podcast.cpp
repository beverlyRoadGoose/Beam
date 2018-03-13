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

#include <iostream>

#include "podcast.h"

Podcast::Podcast(long & id, std::string & title, std::string & publisher, std::string & feedUrl, std::string & description, std::string & imageUrl, std::string & url)
        : id(id), title(title), publisher(publisher), feedUrl(feedUrl), description(description), imageUrl(imageUrl), url(url) {}

Podcast::~Podcast() = default;

long Podcast::getId() {
    return id;
}

std::string Podcast::getTitle() {
    return title;
}

std::string Podcast::getPublisher() {
    return publisher;
}

std::string Podcast::getFeedUrl() {
    return feedUrl;
}

std::string Podcast::getDescription() {
    return description;
}

std::string Podcast::getImageUrl() {
    return imageUrl;
}

std::string Podcast::getUrl() {
    return url;
}

void Podcast::setUrl(std::string & url) {
    this->url = url;
}

void Podcast::setDescription(std::string &description) {
    this->description = description;
}

std::string Podcast::getLocalImageDir() {
    return localImageDir;
}

void Podcast::setLocalImageDir(std::string & dir) {
    localImageDir = dir;
}
