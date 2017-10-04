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

    std::string testPodcastName = "Test Podcast";
    Podcast testPodcast = TestUtils::createPodcastForTest(testPodcastName);

    std::string testEpisodeTitle = "Test Episode";
    Episode episode = Episode(testPodcast.getId(), testEpisodeTitle);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.insert(episode);

    REQUIRE(episodesRepository.getAll().size() == 1);
}

TEST_CASE("insert new episode for non existing podcast", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    boost::uuids::random_generator generator;
    boost::uuids::uuid randomPodcastId = generator();

    std::string testEpisodeTitle = "Test Episode";
    Episode episode = Episode(randomPodcastId, testEpisodeTitle);

    EpisodesRepository episodesRepository = EpisodesRepository();
    REQUIRE_THROWS(episodesRepository.insert(episode));
}

TEST_CASE("get episode by id", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string testPodcastName = "Test Podcast";
    Podcast testPodcast = TestUtils::createPodcastForTest(testPodcastName);

    std::string testEpisodeTitle = "Test Episode";
    Episode episode = Episode(testPodcast.getId(), testEpisodeTitle);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.insert(episode);

    Episode retrievedEpisode = episodesRepository.getById(episode.getId());
    REQUIRE(retrievedEpisode.getTitle() == episode.getTitle());
}

TEST_CASE("get non existing episode by id", "[episodesRepositoryTests]") {
    EpisodesRepository episodesRepository = EpisodesRepository();
    boost::uuids::random_generator generator;
    boost::uuids::uuid randomId = generator();

    REQUIRE_THROWS(episodesRepository.getById(randomId));
}

TEST_CASE("get all episodes", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string testPodcastName = "Test Podcast";
    Podcast testPodcast = TestUtils::createPodcastForTest(testPodcastName);

    std::string episodeAName = "Test Episode A";
    std::string episodeBName = "Test Episode B";

    TestUtils::createEpisodeForTest(testPodcast.getId(), episodeAName);
    TestUtils::createEpisodeForTest(testPodcast.getId(), episodeBName);

    EpisodesRepository episodesRepository = EpisodesRepository();
    REQUIRE(episodesRepository.getAll().size() == 2);
}

TEST_CASE("get all episodes in podcast", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastAName = "Test Podcast A";
    std::string podcastBName = "Test Podcast B";

    Podcast testPodcastA = TestUtils::createPodcastForTest(podcastAName);
    Podcast testPodcastB = TestUtils::createPodcastForTest(podcastBName);

    std::string episodeAName = "Test Episode A";
    std::string episodeBName = "Test Episode B";
    std::string episodeCName = "Test Episode C";

    TestUtils::createEpisodeForTest(testPodcastA.getId(), episodeAName);
    TestUtils::createEpisodeForTest(testPodcastB.getId(), episodeBName);
    TestUtils::createEpisodeForTest(testPodcastB.getId(), episodeCName);

    EpisodesRepository episodesRepository = EpisodesRepository();
    REQUIRE(episodesRepository.getByPodcastId(testPodcastB.getId()).size() == 2);
}

TEST_CASE("update episode", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastName = "Test Podcast";
    Podcast podcast = TestUtils::createPodcastForTest(podcastName);

    std::string originalEpisodeTitle = "Test Episode";
    Episode episode = TestUtils::createEpisodeForTest(podcast.getId(), originalEpisodeTitle);

    std::string updatedEpisodeTitle = "Test Episode 2";
    episode.setTitle(updatedEpisodeTitle);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.update(episode);

    Episode retrievedEpisode = episodesRepository.getById(episode.getId());
    REQUIRE(retrievedEpisode.getTitle() == updatedEpisodeTitle);
}

TEST_CASE("delete episode by id", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastName = "Test Podcast";
    Podcast podcast = TestUtils::createPodcastForTest(podcastName);

    std::string episodeTitle = "Test Episode";
    Episode episode = TestUtils::createEpisodeForTest(podcast.getId(), episodeTitle);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.deleteById(episode.getId());
    REQUIRE(episodesRepository.getAll().empty());
}

TEST_CASE("delete all episodes", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastName = "Test Podcast";
    Podcast podcast = TestUtils::createPodcastForTest(podcastName);

    std::string episodeTitle = "Test Episode";
    TestUtils::createEpisodeForTest(podcast.getId(), episodeTitle);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.deleteAll();
    REQUIRE(episodesRepository.getAll().empty());
}

TEST_CASE("delete all episodes in podcast", "[episodesRepositoryTests]") {
    TestUtils::emptyDatabase();

    std::string podcastAName = "Test Podcast A";
    std::string podcastBName = "Test Podcast B";

    Podcast testPodcastA = TestUtils::createPodcastForTest(podcastAName);
    Podcast testPodcastB = TestUtils::createPodcastForTest(podcastBName);

    std::string episodeAName = "Test Episode A";
    std::string episodeBName = "Test Episode B";
    std::string episodeCName = "Test Episode C";

    TestUtils::createEpisodeForTest(testPodcastA.getId(), episodeAName);
    TestUtils::createEpisodeForTest(testPodcastB.getId(), episodeBName);
    TestUtils::createEpisodeForTest(testPodcastB.getId(), episodeCName);

    EpisodesRepository episodesRepository = EpisodesRepository();
    episodesRepository.deleteByPodcastId(testPodcastB.getId());

    REQUIRE(episodesRepository.getAll().size() == 1);
}