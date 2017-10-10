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

#ifndef BEAM_EPISODE_H
#define BEAM_EPISODE_H

#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

class Episode {
private:
    boost::uuids::random_generator generator;
    const boost::uuids::uuid id;
    const long podcastId;
    const std::string title;
    const std::string summary;
    const std::string publishDate;
    const std::string enclosureUrl;
public:
    Episode(long & podcastId, std::string & title, std::string & summary, std::string & publishDate, std::string & enclosureUrl);
    Episode(boost::uuids::uuid & id, long & podcastId, std::string & title, std::string & summary, std::string & publishDate, std::string & enclosureUrl);
    ~Episode();
    boost::uuids::uuid getId();
    long getPodcastId();
    std::string getTitle();
    std::string getSummary();
    std::string getPublishDate();
    std::string getEnclosureUrl();
};

#endif //BEAM_EPISODE_H
