#include "GameList.h"

namespace GameAPI {
    void GameList::forEachActor(std::function<void(GameActor)> lambda) {
        form->ForEachForm([&lambda](RE::TESForm* element) {
            if (element->Is(RE::Actor::FORMTYPE)) {
                lambda(element->As<RE::Actor>());
            }

            return RE::BSContainer::ForEachResult::kContinue;
        });
    }

    void GameList::forEachActorBase(std::function<void(GameActorBase)> lambda) {
        form->ForEachForm([&lambda](RE::TESForm* element) {
            if (element->Is(RE::TESNPC::FORMTYPE)) {
                lambda(element->As<RE::TESNPC>());
            }

            return RE::BSContainer::ForEachResult::kContinue;
        });
    }
}