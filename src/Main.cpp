#include "Logger.h"

#include "OStim/InterfaceExchangeMessage.h"

#include "Menus/MainMenu.h"
#include "Stats/StatTable.h"

namespace {
    OStim::GraphInterface* graph = nullptr;

    void MessageHandler(SKSE::MessagingInterface::Message* message) {
        if (message->type == SKSE::MessagingInterface::kPostLoad) {
            OStim::InterfaceExchangeMessage msg;
            auto intfc = SKSE::GetMessagingInterface();
            intfc->Dispatch(OStim::InterfaceExchangeMessage::MESSAGE_TYPE, (void*)&msg, sizeof(OStim::InterfaceExchangeMessage*), "OStim");
            if (!msg.interfaceMap) {
                logger::critical("Couldn't get OStim interface map.");
                return;
            }

            graph = static_cast<OStim::GraphInterface*>(msg.interfaceMap->queryInterface(OStim::GraphInterface::NAME));

            Menus::registerMenus();
        } else if (message->type == SKSE::MessagingInterface::kDataLoaded) {
            Stats::StatTable::loadStats(graph);
        }
    }
}


SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener(MessageHandler);
    SetupLog();
    logger::info("Plugin loaded");
    return true;
}