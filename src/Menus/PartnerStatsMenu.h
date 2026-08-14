#pragma once

namespace Menus {
    void registerPartnerStatsMenu(std::string section);

    namespace PartnerStats {
        void __stdcall render();
    }
}