#include "Framework.h"
#include "FightTestScene.h"

FightTestScene::FightTestScene()
{
	valphalk = new Valphalk();
	valphalk->Pos().z = -1500.0f;
	garuk = new Sample();

	player = new Player();

	valphalk->SetTarget(player->GetRealPos());
	garuk->SetTarget(player->GetRealPos());
	player->SetGaruk(garuk->GetRealPos());
	player->SetDog(garuk);

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
	garuk->Update();
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
	garuk->Render();
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
