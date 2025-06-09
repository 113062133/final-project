#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <vector>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Scene/ScoreboardScene.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"

void ScoreboardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    Engine::ImageButton *btn;

    AddNewObject(new Engine::Label("SCOREBOARD", "pirulen.ttf", 50, halfW, halfH / 3 - 50, 10, 255, 10, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("RANK", "pirulen.ttf", 40, halfW - 600, halfH / 3 + 50, 10, 255, 10, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("NAME", "pirulen.ttf", 40, halfW - 300, halfH / 3 + 50, 10, 255, 10, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("SCORE", "pirulen.ttf", 40, halfW + 100, halfH / 3 + 50, 10, 255, 10, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("DATE", "pirulen.ttf", 40, halfW + 500, halfH / 3 + 50, 10, 255, 10, 255, 0.5, 0.5));

    entries.clear();
    std::ifstream fin("C:/vscode_test/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
    std::string nm;
    int sc;
    std::string dt;
    while (fin >> nm >> sc >> dt) {
        entries.push_back({nm, sc, dt});
    }
    fin.close();

    for (int i = (page - 1) *5; i < page * 5 && i<entries.size(); i++) {
        const auto& e = entries[i];
        int y = halfH / 3 + 100 + 50 * (i - (page - 1) * 5 + 1);
        AddNewObject(new Engine::Label(std::to_string(i + 1), "pirulen.ttf", 40, halfW - 600, y, 10, 255, 10, 150, 0.5, 0.5));
        AddNewObject(new Engine::Label(e.name, "pirulen.ttf", 40, halfW - 300, y, 10, 255, 10, 150, 0.5, 0.5));
        AddNewObject(new Engine::Label(std::to_string(e.score), "pirulen.ttf", 40, halfW + 100, y, 10, 255, 10, 150, 0.5, 0.5));
        AddNewObject(new Engine::Label(e.date, "pirulen.ttf", 40, halfW + 500, y, 10, 255, 10, 150, 0.5, 0.5));
    }

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 700, halfH * 3 / 2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::PrevPageOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48, halfW - 500, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW+ 300, halfH * 3 / 2 + 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextPageOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next Page", "pirulen.ttf", 48, halfW + 500, halfH * 3 / 2 + 100, 0, 0, 0, 255, 0.5, 0.5));

    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
    bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void ScoreboardScene::Terminate() {
    AudioHelper::StopSample(bgmInstance);
    bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
    IScene::Terminate();
}
void ScoreboardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void ScoreboardScene::PrevPageOnClick(int stage) {
    if (page > 1) {
        page--;
        Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
    }
}
void ScoreboardScene::NextPageOnClick(int stage) {
    if (page * 5 < entries.size()) {
        page++;
        Engine::GameEngine::GetInstance().ChangeScene("scoreboard");
    }
}
