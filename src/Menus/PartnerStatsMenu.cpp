#include "PartnerStatsMenu.h"

#include "SKSEMenuFramework/SKSEMenuFramework.h"

#include "Game/LocaleManager.h"
#include "GameAPI/GameFaction.h"
#include "Stats/StatTable.h"

namespace Menus {
    void registerPartnerStatsMenu(std::string section) {
        SKSEMenuFramework::AddSectionItem(section + LocaleManager::GetSingleton()->Translate("$ostim_diary_page_partner_stats"), PartnerStats::render);
    }

    void resetPartnerStatForms() {
        PartnerStats::partners.clear();
    }

    namespace PartnerStats {
        static ImGuiMCP::ImGuiTableFlags flags = ImGuiMCP::ImGuiTableFlags_Resizable | ImGuiMCP::ImGuiTableFlags_Reorderable | ImGuiMCP::ImGuiTableFlags_Hideable | ImGuiMCP::ImGuiTableFlags_RowBg | ImGuiMCP::ImGuiTableFlags_BordersOuter |
                                                 ImGuiMCP::ImGuiTableFlags_BordersV | ImGuiMCP::ImGuiTableFlags_NoBordersInBody | ImGuiMCP::ImGuiTableFlags_ScrollY;

        static void renderLine(GameAPI::GameFaction stat){
            int value = stat ? stat.getRank(partner) : 0;

            if (value <= 0) {
                return;
            }

            ImGuiMCP::TableNextRow();
            ImGuiMCP::TableSetColumnIndex(0);
            ImGuiMCP::Text(LocaleManager::GetSingleton()->Translate("$" + stat.getEditorID()).c_str());
            ImGuiMCP::TableSetColumnIndex(1);
            ImGuiMCP::Text(value > 99 ? ">99" : std::to_string(value).c_str());
        }

        void __stdcall render() {
            GameAPI::GameList statList = Stats::StatTable::getStatList();
            if (partners.size() != statList.size()) {
                partners.clear();
                statList.forEachActorBase([](GameAPI::GameActorBase actor) {
                    partners.push_back(actor);
                });

                std::sort(partners.begin(), partners.end(), [](GameAPI::GameActorBase a, GameAPI::GameActorBase b) {
                    return a.getName() < b.getName();
                });

                if (partners.size() != 0) {
                    partner = partners[0];
                }
            }

            if (partners.size() == 0) {
                ImGuiMCP::Text(LocaleManager::GetSingleton()->Translate("$ostim_diary_no_partners").c_str());
                return;
            }

            if (ImGuiMCP::BeginCombo(LocaleManager::GetSingleton()->Translate("$ostim_diary_actor").c_str(), partner.getName().c_str())) {
                for (GameAPI::GameActorBase actor : partners) {
                    if (ImGuiMCP::Selectable(actor.getName().c_str(), actor == partner)) {
                        partner = actor;
                    }
                }
                ImGuiMCP::EndCombo();
            }

            if (ImGuiMCP::BeginTable("partnerStats", 2, flags)) {
                ImGuiMCP::TableSetupColumn("");
                ImGuiMCP::TableSetupColumn(LocaleManager::GetSingleton()->Translate("$ostim_diary_count").c_str());
                ImGuiMCP::TableHeadersRow();

                for (Stats::Stat& stat : Stats::StatTable::getStats()) {
                    renderLine(stat.actor->getTimesPerformedWithPlayerFaction());
                    renderLine(stat.actor->getTimesClimaxedWithPlayerFaction());
                    renderLine(stat.actor->getTimesPartnerClimaxedWithPlayerFaction());
                    if (stat.actor->getTimesPerformedWithPlayerFaction() != stat.target->getTimesPerformedWithPlayerFaction()) {
                        renderLine(stat.target->getTimesPerformedWithPlayerFaction());
                        renderLine(stat.target->getTimesClimaxedWithPlayerFaction());
                        renderLine(stat.target->getTimesPartnerClimaxedWithPlayerFaction());
                    }
                }

                ImGuiMCP::EndTable();
            }
        }
    }
}