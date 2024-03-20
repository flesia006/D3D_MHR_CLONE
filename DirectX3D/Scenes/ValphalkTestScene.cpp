#include "Framework.h"
#include "ValphalkTestScene.h"

ValphalkTestScene::ValphalkTestScene()
{
//	objects = new M41Objects();

	valphalk = new Valphalk();
	valphalk->Pos() = Vector3(4000, 500, 4000);

	garuk = new Sample();
	garuk->Pos() = Vector3(4000, 500, 4000);
	terrain = new TerrainEditor();

	valphalk->SetTarget(garuk);
	valphalk->SetTerrain(terrain);

	garuk->SetEnemy(valphalk);
	garuk->SetTarget(valphalk->GetRealPos());
	garuk->SetTerrain(terrain);

	rasterizer = new RasterizerState();
	rasterizer->CullMode(D3D11_CULL_NONE);


}

ValphalkTestScene::~ValphalkTestScene()
{
	delete valphalk;
}

void ValphalkTestScene::Update()
{
	valphalk->Update();
	garuk->Update();
}

void ValphalkTestScene::PreRender()
{
}

void ValphalkTestScene::Render()
{
	rasterizer->SetState();
//	objects->Render();
	valphalk->Render();
	garuk->Render();
	//	terrain->Render();
}

void ValphalkTestScene::PostRender()
{
	garuk->PostRender();
}

void ValphalkTestScene::GUIRender()
{
	valphalk->GUIRender();
}