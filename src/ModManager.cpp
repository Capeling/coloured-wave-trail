#include "ModManager.hpp"

using namespace geode::prelude;

ModManager* ModManager::sharedState() {
    static ModManager instance;
    return &instance;
}

ModManager::ModManager() {
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
}