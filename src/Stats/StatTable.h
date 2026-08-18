#pragma once

#include "Stat.h"

#include "OStim/Graph/GraphInterface.h"

#include "GameAPI/GameList.h"

namespace Stats {
    class StatTable {
    public:
        static void loadStats(OStim::GraphInterface* graph);

        inline static GameAPI::GameList getStatList() { return statList; }
        inline static std::vector<Stat>& getStats() { return stats; }

    private:
        inline static GameAPI::GameList statList;
        inline static std::vector<Stat> stats;
    };
}