#include "PlayerObject.hpp"
#include "ModManager.hpp"

void HookPlayerObject::resetStreak() {
    PlayerObject::resetStreak();
    updateStreak();
}

void HookPlayerObject::updateStreak() {
    auto mm = ModManager::sharedState();
    auto gm = GameManager::get();
    m_waveTrail->m_isSolid = mm->m_solid;

    if(mm->m_noWave) {
        m_waveTrail->setVisible(false);
        return;
    }
    m_waveTrail->setVisible(true);

    if(!mm->m_solid) {
        m_waveTrail->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
    } else {
        m_waveTrail->setBlendFunc({ 770, 771 }); 
    }
    
    if(m_isSecondPlayer) {
        if(mm->m_color2Enabled)
            m_waveTrail->setColor(mm->m_color2);
        else
            m_waveTrail->setColor(gm->colorForIdx(gm->getPlayerColor2()));
    } else {
        if(mm->m_color1Enabled)
            m_waveTrail->setColor(mm->m_color1);
        else
            m_waveTrail->setColor(gm->colorForIdx(gm->getPlayerColor()));
    }
}

void HookPlayerObject::toggleDartMode(bool p0, bool p1) {
    PlayerObject::toggleDartMode(p0, p1);

    if(p0 && ModManager::sharedState()->m_noDefaultTrail)
        m_regularTrail->setVisible(false);
    else
        m_regularTrail->setVisible(true);

    updateStreak();
}