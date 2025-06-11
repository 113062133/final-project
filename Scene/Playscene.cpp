#include <algorithm>
#include <allegro5/allegro.h>
#include <cmath>
#include <fstream>
#include <functional>
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include <iostream>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "Scene/Playscene.hpp"
#include "Scene/WinScene.hpp"
#include "Trap/Spike.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "allegro5/keycodes.h"
#include "Door/Door.hpp"
#include "Player/Player.hpp"
#include "allegro5/allegro_primitives.h"

Player* player;
bool PlayScene::DebugMode = false;
const std::vector<Engine::Point> PlayScene::directions = { Engine::Point(-1, 0), Engine::Point(0, -1), Engine::Point(1, 0), Engine::Point(0, 1) };
const int PlayScene::MapWidth = 25, PlayScene::MapHeight = 13;
const int PlayScene::BlockSize = 64;
const Engine::Point PlayScene::SpawnGridPoint = Engine::Point(-1, 0);
const Engine::Point PlayScene::EndGridPoint = Engine::Point(MapWidth, MapHeight - 1);


Engine::Point PlayScene::GetClientSize() {
    return Engine::Point(MapWidth * BlockSize, MapHeight * BlockSize);
}
void PlayScene::Initialize() {
    while(!objects.empty()){
        objects.pop_back();
    }
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    mapState.clear();
    AddNewObject(new Engine::Image("play/background_image.png",0,0,w,h));
    // Add groups from bottom to top.
    AddNewObject(TileMapGroup = new Group());
    AddNewObject(GroundEffectGroup = new Group());
    AddNewObject(DebugIndicatorGroup = new Group());
    AddNewObject(EffectGroup = new Group());
    // Should support buttons.
    AddNewControlObject(UIGroup = new Group());

    ReadMap();
    // Start BGM.
    bgmId = AudioHelper::PlayBGM("play.ogg");
}
void PlayScene::Terminate() {
    AudioHelper::StopBGM(bgmId);
    IScene::Terminate();
}
void PlayScene::Update(float deltaTime) {
    player->Update(deltaTime);

    for (auto& obj : objects) {
        if (obj.type == ObjectType::MOVING_FLOOR && obj.activated) {
            obj.y += obj.fallSpeed * deltaTime;
            if (obj.image) {
                obj.image->Position.y = obj.y;
            }
            // Optional：如果掉出畫面就移除
            if (obj.y > Engine::GameEngine::GetInstance().GetScreenSize().y + 200) {
                // 將 obj.type 改為無效類型以跳過後續判斷
                obj.type = ObjectType::FLOOR; // 不再處理（或設 INVALID）
            }
        }
        else if (obj.type == ObjectType::PUSH_FLOOR && obj.activated) {
            float newX = obj.x + obj.movespeed * deltaTime;
            // 檢查移動距離
            if ((obj.movespeed < 0 && newX > obj.moveuntil) || (obj.movespeed > 0 && newX < obj.moveuntil)) {
                obj.x = newX;
                if (obj.image) {
                    obj.image->Position.x = obj.x;
                }
            } else {
                obj.activated = false; // 停止移動
            }
        }
    }
}
void PlayScene::Draw() const {
    IScene::Draw();
    if (DebugMode) {
        // Draw reverse BFS distance on all reachable blocks.
        for (int i = 0; i < MapHeight; i++) {
            for (int j = 0; j < MapWidth; j++) {
                if (mapDistance[i][j] != -1) {
                    // Not elegant nor efficient, but it's quite enough for debugging.
                    Engine::Label label(std::to_string(mapDistance[i][j]), "pirulen.ttf", 32, (j + 0.5) * BlockSize, (i + 0.5) * BlockSize);
                    label.Anchor = Engine::Point(0.5, 0.5);
                    label.Draw();
                }
            }
        }
    }
}
void PlayScene::OnMouseDown(int button, int mx, int my) {
    IScene::OnMouseDown(button, mx, my);
}
void PlayScene::OnMouseMove(int mx, int my) {
    IScene::OnMouseMove(mx, my);
    
}
void PlayScene::OnMouseUp(int button, int mx, int my) {
    IScene::OnMouseUp(button, mx, my);

}
void PlayScene::OnKeyDown(int keyCode) {
    IScene::OnKeyDown(keyCode);
    if (keyCode == ALLEGRO_KEY_W || keyCode == ALLEGRO_KEY_UP) {
        player->Jump();
    }
    if (MapId != 5) {
        if (keyCode == ALLEGRO_KEY_A || keyCode == ALLEGRO_KEY_LEFT) {
            player->isMovingLeft = true;
        }
        if (keyCode == ALLEGRO_KEY_D || keyCode == ALLEGRO_KEY_RIGHT) {
            player->isMovingRight = true;
        }
    } else {
        if (keyCode == ALLEGRO_KEY_A || keyCode == ALLEGRO_KEY_LEFT) {
            player->isMovingRight = true;
        }
        if (keyCode == ALLEGRO_KEY_D || keyCode == ALLEGRO_KEY_RIGHT) {
            player->isMovingLeft = true;
        }
    }
}
void PlayScene::OnKeyUp(int keyCode) {
    IScene::OnKeyUp(keyCode);
    if (MapId != 5) {
        if (keyCode == ALLEGRO_KEY_A || keyCode == ALLEGRO_KEY_LEFT) {
            player->isMovingLeft = false;
        }
        if (keyCode == ALLEGRO_KEY_D || keyCode == ALLEGRO_KEY_RIGHT) {
            player->isMovingRight = false;
        }
    } else {
        if (keyCode == ALLEGRO_KEY_A || keyCode == ALLEGRO_KEY_LEFT) {
            player->isMovingRight = false;
        }
        if (keyCode == ALLEGRO_KEY_D || keyCode == ALLEGRO_KEY_RIGHT) {
            player->isMovingLeft = false;
        }
    }
}


