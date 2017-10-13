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

#include <iostream>
#include <utils/json_utils.h>
#include <networking/network_utils.h>
#include <networking/apis/digital_podcasts.h>

#include "discovery_panel_manager.h"

DiscoveryPanelManager::DiscoveryPanelManager() = default;

DiscoveryPanelManager::~DiscoveryPanelManager() = default;

std::vector<Podcast> DiscoveryPanelManager::getTopPodcasts() {
    std::vector<Podcast> podcasts;
    std::string url = "https://rss.itunes.apple.com/api/v1/us/podcasts/top-podcasts/all/100/explicit.json";

    std::string response = NetworkUtils::query(url);
    rapidjson::Document responseJson = JSONUtils::parseJSONString(response);

    const rapidjson::Value & responseObject = responseJson["feed"];
    const rapidjson::Value & podcastsJSONArray = responseObject["results"];
    assert(podcastsJSONArray.IsArray());

    for (rapidjson::SizeType i = 0; i < podcastsJSONArray.Size(); i++) {
        const rapidjson::Value & JSONObject = podcastsJSONArray[i];

        long id = atol(JSONObject["id"].GetString());
        std::string title = JSONObject["name"].GetString();
        std::string publisher = JSONObject["artistName"].GetString();
        std::string feedUrl = "";
        std::string description = JSONObject["name"].GetString();
        std::string imageUrl = JSONObject["artworkUrl100"].GetString();
        std::string url = JSONObject["url"].GetString();

        Podcast podcast = Podcast(id, title, publisher, feedUrl, description, imageUrl, url);
        std::string imageExtension = "png";
        NetworkUtils::downloadPodcastImage(podcast, imageExtension);

        podcasts.push_back(podcast);
    }

    return podcasts;
}

std::vector<Podcast> DiscoveryPanelManager::getSocietyAndCulturePodcasts() {
    std::vector<Podcast> podcasts;

    std::string url = "https://itunes.apple.com/search?term=podcast&genreId=1324&limit=100";
    std::string response = NetworkUtils::query(url);
    rapidjson::Document responseJson = JSONUtils::parseJSONString(response);

    const rapidjson::Value & podcastsJSONArray = responseJson["results"];
    assert(podcastsJSONArray.IsArray());

    for (rapidjson::SizeType i = 0; i < podcastsJSONArray.Size(); i++) {
        const rapidjson::Value & JSONObject = podcastsJSONArray[i];

        long id = (long)(JSONObject["collectionId"].GetInt());
        std::string title = JSONObject["collectionName"].GetString();
        std::string publisher = JSONObject["artistName"].GetString();
        std::string feedUrl = JSONObject["feedUrl"].GetString();
        std::string description = JSONObject["collectionName"].GetString();
        std::string imageUrl = JSONObject["artworkUrl600"].GetString();
        std::string url = JSONObject["collectionViewUrl"].GetString();

        Podcast podcast = Podcast(id, title, publisher, feedUrl, description, imageUrl, url);
        std::string imageExtension = "jpg";
        NetworkUtils::downloadPodcastImage(podcast, imageExtension);

        podcasts.push_back(podcast);
    }

    return podcasts;
}
