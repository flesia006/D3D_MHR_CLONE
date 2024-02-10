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

	//colliders[HEAD]->Scale() = // �Ӹ�

	colliders[BODY]->Scale() *= 2.0f; // ����
	colliders[BODY]->Rot().x += 4.8f;

	colliders[LWING]->Scale() *= 3.0f; // ���� ����

	colliders[RWING]->Scale() *= 3.0f; // ������ ����

	colliders[LLEG1]->Scale() *= 1.3f; // ���� �ٸ� (��)

	colliders[LLEG2]->Scale() *= 1.2f;// ���� �ٸ� (��)
	colliders[LLEG2]->Rot().x += 10.0f;

	colliders[RLEG1]->Scale() *= 1.3f; // ������ �ٸ� (��)

	colliders[RLEG2]->Scale() *= 1.2f; // ������ �ٸ� (��)
	colliders[RLEG2]->Rot().x += 10.0f;

	colliders[TAIL]->Scale().y *= 3.0f; // ����
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

	colliders[HEAD]->Pos() = GetTranslationByNode(14); // �Ӹ�
	colliders[BODY]->Pos() = GetTranslationByNode(4); // ����
	colliders[LWING]->Pos() = GetTranslationByNode(84); // ���� ����
	colliders[RWING]->Pos() = GetTranslationByNode(64); // ������ ����
	colliders[LLEG1]->Pos() = GetTranslationByNode(40); // ���� �ٸ� (��)
	colliders[LLEG2]->Pos() = GetTranslationByNode(112); // ���� �ٸ� (��)
	colliders[RLEG1]->Pos() = GetTranslationByNode(30); // ������ �ٸ� (��)
	colliders[RLEG2]->Pos() = GetTranslationByNode(98); // ������ �ٸ� (��)
	colliders[TAIL]->Pos() = GetTranslationByNode(127); // ����

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
	// ����� �ؽ�ó ���� ����
	// ���� ��� (*���⼭ ���Ҽ��� ������)
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
