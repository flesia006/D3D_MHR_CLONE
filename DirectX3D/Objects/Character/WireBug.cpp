#include "Framework.h"

WireBug::WireBug()
	: ModelAnimator("WireBug")
{
	ReadClip("IDLE");
	Pos().y += 130; // ¹åÁÙ¹ú·¹ À§Ä¡´Â ¿©±â¼­ Á¶Á¤ÇÏ¸é µÊ
	UpdateWorld();

	wireBugPickUpUI = new Quad(L"Textures/UI/WireBugPickUpUI.png");
	wireBugPickUpUI->Scale() *= 1.5f;
}

WireBug::~WireBug()
{
	delete wireBugPickUpUI;
}

void WireBug::Update()
{
	SetAnimation();
	Respawn();
	UpdateUI();

	ModelAnimator::Update();
}

void WireBug::Render()
{
	if(Active())
		ModelAnimator::Render();
}

void WireBug::GUIRender()
{
	Model::GUIRender();
}

void WireBug::PostRender()
{
	if (isWireBugPickUpUIActive)
		wireBugPickUpUI->Render();
}

void WireBug::Respawn()
{
	if (!Active())
		respawnDuration += DELTA;

	if (respawnDuration > respawnDurationLimit)
	{
		SetActive(true);
		respawnDuration = 0.0f;
	}
}

void WireBug::SetAnimation()
{
	SetState(IDLE);
}

void WireBug::SetState(State state)
{
	if (state == curState) return;

	curState = state;
	PlayClip(state);
}

void WireBug::UpdateUI()
{
	UIPos = Pos() + Vector3::Up() * 60;

	if (!CAM->ContainPoint(UIPos))
	{
		SetWireBugPickUpUIActive(false);
		return;
	}

	wireBugPickUpUI->Pos() = CAM->WorldToScreen(UIPos);
	
	wireBugPickUpUI->UpdateWorld();
}
