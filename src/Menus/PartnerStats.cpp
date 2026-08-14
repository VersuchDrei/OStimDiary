#include "PartnerStatsMenu.h"

#include "SKSEMenuFramework/SKSEMenuFramework.h"

#include "Game/LocaleManager.h"

namespace Menus {
    void registerPartnerStatsMenu(std::string section) {
        SKSEMenuFramework::AddSectionItem(section + LocaleManager::GetSingleton()->Translate("$ostim_diary_page_partner_stats"), PartnerStats::render);
    }

    namespace PartnerStats {
        void __stdcall render() {

        }
    }
}