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
#include "testutils.h"
#include <database/repositories/podcasts_repository.h>
#include <database/repositories/episodes_repository.h>

bool TestUtils::isValidUUID(const boost::uuids::uuid & id) {
    std::string uuidString = boost::uuids::to_string(id);

    try {
        boost::uuids::string_generator generator;
        boost::uuids::uuid temp = generator(uuidString);
        return temp.version() != boost::uuids::uuid::version_unknown;
    }
    catch (const std::exception & ex) {
        std::stringstream ss;
        ss << "Invalid uuid: " << *ex.what();
        throw ss.str();
    }
}

void TestUtils::emptyDatabase() {
    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.deleteAll();

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.deleteAll();
}

Podcast TestUtils::createPodcastForTest(std::string & podcastName) {
    Podcast podcast = Podcast(podcastName);
    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.insert(podcast);

    return podcast;
}

Episode TestUtils::createEpisodeForTest(const boost::uuids::uuid & podcastId, std::string & episodeTitle) {
    Episode episode = Episode(podcastId, episodeTitle);
    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.insert(episode);

    return episode;
}
