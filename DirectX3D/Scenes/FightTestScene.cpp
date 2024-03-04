#include "Framework.h"
#include "FightTestScene.h"

FightTestScene::FightTestScene()
{
	valphalk = new Valphalk();
	valphalk->Pos().z = -1500.0f;

	player = new Player();

	valphalk->SetTarget(player->GetRealPos());


	rasterizer = new RasterizerState();
	rasterizer->CullMode(D3D11_CULL_NONE);

	UIManager::Get();
}

FightTestScene::~FightTestScene()
{
	delete valphalk;
	delete player;
}

void FightTestScene::Update()
{

	valphalk->Update();
	player->Update();
	UIManager::Get()->Update();
}

void FightTestScene::PreRender()
{
}

void FightTestScene::Render()
{
	rasterizer->SetState();
	valphalk->Render();
	player->Render();
}

void FightTestScene::PostRender()
{
	UIManager::Get()->PostRender();
	player->PostRender();
}

void FightTestScene::GUIRender()
{
//	player->GUIRender();
	valphalk->GUIRender();


}
