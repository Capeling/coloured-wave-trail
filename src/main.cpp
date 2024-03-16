#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
        if(!Mod::get()->getSettingValue<bool>("colourEnabled")) return;
		auto colour1 = Mod::get()->getSettingValue<ccColor3B>("colour");
        auto colour2 = Mod::get()->getSettingValue<ccColor3B>("colour2");
		m_player1->m_waveTrail->setColor(colour1);
		m_player2->m_waveTrail->setColor(colour2);
	}
};

bool myDrawCircle(CCDrawNode* ins, CCPoint *verts, unsigned int count, const ccColor4F &fillColor, float borderWidth, const ccColor4F &borderColor) { //thanks TheSillyDoggo (https://github.com/TheSillyDoggo/GeodeMenu/blob/main/src/Hacks/SolidWaveTrail.cpp)
    if (typeinfo_cast<HardStreak*>(ins))
    {
            if(!Mod::get()->getSettingValue<bool>("noWave")) return true;

            if(Mod::get()->getSettingValue<bool>("solid")) {
                if (fillColor.r >= 1.0f && fillColor.g >= 1.0f && fillColor.b >= 1.0f && ins->getColor() != ccc3(255, 255, 255))
                    return true;

                if (ins->getTag() != 1)
                {
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