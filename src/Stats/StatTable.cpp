#include "StatTable.h"

#include "nlohmann/json.hpp"

namespace Stats {
    const char* STATS_FILE_PATH{"Data/SKSE/Plugins/OStimDiary.json"};

    void StatTable::loadStats(OStim::GraphInterface* graph) {
        if (!graph) {
            return;
        }

        if (!std::filesystem::exists(STATS_FILE_PATH)) {
            logger::warn("config file does not exist");
            return;
        }

        std::ifstream ifs(STATS_FILE_PATH);
        nlohmann::json json = nlohmann::json::parse(ifs, nullptr, false);
        if (json.is_discarded()) {
            logger::warn("config file is malformed");
            return;
        }

        if (!json.is_array()) {
            logger::warn("config file is not an array");
            return;
        }

        int i = -1;
        for (nlohmann::json element : json) {
            i++;
            if (!element.is_object()) {
                logger::warn("element {} in config file is not an object", i);
                continue;
            }

            if (!element.contains("type")) {
                logger::warn("element {} in config file does not contain property 'type'", i);
                continue;
            }

            if (!element["type"].is_string()) {
                logger::warn("property 'string' of element {} in config file is not a string", i);
                continue;
            }

            if (!element.contains("id")) {
                logger::warn("element {} in config file does not contain property 'id'", i);
                continue;
            }

            if (!element["id"].is_string()) {
                logger::warn("property 'id' of element {} in config file is not a string", i);
                continue;
            }

            std::string type = element["type"];
            std::string id = element["id"];

            if (type == "tag") {
                OStim::ActionTag* tag = graph->getActionTag(id.c_str());
                if (!tag) {
                    logger::warn("element {} in config file has unknown tag '{}'", i, id);
                    continue;
                }

                stats.push_back({tag->getActor(OStim::Role::ACTOR), tag->getActor(OStim::Role::TARGET)});
            } else if (type == "action") {
                OStim::ActionType* action = graph->getActionType(id.c_str());
                if (!action) {
                    logger::warn("element {} in config file has unknown action '{}'", i, id);
                    continue;
                }

                stats.push_back({action->getActor(OStim::Role::ACTOR), action->getActor(OStim::Role::TARGET)});
            } else {
                logger::warn("element {} in config file has unknown type '{}'", i, type);
            }
        }
    }
}