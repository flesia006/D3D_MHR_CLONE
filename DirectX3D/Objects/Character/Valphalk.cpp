#include "Framework.h"
#include "Scenes/ShadowScene.h"

Valphalk::Valphalk() : ModelAnimator("Valphalk")
{
	ReadClip("stun");
	ReadClip("E_2005");
	// 아래 있는게 첫 포효
	ReadClip("E_4013");
	// 플레이어 발견 전
	ReadClip("E_0043");
	ReadClip("E_0044");
	ReadClip("E_0045");
	// 플레이어 발견 후
	ReadClip("E_0097");
	ReadClip("E_0098");
	ReadClip("E_0099");

	FOR(TAIL + 1)
	{
		Transform* transForm = new Transform();
		//transForm->SetActive(true);
		transforms.push_back(transForm);
		CapsuleCollider* capsuleCollider = new CapsuleCollider();
		capsuleCollider->SetActive(true);
		colliders.push_back(capsuleCollider);
	}

	// 큐브로 한 방법
	{
		//FOR(RWING + 1)
		//{
		//	Transform* transForm = new Transform();
		//	//transForm->SetActive(true);
		//	Wingtransforms.push_back(transForm);
		//	BoxCollider* boxCollider = new BoxCollider();
		//	boxCollider->SetActive(true);
		//	boxCollider->Scale() *= 100.0f;
		//	wings.push_back(boxCollider);
		//}
	}

	// 머리 부분
 	{
		colliders[HEAD]->SetParent(transforms[HEAD]);
		colliders[HEAD]->Scale().x = 90.0f;
		colliders[HEAD]->Scale().y = 70.0f;
		colliders[HEAD]->Scale().z = 100.0f;
		colliders[HEAD]->Rot().x = 1.73f;
		colliders[HEAD]->part = HEAD;
		colliders[HEAD]->SetTag("HEAD");
	}

	// 목 부분
	{
		colliders[NECK]->SetParent(transforms[NECK]);
		colliders[NECK]->Scale().x = 80.0f;
		colliders[NECK]->Scale().y = 60.0f;
		colliders[NECK]->Scale().z = 80.0f;
		colliders[NECK]->Rot().x = 1.80f;
		colliders[NECK]->SetTag("NECK");
	}

	// 가슴 부분
	{ 
		colliders[CHEST]->SetParent(transforms[CHEST]);
		colliders[CHEST]->Scale().x = 150.0f;
		colliders[CHEST]->Scale().y = 110.0f;
		colliders[CHEST]->Scale().z = 150.0f;
		colliders[CHEST]->Rot().x = 0.02;
		colliders[CHEST]->SetTag("CHEST");
	}

	// 몸 부분
	{
		colliders[BODY]->SetParent(transforms[BODY]);
		colliders[BODY]->Scale().x = 130.0f;
		colliders[BODY]->Scale().y = 120.0f;
		colliders[BODY]->Scale().z = 120.0f;
		colliders[BODY]->Rot().x = 1.65f;
		colliders[BODY]->part = BODY;
		colliders[BODY]->SetTag("BODY");
	}

	// 왼쪽 날개
	{
		//wings[LWING1]->SetParent(Wingtransforms[LWING1]);
		//wings[LWING1]->Scale() *= 60;
		//wings[LWING1]->SetTag("LWING");
		colliders[LWING]->SetParent(transforms[LWING]);
		colliders[LWING]->Scale() *= 250.0f;
		colliders[LWING]->Rot().z = -1.6f;
		colliders[LWING]->Pos().x = 300.0f;
		colliders[LWING]->part = LWING;
		colliders[LWING]->SetTag("LWING");
	}

	// 왼쪽 날개 연결 부분
	{
		colliders[LWING_RADIUS]->SetParent(transforms[LWING_RADIUS]);
		colliders[LWING_RADIUS]->Scale().x = 80.0f;
		colliders[LWING_RADIUS]->Scale().y = 70.0f;
		colliders[LWING_RADIUS]->Scale().z = 80.0f;
		colliders[LWING_RADIUS]->Rot().x = 1.22f;
		colliders[LWING_RADIUS]->SetTag("LWING_RADIUS");
	}

	// 오른쪽 날개
	{
		//wings[RWING1]->SetParent(Wingtransforms[RWING1]);
		//wings[RWING1]->Scale() *= 60;
		//wings[RWING1]->SetTag("RWING");
		colliders[RWING]->SetParent(transforms[RWING]);
		colliders[RWING]->Scale() *= 250.0f;
		colliders[RWING]->Rot().z = 1.62f;
		colliders[RWING]->Pos().x = -300.0f;
		colliders[RWING]->part = RWING;
		colliders[RWING]->SetTag("RWING");
	}

	// 오른쪽 날개 연결 부분
	{
		colliders[RWING_RADIUS]->SetParent(transforms[RWING_RADIUS]);
		colliders[RWING_RADIUS]->Scale().x = 80.0f;
		colliders[RWING_RADIUS]->Scale().y = 70.0f;
		colliders[RWING_RADIUS]->Scale().z = 80.0f;
		colliders[RWING_RADIUS]->Rot().x = 1.22f;
		colliders[RWING_RADIUS]->SetTag("RWING_RADIUS");
	}

	// 왼쪽 다리 (앞)
	{
		colliders[LLEG1]->SetParent(transforms[LLEG1]);
		colliders[LLEG1]->Scale().x = 70.0f;
		colliders[LLEG1]->Scale().y = 60.0f;
		colliders[LLEG1]->Scale().z = 70.0f;
		//colliders[LLEG1]->Rot().x = -29.0f;
		//colliders[LLEG1]->Rot().y = 161.995f;
		//colliders[LLEG1]->Rot().z = -177.0f;
		colliders[LLEG1]->part = LLEG1;
		colliders[LLEG1]->SetTag("LLEG1");
	}
	
	// 왼쪽 발바닥 (앞)
	{
		colliders[LLEG1_FOOT]->SetParent(transforms[LLEG1_FOOT]);
		colliders[LLEG1_FOOT]->Scale().x = 80.0f;
		colliders[LLEG1_FOOT]->Scale().y = 90.0f;
		colliders[LLEG1_FOOT]->Scale().z = 100.0f;
		colliders[LLEG1_FOOT]->Rot().x = 2.55f;
		colliders[LLEG1_FOOT]->SetTag("LLEG1_FOOT");
	}

	// 왼쪽 다리 (뒤)
	{
		colliders[LLEG2]->SetParent(transforms[LLEG2]);
		colliders[LLEG2]->Scale().x = 70.0f;
		colliders[LLEG2]->Scale().y = 60.0f;
		colliders[LLEG2]->Scale().z = 70.0f;
		//colliders[LLEG2]->Rot().x = 0.64f;
		colliders[LLEG2]->part = LLEG2;
		colliders[LLEG2]->SetTag("LLEG2");
	}

	// 왼쪽 다리 발바닥 (뒤)
	{
		colliders[LLEG2_FOOT]->SetParent(transforms[LLEG2_FOOT]);
		colliders[LLEG2_FOOT]->Scale().x = 70.0f;
		colliders[LLEG2_FOOT]->Scale().y = 60.0f;
		colliders[LLEG2_FOOT]->Scale().z = 70.0f;
		colliders[LLEG2_FOOT]->Rot().x = -0.74f;
		colliders[LLEG2_FOOT]->SetTag("LLEG2_FOOT");
	}

	// 오른쪽 다리 (앞)
	{
		colliders[RLEG1]->SetParent(transforms[RLEG1]);
		colliders[RLEG1]->Scale().x = 70.0f;
		colliders[RLEG1]->Scale().y = 60.0f;
		colliders[RLEG1]->Scale().z = 70.0f;
		//colliders[RLEG1]->Rot().x = -43.0f;
		//colliders[RLEG1]->Rot().y = 22.0f;
		colliders[RLEG1]->part = RLEG1;
		colliders[RLEG1]->SetTag("RLEG1");
	}
	
	// 오른쪽 다리 발바닥(앞)
	{
		colliders[RLEG1_FOOT]->SetParent(transforms[RLEG1_FOOT]);
		colliders[RLEG1_FOOT]->Scale().x = 80.0f;
		colliders[RLEG1_FOOT]->Scale().y = 90.0f;
		colliders[RLEG1_FOOT]->Scale().z = 100.0f;
		colliders[RLEG1_FOOT]->Rot().x = -0.45f;
		//colliders[RLEG1_FOOT]->Rot().y = 22.0f;
		colliders[RLEG1_FOOT]->SetTag("RLEG1_FOOT");
	}

	// 오른쪽 다리 (뒤)
	{
		colliders[RLEG2]->SetParent(transforms[RLEG2]);
		colliders[RLEG2]->Scale().x = 70.0f;
		colliders[RLEG2]->Scale().y = 60.0f;
		colliders[RLEG2]->Scale().z = 70.0f;
		//colliders[RLEG2]->Rot().x = 50.0f;
		colliders[RLEG2]->SetTag("RLEG2");
	}

	// 오른쪽 발바닥 (뒤)
	{
		colliders[RLEG2_FOOT]->SetParent(transforms[RLEG2_FOOT]);
		colliders[RLEG2_FOOT]->Scale().x = 70.0f;
		colliders[RLEG2_FOOT]->Scale().y = 60.0f;
		colliders[RLEG2_FOOT]->Scale().z = 70.0f;
		colliders[RLEG2_FOOT]->Rot().x = -0.74f;
		colliders[RLEG2_FOOT]->SetTag("RLEG2_FOOT");
	}

	// 꼬리 시작
	{
		colliders[TAIL_START]->SetParent(transforms[TAIL_START]);
		colliders[TAIL_START]->Scale().x = 120.0f;
		colliders[TAIL_START]->Scale().y = 100.0f;
		colliders[TAIL_START]->Scale().z = 120.0f;
		colliders[TAIL_START]->Rot().x = 1.78f;
		colliders[TAIL_START]->SetTag("TAIL_START");
	}

	// 꼬리 1/4 부분
	{
		colliders[TAIL_1]->SetParent(transforms[TAIL_1]);
		colliders[TAIL_1]->Scale() *= 80.0f;
		colliders[TAIL_1]->Rot().x = 1.55f;
		colliders[TAIL_1]->SetTag("TAIL_1");
	}

	// 꼬리 1/2 부분
	{
		colliders[TAIL_2]->SetParent(transforms[TAIL_2]);
		colliders[TAIL_2]->Scale().x = 50.0f;
		colliders[TAIL_2]->Scale().y = 60.0f;
		colliders[TAIL_2]->Scale().z = 50.0f;
		colliders[TAIL_2]->Rot().x += 1.6f;
		colliders[TAIL_2]->SetTag("TAIL_2");
	}

	// 꼬리 끝 부분
	{
		colliders[TAIL]->SetParent(transforms[TAIL]);
		colliders[TAIL]->Scale() *= 80.0f; // 꼬리
		colliders[TAIL]->Rot().x += 4.8f;
		colliders[TAIL]->part = TAIL;
		colliders[TAIL]->SetTag("TAIL");
	}


	//SetState(curState);
	//PlayClip(3);
}

