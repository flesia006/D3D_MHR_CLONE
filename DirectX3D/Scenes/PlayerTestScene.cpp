#include "Framework.h"
#include "PlayerTestScene.h"

PlayerTestScene::PlayerTestScene()
{
	valphalk = new DummyValphalk();
	valphalk->Pos().z = -1500.0f;

	player = new Player();
	UI;

	wireBug = new WireBug();
	player->SetWireBug(wireBug);
}

PlayerTestScene::~PlayerTestScene()
{
	delete valphalk;
	delete player;
	delete wireBug;
}

void PlayerTestScene::Update()
{
	valphalk->Update();
	player->Update();
	wireBug->Update();
	UI->Update();
}

void PlayerTestScene::PreRender()
{
}

void PlayerTestScene::Render()
{
	valphalk->Render();
	player->Render();
	wireBug->Render();
}

void PlayerTestScene::PostRender()
{
	player->PostRender();
	UI->PostRender();
}

void PlayerTestScene::GUIRender()
{
	//valphalk->GUIRender();
	//player->GUIRender();
	wireBug->GUIRender();
}
