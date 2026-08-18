#pragma once

#include "GameActor.h"
#include "GameActorBase.h"
#include "GameRecord.h"

namespace GameAPI {
    struct GameFaction : public GameRecord<RE::TESFaction> {
    public:
        inline GameFaction() {}
        inline GameFaction(RE::TESFaction* faction) { form = faction; }
        inline GameFaction(void* faction) { form = (RE::TESFaction*)faction; }

        inline bool contains(GameActor actor) const { return actor.form->IsInFaction(form); }
        int getRank(GameActor actor) const;
        inline bool contains(GameActorBase actor) const { return actor.form->IsInFaction(form); }
        int getRank(GameActorBase actor) const;
    };
}