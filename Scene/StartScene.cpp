#include "StartScene.h"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "PlayScene.hpp"
#include "Scene/StartScene.h"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"

void StartScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton *btn;

    AddNewObject(new Engine::Image("stage-select/background.png", 0, 0, w, h));

    //level 1 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 30, halfH - 30, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level 2 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 180, halfH + 30, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);

    //level 3 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 360, halfH - 20, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 3));
    AddNewControlObject(btn);

    //level 4 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW - 270, halfH / 2 + 210, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 4));
    AddNewControlObject(btn);

    //level 5 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 430, 545, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 5));
    AddNewControlObject(btn);

    //level 6 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 480, 680, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 6));
    AddNewControlObject(btn);

    //level 7 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 685, 670, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 7));
    AddNewControlObject(btn);

    //level 8 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 795, 550, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 8));
    AddNewControlObject(btn);

    //level 9 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW - 30, halfH / 2 + 200, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 9));
    AddNewControlObject(btn);

    //level 10 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 100, halfH / 2 + 150, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 10));
    AddNewControlObject(btn);

    //level 11 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 280, halfH / 2 + 250, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 11));
    AddNewControlObject(btn);

    //level 12 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 295, halfH / 2 + 390, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 12));
    AddNewControlObject(btn);

    //level 13 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 385, halfH / 2 + 495, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 13));
    AddNewControlObject(btn);

    //level 14 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 605, halfH / 2 + 500, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 14));
    AddNewControlObject(btn);

    //level 15 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", w - 85, halfH + 190, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 15));
    AddNewControlObject(btn);
    
    //boss level button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 600, halfH / 2 + 170, 110, 110);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 16));
    AddNewControlObject(btn);

    //settings button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 10, h - 150, 350, 130);
    btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 17));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "pirulen.ttf", 48, 185, h - 85, 0, 0, 0, 255, 0.5, 0.5));
}
void StartScene::Terminate() {
    IScene::Terminate();
}
void StartScene::PlayOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("play");
}
void StartScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}
