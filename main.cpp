#include "Engine/GameEngine.hpp"
#include "Engine/LOG.hpp"
#include "Scene/Playscene.hpp"
#include "Scene/WinScene.hpp"
#include "Scene/StartScene.h"
#include "Scene/SettingsScene.hpp"

int main(int argc, char **argv) {
	Engine::LOG::SetConfig(true);
	Engine::GameEngine& game = Engine::GameEngine::GetInstance();

	game.AddNewScene("start", new StartScene());
	game.AddNewScene("settings", new SettingsScene());
	game.AddNewScene("play", new PlayScene());
	game.AddNewScene("win", new WinScene());

	game.Start("start", 60, 1600, 832);
	return 0;
}
