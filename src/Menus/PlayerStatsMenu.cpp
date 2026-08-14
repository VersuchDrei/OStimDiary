#include "PlayerStatsMenu.h"

#include "SKSEMenuFramework/SKSEMenuFramework.h"

#include "Game/LocaleManager.h"
#include "GameAPI/GameFaction.h"
#include "GameAPI/GameList.h"
#include "Stats/StatTable.h"

namespace Menus {
    void registerPlayerStatsMenu(std::string section) {
        SKSEMenuFramework::AddSectionItem(section + LocaleManager::GetSingleton()->Translate("$ostim_diary_page_player_stats"), PlayerStats::render);
    }

    namespace PlayerStats {
        static ImGuiMCP::ImGuiTableFlags flags = ImGuiMCP::ImGuiTableFlags_Resizable | ImGuiMCP::ImGuiTableFlags_Reorderable | ImGuiMCP::ImGuiTableFlags_Hideable | ImGuiMCP::ImGuiTableFlags_RowBg | ImGuiMCP::ImGuiTableFlags_BordersOuter |
                                                 ImGuiMCP::ImGuiTableFlags_BordersV | ImGuiMCP::ImGuiTableFlags_NoBordersInBody | ImGuiMCP::ImGuiTableFlags_ScrollY;

        void renderLine(GameAPI::GameFaction total, GameAPI::GameList unique) {
            int totalValue = total ? total.getRank(GameAPI::GameActor::getPlayer()) : 0;
            if (totalValue < 0) {
                totalValue = 0;
            }
            int uniqueValue = unique ? unique.size() : 0;

            if (totalValue == 0 && uniqueValue == 0) {
                return;
            }

            ImGuiMCP::TableNextRow();
            ImGuiMCP::TableSetColumnIndex(0);
            ImGuiMCP::Text(LocaleManager::GetSingleton()->Translate("$" + total.getEditorID()).c_str());
            ImGuiMCP::TableSetColumnIndex(1);
            ImGuiMCP::Text(totalValue > 99 ? ">99" : std::to_string(totalValue).c_str());
            ImGuiMCP::TableSetColumnIndex(2);
            ImGuiMCP::Text(std::to_string(uniqueValue).c_str());
        }

        void __stdcall render() {
            if (ImGuiMCP::BeginTable("playerStats", 3, flags)) {
                ImGuiMCP::TableSetupColumn("");
                ImGuiMCP::TableSetupColumn("total");
                ImGuiMCP::TableSetupColumn("unique");
                ImGuiMCP::TableHeadersRow();

                for (Stats::Stat& stat : Stats::StatTable::getStats()) {
                    renderLine(stat.actor->getTimesPerformedFaction(), stat.target->getPlayerMateList());
                    renderLine(stat.actor->getTimesClimaxedFaction(), stat.target->getPlayerMatePartnerClimaxedList());
                    renderLine(stat.actor->getTimesPartnerClimaxedFaction(), stat.target->getPlayerMateClimaxedList());
                    if (stat.actor->getTimesPerformedFaction() != stat.target->getTimesPerformedFaction()) {
                        renderLine(stat.target->getTimesPerformedFaction(), stat.actor->getPlayerMateList());
                        renderLine(stat.target->getTimesClimaxedFaction(), stat.actor->getPlayerMatePartnerClimaxedList());
                        renderLine(stat.target->getTimesPartnerClimaxedFaction(), stat.actor->getPlayerMateClimaxedList());
                    }
                }

                ImGuiMCP::EndTable();
            }
        }
    }
}