#include "GameFaction.h"

namespace GameAPI {
    int GameFaction::getRank(GameActor actor) const {
        for (RE::FACTION_RANK rank : actor.form->GetActorBase()->factions) {
            if (rank.faction == form) {
                return rank.rank;
            }
        }

        return -2;
    }
}