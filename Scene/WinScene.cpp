#include <functional>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "PlayScene.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "allegro5/allegro_primitives.h"
#include "allegro5/color.h"
#include "allegro5/keycodes.h"
#include "WinScene.hpp"

void WinScene::Initialize() {
    ticks = 0;
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
    AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 - 10, 255, 255, 255, 255, 0.5, 0.5));
    Engine::ImageButton *btn;
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
    bgmId = AudioHelper::PlayAudio("win.wav");

    name = "";
    score = lives * 100 + money / 100;
    AddNewObject(new Engine::Label("Score: " + std::to_string(score), "pirulen.ttf", 48, halfW + 487.5, halfH / 4 - 10, 10, 255, 10, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Name: ", "pirulen.ttf", 48, halfW + 350, halfH / 4 + 90, 10, 255, 10, 50, 0.5, 0.5));
    nameLabel = new Engine::Label(name, "pirulen.ttf", 48, halfW + 230, halfH / 4 + 90, 10, 255, 10, 255, 0, 0.5);
    AddNewObject(nameLabel);
}
void WinScene::Terminate() {
    IScene::Terminate();
    AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
    ticks += deltaTime;
    if (ticks > 4 && ticks < 100 &&
        dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
        ticks = 100;
        bgmId = AudioHelper::PlayBGM("happy.ogg");
    }

    if (nameLabel) {
        bool showCursor = static_cast<int>(ticks *2) % 2 == 0;
        nameLabel->Text = name + (showCursor?"|":"");
    }
}
void WinScene::BackOnClick(int stage) {
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void WinScene::SetResult(int l,int m) {
    lives = l;
    money = m;
}
void WinScene::SaveScore(const std::string& name, int score) {
    time_t now = time(nullptr);
    tm now_tm;
    localtime_s(&now_tm, &now);
    
    char dateStr[11];
    std::snprintf(dateStr, sizeof(dateStr), "%04d/%02d/%02d", now_tm.tm_year + 1900, now_tm.tm_mon + 1, now_tm.tm_mday);
    std::string date = dateStr;
    
    std::vector<ScoreEntry> entries;
    
    std::ifstream fin("C:/vscode_test/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
    std::string nm;
    int sc;
    std::string dt;
    while (fin >> nm >> sc >> dt) {
        entries.push_back({nm, sc, dt});
    }
    fin.close();

    entries.push_back({name, score, date});
    std::sort(entries.begin(), entries.end(), [](const ScoreEntry& a, ScoreEntry& b) {
        return a.score > b.score;
    });
    
    std::ofstream fout("C:/vscode_test/2025_I2P2_TowerDefense-main/Resource/scoreboard.txt");
    for (auto& e : entries) {
        fout << e.name << " " << e.score << " " << e.date << std::endl;
    }
    fout.close();
}
void WinScene::OnKeyDown(int keyCode) {
    if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) {
        if (name.length() < 10) {
            name += 'A' + (keyCode - ALLEGRO_KEY_A);
        }
    } else if (keyCode == ALLEGRO_KEY_BACKSPACE && !name.empty()) {
        name.pop_back();
    } else if (keyCode == ALLEGRO_KEY_ENTER) {
        SaveScore(name, score);
        Engine::GameEngine::GetInstance().ChangeScene("scoreboard");        
    }
}
void WinScene::Draw() const {
    IScene::Draw();
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    al_draw_rectangle(halfW + 200, halfH / 4 + 50, halfW + 775, halfH / 4 + 130, al_map_rgba(10, 255, 10, 255), 5);
}