#include "Manager.h"

#include "Menus/MainMenu.h"

namespace Serialization {
    void Save(SKSE::SerializationInterface* serial) {}

    void Load(SKSE::SerializationInterface* serial) {
        Menus::resetForms();
    }

    void Revert(SKSE::SerializationInterface* serial) {
        Menus::resetForms();
    }
}