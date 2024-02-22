#include "Framework.h"
#include "ValphalkTestScene.h"

ValphalkTestScene::ValphalkTestScene()
{
	valphalk = new Valphalk();
	valphalk->Pos().z = -1500.0f;
	
	capsule = new CapsuleCollider(10, 50);
	capsule->Pos().y += 50;
	capsule->UpdateWorld();
	valphalk->SetTarget(capsule);
	//player = new Player();
}

ValphalkTestScene::~ValphalkTestScene()
{
	delete valphalk;
	//delete player;
}

void ValphalkTestScene::Update()
{
	valphalk->Update();

}

void ValphalkTestScene::PreRender()
{
}

void ValphalkTestScene::Render()
{
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
	if (KEY_PRESS('W')) capsule->Pos().z -= 1300 * DELTA;
	if (KEY_PRESS('S')) capsule->Pos().z += 1300 * DELTA;
	if (KEY_PRESS('A')) capsule->Pos().x += 1300 * DELTA;
	if (KEY_PRESS('D')) capsule->Pos().x -= 1300 * DELTA;
	capsule->Update();
}