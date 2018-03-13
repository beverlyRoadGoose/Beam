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

#define CATCH_CONFIG_MAIN

#include <catch/catch.hpp>
#include <tests/testutils.h>
#include <database/repositories/podcasts_repository.h>

TEST_CASE("insert new podcast", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    long id = 1;
    std::string title = "title";
    std::string publisher = "publisher";
    std::string feedUrl = "feedUrl";
    std::string description = "description";
    std::string imageUrl = "imageUrl";
    std::string url = "url";

    Podcast podcast = Podcast(id, title, publisher, feedUrl, description, imageUrl, url);
    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.insert(podcast);
    REQUIRE(podcastsRepository.getAll().size() == 1);
}

TEST_CASE("get podcast by id", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    long id = 1;
    std::string title = "title";
    std::string publisher = "publisher";
    std::string feedUrl = "feedUrl";
    std::string description = "description";
    std::string imageUrl = "imageUrl";
    std::string url = "url";

    PodcastsRepository podcastsRepository = PodcastsRepository();

    Podcast originalPodcast = Podcast(id, title, publisher, feedUrl, description, imageUrl, url);
    podcastsRepository.insert(originalPodcast);

    Podcast retrievedPodcast = podcastsRepository.getById(id);
    REQUIRE(retrievedPodcast.getTitle() == title);
}

TEST_CASE("get all podcasts", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    long idA = 1;
    long idB = 2;

    TestUtils::createPodcastForTest(idA);
    TestUtils::createPodcastForTest(idB);

    PodcastsRepository podcastsRepository = PodcastsRepository();
    REQUIRE(podcastsRepository.getAll().size() == 2);
}

TEST_CASE("get non existing podcast by id", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();
    long id = 1;

    PodcastsRepository podcastsRepository = PodcastsRepository();
    REQUIRE_THROWS(podcastsRepository.getById(id));
}

TEST_CASE("delete podcast by id", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    long id = 1;
    Podcast podcast = TestUtils::createPodcastForTest(id);
    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.deleteById(id);

    REQUIRE(podcastsRepository.getAll().empty());
}

TEST_CASE("delete all podcasts", "[podcastsRepositoryTests]") {
    TestUtils::emptyDatabase();

    long id = 1;
    TestUtils::createPodcastForTest(id);

    PodcastsRepository podcastsRepository = PodcastsRepository();
    podcastsRepository.deleteAll();
    REQUIRE(podcastsRepository.getAll().empty());
}