Valphalk::~Valphalk()
{
	for (CapsuleCollider* capsulCollider : colliders)
	{
		delete capsulCollider;
	}
	for (Transform* transform : transforms)
	{
		delete transform;
	}
	
}

void Valphalk::Update()
{
	Move();

	for (CapsuleCollider* capsulCollider : colliders)
	{
		capsulCollider->Update();;
	}

	for (BoxCollider* boxCollider : wings )
	{
		boxCollider->UpdateWorld();
	}

	ColliderNodePos();

	ModelAnimator::Update();

	// Test 샘플 코드
	//===================================
	//if (Count <= 0)
	//{
	////	colliders[TARGETDOME]->Pos() = GetTranslationByNode(4); // 타겟 보는 범위
	//	StartRoar();
	//}
	//
	//// 잘 들어갔나 확인하기 용 코드
	if (KEY_DOWN('1'))
	{
		SetState(STUN);
	//	//PlayClip(0);
	}
	//if (KEY_DOWN('2'))
	//{
	//	SetState(E_2005);
	//	//PlayClip(1);
	//}
	if (KEY_DOWN('2'))
	{
		SetState(E_4013);
		//PlayClip(1);
	}
	if (KEY_DOWN('3'))
	{
		SetState(E_0043);
	}
	if (KEY_DOWN('4'))
	{
		SetState(E_0044);
	}

	switch (curState)
	{
	case STUN:
		break;
	case E_2005:
		break;
	case E_4013:		
		break;
	}
	//===================================
	if (curState == E_4013)
	{
		if (RATIO > 0.2 && RATIO < 0.28)
			Sounds::Get()->Play("em086_05_vo_media_10", 0.5f);
		if(RATIO>0.98)
		SetState(STUN);
	}
}

