#ifndef ScoreboardScene_HPP
#define ScoreboardScene_HPP
#include <memory>
#include <string>
#include <vector>

#include "Engine/IScene.hpp"
#include <allegro5/allegro_audio.h>

struct ScoreEntry1 {
    std::string name;
    int score;
    std::string date;
};

class ScoreboardScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    std::vector<ScoreEntry1> entries;
    int page = 1;

public:
    explicit ScoreboardScene() = default;
    void Initialize() override;
    void Terminate() override;
    void BackOnClick(int stage);
    void PrevPageOnClick(int stage);
    void NextPageOnClick(int stage);
};

#endif   // ScoreboardScene_HPP
