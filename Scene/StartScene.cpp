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
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 30, halfH - 30, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 2
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 180, halfH + 30, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 3
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 360, halfH - 20, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 4
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 270, halfH / 2 + 210, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 5
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 430, 545, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 6
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 480, 680, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 7
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 685, 670, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 8
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 795, 550, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 9
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 30, halfH / 2 + 200, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 10
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 100, halfH / 2 + 150, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 11
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 280, halfH / 2 + 250, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 12
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 295, halfH / 2 + 390, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 13
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 385, halfH / 2 + 495, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level button 14
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 605, halfH / 2 + 500, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //level 15 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", w - 85, halfH + 190, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    
    //boss level button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 600, halfH / 2 + 170, 110, 110);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);

    //setting button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", 10, h - 150, 350, 130);
    btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Settings", "pirulen.ttf", 48, 185, h - 85, 0, 0, 0, 255, 0.5, 0.5));
}
void StartScene::Terminate() {
    IScene::Terminate();
}
void StartScene::PlayOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
void StartScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}
