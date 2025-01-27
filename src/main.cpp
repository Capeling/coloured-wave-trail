#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/ui/GeodeUI.hpp>
#include "ModManager.hpp"

using namespace geode::prelude;

class $modify(PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto rightMenu = static_cast<CCMenu*>(this->getChildByID("right-button-menu"));
        if(!rightMenu) {
            log::error("right-button-menu not found, returning");
            return;
        }

        auto button = CCMenuItemExt::createSpriteExtraWithFilename("optionsBtn.png"_spr, 0.6f, [=](CCObject*) {
            openSettingsPopup(Mod::get());
        });
        button->setID("wave-settings-button"_spr);
        rightMenu->addChild(button);
        rightMenu->updateLayout();
    }
};

class $modify(PlayLayer) {
	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);

        auto mm = ModManager::sharedState();

        m_player1->m_regularTrail->setVisible(true);
        m_player2->m_regularTrail->setVisible(true);

        if(mm->m_color1Enabled) {
		    m_player1->m_waveTrail->setColor(mm->m_color1);      
        }
        if(mm->m_color2Enabled) {
            m_player2->m_waveTrail->setColor(mm->m_color2);
        }

        if(m_player1->m_isDart && mm->m_noDefaultTrail)
            m_player1->m_regularTrail->setVisible(false);
            
        if(m_player2->m_isDart && mm->m_noDefaultTrail)
            m_player2->m_regularTrail->setVisible(false);
	}
};

#ifndef GEODE_IS_MACOS
bool myDrawCircle(CCDrawNode* ins, CCPoint *verts, unsigned int count, const ccColor4F &fillColor, float borderWidth, const ccColor4F &borderColor) { //thanks TheSillyDoggo (https://github.com/TheSillyDoggo/GeodeMenu/blob/main/src/Hacks/SolidWaveTrail.cpp)
    if (typeinfo_cast<HardStreak*>(ins)) {
        auto mm = ModManager::sharedState();

        if(mm->m_noWave) return true;

        if(mm->m_solid) {
            if (fillColor.r >= 1.0f && fillColor.g >= 1.0f && fillColor.b >= 1.0f && ins->getColor() != ccc3(255, 255, 255))
                return true;

            if (ins->getTag() != 1) {
                ins->setTag(1);
                ins->setBlendFunc(CCSprite::create()->getBlendFunc());
            }

            ins->setZOrder(-1);
        }
    }
    return ins->drawPolygon(verts, count, fillColor, borderWidth, borderColor);
}

$execute {
    Mod::get()->hook(
        reinterpret_cast<void*>(
            geode::addresser::getNonVirtual(&HardStreak::drawPolygon)
        ),
        &myDrawCircle,
        "cocos2d::CCDrawNode::drawPolygon",
        tulip::hook::TulipConvention::Thiscall
    );
}
#endif