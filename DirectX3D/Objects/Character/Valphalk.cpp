#include "Framework.h"
#include "Scenes/ShadowScene.h"

Valphalk::Valphalk() : ModelAnimator("Valphalk")
{
	head = new Transform();
	ReadClip("E_0003");
	ReadClip("E_0007");
	// 플레이어 발견 전
	ReadClip("E_0043");
	ReadClip("E_0044");
	ReadClip("E_0045");
	// 플레이어 발견 후
	ReadClip("E_0097");
	ReadClip("E_0098");
	ReadClip("E_0099");
	ReadClip("E_0146");
	ReadClip("E_1151");
	ReadClip("E_1155");
	ReadClip("E_1163");
	ReadClip("E_1164");
	ReadClip("E_2001");
	ReadClip("E_2002");
	ReadClip("E_2003");
	ReadClip("E_2013");
	ReadClip("E_2015");
	ReadClip("E_2017");
	ReadClip("E_2019");
	//ReadClip("E_2020");
	//ReadClip("E_2022");
	//ReadClip("E_2027");
	//ReadClip("E_2032");
	//ReadClip("E_2038");
	//ReadClip("E_2040");
	//ReadClip("E_2041");
	//ReadClip("E_2042");
	//ReadClip("E_2044");
	//ReadClip("E_2045");
	//ReadClip("E_2054");
	//ReadClip("E_2056");
	//ReadClip("E_2106");
	//ReadClip("E_2107");
	//ReadClip("E_2108");
	//ReadClip("E_2118");
	//ReadClip("E_2121");
	//ReadClip("E_2173");
	//ReadClip("E_2174");
	//ReadClip("E_2175");
	//ReadClip("E_2185");
	//ReadClip("E_2188");
	//ReadClip("E_2189");
	//ReadClip("E_2190");
	//ReadClip("E_2192");
	//ReadClip("E_2193");
	//ReadClip("E_2200");
	ReadClip("E_2210");
	ReadClip("E_2211");
	ReadClip("E_3001");
	ReadClip("E_3023");
	// 아래 있는게 첫 포효
	ReadClip("E_4013");
	//ReadClip("E_22005");

	ColliderAdd();	

	realPos = new CapsuleCollider(1, 0.1);
	realPos->Scale() *= 6.0f;


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
	delete head;
	delete realPos;
}

void Valphalk::Update()
{
	//Pos().x = 2000; // 임시 고정용
	UpdateWorld();
	Move();
	head->Pos() = realPos->Pos() + Vector3::Up() * 200;
	head->UpdateWorld();
	realPos->Pos() = GetTranslationByNode(1);
	realPos->UpdateWorld();
	
	velocity = target->GlobalPos() - GlobalPos();

	for (CapsuleCollider* capsulCollider : colliders)	
		capsulCollider->Update();	

	for (BoxCollider* boxCollider : wings )	
		boxCollider->UpdateWorld();	

	ColliderNodePos();

	ModelAnimator::Update();
	patrolTime += DELTA;

	// Test 샘플 코드
	//===================================
	//if (Count <= 0)
	//{
	////	colliders[TARGETDOME]->Pos() = GetTranslationByNode(4); // 타겟 보는 범위
	//	StartRoar();
	//}
	//
	//// 잘 들어갔나 확인하기 용 코드
	//if (patrolTime > 6 && curState==E_0003 || patrolTime > 6 && curState==E_0043)
	//	encounter = true;
	//Patrol();
	//if (encounter == true)
	//{
	//	SetState(E_4013);
	//	encounter = false;
	//}
	//Fight();

	if (KEY_DOWN('5') || stormTime > 0.001f)
		Storm();

	if (KEY_DOWN('6'))
		SetState(E_2001);

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
	realPos->Render();
}

