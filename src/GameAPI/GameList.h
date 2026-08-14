#pragma once

#include "GameActor.h"
#include "GameRecord.h"

namespace GameAPI {
    struct GameList : public GameRecord<RE::BGSListForm> {
    public:
        inline GameList() {}
        inline GameList(RE::BGSListForm* list) { form = list; }
        inline GameList(void* list) { form = (RE::BGSListForm*)list; }

        inline bool contains(GameActor actor) const { return form->HasForm(actor.form) || form->HasForm(actor.form->GetActorBase()) || form->HasForm(actor.form->GetRace()); }
        inline uint32_t size() { return form->forms.size() + (form->scriptAddedTempForms ? form->scriptAddedTempForms->size() : 0); }
    };
}