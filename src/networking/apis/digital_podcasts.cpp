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
#include <iostream>
#include <utils/xml_utils.h>
#include <utils/json_utils.h>
#include <pugixml/src/pugixml.hpp>
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

std::vector<Episode> DigitalPodcasts::parsePodcastEpisodes(Podcast & podcast) {
    std::vector<Episode> episodes;
    std::string feedUrl = podcast.getFeedUrl();
    std::string feed = NetworkUtils::query(feedUrl);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(feed.c_str());

    if (!result) {
        std::cout << "XML parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (feed.c_str() + result.offset) << "]\n\n";
    }

    for (pugi::xml_node item = doc.child("channel").child("item"); item; item = item.next_sibling("item")) {
        std::cout << "within";
        long podcastId = podcast.getId();
        std::string title = item.child_value("title");
        std::string summary = item.child_value("itunes:summary");
        std::string publishDate = item.child_value("pubDate");
        std::string enclosureUrl = item.attribute("url").value();
        int duration = atoi(item.child_value("duration"));

        Episode episode = Episode(podcastId, title, summary, publishDate, enclosureUrl, duration);
        episodes.push_back(episode);
    }

    return episodes;
}
