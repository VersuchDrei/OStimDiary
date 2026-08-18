#include "RankingsMenu.h"

#include "SKSEMenuFramework/SKSEMenuFramework.h"

#include "Game/LocaleManager.h"
#include "GameAPI/GameFaction.h"
#include "Stats/StatTable.h"

namespace Menus {
    void registerRankingsMenu(std::string section) {
        SKSEMenuFramework::AddSectionItem(section + LocaleManager::GetSingleton()->Translate("$ostim_diary_page_rankings"), Rankings::render);
    }

    namespace Rankings {
        static ImGuiMCP::ImGuiTableFlags flags = ImGuiMCP::ImGuiTableFlags_Resizable | ImGuiMCP::ImGuiTableFlags_Reorderable | ImGuiMCP::ImGuiTableFlags_Hideable | ImGuiMCP::ImGuiTableFlags_RowBg | ImGuiMCP::ImGuiTableFlags_BordersOuter |
                                                 ImGuiMCP::ImGuiTableFlags_BordersV | ImGuiMCP::ImGuiTableFlags_NoBordersInBody | ImGuiMCP::ImGuiTableFlags_ScrollY;

        static const uint32_t maxColumns = 5;
        static uint32_t columns = 0;

        static void renderLine(GameAPI::GameFaction stat, GameAPI::GameList actors) {
            if (!stat || !actors || actors.size() == 0) {
                return;
            }

            std::vector<GameAPI::GameActorBase> partners;
            actors.forEachActorBase([&partners](GameAPI::GameActorBase actor) {
                partners.push_back(actor);    
            });

            std::sort(partners.begin(), partners.end(), [stat](GameAPI::GameActorBase a, GameAPI::GameActorBase b) {
                return stat.getRank(a) > stat.getRank(b);
            });

            if (partners.size() == 0) {
                // this should only happen if some mod put something other than an actor base in the form list
                // which really shouldn't happen because it will fuck with OStim big time
                // but it's better to be save than sorry
                return;
            }

            if (stat.getRank(partners[0]) <= 0) {
                return;
            }

            ImGuiMCP::TableNextRow();
            ImGuiMCP::TableSetColumnIndex(0);
            ImGuiMCP::Text(LocaleManager::GetSingleton()->Translate("$" + stat.getEditorID()).c_str());

            for (int i = 0; i < columns; i++) {
                if (partners.size() == i) {
                    break;
                }

                int rank = stat.getRank(partners[i]);
                if (rank <= 0) {
                    break;
                }

                ImGuiMCP::TableSetColumnIndex(i + 1);
                ImGuiMCP::Text((partners[i].getName() + " (" + std::to_string(rank) + ")").c_str());
            }
        }

        void __stdcall render() {
            columns = std::min(maxColumns, Stats::StatTable::getStatList().size());
            if (columns == 0) {
                ImGuiMCP::Text(LocaleManager::GetSingleton()->Translate("$ostim_diary_no_partners").c_str());
                return;
            }

            if (ImGuiMCP::BeginTable("rankings", columns + 1, flags)) {
                
                for (Stats::Stat& stat : Stats::StatTable::getStats()) {
                    renderLine(stat.actor->getTimesPerformedWithPlayerFaction(), stat.actor->getPlayerMateList());
                    renderLine(stat.actor->getTimesClimaxedWithPlayerFaction(), stat.actor->getPlayerMatePartnerClimaxedList());
                    renderLine(stat.actor->getTimesPartnerClimaxedWithPlayerFaction(), stat.actor->getPlayerMateClimaxedList());
                    if (stat.actor->getTimesPerformedWithPlayerFaction() != stat.target->getTimesPerformedWithPlayerFaction()) {
                        renderLine(stat.target->getTimesPerformedWithPlayerFaction(), stat.target->getPlayerMateList());
                        renderLine(stat.target->getTimesClimaxedWithPlayerFaction(), stat.target->getPlayerMatePartnerClimaxedList());
                        renderLine(stat.target->getTimesPartnerClimaxedWithPlayerFaction(), stat.target->getPlayerMateClimaxedList());
                    }
                }

                ImGuiMCP::EndTable();
            }
        }
    }
}