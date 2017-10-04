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
#include <database/repositories/podcasts_repository.h>

TEST_CASE("insert new podcast", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastName = "Test Podcast";
    Podcast podcast = Podcast(podcastName);
    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.insert(podcast);
    REQUIRE(podcastsRepository.getAll().size() == 1);
}

TEST_CASE("get podcast by id", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastName = "Test Podcast";
    PodcastsRepository podcastsRepository = PodcastsRepository();

    Podcast originalPodcast = Podcast(podcastName);
    podcastsRepository.insert(originalPodcast);

    Podcast retrievedPodcast = podcastsRepository.getById(originalPodcast.getId());
    REQUIRE(retrievedPodcast.getName() == podcastName);
}

TEST_CASE("get all podcasts", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastAName = "Test Podcast A";
    std::string podcastBName = "Test Podcast B";

    TestUtils::createPodcastForTest(podcastAName);
    TestUtils::createPodcastForTest(podcastBName);

    PodcastsRepository podcastsRepository = PodcastsRepository();
    REQUIRE(podcastsRepository.getAll().size() == 2);
}

TEST_CASE("get non existing podcast by id", "[podcastsRepositoryTests]") {
    PodcastsRepository podcastsRepository = PodcastsRepository();
    boost::uuids::random_generator generator;
    boost::uuids::uuid randomId = generator();

    REQUIRE_THROWS(podcastsRepository.getById(randomId));
}

TEST_CASE("update podcast", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastName = "Test Podcast";
    std::string updatedName = "Updated test podcast";

    Podcast originalPodcast = TestUtils::createPodcastForTest(podcastName);
    originalPodcast.setName(updatedName);

    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.update(originalPodcast);

    Podcast retrievedPodcast = podcastsRepository.getById(originalPodcast.getId());
    REQUIRE(retrievedPodcast.getName() == updatedName);
}

TEST_CASE("delete podcast by id", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastName = "Test Podcast";
    Podcast podcast = TestUtils::createPodcastForTest(podcastName);

    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.deleteById(podcast.getId());
    REQUIRE(podcastsRepository.getAll().empty());
}

TEST_CASE("delete all podcasts", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastName = "Test Podcast";
    TestUtils::createPodcastForTest(podcastName);

    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.deleteAll();
    REQUIRE(podcastsRepository.getAll().empty());
}
