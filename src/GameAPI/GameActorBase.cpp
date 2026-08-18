#include "GameActorBase.h"

namespace GameAPI {
    std::string GameActorBase::getName() const {
        RE::Actor* actor = form->GetUniqueActor();
        if (actor) {
            return actor->GetDisplayFullName();
        } else {
            return "generic actor";
        }
    }
}