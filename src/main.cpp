#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
	void postUpdate(float dt) {
		PlayLayer::postUpdate(dt);
		auto colour = Mod::get()->getSettingValue<ccColor3B>("colour");
		m_player1->m_waveTrail->setColor(colour);
		m_player2->m_waveTrail->setColor(colour);
	}
};

bool myDrawCircle(CCDrawNode* ins, CCPoint *verts, unsigned int count, const ccColor4F &fillColor, float borderWidth, const ccColor4F &borderColor) {

    if (typeinfo_cast<HardStreak*>(ins))
    {
            if (fillColor.r >= 1.0f && fillColor.g >= 1.0f && fillColor.b >= 1.0f && ins->getColor() != ccc3(255, 255, 255))
                return true;

            if (ins->getTag() != 1)
            {
                ins->setTag(1);
                ins->setBlendFunc(CCSprite::create()->getBlendFunc());
            }

            ins->setZOrder(-1);
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