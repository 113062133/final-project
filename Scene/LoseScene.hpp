#ifndef LOSESCENE_HPP
#define LOSESCENE_HPP
#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>
#include <memory>

class LoseScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

public:
    explicit LoseScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
};

#endif   // LOSESCENE_HPP
