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
#include <entities/podcast.h>
#include <database/repositories/podcasts_repository.h>

TEST_CASE("insert new podcast", "[podcastsRepositoryTests]") {
    std::string podcastName = "Test Podcast";
    Podcast podcast = Podcast(podcastName);
    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.insert(podcast);
    REQUIRE(podcastsRepository.getAll().size() == 1);
}

TEST_CASE("get podcast by id", "[podcastsRepositoryTests]") {
    std::string podcastName = "Test Podcast";
    PodcastsRepository podcastsRepository = PodcastsRepository();

    Podcast originalPodcast = Podcast(podcastName);
    podcastsRepository.insert(originalPodcast);

    Podcast retrievedPodcast = podcastsRepository.getById(originalPodcast.getId());
    REQUIRE(retrievedPodcast.getName() == podcastName);
}

TEST_CASE("update podcast", "[podcastsRepositoryTests]") {
    std::string podcastName = "Test Podcast";
    std::string updatedName = "Updated test podcast";
    PodcastsRepository podcastsRepository = PodcastsRepository();

    Podcast originalPodcast = Podcast(podcastName);
    podcastsRepository.insert(originalPodcast);

    originalPodcast.setName(updatedName);
    podcastsRepository.update(originalPodcast);

    Podcast retrievedPodcast = podcastsRepository.getById(originalPodcast.getId());
    REQUIRE(retrievedPodcast.getName() == updatedName);
}