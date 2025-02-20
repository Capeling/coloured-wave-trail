#include "ModManager.hpp"
#include "PlayerObject.hpp"

using namespace geode::prelude;

ModManager* ModManager::sharedState() {
    static ModManager instance;
    return &instance;
}

void ModManager::load() {
    auto mod = Mod::get();
    
    m_color1 = mod->getSettingValue<ccColor3B>("colour");
    m_color2 = mod->getSettingValue<ccColor3B>("colour2");
    m_color1Enabled = mod->getSettingValue<bool>("colour1Enabled");
    m_color2Enabled = mod->getSettingValue<bool>("colour2Enabled");
    m_noWave = mod->getSettingValue<bool>("noWave");
    m_noDefaultTrail = mod->getSettingValue<bool>("noDefaultTrail");
    m_solid = mod->getSettingValue<bool>("solid");

}

$on_mod(Loaded) {
    auto mm = ModManager::sharedState();
    mm->load();
    
    listenForSettingChanges("colour", [mm](ccColor3B val) {
        mm->m_color1 = val;
    });
    
    listenForSettingChanges("colour2", [mm](ccColor3B val) {
        mm->m_color2 = val;
    });
    
    listenForSettingChanges("colour1Enabled", [mm](bool val) {
        mm->m_color1Enabled = val;
    });
    
    listenForSettingChanges("colour2Enabled", [mm](bool val) {
        mm->m_color2Enabled = val;
    });
    
    listenForSettingChanges("noWave", [mm](bool val) {
        mm->m_noWave = val;
    });
    
    listenForSettingChanges("noDefaultTrail", [mm](bool val) {
        mm->m_noDefaultTrail = val;
    });
    
    listenForSettingChanges("solid", [mm](bool val) {
        mm->m_solid = val;
    });

    listenForAllSettingChanges([](std::shared_ptr<SettingV3> setting) {
        if(!PlayLayer::get())
            return;

        auto p1 = static_cast<HookPlayerObject*>(PlayLayer::get()->m_player1);
        auto p2 = static_cast<HookPlayerObject*>(PlayLayer::get()->m_player2);

        if(p1 && p2) {
            p1->updateStreak();
            p2->updateStreak();
        }
    });
}