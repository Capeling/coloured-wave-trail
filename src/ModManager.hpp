#pragma once

#include <Geode/Geode.hpp>

class ModManager {
public:
    static ModManager* sharedState();

    ModManager();

    cocos2d::ccColor3B m_color1;
    cocos2d::ccColor3B m_color2;
    bool m_color1Enabled;
    bool m_color2Enabled;
    bool m_solid;
    bool m_noWave;
    bool m_noDefaultTrail;
};