void Valphalk::PreRender()
{

}

void Valphalk::Render()
{
	for (CapsuleCollider* capsulCollider : colliders)
	{
		capsulCollider->Render();
	}

	for (BoxCollider* boxCollider : wings )
	{
		boxCollider->Render();
	}

	ModelAnimator::Render();
}

void Valphalk::GUIRender()
{
	//ModelAnimator::GUIRender();
	ImGui::SliderFloat3("ValphalkPos", (float*)&Pos(), 0, 100);
	for (int i = 0; i < colliders.size(); i++)
	{
		colliders[i]->GUIRender();
		//ImGui::SliderFloat3("ValphalkPos", (float*)&colliders[i]->Rot(), -10, 10);
		//ImGui::SliderFloat3("ValphalkScale", (float*)&colliders[i]->Scale(), 0, 1000);
	}

	for (int i = 0; i < wings.size(); i++)
	{
		wings[i]->GUIRender();
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

void Valphalk::ColliderNodePos()
{
	// 머리
	transforms[HEAD]->SetWorld(GetTransformByNode(14));

	// 목
	transforms[NECK]->SetWorld(GetTransformByNode(7));

	// 가슴
	transforms[CHEST]->SetWorld(GetTransformByNode(5));

	// 몸통
	transforms[BODY]->SetWorld(GetTransformByNode(3));

	// 왼쪽 날개
	transforms[LWING]->SetWorld(GetTransformByNode(63));
	//Wingtransforms[LWING1]->SetWorld(GetTransformByNode(64));
	 
	// 왼쪽 연결 관절
	transforms[LWING_RADIUS]->SetWorld(GetTransformByNode(57));
	
	// 오른쪽 날개
	transforms[RWING]->SetWorld(GetTransformByNode(83));
	//Wingtransforms[RWING1]->SetWorld(GetTransformByNode(84));
	
	// 오른쪽 연결 관절
	transforms[RWING_RADIUS]->SetWorld(GetTransformByNode(77));

	// 왼쪽 다리 (앞)
	transforms[LLEG1]->SetWorld(GetTransformByNode(16));

	// 왼쪽 발바닥 (앞)
	transforms[LLEG1_FOOT]->SetWorld(GetTransformByNode(30));

	// 왼쪽 다리 (뒤)
	transforms[LLEG2]->SetWorld(GetTransformByNode(98));

	// 왼쪽 발바닥 (뒤)
	transforms[LLEG2_FOOT]->SetWorld(GetTransformByNode(100));

	// 오른쪽 다리 (앞)
	transforms[RLEG1]->SetWorld(GetTransformByNode(36));

	// 오른쪽 발바닥 (앞)
	transforms[RLEG1_FOOT]->SetWorld(GetTransformByNode(50));

	// 오른쪽 다리 (뒤)
	transforms[RLEG2]->SetWorld(GetTransformByNode(112));

	// 오른쪽 발바닥 (뒤)
	transforms[RLEG2_FOOT]->SetWorld(GetTransformByNode(114));

	// 꼬리 시작
	transforms[TAIL_START]->SetWorld(GetTransformByNode(126));

	// 꼬리 1/4 끝
	transforms[TAIL_1]->SetWorld(GetTransformByNode(127));
	
	// 꼬리 1/2 끝
	transforms[TAIL_2]->SetWorld(GetTransformByNode(128));
	
	// 꼬리 끝
	transforms[TAIL]->SetWorld(GetTransformByNode(130));

}

void Valphalk::EndRoar() // 포효 끝나고 원래 모션으로 돌아옴
{
	SetState(STUN);
	Count = 1;
	LookatPlayer = false;
	
}

void Valphalk::StartRoar()
{
	// 플레이어 필요해서 임시로 불러옴
	//Player* player =
	//	dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetPlayer();
	//
	//float dirB = 1000.0f;
	//float dirA = Distance(Pos(),player->getCollider()->Pos());

	//if (dirA < dirB)
	//{
	//	LookatPlayer = true; // 플레이어를 타겟으로 잡게됨
	//	SetState(E_4013);
	//}

	//if (LookatPlayer)
	//{
	//	if (RATIO > 0.98)
	//	{
	//		EndRoar();
	//	}
	//}
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
	//Pos() = GetTranslationByNode(0);
}

void Valphalk::UpdateUI()
{

}

void Valphalk::E4013()
{	
	PLAY;
	if (RATIO > 0.7)
		Sounds::Get()->Play("em086_05_vo_media_10", 0.5f);

}