void Valphalk::GUIRender()
{
	//ModelAnimator::GUIRender();
	Vector3 realpos = realPos->Pos();
	ImGui::SliderFloat3("ValphalkPos", (float*)&Pos(), -5000, 5000);
	ImGui::DragFloat3("RealPos", (float*)&realPos->Pos());
	ImGui::Text("RanPatrolNum : %d", ranPatrol);
	ImGui::Text("stormTime : %.3f", stormTime);
	ImGui::Text("Length : %.3f", velocity.Length());

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

void Valphalk::Storm()
{
	combo = true;
	stormTime += DELTA;
	if (stormTime < 0.1f)
		SetState(E_1151);

	if (RATIO > 0.98)
		SetState(E_1155);
	
	if (stormTime > 6 && curState != E_1164)
		SetState(E_1163);

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

void Valphalk::SetState(State state)
{
	if (state == curState)
		return;

	Vector3 pos1;
	if (combo == false) // 연계공격중일때는 갱신X
	{
		Pos() = realPos->Pos();
		Pos().y = pos1.y;
	}
	if (Pos().y < 0)
		Pos().y = 0;
	//bossRealPos->Pos() = Pos();

	curState = state;
	PlayClip(state);

	//TerrainEditor* terrain = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetTerrain();
	//
	//	
	//terrain->ComputePicking(pos1, head->Pos() + Vector3::Up() * 200, Vector3::Down());

		//	float y = max(pos1.y, pos2.y);	
//	TerrainEditor* terrain = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetTerrain();
//
//	Vector3 pos1;
//	terrain->ComputePicking(pos1, head->Pos() + Vector3::Up() * 200, Vector3::Down());
//
//	//	float y = max(pos1.y, pos2.y);
//	Pos().y = pos1.y;
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

void Valphalk::Patrol()
{	
	if (velocity.Length() < 2000) return;
	// 타겟과의 거리가 일정 거리 이상이면 패트롤 = 일정거리 안으로 들어오면 패트롤을 중지후, 공격 태세	
	//preran 설정으로 같은패턴이 연속 두번이상 나오지 않도록 수정예정.
	if (patrolTime > 5)
	{
		ranPatrol = rand() % 2;
		patrolTime = 0;
	}
	if(ranPatrol == 0)
		SetState(E_0003);
	if (ranPatrol == 1)
		SetState(E_0043);
}

void Valphalk::Fight()
{
	SetState(E_2040);



}

void Valphalk::ChooseNextPattern()
{
	// 1. 패턴 대기열에 대기중인 패턴이 있는가? (분노 포효, 흡기, 필살기) 
	// 2. 싸우는 중인가? (비전투 시에는 패트롤, 인식하면 포효)
	// 
	// 3. 거리가 가까운가? (너무 멀면 이동 먼저) 
	// 4. 참격모드인가 포격모드인가?
	// 5. 용기 상태인가?
	// 
	// 6. 분노했는가? // 이건 패턴에서 따지는게 나을 듯
	// 7. 그렇다면 가능한 패턴을 리스트업 후에 난수든 뭐든 선택



}

void Valphalk::Move()
{
	switch (curState)
	{
	case Valphalk::E_0003:	 E0003();		break;
	case Valphalk::E_0007:	 E0007();		break;
	case Valphalk::E_0043:	 E0043();		break;
	case Valphalk::E_0044:	 E0044();		break;
	case Valphalk::E_0045:	 E0045();		break;
	case Valphalk::E_0097:	 E0097();		break;
	case Valphalk::E_0146:	 E0146();		break;
	case Valphalk::E_1151:	 E1151();		break;
	case Valphalk::E_1155:	 E1155();		break;
	case Valphalk::E_1163:	 E1163();		break;
	case Valphalk::E_1164:	 E1164();		break;
	case Valphalk::E_2001:	 E2001();		break;
	case Valphalk::E_2002:	 E2002();		break;
	case Valphalk::E_2003:	 E2003();		break;
	case Valphalk::E_2013:	 E2013();		break;
	case Valphalk::E_2015:	 E2015();		break;
	case Valphalk::E_2017:	 E2017();		break;
	case Valphalk::E_2019:	 E2019();		break;
	//case Valphalk::E_2020:	 E2020();		break;
	//case Valphalk::E_2022:	 E2022();		break;
	//case Valphalk::E_2027:	 E2027();		break;
	//case Valphalk::E_2032:	 E2032();		break;
	case Valphalk::E_2038:	 E2038();		break;
	case Valphalk::E_2040:	 E2040();		break;
	//case Valphalk::E_2041:	 E2041();		break;
	//case Valphalk::E_2042:	 E2042();		break;
	//case Valphalk::E_2044:	 E2044();		break;
	//case Valphalk::E_2045:	 E2045();		break;
	case Valphalk::E_2054:	 E2054();		break;
	//case Valphalk::E_2056:	 E2056();		break;
	//case Valphalk::E_2106:	 E2106();		break;
	//case Valphalk::E_2107:	 E2107();		break;
	//case Valphalk::E_2108:	 E2108();		break;
	//case Valphalk::E_2118:	 E2118();		break;
	//case Valphalk::E_2121:	 E2121();		break;
	//case Valphalk::E_2173:	 E2173();		break;
	//case Valphalk::E_2174:	 E2174();		break;
	//case Valphalk::E_2175:	 E2175();		break;
	//case Valphalk::E_2185:	 E2185();		break;
	//case Valphalk::E_2188:	 E2188();		break;
	//case Valphalk::E_2189:	 E2189();		break;
	//case Valphalk::E_2190:	 E2190();		break;
	//case Valphalk::E_2192:	 E2192();		break;
	//case Valphalk::E_2193:	 E2193();		break;
	//case Valphalk::E_2200:	 E2200();		break;
	case Valphalk::E_2210:	 E2210();		break;
	case Valphalk::E_2211:	 E2211();		break;
	case Valphalk::E_3001:	 E3001();		break;
	case Valphalk::E_3023:	 E3023();		break;
	case Valphalk::E_4013:	 E4013();		break;
	}
}

void Valphalk::UpdateUI()
{

}

void Valphalk::E0003() // 평상시 대기
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0007() // 탈진
{
	PLAY;
}

void Valphalk::E0043() // 앞으로 전진
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0044() // 좌회전
{
	PLAY;
}

void Valphalk::E0045() // 뒤로 회전
{
	PLAY;
}

void Valphalk::E0097() // 정지 (공격 준비)
{
	PLAY;
}

void Valphalk::E0098() // 급좌회전 턴
{
	PLAY;
}

void Valphalk::E0099() // 급뒤로 턴
{
	PLAY;
}

void Valphalk::E0146() //대기상태에서 포격모드로 변환
{
	PLAY;
	if (RATIO > 0.98)
		//SetState(E_0151); --> 이게 포격형 Idle 자세, 만들어지면 이거로 바꿔야됨
		SetState(E_0003);
}

void Valphalk::E1151() // 습격준비
{
	PLAY;
	if(RATIO<0.1)
	Sounds::Get()->Play("em086_05_fx_media_25", 0.5f);
}

void Valphalk::E1155() // 비상
{
	Rot().x = 1.2f;
	Pos().y += 30000 * DELTA;
	Pos().z += 1000 * DELTA;	
	
	PLAY;	
	if (RATIO < 0.1)
		Sounds::Get()->Play("em086_05_fx_media_22", 0.5f);

	if (Pos().y > 80000)
		Sounds::Get()->Play("em086_05_fx_media_33", 0.5f);
}

void Valphalk::E1163() // 하강
{
	Player* p = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetPlayer();
	Rot().x = -.8f;
	Pos().y -= 25000 * DELTA;
	Pos().z += 1000 * DELTA;
	if (Pos().y > p->Pos().y)
	{
		Pos().x = p->Pos().x;
		Pos().z = p->Pos().z - 500;
		//Pos().y = realPos->Pos().y;
		//realPos->Pos().y = Pos().y;
		//Pos() = realPos->Pos();
		//Pos().y = realPos->Pos().y;
		PLAY;
	}
	else 
	{
		SetState(E_1164); 
		return;
	}
	if (Pos().y > 25000 && Pos().y < 25500)
		Sounds::Get()->Play("em086_05_fx_media_19", 0.5f);
	if (Pos().y > 3000 && Pos().y < 3500)
	Sounds::Get()->Play("em086_05_fx_media_20", 0.5f);

}

void Valphalk::E1164() // 착지
{
	Pos().y = 1380.0f;	
	Rot().x = 0;
	stormTime = 0;
	PLAY;

	if (RATIO > 0.98)
	{
		combo = false;
		SetState(E_0003);
	}
	
}

void Valphalk::E2001()
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2002()
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2003()
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2013()
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2015);
}

void Valphalk::E2015()
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2017);
}

