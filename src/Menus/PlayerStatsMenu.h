#pragma once

namespace Menus {
    void registerPlayerStatsMenu(std::string section);

    namespace PlayerStats {
        void __stdcall render();
    }
}