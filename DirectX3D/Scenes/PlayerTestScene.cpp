#include "Framework.h"
#include "PlayerTestScene.h"

PlayerTestScene::PlayerTestScene()
{
	valphalk = new DummyValphalk();
	valphalk->Pos().x = -1500.0f;
	valphalk->Pos().z = -1500.0f;

	garuk = new Sample();
	player = new Player();
	player->Pos().x = -100.0f;
	player->Pos().z = -100.0f;
	terrain = new TerrainEditor();
	garuk->SetTarget(player->GetRealPos());
	garuk->SetTerrain(terrain);

	player->SetGaruk(garuk->GetRealPos());
	player->SetValphalk(valphalk);
	player->SetDog(garuk);
	player->SetTerrain(terrain);

	UI;

	wireBug = new WireBug();
	player->SetWireBug(wireBug);

	//CAM->SetTerrain(terrain);
}

PlayerTestScene::~PlayerTestScene()
{
	delete valphalk;
	delete player;
	delete garuk;
	delete wireBug;
}

void PlayerTestScene::Update()
{
	valphalk->Update();
	garuk->Update();
	player->Update();
	wireBug->Update();
	UI->Update();
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
	terrain->Render();
	valphalk->Render();
	player->Render();
	garuk->Render();
	wireBug->Render();	
	ItemManager::Get()->Render();
}

void PlayerTestScene::PostRender()
{
	player->PostRender();
	UI->PostRender();
	wireBug->PostRender();
	garuk->PostRender();
}

void PlayerTestScene::GUIRender()
{
	//valphalk->GUIRender();
	player->GUIRender();
	garuk->GUIRender();
	wireBug->GUIRender();
	CAM->GUIRender();
	ItemManager::Get()->GUIRender();
}
