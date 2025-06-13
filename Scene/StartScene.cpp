#include "StartScene.h"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Playscene.hpp"
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

    
    AddNewObject(new Engine::Image("stage-select/background1.png", 0, 0, w, h));
    AddNewObject(new Engine::Label("you  die  again", "pirulen.ttf", 120, halfW, 120, 209, 150, 102, 255, 0.5, 0.5));

    //level 1 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 30, halfH - 30, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("1", "pirulen.ttf", 60, 65 , halfH + 5, 0, 0, 150, 255, 0.5, 0.5));

    //level 2 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 180, halfH + 30, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("2", "pirulen.ttf", 60, 215 , halfH + 65, 0, 0, 150, 255, 0.5, 0.5));

    //level 3 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 360, halfH - 20, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 3));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("3", "pirulen.ttf", 60, 395 , halfH + 15, 0, 0, 150, 255, 0.5, 0.5));

    //level 4 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW - 270, halfH / 2 + 210, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 4));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("4", "pirulen.ttf", 60, halfW - 235 , halfH / 2 + 245, 0, 0, 150, 255, 0.5, 0.5));

    //level 5 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 430, 545, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 5));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("5", "pirulen.ttf", 60, 465 , 580, 0, 0, 150, 255, 0.5, 0.5));

    //level 6 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 480, 680, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 6));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("6", "pirulen.ttf", 60, 515 , 715, 0, 0, 150, 255, 0.5, 0.5));

    //level 7 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 685, 670, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 7));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("7", "pirulen.ttf", 60, 720 , 705, 0, 0, 150, 255, 0.5, 0.5));

    //level 8 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", 795, 550, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 8));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("8", "pirulen.ttf", 60, 830 , 585, 0, 0, 150, 255, 0.5, 0.5));

    //level 9 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW - 30, halfH / 2 + 200, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 9));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("9", "pirulen.ttf", 60, halfW + 5 , halfH / 2 + 235, 0, 0, 150, 255, 0.5, 0.5));

    //level 10 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 100, halfH / 2 + 150, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 10));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("10", "pirulen.ttf", 55, halfW + 135 , halfH / 2 + 185, 0, 0, 150, 255, 0.5, 0.5));

    //level 11 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 280, halfH / 2 + 250, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 11));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("11", "pirulen.ttf", 55, halfW + 315 , halfH / 2 + 285, 0, 0, 150, 255, 0.5, 0.5));

    //level 12 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 295, halfH / 2 + 390, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 12));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("12", "pirulen.ttf", 55, halfW + 330 , halfH / 2 + 425, 0, 0, 150, 255, 0.5, 0.5));

    //level 13 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 385, halfH / 2 + 495, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 13));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("13", "pirulen.ttf", 55, halfW + 420 , halfH / 2 + 530, 0, 0, 150, 255, 0.5, 0.5));

    //level 14 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", halfW + 605, halfH / 2 + 500, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 14));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("14", "pirulen.ttf", 55, halfW + 640 , halfH / 2 + 535, 0, 0, 150, 255, 0.5, 0.5));

    //level 15 button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/yellow.png", w - 85, halfH + 190, 70, 70);
    btn->SetOnClickCallback(std::bind(&StartScene::PlayOnClick, this, 15));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("15", "pirulen.ttf", 55, w - 50 , halfH + 225, 0, 0, 150, 255, 0.5, 0.5));
    
    //level 16 button
    AddNewObject(new Engine::Image("stage-select/trophy.png", halfW + 550, halfH / 2 + 110, 180, 180));
    

    //settings button
    btn = new Engine::ImageButton("stage-select/setting-button-1.png", "stage-select/setting-button-2.png", 20, h - 70, 50, 50);
    btn->SetOnClickCallback(std::bind(&StartScene::SettingsOnClick, this, 17));
    AddNewControlObject(btn);
    //AddNewObject(new Engine::Label("Settings", "pirulen.ttf", 48, 185, h - 85, 0, 0, 0, 255, 0.5, 0.5));
}
void StartScene::Terminate() {
    IScene::Terminate();
}
void StartScene::PlayOnClick(int stage) {
    PlayScene *scene = dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetScene("play"));
    scene->MapId = stage;
    Engine::GameEngine::GetInstance().ChangeScene("play");
    
}
void StartScene::SettingsOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("settings");
}
