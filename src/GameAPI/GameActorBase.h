#pragma once

#include "GameRecord.h"

namespace GameAPI {
    struct GameActorBase : public GameRecord<RE::TESNPC> {
        inline GameActorBase() {}
        inline GameActorBase(RE::TESNPC* actor) { form = actor; }
        inline GameActorBase(void* actor) { form = (RE::TESNPC*)actor; }

        inline bool isPlayer() const { return form->IsPlayer(); }
        std::string getName() const;
    };
}