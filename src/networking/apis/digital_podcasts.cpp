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
std::string DigitalPodcasts::search(std::string & searchString) {
    std::string appId = DigitalPodcasts::getAppId();
    std::stringstream ss;

    ss << BASE_URL << "search/?" << "appid=" << appId << "&keywords=" << searchString << "&format="
            << DigitalPodcasts::FORMAT << "&searchsource=title";

    std::string url = ss.str();
    std::string response = NetworkUtils::query(url);

    return response;
}
