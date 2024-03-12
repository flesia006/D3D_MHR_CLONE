#include "Framework.h"

PlayerWireBug::PlayerWireBug()
	:ModelAnimator("WireBug")
{
	ReadClip("IDLE");
	ReadClip("FLY");
	moveVec = {};
}

PlayerWireBug::~PlayerWireBug()
{
}

void PlayerWireBug::Update()
{
	SetAnimation();
	Move();

	ModelAnimator::Update();
}

void PlayerWireBug::Render()
{
	if (Active())
		ModelAnimator::Render();
}

void PlayerWireBug::GUIRender()
{
	Model::GUIRender();
}

void PlayerWireBug::PostRender()
{
}

void PlayerWireBug::SetMove(Vector3 startPos, bool isMoving, Vector3 moveVec)
{
	Pos() = startPos;
	this->isMoving = isMoving;
	this->moveVec = moveVec;
}

void PlayerWireBug::SetAnimation()
{
	if (moveVec != Vector3::Zero())
		SetState(IDLE);
	else
		SetState(FLY);
}

void PlayerWireBug::SetState(State state)
{
	if (state == curState) return;

	curState = state;
	PlayClip(state);
}

void PlayerWireBug::Move()
{
	if (!isMoving)
		return;

	Pos() += moveVec * DELTA;
}
