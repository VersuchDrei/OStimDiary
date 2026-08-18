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
    int GameFaction::getRank(GameActorBase actor) const {
        for (RE::FACTION_RANK rank : actor.form->factions) {
            if (rank.faction == form) {
                return rank.rank;
            }
        }

        return -2;
    }
}