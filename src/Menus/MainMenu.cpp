#include "MainMenu.h"

#include "PartnerStatsMenu.h"
#include "PlayerStatsMenu.h"
#include "RankingsMenu.h"

#include "SKSEMenuFramework/SKSEMenuFramework.h"

#include "Game/LocaleManager.h"

namespace Menus {
    void registerMenus() {
        if (!SKSEMenuFramework::IsInstalled()) {
            logger::critical("Couldn't get SKSE Menu Framework.");
            return;
        }

        SKSEMenuFramework::SetSection("OStim Standalone");
        std::string section = LocaleManager::GetSingleton()->Translate("$ostim_page_addons") + "/" + LocaleManager::GetSingleton()->Translate("$ostim_diary") + "/";
        registerPlayerStatsMenu(section);
        registerPartnerStatsMenu(section);
        registerRankingsMenu(section);
    }
}