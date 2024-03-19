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
	player->SetValphalk(valphalk);
	player->SetGaruk(garuk->GetRealPos());
	player->SetDog(garuk);

	rasterizer = new RasterizerState();
	rasterizer->CullMode(D3D11_CULL_NONE);

	garuk->SetEnemy(valphalk);
	UIManager::Get();
}

FightTestScene::~FightTestScene()
{
	delete valphalk;
	delete player;
	delete garuk;
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
	player->PreRender();
}

void FightTestScene::Render()
{
	rasterizer->SetState();
	valphalk->Render();
	garuk->Render();
	player->Render();
	ItemManager::Get()->Render();
}

void FightTestScene::PostRender()
{
	UIManager::Get()->PostRender();
	player->PostRender();
	garuk->PostRender();
}

void FightTestScene::GUIRender()
{
//	player->GUIRender();
	valphalk->GUIRender();


}
