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
#include <database/repositories/episodes_repository.h>

TEST_CASE("insert new episode", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    long testPodcastId = 1;
    Podcast testPodcast = TestUtils::createPodcastForTest(testPodcastId);

    boost::uuids::random_generator generator;
    boost::uuids::uuid episodeId = generator();
    std::string testEpisodeTitle = "Test Episode";
    std::string summary = "summary";
    std::string publishDate = "publishDate";
    std::string enclosureUrl = "enclosureUrl";

    Episode episode = Episode(episodeId, testPodcastId, testEpisodeTitle, summary, publishDate, enclosureUrl);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.insert(episode);

    REQUIRE(episodesRepository.getAll().size() == 1);
}

TEST_CASE("insert new episode for non existing podcast", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    long testPodcastId = 1; // note that the podcast isn't actually created
    boost::uuids::random_generator generator;
    boost::uuids::uuid episodeId = generator();

    std::string testEpisodeTitle = "Test Episode";
    std::string summary = "summary";
    std::string publishDate = "publishDate";
    std::string enclosureUrl = "enclosureUrl";

    Episode episode = Episode(episodeId, testPodcastId, testEpisodeTitle, summary, publishDate, enclosureUrl);

    EpisodesRepository episodesRepository = EpisodesRepository();
    REQUIRE_THROWS(episodesRepository.insert(episode));
}

TEST_CASE("get episode by id", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    long testPodcastId = 1;
    Podcast testPodcast = TestUtils::createPodcastForTest(testPodcastId);

    boost::uuids::random_generator generator;
    boost::uuids::uuid episodeId = generator();
    std::string testEpisodeTitle = "Test Episode";
    std::string summary = "summary";
    std::string publishDate = "publishDate";
    std::string enclosureUrl = "enclosureUrl";

    Episode episode = Episode(episodeId, testPodcastId, testEpisodeTitle, summary, publishDate, enclosureUrl);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.insert(episode);

    Episode retrievedEpisode = episodesRepository.getById(episodeId);
    REQUIRE(retrievedEpisode.getTitle() == episode.getTitle());
}

TEST_CASE("get non existing episode by id", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();
    boost::uuids::random_generator generator;
    boost::uuids::uuid episodeId = generator();

    EpisodesRepository episodesRepository = EpisodesRepository();
    REQUIRE_THROWS(episodesRepository.getById(episodeId));
}

TEST_CASE("get all episodes", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    long testPodcastId = 1;
    Podcast testPodcast = TestUtils::createPodcastForTest(testPodcastId);

    boost::uuids::random_generator generator;
    boost::uuids::uuid episodeAId = generator();
    boost::uuids::uuid episodeBId = generator();

    TestUtils::createEpisodeForTest(testPodcastId, episodeAId);
    TestUtils::createEpisodeForTest(testPodcastId, episodeBId);

    EpisodesRepository episodesRepository = EpisodesRepository();
    REQUIRE(episodesRepository.getAll().size() == 2);
}

TEST_CASE("get all episodes in podcast", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    long podcastAId = 1;
    long podcastBId = 2;

    Podcast testPodcastA = TestUtils::createPodcastForTest(podcastAId);
    Podcast testPodcastB = TestUtils::createPodcastForTest(podcastBId);

    boost::uuids::random_generator generator;
    boost::uuids::uuid episodeAId = generator();
    boost::uuids::uuid episodeBId = generator();
    boost::uuids::uuid episodeCId = generator();

    TestUtils::createEpisodeForTest(podcastAId, episodeAId);
    TestUtils::createEpisodeForTest(podcastBId, episodeBId);
    TestUtils::createEpisodeForTest(podcastBId, episodeCId);

    EpisodesRepository episodesRepository = EpisodesRepository();
    REQUIRE(episodesRepository.getByPodcastId(podcastBId).size() == 2);
}

TEST_CASE("delete episode by id", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    long testPodcastId = 1;
    Podcast testPodcast = TestUtils::createPodcastForTest(testPodcastId);

    boost::uuids::random_generator generator;
    boost::uuids::uuid episodeId = generator();
    Episode episode = TestUtils::createEpisodeForTest(testPodcastId, episodeId);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.deleteById(episodeId);
    REQUIRE(episodesRepository.getAll().empty());
}

TEST_CASE("delete all episodes", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    long testPodcastId = 1;
    Podcast testPodcast = TestUtils::createPodcastForTest(testPodcastId);

    boost::uuids::random_generator generator;
    boost::uuids::uuid episodeId = generator();
    Episode episode = TestUtils::createEpisodeForTest(testPodcastId, episodeId);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.deleteAll();
    REQUIRE(episodesRepository.getAll().empty());
}

TEST_CASE("delete all episodes in podcast", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    long podcastAId = 1;
    long podcastBId = 2;

    Podcast testPodcastA = TestUtils::createPodcastForTest(podcastAId);
    Podcast testPodcastB = TestUtils::createPodcastForTest(podcastBId);

    boost::uuids::random_generator generator;
    boost::uuids::uuid episodeAId = generator();
    boost::uuids::uuid episodeBId = generator();
    boost::uuids::uuid episodeCId = generator();

    TestUtils::createEpisodeForTest(podcastAId, episodeAId);
    TestUtils::createEpisodeForTest(podcastBId, episodeBId);
    TestUtils::createEpisodeForTest(podcastBId, episodeCId);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.deleteByPodcastId(podcastBId);

    REQUIRE(episodesRepository.getAll().size() == 1);
}