void Valphalk::E2017()
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2019);
}

void Valphalk::E2019()
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E2020()
{
}

void Valphalk::E2022()
{
}

void Valphalk::E2027()
{
}

void Valphalk::E2032()
{
}

void Valphalk::E2038() // 날개 찌르기
{
	combo = true; // 콤보 시작

	PLAY;

	if (RATIO > 0.98)
		SetState(E_2054);
}

void Valphalk::E2040() // 찌르기 준비
{
	PLAY;	
	if (RATIO > 0.98)
		SetState(E_2038);
}

void Valphalk::E2041()
{
}

void Valphalk::E2042()
{
}

void Valphalk::E2044()
{
}

void Valphalk::E2045()
{
}

void Valphalk::E2054() // 찌르기 날개 회수
{
	PLAY;

	if (RATIO > 0.98)
	{
		SetState(E_0003);
		combo = false; // 콤보 마무리
	}
}

void Valphalk::E2056()
{
}

void Valphalk::E2106()
{
}

void Valphalk::E2107()
{
}

void Valphalk::E2108()
{
}

void Valphalk::E2118()
{
}

void Valphalk::E2121()
{
}

void Valphalk::E2173()
{
}

void Valphalk::E2174()
{
}

void Valphalk::E2175()
{
}

void Valphalk::E2185()
{
}

