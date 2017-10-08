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

#ifndef BEAM_DIGITAL_PODCASTS_H
#define BEAM_DIGITAL_PODCASTS_H

#include <vector>
#include <entities/podcast.h>

namespace DigitalPodcasts {
    const static std::string BASE_URL = "http://api.digitalpodcast.com/v2r/";
    const static std::string APP_ID = std::getenv("DIGITAL_PODCAST_APP_ID");
    const static std::string FORMAT = "json";

    std::string search(std::string & searchString);
}

#endif //BEAM_DIGITAL_PODCASTS_H
