#pragma once

#include "GameAPI/GameActorBase.h"

namespace Menus {
    void registerPartnerStatsMenu(std::string section);
    void resetPartnerStatForms();

    namespace PartnerStats {
        static std::vector<GameAPI::GameActorBase> partners;
        static GameAPI::GameActorBase partner;

        void __stdcall render();
    }
}