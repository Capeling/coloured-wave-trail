#pragma once
#include <Geode/DefaultInclude.hpp>
#include <Geode/modify/PlayerObject.hpp>

struct HookPlayerObject : geode::Modify<HookPlayerObject, PlayerObject> {
    void resetStreak();
    void updateStreak();
    void toggleDartMode(bool p0, bool p1);
};