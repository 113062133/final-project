#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <string>
#include "Engine/IScene.hpp"
#include "UI/Component/Label.hpp"
#include <allegro5/allegro_audio.h>

struct ScoreEntry {
    std::string name;
    int score;
    std::string date;
};

class WinScene final : public Engine::IScene {
private:
    float ticks;
    ALLEGRO_SAMPLE_ID bgmId;
    int lives = 0, money = 0;
    int score = 0;
    std::string name;
    Engine::Label* nameLabel;

public:
    explicit WinScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void BackOnClick(int stage);
    void SetResult(int lives,int money);
    void SaveScore(const std::string& name, int score);
    void OnKeyDown(int keyCode) override;
    void Draw() const override;
};

#endif   // WINSCENE_HPP
