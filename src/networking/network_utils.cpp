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
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "network_utils.h"

/*
 * Query the passed string url and return the response as a
 * string
 */
std::string NetworkUtils::query(std::string & url) {
    std::ostringstream os;
    curlpp::Cleanup curlppCleanup;

    try {
        os << curlpp::options::Url(url);
    } catch (const std::exception & e) {
        std::stringstream ss;
        ss << "Error querying url: " << e.what();
        throw ss.str();
    }

    return  os.str();
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void NetworkUtils::downloadPodcastImage(Podcast & podcast, std::string & extension) {
    boost::uuids::random_generator generator;

    std::stringstream saveLocaleStream;
    saveLocaleStream << "build/.cache/" << generator() << "." << extension;
    std::string saveLocale = saveLocaleStream.str();

    CURL * curl;
    FILE * fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(saveLocale.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, podcast.getImageUrl().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt (curl, CURLOPT_VERBOSE, 1L);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    podcast.setLocalImageDir(saveLocale);
}
