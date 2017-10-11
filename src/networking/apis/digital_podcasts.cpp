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
    ss << BASE_URL << "search/?" << "appid=" << appId << "&keywords=" << searchString << "&format=rss" << "&searchsource=all";

    std::string url = ss.str();
    std::string response = NetworkUtils::query(url);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(response.c_str());

    if (result) {
        
    }
    else {
        std::cout << "XML parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (response.c_str() + result.offset) << "]\n\n";
    }

    return podcasts;
}

std::vector<Episode> DigitalPodcasts::parsePodcastEpisodes(Podcast & podcast) {
    std::vector<Episode> episodes;
    std::string feedUrl = podcast.getFeedUrl();
    std::string feed = NetworkUtils::query(feedUrl);

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(feed.c_str());

    if (result) {

    }
    else {
        std::cout << "XML parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
        std::cout << "Error description: " << result.description() << "\n";
        std::cout << "Error offset: " << result.offset << " (error at [..." << (feed.c_str() + result.offset) << "]\n\n";
    }

    return episodes;
}
