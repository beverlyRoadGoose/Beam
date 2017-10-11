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

add_library(beam-utils
        src/utils/json_utils.cpp
        src/utils/json_utils.h
        src/utils/xml_utils.cpp
        src/utils/xml_utils.h)
target_link_libraries(beam-utils pugixml)

add_library(beam-database
        src/database/databasemanager.h
        src/database/databasemanager.cpp
        src/database/repositories/podcasts_repository.h
        src/database/repositories/podcasts_repository.cpp
        src/database/repositories/episodes_repository.h
        src/database/repositories/episodes_repository.cpp)
target_link_libraries(beam-database sqlite3)

add_library(beam-entities
        src/entities/podcast.h
        src/entities/podcast.cpp
        src/entities/episode.h
        src/entities/episode.cpp)

add_library(beam-modules
        src/modules/discovery_panel_manager.cpp
        src/modules/discovery_panel_manager.h)
target_link_libraries(beam-modules beam-entities beam-networking beam-database beam-utils)

add_library(beam-networking
        src/networking/network_utils.cpp
        src/networking/network_utils.h
        src/networking/apis/digital_podcasts.cpp
        src/networking/apis/digital_podcasts.h)
target_link_libraries(beam-networking curlpp ${CURL_LIBRARIES} beam-utils beam-entities)

add_library(beam-ui
        src/ui/mainframe.h
        src/ui/mainframe.cpp
        src/ui/panels/podcasts_panel.cpp
        src/ui/panels/podcasts_panel.h
        src/ui/widgets/podcasts_list_item_panel.cpp
        src/ui/widgets/podcasts_list_item_panel.h
        src/ui/widgets/podcasts_list_panel.cpp
        src/ui/widgets/podcasts_list_panel.h
        src/ui/panels/discovery_panel.cpp
        src/ui/panels/discovery_panel.h)
target_link_libraries(beam-ui ${wxWidgets_LIBRARIES} beam-modules)