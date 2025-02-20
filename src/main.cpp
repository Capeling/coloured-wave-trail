#include <Geode/Geode.hpp>
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