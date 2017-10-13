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

#include "episode.h"

Episode::Episode(long & podcastId, std::string & title, std::string & summary, std::string & publishDate, std::string & enclosureUrl, int & duration)
        : id(generator()), podcastId(podcastId), title(title), summary(summary), publishDate(publishDate), enclosureUrl(enclosureUrl), duration(duration) {}

Episode::Episode(boost::uuids::uuid & id, long & podcastId, std::string & title, std::string & summary, std::string & publishDate, std::string & enclosureUrl, int & duration)
        : id(id), podcastId(podcastId), title(title), summary(summary), publishDate(publishDate), enclosureUrl(enclosureUrl), duration(duration) {}

Episode::~Episode() = default;

boost::uuids::uuid Episode::getId() {
    return id;
}

long Episode::getPodcastId() {
    return podcastId;
}

std::string Episode::getTitle() {
    return title;
}

std::string Episode::getSummary() {
    return summary;
}

std::string Episode::getPublishDate() {
    return publishDate;
}

std::string Episode::getEnclosureUrl() {
    return enclosureUrl;
}

int Episode::getDuration() {
    return duration;
}
