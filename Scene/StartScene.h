#ifndef StartScene_H
#define StartScene_H

#include <allegro5/allegro_audio.h>
#include <memory>

#include "Engine/IScene.hpp"
class StartScene final : public Engine::IScene {
public:
    explicit StartScene() = default;
    void Initialize() override;
    void Terminate() override;
    void PlayOnClick(int stage);
    void SettingsOnClick(int stage);
};
#endif   // STARTSCENE_H
