#pragma once

#include "GameRecord.h"

namespace GameAPI {
    struct GameActor : public GameRecord<RE::Actor> {
    public:
        inline static GameActor getPlayer() { return RE::PlayerCharacter::GetSingleton(); }

        inline GameActor() {}
        inline GameActor(RE::Actor* actor) { form = actor; }
        inline GameActor(void* actor) { form = (RE::Actor*)actor; }

        inline bool isPlayer() const { return form->IsPlayerRef(); }
        inline std::string getName() const { return form->GetDisplayFullName(); }
    };
}