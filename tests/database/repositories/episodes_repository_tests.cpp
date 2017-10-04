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
#include <tests/testutils.h>
#include <entities/episode.h>
#include <database/repositories/episodes_repository.h>

TEST_CASE("insert new episode", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string testPodcastName = "Test Podcast";
    Podcast testPodcast = TestUtils::createPodcastForTest(testPodcastName);

    std::string testEpisodeTitle = "Test Episode";
    Episode episode = Episode(testPodcast.getId(), testEpisodeTitle);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.insert(episode);

    REQUIRE(episodesRepository.getAll().size() == 1);
}