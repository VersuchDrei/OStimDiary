#pragma once

#include "Stat.h"

#include "OStim/Graph/GraphInterface.h"

namespace Stats {
    class StatTable {
    public:
        static void loadStats(OStim::GraphInterface* graph);

        inline static std::vector<Stat>& getStats() { return stats; }

    private:
        inline static std::vector<Stat> stats;
    };
}