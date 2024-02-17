#include "Framework.h"
#include "Scenes/ShadowScene.h"

Valphalk::Valphalk() : ModelAnimator("Valphalk")
{
	ReadClip("stun");
	ReadClip("E_2005");
	// 아래 있는게 첫 포효
	ReadClip("E_4013");

	FOR(Valphalk::TAIL+1)
	{
		CapsuleCollider* capsuleCollider = new CapsuleCollider();
		capsuleCollider->SetActive(true);
		capsuleCollider->Scale() *= 80.0f;		
		colliders.push_back(capsuleCollider);
	}

	colliders[HEAD]->part = HEAD;

	colliders[BODY]->Scale() *= 2.0f; // 몸통
	colliders[BODY]->Rot().x += 4.8f;
	colliders[BODY]->part = BODY;

	colliders[LWING]->Scale() *= 3.0f; // 왼쪽 날개
	colliders[LWING]->part = LWING;

	colliders[RWING]->Scale() *= 3.0f; // 오른쪽 날개
	colliders[RWING]->part = RWING;

	colliders[LLEG1]->Scale() *= 1.3f; // 왼쪽 다리 (앞)
	colliders[LLEG1]->part = LLEG1;

	colliders[LLEG2]->Scale() *= 1.2f;// 왼쪽 다리 (뒤)
	colliders[LLEG2]->Rot().x += 10.0f;
	colliders[LLEG2]->part = LLEG2;

	colliders[RLEG1]->Scale() *= 1.3f; // 오른쪽 다리 (앞)
	colliders[RLEG1]->part = RLEG1;

	colliders[RLEG2]->Scale() *= 1.2f; // 오른쪽 다리 (뒤)
	colliders[RLEG2]->Rot().x += 10.0f;
	colliders[RLEG2]->part = RLEG2;

	colliders[TAIL]->Scale().y *= 3.0f; // 꼬리
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

	colliders[HEAD]->Pos() = GetTranslationByNode(14); // 머리

	colliders[BODY]->Pos() = GetTranslationByNode(4); // 몸통

	colliders[LWING]->Pos() = GetTranslationByNode(64); // 왼쪽 날개

	colliders[RWING]->Pos() = GetTranslationByNode(84); // 오른쪽 날개

	colliders[LLEG1]->Pos() = GetTranslationByNode(30); // 왼쪽 다리 (앞)

	colliders[LLEG2]->Pos() = GetTranslationByNode(98); // 왼쪽 다리 (뒤)

	colliders[RLEG1]->Pos() = GetTranslationByNode(40); // 오른쪽 다리 (앞)

	colliders[RLEG2]->Pos() = GetTranslationByNode(112); // 오른쪽 다리 (뒤)

	colliders[TAIL]->Pos() = GetTranslationByNode(127); // 꼬리

	ModelAnimator::Update();

	// Test 샘플 코드
	//===================================
	if (Count <= 1)
	{
	//	colliders[TARGETDOME]->Pos() = GetTranslationByNode(4); // 타겟 보는 범위
		StartRoar();
	}

	// 잘 들어갔나 확인하기 용 코드
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

void Valphalk::EndRoar() // 포효 끝나고 원래 모션으로 돌아옴
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
	// 플레이어 필요해서 임시로 불러옴
	Player* player =
		dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetPlayer();
	
	float dirB = 1000.0f;
	float dirA = Distance(Pos(),player->getCollider()->Pos());

	if (dirA < dirB)
	{
		LookatPlayer = true; // 플레이어를 타겟으로 잡게됨
		SetState(E_4013);
	}
//	if (!LookatPlayer && Count <= 1)
//	{
//		if (player->getCollider()->IsCapsuleCollision(colliders[TARGETDOME])) // 플레이어가 영역안에 들어오면
//		{
//			LookatPlayer = true; // 플레이어를 타겟으로 잡게됨
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
