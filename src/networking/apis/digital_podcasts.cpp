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
#include <utils/json_utils.h>
#include <networking/network_utils.h>

#include "digital_podcasts.h"

std::string DigitalPodcasts::getAppId() {
    if (std::getenv("DIGITAL_PODCAST_APP_ID") == nullptr)
        throw "Environment variable DIGITAL_PODCAST_APP_ID is not set.";
    return std::getenv("DIGITAL_PODCAST_APP_ID");
}

/*
 * query the api with the passed search string and return a vector
 * of the matching podcasts
 *
 * TODO change return type to vector
 */
std::vector<Podcast> DigitalPodcasts::search(std::string & searchString) {
    std::vector<Podcast> podcasts;

    std::string appId = DigitalPodcasts::getAppId();
    std::stringstream ss;

    ss << BASE_URL << "search/?" << "appid=" << appId << "&keywords=" << searchString << "&format="
            << DigitalPodcasts::FORMAT << "&searchsource=all";

    std::string url = ss.str();
    std::string response = NetworkUtils::query(url);
    rapidjson::Document responseJson = JSONUtils::parseJSONString(response);

    const rapidjson::Value & podcastsJSONArray = responseJson["feeds"];
    assert(podcastsJSONArray.IsArray());

    for (rapidjson::SizeType i = 0; i < podcastsJSONArray.Size(); i++) {
        const rapidjson::Value & JSONWrapperObject = podcastsJSONArray[i];
        const rapidjson::Value & JSONObject = JSONWrapperObject["feed"];

        long id = (long)(JSONObject["id"].GetInt());
        std::string title = JSONObject["title"].GetString();
        std::string link = JSONObject["link"].GetString();
        std::string feedUrl = JSONObject["feed_url"].GetString();
        std::string description = JSONObject["description"].GetString();
        std::string imageUrl = JSONObject["small_feed_image_url"].GetString();
        std::string url = JSONObject["url"].GetString();

        Podcast podcast = Podcast(id, title, link, feedUrl, description, imageUrl, url);
        podcasts.push_back(podcast);
    }

    return podcasts;
}
