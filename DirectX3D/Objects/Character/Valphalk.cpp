#include "Framework.h"
#include "Scenes/ShadowScene.h"

Valphalk::Valphalk() : ModelAnimator("Valphalk")
{
	ReadClip("stun");
	ReadClip("E_2005");
	// �Ʒ� �ִ°� ù ��ȿ
	ReadClip("E_4013");

	FOR(Valphalk::TAIL+1)
	{
		CapsuleCollider* capsuleCollider = new CapsuleCollider();
		capsuleCollider->SetActive(true);
		capsuleCollider->Scale() *= 80.0f;		
		colliders.push_back(capsuleCollider);
	}

	colliders[HEAD]->part = HEAD;

	colliders[BODY]->Scale() *= 2.0f; // ����
	colliders[BODY]->Rot().x += 4.8f;
	colliders[BODY]->part = BODY;

	colliders[LWING]->Scale() *= 3.0f; // ���� ����
	colliders[LWING]->part = LWING;

	colliders[RWING]->Scale() *= 3.0f; // ������ ����
	colliders[RWING]->part = RWING;

	colliders[LLEG1]->Scale() *= 1.3f; // ���� �ٸ� (��)
	colliders[LLEG1]->part = LLEG1;

	colliders[LLEG2]->Scale() *= 1.2f;// ���� �ٸ� (��)
	colliders[LLEG2]->Rot().x += 10.0f;
	colliders[LLEG2]->part = LLEG2;

	colliders[RLEG1]->Scale() *= 1.3f; // ������ �ٸ� (��)
	colliders[RLEG1]->part = RLEG1;

	colliders[RLEG2]->Scale() *= 1.2f; // ������ �ٸ� (��)
	colliders[RLEG2]->Rot().x += 10.0f;
	colliders[RLEG2]->part = RLEG2;

	colliders[TAIL]->Scale().y *= 3.0f; // ����
	colliders[TAIL]->Rot().x += 4.8f;
	colliders[TAIL]->part = TAIL;

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
		capsulCollider->Update();;
	}

	colliders[HEAD]->Pos() = GetTranslationByNode(14); // �Ӹ�

	colliders[BODY]->Pos() = GetTranslationByNode(4); // ����

	colliders[LWING]->Pos() = GetTranslationByNode(64); // ���� ����

	colliders[RWING]->Pos() = GetTranslationByNode(84); // ������ ����

	colliders[LLEG1]->Pos() = GetTranslationByNode(30); // ���� �ٸ� (��)

	colliders[LLEG2]->Pos() = GetTranslationByNode(98); // ���� �ٸ� (��)

	colliders[RLEG1]->Pos() = GetTranslationByNode(40); // ������ �ٸ� (��)

	colliders[RLEG2]->Pos() = GetTranslationByNode(112); // ������ �ٸ� (��)

	colliders[TAIL]->Pos() = GetTranslationByNode(127); // ����

	ModelAnimator::Update();

	// Test ���� �ڵ�
	//===================================
	if (Count <= 1)
	{
	//	colliders[TARGETDOME]->Pos() = GetTranslationByNode(4); // Ÿ�� ���� ����
		StartRoar();
	}

	// �� ���� Ȯ���ϱ� �� �ڵ�
	if (KEY_DOWN('1'))
	{
		SetState(STUN);
		//PlayClip(0);
	}
	if (KEY_DOWN('2'))
	{
		SetState(E_2005);
		//PlayClip(1);
	}
	if (KEY_DOWN('3'))
	{
		SetState(E_4013);
		//PlayClip(1);
	}

	
	//===================================
}

void Valphalk::PreRender()
{

}

void Valphalk::Render()
{
	//for (CapsuleCollider* capsulCollider : colliders)
	//{
	//	capsulCollider->Render();;
	//}

	if (Count <= 1)
	{
	//	colliders[TARGETDOME]->Render();
	}

	ModelAnimator::Render();
}

void Valphalk::GUIRender()
{
	ModelAnimator::GUIRender();
	//for (CapsuleCollider* capsulCollider : colliders)
	//{
	//	capsulCollider->GUIRender();
	//}

	ImGui::SliderFloat3("ValphalkPos", (float*)&Pos(), 0, 100);
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

void Valphalk::SetEvent(int clip, Event event, float timeRatio)
{
	if (totalEvents[clip].count(timeRatio) > 0)
		return;

	totalEvents[clip][timeRatio] = event;
}

void Valphalk::ExecuteEvent()
{

	int index = curState;

	if (totalEvents[index].empty()) return; 
	if (eventIters[index] == totalEvents[index].end()) return;

	float ratio = motion->runningTime / motion->duration; 

	if (eventIters[index]->first > ratio) return; 

	
	eventIters[index]->second();
	eventIters[index]++;
}

void Valphalk::EndRoar() // ��ȿ ������ ���� ������� ���ƿ�
{
	SetState(STUN);
	Count += 1;

	if (Count <= 1)
	{
		LookatPlayer = false;
	}
}

void Valphalk::StartRoar()
{
	// �÷��̾� �ʿ��ؼ� �ӽ÷� �ҷ���
	Player* player =
		dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetPlayer();
	
	float dirB = 1000.0f;
	float dirA = Distance(Pos(),player->getCollider()->Pos());

	if (dirA < dirB)
	{
		LookatPlayer = true; // �÷��̾ Ÿ������ ��Ե�
		SetState(E_4013);
	}
//	if (!LookatPlayer && Count <= 1)
//	{
//		if (player->getCollider()->IsCapsuleCollision(colliders[TARGETDOME])) // �÷��̾ �����ȿ� ������
//		{
//			LookatPlayer = true; // �÷��̾ Ÿ������ ��Ե�
//			SetState(E_2005);
//			//PlayClip(1);
//		}
//	}
	if (LookatPlayer)
	{
		if (RATIO > 0.98)
		{
			EndRoar();
		}
	}
}

void Valphalk::SetState(State state)
{
	if (state == curState)
		return;
	curState = state;
	PlayClip(state);
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
