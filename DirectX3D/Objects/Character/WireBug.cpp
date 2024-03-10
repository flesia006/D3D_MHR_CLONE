#include "Framework.h"

WireBug::WireBug()
	: ModelAnimator("WireBug")
{
	ReadClip("IDLE");
	Pos().y += 130; // ¹åÁÙ¹ú·¹ À§Ä¡´Â ¿©±â¼­ Á¶Á¤ÇÏ¸é µÊ
}

WireBug::~WireBug()
{
}

void WireBug::Update()
{
	SetAnimation();
	Respawn();

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
