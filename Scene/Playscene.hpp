#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#pragma once
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>
#include<string>

#include "Player/Player.hpp"
#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Door/Door.hpp"
#include "Scene/FallingBackground.hpp"

struct Floor {
    float x, y, w, h;
};

class FallingBackground;


class PlayScene final : public Engine::IScene {
private:
    ALLEGRO_SAMPLE_ID bgmId;
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;


public:
    //死亡音效
    bool isalive = true;
    bool iswin = false;
    float  _deathStartTime = 0.0f;
    
    void Death();
    
    enum TileType {
        TILE_DIRT,
        TILE_FLOOR,
        TILE_OCCUPIED,
        TILE_PLAYER,
        TILE_DOOR
    };

    enum class ObjectType { FLOOR, DOOR, SPIKE, BOUNCE, FALL_FLOOR , SPIKE_FLOOR, PUSH_FLOOR, MOVE_FLOOR ,BALL, FAKE_DOOR, FAKE_WALL, REVERSE_SPIKE, MOVE_SPIKE, PORTAL};
    struct Object {
        float x, y, w, h;
        float speedx = 0;
        float speedy = 0;
        float movefrom = 0;
        float moveuntil = 0;
        ObjectType type;
        bool activated = false;
        Engine::Image* image = nullptr; // ⬅ 新增：該物件對應的圖片
    };
    std::vector<Object> objects; 

    // 透明方塊結構
    struct TriggerBlock {
        float x, y, w, h; // 觸發區域
        ObjectType type;
        Object* target;   // 目標物件指標
    };
    std::vector<TriggerBlock> triggerBlocks;

    
    ObjectType StringToObjectType(const std::string& type) {
        if (type == "F") return ObjectType::FLOOR;
        if (type == "D") return ObjectType::DOOR;
        if (type == "S") return ObjectType::SPIKE;
        if (type == "RS") return ObjectType::REVERSE_SPIKE;
        if (type == "MS") return ObjectType::MOVE_SPIKE;
        if (type == "B") return ObjectType::BOUNCE;
        if (type == "FF") return ObjectType::FALL_FLOOR;
        if (type == "PF") return ObjectType::PUSH_FLOOR;
        if (type == "MF") return ObjectType::MOVE_FLOOR;
        if (type == "SF") return ObjectType::SPIKE_FLOOR;
        if (type == "FD") return ObjectType::FAKE_DOOR;
        if (type == "FW") return ObjectType::FAKE_WALL;
        if (type == "POR") return ObjectType::PORTAL;
        if (type == "BAL") return ObjectType::BALL;
        return ObjectType::FLOOR; // 預設值
    }

    static bool DebugMode;
    static const std::vector<Engine::Point> directions;
    static const int MapWidth, MapHeight;
    static const int BlockSize;
    static const float DangerTime;
    static const Engine::Point SpawnGridPoint;
    static const Engine::Point EndGridPoint;
    static const std::vector<int> code;
    int MapId;
    // Map tiles.
    Group *TileMapGroup;
    Group *GroundEffectGroup;
    Group *DebugIndicatorGroup;
    Group *EffectGroup;
    Group *UIGroup;
    
    Door *door;
    std::vector<std::vector<TileType>> mapState;
    std::vector<std::vector<int>> mapDistance;
    std::list<std::pair<int, float>> enemyWaveData;
    std::list<int> keyStrokes;
    static Engine::Point GetClientSize();
    explicit PlayScene() = default;
    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;
    void Draw() const override;
    void OnMouseDown(int button, int mx, int my) override;
    void OnMouseMove(int mx, int my) override;
    void OnMouseUp(int button, int mx, int my) override;
    void OnKeyDown(int keyCode) override;
    void OnKeyUp(int keyCode) override;
    void ReadMap();
    void ReadEnemyWave();
    void BackOnClick();
    void RestartOnClick();
    void ConstructUI();
    void UIBtnClicked(int id);
    
    
    Engine::Image* fallingBG = nullptr;
    float fallingBGSpeed = 900.0f;
    float fallingBGDelayTimer = -1.0f; // -1 表示還沒開始延遲
    int flag = 0;

};


#endif   // PLAYSCENE_HPP
