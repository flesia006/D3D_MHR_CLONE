#include "Framework.h"
#include "PlayerTestScene.h"

PlayerTestScene::PlayerTestScene()
{
	valphalk = new DummyValphalk();
	valphalk->Pos().z = -1500.0f;

	garuk = new Sample();
	player = new Player();
	terrain = new TerrainEditor();
	garuk->SetTarget(player->GetRealPos());
	garuk->SetEnemy(player->GetRealPos());
	garuk->SetTerrain(terrain);

	player->SetGaruk(garuk->GetRealPos());
	player->SetDog(garuk);
	player->SetTerrain(terrain);
	UI;
	ARROW;

}

PlayerTestScene::~PlayerTestScene()
{
	delete valphalk;
	delete player;
	delete garuk;
	ARROW->Delete();
}

void PlayerTestScene::Update()
{
	valphalk->Update();
	garuk->Update();
	player->Update();
	UI->Update();
	ARROW->Update();
	//	Vector3 playerPos;
	//	Vector3 garuk1Pos;
	//	Vector3 garuk2Pos;
	//
	//
	//	terrain->MultiComputePicking(
	//		playerPos, player->GetRealPos()->Pos() + Vector3::Up() * 400,
	//		garuk1Pos, garuk->GetRealPos()->Pos() + Vector3::Up() * 400,
	//		garuk2Pos, garuk2->GetRealPos()->Pos() + Vector3::Up() * 400);
	//
	//	player->Pos().y = playerPos.y;
	//	garuk->Pos().y = garuk1Pos.y;
	//	garuk2->Pos().y = garuk2Pos.y;

}

void PlayerTestScene::PreRender()
{
	player->PreRender();
}

void PlayerTestScene::Render()
{
	valphalk->Render();
	player->Render();
	garuk->Render();
	terrain->Render();
	ARROW->Render();
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
	garuk->GUIRender();
}