void PlayScene::ReadMap() {
    std::string filename = std::string("Resource/level") + std::to_string(MapId) + ".txt";
    // Read map file.
    
    std::ifstream fin(filename);
    std::string type;
    float x, y, w, h, movespeed = 0, moveuntil = 0;;
    while (fin >> type >> x >> y >> w >> h) {
        if (type == "F") {
            objects.push_back({x, y, w, h, movespeed, moveuntil, ObjectType::FLOOR, false, 0});
            TileMapGroup->AddNewObject(new Engine::Image("play/floor.png", x, y, w, h));
        } else if (type == "P") {
            player = new Player("play/player.png", x, y, w/2, h);
            AddNewObject(player);
        } else if (type == "D") {
            objects.push_back({x, y, w, h, movespeed, moveuntil, ObjectType::DOOR, false, 0});
            TileMapGroup->AddNewObject(new Engine::Image("play/door.png", x, y, w, h));
        } else if (type == "S") {
            objects.push_back({x, y, w, h, movespeed, moveuntil, ObjectType::SPIKE, false, 0});
            TileMapGroup->AddNewObject(new Engine::Image("play/spike1.png", x, y, w, h));
        } else if (type == "MS") {
            objects.push_back({x, y, w, h, movespeed, moveuntil, ObjectType::SPIKE, false, 0});
            TileMapGroup->AddNewObject(new Engine::Image("play/spike1.png", x, y, w, h));
        } else if (type == "MF") {
            auto* img = new Engine::Image("play/floor.png", x, y, w, h);
            TileMapGroup->AddNewObject(img);
            objects.push_back({x, y, w, h, movespeed,  moveuntil, ObjectType::MOVING_FLOOR, false, 0, img});
        } else if (type == "PF") {
            fin >> movespeed >> moveuntil;
            auto* img = new Engine::Image("play/floor.png", x, y, w, h);
            TileMapGroup->AddNewObject(img);
            objects.push_back({x, y, w, h, movespeed,  moveuntil, ObjectType::PUSH_FLOOR, false, 0, img});
        } else if (type == "SF") {
            auto* img = new Engine::Image("play/floor.png", x, y, w, h);
            TileMapGroup->AddNewObject(img);
            objects.push_back({x, y, w, h, movespeed, moveuntil, ObjectType::SPIKE_FLOOR, false, 0, img});
        } 
        else {
            Engine::LOG(Engine::ERROR) << "Unknown object type: " << type;
        }
    }
    fin.close();

}

void PlayScene::ConstructUI() {
    // Background
    UIGroup->AddNewObject(new Engine::Image("play/sand.png", 1280, 0, 320, 832));
    // Text
    UIGroup->AddNewObject(new Engine::Label(std::string("Stage ") + std::to_string(MapId), "pirulen.ttf", 32, 1294, 0));
}
void PlayScene::UIBtnClicked(int id) {
    
}
