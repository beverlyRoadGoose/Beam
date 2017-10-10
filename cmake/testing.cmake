#
#  Copyright 2017 Oluwatobi Adeyinka
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

enable_testing()

add_library(Catch lib/catch/catch.hpp lib/catch/catch.cpp)

add_library(TestUtils tests/testutils.h tests/testutils.cpp)
target_link_libraries(TestUtils beam-database)

add_executable(podcast-tests tests/entities/podcasttests.cpp)
target_link_libraries(podcast-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME PodcastTests COMMAND podcast-tests)

add_executable(episode-tests tests/entities/episodetests.cpp)
target_link_libraries(episode-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME EpisodeTests COMMAND episode-tests)

add_executable(database-manager-tests tests/database/databasemanagertests.cpp)
target_link_libraries(database-manager-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME DatabaseManagerTests COMMAND database-manager-tests)

add_executable(podcasts-repository-tests tests/database/repositories/podcasts_repository_tests.cpp)
target_link_libraries(podcasts-repository-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME PodcastsRepositoryTests COMMAND podcasts-repository-tests)

add_executable(episodes-repository-tests tests/database/repositories/episodes_repository_tests.cpp)
target_link_libraries(episodes-repository-tests Catch TestUtils sqlite3 beam-database beam-entities)
add_test(NAME EpisodesRepositoryTests COMMAND episodes-repository-tests)

add_executable(network-utils-tests tests/networking/network_utils_tests.cpp)
target_link_libraries(network-utils-tests Catch beam-networking)
add_test(NAME NetworkUtilsTests COMMAND network-utils-tests)

add_executable(digital-podcasts-tests tests/networking/apis/digital_podcasts_tests.cpp)
target_link_libraries(digital-podcasts-tests Catch beam-entities beam-networking beam-database)
add_test(NAME DigitalPodcastsTests COMMAND digital-podcasts-tests)

add_executable(json-utils-tests tests/utils/json_utils_tests.cpp)
target_link_libraries(json-utils-tests Catch beam-utils beam-networking)
add_test(NAME JSONUtilsTests COMMAND json-utils-tests)

add_executable(xml-utils-tests tests/utils/xml_utils_tests.cpp)
target_link_libraries(xml-utils-tests Catch beam-utils beam-networking beam-entities)
add_test(NAME XMLUtilsTests COMMAND xml-utils-tests)