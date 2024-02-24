#include "Framework.h"
#include "ValphalkTestScene.h"

ValphalkTestScene::ValphalkTestScene()
{
	valphalk = new Valphalk();
	valphalk->Pos().z = -1500.0f;
	
	capsule = new CapsuleCollider(10, 50);
	capsule->Pos().y += 150;
	capsule->UpdateWorld();
	valphalk->SetTarget(capsule);
	
	//player = new Player();

	rasterizer = new RasterizerState();
	rasterizer->CullMode(D3D11_CULL_NONE);

}

ValphalkTestScene::~ValphalkTestScene()
{
	delete valphalk;
	//delete player;
}

void ValphalkTestScene::Update()
{
	valphalk->Update();
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
}

void ValphalkTestScene::PostRender()
{
}

void ValphalkTestScene::GUIRender()
{
	valphalk->GUIRender();
}

void ValphalkTestScene::CapsuleMove()
{
	if (KEY_PRESS('W')) capsule->Pos().z += 1300 * DELTA;
	if (KEY_PRESS('S')) capsule->Pos().z -= 1300 * DELTA;
	if (KEY_PRESS('A')) capsule->Pos().x -= 1300 * DELTA;
	if (KEY_PRESS('D')) capsule->Pos().x += 1300 * DELTA;

	if (KEY_DOWN(VK_F5)) CAM->SetTarget(capsule);
	if (KEY_DOWN(VK_F6)) CAM->SetTarget(nullptr);


	capsule->Update();
}