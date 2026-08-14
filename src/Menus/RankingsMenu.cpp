#include "RankingsMenu.h"

#include "SKSEMenuFramework/SKSEMenuFramework.h"

#include "Game/LocaleManager.h"

namespace Menus {
    void registerRankingsMenu(std::string section) {
        SKSEMenuFramework::AddSectionItem(section + LocaleManager::GetSingleton()->Translate("$ostim_diary_page_rankings"), Rankings::render);
    }

    namespace Rankings {
        void __stdcall render() {

        }
    }
}