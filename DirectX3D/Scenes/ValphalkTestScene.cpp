#include "Framework.h"
#include "ValphalkTestScene.h"

ValphalkTestScene::ValphalkTestScene()
{
	valphalk = new Valphalk();
	valphalk->Pos().z = -1500.0f;
	garuk = new Sample();


	capsule = new CapsuleCollider(10, 50);
	capsule->Pos().y += 150;
	valphalk->SetTarget(garuk);
	garuk->SetEnemy(valphalk);
	garuk->SetTarget(capsule);

	rasterizer = new RasterizerState();
	rasterizer->CullMode(D3D11_CULL_NONE);

	UIManager::Get();

}

ValphalkTestScene::~ValphalkTestScene()
{
	delete valphalk;
	delete capsule;
}

void ValphalkTestScene::Update()
{
	capsule->UpdateWorld();
	valphalk->Update();
	garuk->Update();
	UIManager::Get()->Update();
	ARROW->Update();
	CapsuleMove();
}

void ValphalkTestScene::PreRender()
{
}

void ValphalkTestScene::Render()
{
	rasterizer->SetState();
	valphalk->Render();
	capsule->Render();
	garuk->Render();
	ARROW->Render();
}

void ValphalkTestScene::PostRender()
{
	UIManager::Get()->PostRender();
	ARROW->PostRender();
}

void ValphalkTestScene::GUIRender()
{
	valphalk->GUIRender();
}

void ValphalkTestScene::CapsuleMove()
{
	if (KEY_PRESS('W')) capsule->Pos().z -= 1300 * DELTA;
	if (KEY_PRESS('S')) capsule->Pos().z += 1300 * DELTA;
	if (KEY_PRESS('A')) capsule->Pos().x += 1300 * DELTA;
	if (KEY_PRESS('D')) capsule->Pos().x -= 1300 * DELTA;

	if (KEY_DOWN(VK_F5)) CAM->SetTarget(capsule);
	if (KEY_DOWN(VK_F6)) CAM->SetTarget(nullptr);

	if (KEY_PRESS('Z')) valphalk->curHP -= 1000;


	capsule->Update();
}