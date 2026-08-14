#pragma once

#include "OStim/Graph/ActionActor.h"

namespace Stats {
    struct Stat {
    public:
        OStim::ActionActor* actor = nullptr;
        OStim::ActionActor* target = nullptr;
    };
}