void Valphalk::E2188()
{
}

void Valphalk::E2189()
{
}

void Valphalk::E2190()
{
}

void Valphalk::E2192()
{
}

void Valphalk::E2193()
{
}

void Valphalk::E2200()
{
}

void Valphalk::E2210()//뒤돌아 날개찍기 준비동작
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2211);
}

void Valphalk::E2211()//뒤돌아 날개찍기 공격동작
{
	PLAY;
	//각도 바꿔주는 Ratio : 0.04 ~ 0.10
	if (RATIO > 0.98)
	{
		combo = false;
		SetState(E_0003);
	}
}

void Valphalk::E3001() // 작은 데미지 피격
{
	PLAY;
}

void Valphalk::E3023() // 사망
{
	PLAY;
	if (RATIO > 0.98)
		GetClip(curState)->SetRatio(0.98); // 사망시 애니메이션 정지	
}

void Valphalk::E4013() // 조우 포효
{	
	PLAY;
	if (RATIO > 0.2 && RATIO < 0.28)
		Sounds::Get()->Play("em086_05_vo_media_10", 0.5f);
	if (RATIO > 0.98)
		SetState(E_2040);
}

void Valphalk::E22005() // 포효
{
	PLAY;
	if (RATIO > 0.5 && RATIO < 0.58)
		Sounds::Get()->Play("em086_05_vo_media_10", 0.5f);
	if (RATIO > 0.98)
		SetState(E_0003);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Collider 관련 함수들

void Valphalk::ColliderAdd()
{
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