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

#define CATCH_CONFIG_MAIN

#include <catch/catch.hpp>
#include <networking/apis/digital_podcasts.h>
#include <src/database/repositories/podcasts_repository.h>

TEST_CASE("search query test", "[digitalPodcastsTests]") {
    std::string searchKey = "radiolab";
    std::vector<Podcast> podcasts = DigitalPodcasts::search(searchKey);

    REQUIRE_FALSE(podcasts.empty());
}


TEST_CASE("episodes feed parse test", "[digitalPodcastsTests]") {
    std::string searchKey = "radiolab";
    std::vector<Podcast> podcasts = DigitalPodcasts::search(searchKey);

    Podcast podcast = podcasts.front();
    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.insert(podcast);

    std::vector<Episode> episodes = DigitalPodcasts::parsePodcastEpisodes(podcast);

    REQUIRE_FALSE(episodes.empty());
}
