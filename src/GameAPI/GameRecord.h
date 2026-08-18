#pragma once

#include "po3tweaks/editorID.hpp"

namespace GameAPI {
    template<class T>
    struct GameRecord {
    public:
        T* form = nullptr;

        inline operator bool() const { return form; }
        inline bool operator==(const GameRecord<T> other) const { return form == other.form; }
        inline bool operator!=(const GameRecord<T> other) const { return form != other.form; }

        inline void clear() { form = nullptr; }

        inline void* toABIPointer() { return form; }
        inline std::string getEditorID() { return clib_util::editorID::get_editorID(form); }

        void loadFile(std::string mod, uint32_t formID) {
            // If mod not specified, indicates likely a runtime generated form.
            if (mod.empty()) {
                form = RE::TESForm::LookupByID<T>(formID | (0xFF >> 24));
            } else {
                form = RE::TESDataHandler::GetSingleton()->LookupForm<T>(formID, mod);
            }
        }
    };
}