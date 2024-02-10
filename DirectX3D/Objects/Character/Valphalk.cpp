#include "Framework.h"

Valphalk::Valphalk() : ModelAnimator("Valphalk")
{
	ReadClip("stun");

	FOR(Index)
	{
		CapsuleCollider* capsuleCollider = new CapsuleCollider();
		capsuleCollider->SetActive(true);
		capsuleCollider->Scale() *= 80.0f;
		colliders.push_back(capsuleCollider);
	}

	//colliders[HEAD]->Scale() = // 머리

	colliders[BODY]->Scale() *= 2.0f; // 몸통
	colliders[BODY]->Rot().x += 4.8f;

	colliders[LWING]->Scale() *= 3.0f; // 왼쪽 날개

	colliders[RWING]->Scale() *= 3.0f; // 오른쪽 날개

	colliders[LLEG1]->Scale() *= 1.3f; // 왼쪽 다리 (앞)

	colliders[LLEG2]->Scale() *= 1.2f;// 왼쪽 다리 (뒤)
	colliders[LLEG2]->Rot().x += 10.0f;

	colliders[RLEG1]->Scale() *= 1.3f; // 오른쪽 다리 (앞)

	colliders[RLEG2]->Scale() *= 1.2f; // 오른쪽 다리 (뒤)
	colliders[RLEG2]->Rot().x += 10.0f;

	colliders[TAIL]->Scale().y *= 3.0f; // 꼬리
	colliders[TAIL]->Rot().x += 4.8f;

}

Valphalk::~Valphalk()
{
	for (CapsuleCollider* capsulCollider : colliders)
	{
		delete capsulCollider;
	}
}

void Valphalk::Update()
{
	for (CapsuleCollider* capsulCollider : colliders)
	{
		capsulCollider->UpdateWorld();;
	}

	colliders[HEAD]->Pos() = GetTranslationByNode(14); // 머리
	colliders[BODY]->Pos() = GetTranslationByNode(4); // 몸통
	colliders[LWING]->Pos() = GetTranslationByNode(84); // 왼쪽 날개
	colliders[RWING]->Pos() = GetTranslationByNode(64); // 오른쪽 날개
	colliders[LLEG1]->Pos() = GetTranslationByNode(40); // 왼쪽 다리 (앞)
	colliders[LLEG2]->Pos() = GetTranslationByNode(112); // 왼쪽 다리 (뒤)
	colliders[RLEG1]->Pos() = GetTranslationByNode(30); // 오른쪽 다리 (앞)
	colliders[RLEG2]->Pos() = GetTranslationByNode(98); // 오른쪽 다리 (뒤)
	colliders[TAIL]->Pos() = GetTranslationByNode(127); // 꼬리

	ModelAnimator::Update();
}

void Valphalk::PreRender()
{

}

void Valphalk::Render()
{
	for (CapsuleCollider* capsulCollider : colliders)
	{
//		capsulCollider->Render();;
	}

	ModelAnimator::Render();
}

void Valphalk::GUIRender()
{
	ModelAnimator::GUIRender();
	for (CapsuleCollider* capsulCollider : colliders)
	{
		capsulCollider->GUIRender();
	}
}

void Valphalk::PostRender()
{
}

void Valphalk::Hit()
{
}

void Valphalk::Spawn(Vector3 pos)
{
}

void Valphalk::SetTarget(Transform* target)
{
}

void Valphalk::SetEvent(int clip, Event event, float timeRatio)
{
}

void Valphalk::ExecuteEvent()
{
}

void Valphalk::SetState(State state)
{
	if (state == curState)
		return;
	curState = state;
}

void Valphalk::SetType(Type type)
{
	if (type == curType)
		return;
	curType = type;
	// 여기는 텍스처 들어갈거 같음
	// 예를 들면 (*여기서 안할수도 있지만)
	if (curType == TypeA)
	{

	}
	if (curType == TypeB)
	{

	}
	if (curType == TypeC)
	{

	}
}

void Valphalk::Move()
{
}

void Valphalk::UpdateUI()
{

}
