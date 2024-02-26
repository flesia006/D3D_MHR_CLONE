#include "Framework.h"
#include "Scenes/ShadowScene.h"

Valphalk::Valphalk() : ModelAnimator("Valphalk")
{
	srand(static_cast<unsigned int>(time(NULL)));

	head = new Transform();
	ReadClip("E_0003");
	ReadClip("E_0007");
	// 플레이어 발견 전
	ReadClip("E_0043");
	ReadClip("E_0044");
	ReadClip("E_0045");
	ReadClip("E_0055");
	// 플레이어 발견 후
	ReadClip("E_0059");
	ReadClip("E_0060");
	ReadClip("E_0061");
	ReadClip("E_0071");
	ReadClip("E_0097");
	ReadClip("E_0098");
	ReadClip("E_0099");
	ReadClip("E_0146");
	ReadClip("E_0147");
	ReadClip("E_0151");
	ReadClip("E_0152");
	ReadClip("E_0153");
	ReadClip("E_0164");
	ReadClip("E_0165");
	ReadClip("E_0166");
	ReadClip("E_0171");
	ReadClip("E_0172");
	ReadClip("E_0173");
	ReadClip("E_0178");
	ReadClip("E_0179");
	ReadClip("E_0180");
	ReadClip("E_0186");
	ReadClip("E_0187");
	ReadClip("E_0188");
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
	ReadClip("E_2020");
	ReadClip("E_2022");
	ReadClip("E_2027");
	ReadClip("E_2032");
	ReadClip("E_2033");
	ReadClip("E_2038");
	ReadClip("E_2040");
	ReadClip("E_2041");
	ReadClip("E_2042");
	ReadClip("E_2044");
	ReadClip("E_2045");
	ReadClip("E_2054");
	ReadClip("E_2056");
	ReadClip("E_2079");
	ReadClip("E_2082");
	ReadClip("E_2091");
	ReadClip("E_2092");
	ReadClip("E_2093");
	ReadClip("E_2103");

	ReadClip("E_2106");
	ReadClip("E_2107");
	ReadClip("E_2108");
	ReadClip("E_2118");
	ReadClip("E_2121");
	ReadClip("E_2124");

	ReadClip("E_2129");
	ReadClip("E_2130");
	ReadClip("E_2131");
	ReadClip("E_2133");
	ReadClip("E_2134");
	ReadClip("E_2141");

	ReadClip("E_2144");
	ReadClip("E_2145");
	ReadClip("E_2146");
	ReadClip("E_2151");
	ReadClip("E_2152");
	ReadClip("E_2153");
	ReadClip("E_2171");

	ReadClip("E_2173");
	ReadClip("E_2174");
	ReadClip("E_2175");
	ReadClip("E_2185");
	ReadClip("E_2188");
	ReadClip("E_2189");
	ReadClip("E_2190");
	ReadClip("E_2192");
	ReadClip("E_2193");
	ReadClip("E_2200");
	ReadClip("E_2200fix");

	ReadClip("E_2210");
	ReadClip("E_2211");
	ReadClip("E_2253");
	ReadClip("E_2265");
	ReadClip("E_2267");
	ReadClip("E_2270");
	ReadClip("E_2271");
	ReadClip("E_2272");
	ReadClip("E_2274");
	ReadClip("E_2275");
	ReadClip("E_2276");
	ReadClip("E_2277");
	ReadClip("E_2278");
	ReadClip("E_2280");
	ReadClip("E_2281");
	ReadClip("E_2282");
	ReadClip("E_2286");
	ReadClip("E_2288");
	ReadClip("E_2290");
	ReadClip("E_2354");
	ReadClip("E_2356");
	ReadClip("E_2359");
	ReadClip("E_2361");
	ReadClip("E_2367");
	ReadClip("E_2368");
	ReadClip("E_2371");
	ReadClip("E_2372");
	ReadClip("E_2373");
	ReadClip("E_2374");
	ReadClip("E_2375");
	ReadClip("E_2376");

	ReadClip("E_2381");
	ReadClip("E_2382");
	ReadClip("E_2383");

	ReadClip("E_2403");
	ReadClip("E_3001");
	ReadClip("E_3023");
	// 아래 있는게 첫 포효
	ReadClip("E_4013");
//	ReadClip("E_22005");

	ColliderAdd();

	realPos = new CapsuleCollider(1, 0.1);
	realPos->Scale() *= 6.0f;
	realPos->UpdateWorld();

	tempCollider = new CapsuleCollider(6, 0.1);
	tempCollider->UpdateWorld();

	/////////////////////////////////////////////
	// 공격 콜라이더 (투사체, 폭발 등)	
	bullets.resize(6);
	FOR(6)
	{
		bullets[i] = new SphereCollider();
		bullets[i]->Scale() *= 100;
		bullets[i]->SetColor(1, 0, 0);
		bullets[i]->SetActive(true);
	}

	forwardBoom = new SphereCollider();
	forwardBoom->Scale() *=500;
	forwardBoom->SetColor(1, 0, 0);
	forwardBoom->Pos() = forwardBoomPosInit;
	forwardBoom->SetParent(head);
	forwardBoom->SetActive(false);
	{//fullBurst
		fullBurst = new BoxCollider();
		fullBurst->Scale() *= 500;
		fullBurst->Scale().z *= 20;
		fullBurst->SetParent(head);
		fullBurst->Pos().z -= 5000;
		fullBurst->SetColor(1, 0, 0);
		fullBurst->SetActive(false);		
		fullBurstScale = fullBurst->Scale();
		fullBurstPos = fullBurst->Pos();
		fullBurstRot = fullBurst->Rot();
	}
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
	for (SphereCollider* bullet : bullets)
		delete bullet;
	delete forwardBoom;
	delete fullBurst;
	delete head;
	delete realPos;
}

void Valphalk::Update()
{
	UpdateWorld();
	if (preState != curState)
		GetClip(preState)->ResetPlayTime();

	PlayPattern();
	// hitCheck() 
	head->Pos() = realPos->Pos() + Vector3::Up() * 200;
	head->UpdateWorld();

	realPos->Pos() = GetTranslationByNode(1);
	Vector3 fwd = (GetTranslationByNode(3) - GetTranslationByNode(5)).GetNormalized();
	realPos->Rot().y = atan2(fwd.x, fwd.z);
	realPos->UpdateWorld();

	tempCollider->Pos() = realPos->Pos() + (realPos->Back() + realPos->Right()).GetNormalized() * 1000;
	tempCollider->UpdateWorld();

	velocity = target->GlobalPos() - GlobalPos();

	for (CapsuleCollider* capsulCollider : colliders)
		capsulCollider->Update();

	for (BoxCollider* boxCollider : wings)
		boxCollider->UpdateWorld();

	for (SphereCollider* bullet : bullets)
		bullet->UpdateWorld();
	
	forwardBoom->UpdateWorld();
	fullBurst->UpdateWorld();

	head->Rot().y = Rot().y;
	
	ColliderNodePos();

	GetRadBtwTrgt();

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
	//if (KEY_DOWN('4'))
	//	SetState(E_0003);
	if (KEY_DOWN('5') || bulletTime > 0.001f)
		EnergyBullets();
	if (KEY_DOWN('6') || stormTime > 0.001f)
		Storm();

	if (KEY_DOWN('7'))
		FullBurst();
		//SetState(E_2001);
	if (KEY_DOWN('8'))
		ForwardBoom();
	
	if (KEY_DOWN('9'))
		SetState(E_2173);		

}

void Valphalk::PreRender()
{
}

void Valphalk::Render()
{
	for (CapsuleCollider* capsulCollider : colliders)
	{
		if (capsulCollider->isAttack)
			capsulCollider->Render();
	}

	for (BoxCollider* boxCollider : wings)
	{
		if (boxCollider->isAttack)
			boxCollider->Render();
	}
	for (int i = 0; i < bullets.size(); ++i)
		bullets[i]->Render();
	forwardBoom->Render();
	fullBurst->Render();

	ModelAnimator::Render();
	realPos->Render();
}

void Valphalk::GUIRender()
{
	//ModelAnimator::GUIRender();
	//ImGui::SliderFloat3("ValphalkPos", (float*)&Pos(), -5000, 5000);
	//ImGui::SliderFloat3("ValphalkRot", (float*)&Rot(), 0, 3.14f);
	ImGui::DragFloat3("RealPos", (float*)&realPos->Pos());
	ImGui::DragFloat3("RealRot", (float*)&realPos->Rot());
	ImGui::DragFloat("radbtwTrgt", (float*)&radBtwTarget);

	ImGui::DragInt("whichPat", &whichPat);
	ImGui::Text("curHP : %f", curHP);
	//for (int i = 0; i < colliders.size(); i++)
	//{
	//	colliders[i]->GUIRender();
	//}
	//ImGui::DragFloat("radBtwTrgt", &radBtwTarget);
	//ImGui::SliderFloat3("ValphalkScale", (float*)&colliders[i]->Scale(), 0, 1000);
	ImGui::DragFloat("radDifference", &radDifference);

	//	ImGui::Text("RanPatrolNum : %d", ranPatrol);
	//	ImGui::Text("stormTime : %.3f", stormTime);
	//	ImGui::Text("Length : %.3f", velocity.Length());

	//	for (int i = 0; i < colliders.size(); i++)
	//	{
	//		colliders[i]->GUIRender();
	//		//ImGui::SliderFloat3("ValphalkPos", (float*)&colliders[i]->Rot(), -10, 10);
	//		//ImGui::SliderFloat3("ValphalkScale", (float*)&colliders[i]->Scale(), 0, 1000);
	//	}
	//
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

Vector3 Valphalk::GetPlayerPos() // 플레이어 위치 추적 함수
{
	Player* player = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetPlayer();
	Vector3 pos;
	pos = player->Pos();	
	return pos;	
}

void Valphalk::Storm()
{
	stormTime += DELTA;
	combo = true;	
	if (sequence == 0) { SetState(E_1151); E1151(); }

	if (sequence == 1) { SetState(E_1155); E1155();	}

	//if (sequence == 2) { SetState(E_1163); E1163();	}
	
	if (stormTime > 6 && curState != E_1164 && sequence == 2) { SetState(E_1163); E1163();	}
	if (sequence == 3) { SetState(E_1164); E1164(); }
}

void Valphalk::EnergyBullets()
{	
	static int whichPattern = 0;
	if (sequence == 0) // 각도 정하기
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}
	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{		
		switch (whichPattern)
		{
		case 1:		SetState(E_0151);  E0151();				break;// SetState(E_2091);  E2091();  break;
		case 2:		SetState(E_0152);  E0152(-XM_PIDIV2);	break; // 왼쪽 90
		case 3:		SetState(E_0153);  E0153(-XM_PI);		break;
		case 4:		SetState(E_0151);  E0151();				break;//;  E2091();  break;
		case 5:		SetState(E_0152);  E0152(+XM_PIDIV2);	break;
		case 6:		SetState(E_0153);  E0153(+XM_PI);		break;
		}	
	}

	if (sequence == 2)
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		sequence++;
	}

	if (sequence == 3)
	{
		for (int i = 0; i < bullets.size(); ++i)
		{
			bullets[0]->Pos() = GetTranslationByNode(61);
			bullets[1]->Pos() = GetTranslationByNode(64);
			bullets[2]->Pos() = GetTranslationByNode(67);
			bullets[3]->Pos() = GetTranslationByNode(81);
			bullets[4]->Pos() = GetTranslationByNode(84);
			bullets[5]->Pos() = GetTranslationByNode(87);
			bullets[i]->SetActive(true);
		}
		sequence++;
	}
	if (sequence == 4)
	{
		SetState(E_2079); E2079();		
		bulletTime += DELTA;

	}
	if (sequence == 5)
	{ 	
		bulletTime = 0; 
		whichPattern = 0; 
		ChooseNextPattern(); 
	}
}

void Valphalk::ForwardBoom()
{
	static int whichPattern = 0;
	if (sequence == 0) // 각도 정했으면 방향 전환함수
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_0151);  E0151();				break;
		case 2:		SetState(E_0152);  E0152(-XM_PIDIV2);	break; // 왼쪽 90
		case 3:		SetState(E_0153);  E0153(-XM_PI);		break; // 왼쪽 180
		case 4:		SetState(E_0151);  E0151();				break;
		case 5:		SetState(E_0152);  E0152(XM_PIDIV2);	break;
		case 6:		SetState(E_0153);  E0153(XM_PI);		break;
		}
	}
	if (sequence == 2)
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		sequence++;
	}
	if (sequence == 3) { SetState(E_2144); E2144(); }
	if (sequence == 4) { SetState(E_2145); E2145(); }
	if (sequence == 5)
	{
		SetState(E_2146); E2146();
	}
}

void Valphalk::FullBurst()
{
	static int whichPattern = 0;
	if (sequence == 0) // 각도 정하기
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}
	if (sequence == 1)
	{
		if (radBtwTarget > -XM_PIDIV2 && radBtwTarget <= 0) // 왼쪽 90도
		{
			whichPattern = 1;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > -XM_PI && radBtwTarget <= -XM_PIDIV2) // 왼뒤쪽 90도 
		{
			whichPattern = 2;
			radDifference = radBtwTarget + XM_PI;
		}
		else if (radBtwTarget > 0 && radBtwTarget <= XM_PIDIV2) // 전방 오쪽 90도
		{
			whichPattern = 3;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > XM_PIDIV2 && radBtwTarget <= XM_PI) // 오른뒤쪽 90도
		{
			whichPattern = 4;
			radDifference = radBtwTarget - XM_PI;
		}

		sequence++;
	}

	if (sequence == 2)
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2354);  E2354();			break;
		case 2:		SetState(E_2356);  E2356(-XM_PI);	break;
		case 3:		SetState(E_2354);  E2354();			break;
		case 4:		SetState(E_2356);  E2356(XM_PI);	break;
		}
	}
	//if (sequence == 1) // 각도 정했으면 방향 전환함수
	//{
	//	switch (whichPattern)
	//	{
	//	case 1:		SetState(E_2354);  E2354(); break;// SetState(E_0098);  E0098(-0.1f);  break;
	//	case 2:		SetState(E_2354);  E2354(-XM_PIDIV2);  break; // 왼쪽 90
	//	case 3:		SetState(E_2356);  E2356(-XM_PI);  break;
	//	case 4:		SetState(E_2354);  E2354(); break; //SetState(E_0098);  E0098(0.1f);  break;
	//	case 5:		SetState(E_2354);  E2354(+XM_PIDIV2);  break;
	//	case 6:		SetState(E_2359);  E2359(+XM_PI);  break;
	//	}
	//}
	if (sequence == 3)
	{
		if (whichPattern == 3 || whichPattern == 4)
			Scale().x *= -1;
		sequence++;
	}
	if (sequence == 4){ SetState(E_2361); E2361(); }	
	if (sequence == 5){ SetState(E_2367); E2367(); }
	if (sequence == 6){ SetState(E_2368); E2368(); }
	if (sequence == 7) ChooseNextPattern();
}

void Valphalk::Hupgi()
{
}

void Valphalk::Sidestep()
{
	if (sequence == 0)
	{
		Vector3 dir = (realPos->Back() + realPos->Right() ).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 1000 + realPos->Right() * 1106 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;		
	}
	
	if (sequence == 1) // 스탭 모션
	{
		SetState(E_2124);
		E2124(vecToTagt);
	}

	if (sequence == 2) // 마무리
	{		
		vecToTagt = {0, 0, 0};
		ChooseNextPattern();
	}

}

void Valphalk::B_Sidestep()
{
	if (sequence == 0)
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 1000 + realPos->Right() * 1106 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 1) // 스탭 모션
	{
		SetState(E_2253);
		E2253(vecToTagt);
	}

	if (sequence == 2) // 마무리
	{
		vecToTagt = { 0, 0, 0 };
		ChooseNextPattern();
	}
}

void Valphalk::Dead()
{
	SetState(E_3023);
	E3023();
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

void Valphalk::SetState(State state, float rad)
{
	if (state == curState)
		return;

	if (combo == false) // 연계공격중일때는 갱신X
	{
		Pos() = realPos->Pos();
	}

	preState = curState;
	curState = state;

	//PlayClip(state);
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
	if (ranPatrol == 0)
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

	SetState(E_2091);
	sequence = 0;
	radDifference = 0;
	initialRad = Rot().y;

//	int i = rand() % 2;
//	switch (i)
//	{
//	case 0:	curPattern = S_LEGATK;  break;
//	case 1:	curPattern = S_STABATK;	  break;
	//case 2:	curPattern = B_DUMBLING;  break;
	//default: curPattern = B_DUMBLING; break;
//	}
}

void Valphalk::PlayPattern()
{

	switch (curPattern)
	{
	case Valphalk::S_LEGATK:		S_LegAtk();			break;
	case Valphalk::S_STABATK:		S_StabAtk();		break;
	case Valphalk::S_BACKWINGATK:	S_BackWingAtk();	break;
	case Valphalk::S_SRUSH:		    S_SRush();			break;
	case Valphalk::S_JETRUSH:		S_JetRush();		break;
	case Valphalk::S_BITE:			S_Bite();			break;
	case Valphalk::S_TRANSFORM:		S_Transform();		break;
	case Valphalk::S_RUNANDBITE:	S_RunAndBite();		break;
	case Valphalk::B_SWINGATK:		B_SwingAtk();		break;
	case Valphalk::B_WINGATK:		B_WingAtk();		break;
	case Valphalk::B_DOWNBLAST:		B_DownBlast();		break;
	case Valphalk::B_FWDBLAST:		B_FwdBlast();		break;
	case Valphalk::B_ENERGYBLAST:	B_EnergyBlast();	break;
	case Valphalk::B_DUMBLING:		B_Dumbling();		break;
	case Valphalk::B_TRANSFORM:		B_Trnasform();		break;
	case Valphalk::B_SIDESTEP:		B_Sidestep();		break;
	case Valphalk::HS_FLYBLAST:		HS_FlyBlast();		break;
	case Valphalk::HS_FLYFALLATK:	HS_FlyFallAtk();	break;
	case Valphalk::HS_FLYWINGBLAST:	HS_FlyWingBlast();	break;
	case Valphalk::HB_LASERBLAST:	HB_LaserBlast();	break;
	case Valphalk::FINDROAR:	    FindRoar();  		break;
	case Valphalk::ANGERROAR:	    AngerRoar();  		break;
	case Valphalk::HUPGI:		    Hupgi();			break;
	case Valphalk::STORM:		    Storm();			break;
	case Valphalk::ENERGYBULLET:	EnergyBullets();	break;
	case Valphalk::FULLBURST:		FullBurst();		break;
	case Valphalk::SIDESTEP:		Sidestep();			break;
	case Valphalk::FORWARDBOOM:		ForwardBoom();		break;
	case Valphalk::DEAD:			Dead();				break;
	default:		break;
	}
}

void Valphalk::UpdateUI()
{

}

float Valphalk::GetRadBtwTrgt()
{
	UpdateWorld();
	Vector3 fwd = Forward();
	Vector3 VtoP = (realPos->Pos() - target->GlobalPos()).GetNormalized();
	Vector3 rad = XMVector3AngleBetweenVectors(fwd, VtoP);
	Vector3 cross = Cross(fwd, VtoP);
	radBtwTarget = rad.x;
	if (Cross(fwd, VtoP).y < 0)
		radBtwTarget *= -1;

	return radBtwTarget;
}

void Valphalk::RotateToTarget(float ratio1, float ratio2)
{
	float curRatio = RATIO;
	curRatio = Clamp(ratio1, ratio2, curRatio);

	float rad = ((curRatio - ratio1) / (ratio2 - ratio1)) * radDifference;

	Rot().y = initialRad + rad;
}

void Valphalk::SetColliderAttack(ColliderName name, float ratio)
{
	colliders[name]->isAttack = true;
	colliders[name]->SetColor(Float4(1, 0, 1, 1));
	if (RATIO > ratio - 0.01)
	{
		colliders[name]->isAttack = false;
		colliders[name]->SetColor(Float4(0, 1, 0, 1));
	}
}

int Valphalk::SetRadAndMirror(bool needMirror)
{
	GetRadBtwTrgt();
	int whichPattern = 0;
	if (needMirror)
	{
		if (radBtwTarget > -rot45 && radBtwTarget <= 0) // 전방 왼쪽 45도
		{
			whichPattern = 1;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > -rot135 && radBtwTarget <= -rot45) // 왼쪽 90도
		{
			whichPattern = 2;
			radDifference = radBtwTarget + XM_PIDIV2;
		}
		else if (radBtwTarget > -XM_PI && radBtwTarget <= -rot135) // 왼뒤쪽 45도
		{
			whichPattern = 3;
			radDifference = radBtwTarget + XM_PI;
		}
		else if (radBtwTarget > 0 && radBtwTarget <= rot45) // 전방 왼쪽 45도
		{
			whichPattern = 4;
			radDifference = radBtwTarget;
			Scale().x *= -1;
		}
		else if (radBtwTarget > rot45 && radBtwTarget <= rot135) // 오른쪽 90도
		{
			whichPattern = 5;
			radDifference = radBtwTarget - XM_PIDIV2;
			Scale().x *= -1;
		}
		else if (radBtwTarget > rot135 && radBtwTarget <= XM_PI) // 오른뒤쪽 45도
		{
			whichPattern = 6;
			radDifference = radBtwTarget - XM_PI;
			Scale().x *= -1;
		}
		else
			whichPattern = 1;
	}
	else
	{
		if (radBtwTarget > -rot45 && radBtwTarget <= 0) // 전방 90도
		{
			whichPattern = 1;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > -rot135 && radBtwTarget <= -rot45) // 왼쪽 90도 
		{
			whichPattern = 2;
			radDifference = radBtwTarget + XM_PIDIV2;
		}
		else if (radBtwTarget > -XM_PI && radBtwTarget <= -rot135) // 왼뒤쪽 45도
		{
			whichPattern = 3;
			radDifference = radBtwTarget + XM_PI;
		}
		else if (radBtwTarget > 0 && radBtwTarget <= rot45) // 전방 왼쪽 45도
		{
			whichPattern = 4;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > rot45 && radBtwTarget <= rot135) // 오른쪽 90도
		{
			whichPattern = 5;
			radDifference = radBtwTarget - XM_PIDIV2;
		}
		else if (radBtwTarget > rot135 && radBtwTarget <= XM_PI) // 오른뒤쪽 45도
		{
			whichPattern = 6;
			radDifference = radBtwTarget - XM_PI;
		}
		else
		{
			whichPattern = 1;
		}
	}

	initialRad = Rot().y;
	return whichPattern;
}

void Valphalk::S_LegAtk()
{
	static int whichPattern = 0;
	if (sequence == 0) // 사이드스탭 할지 앞다리 찍기 할지 판단
	{
		if ((realPos->Pos() - target->GlobalPos()).Length() < 500)
			sequence = 6;
		else
			sequence++;
	}

	if (sequence == 1) // 앞다리 찍기 각도 정하기
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 2) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2106);  E2106();  break;
		case 2:		SetState(E_2107);  E2107(-XM_PIDIV2);  break;
		case 3:		SetState(E_2108);  E2108(-XM_PI);	break;
		case 4:		SetState(E_2106);  E2106();  break;
		case 5:		SetState(E_2107);  E2107(XM_PIDIV2);  break;
		case 6:		SetState(E_2108);  E2108(XM_PI);	break;
		}
	}

	if (sequence == 3) // 공격 모션
	{
		SetState(E_2118);	E2118();
	}

	if (sequence == 4) // 앞다리 찍기 마무리 + 왼날개 찍기
	{
		SetState(E_2121);	E2121();
	}

	if (sequence == 5)
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 6) // 백스탭 위치 계산
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 300 + realPos->Right() * 606 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 7) // 백스탭
	{
		SetState(E_2124);
		E2124(vecToTagt);
	}

	if (sequence == 8) // 백스탭마무리
	{
		vecToTagt = { 0,0,0 };
		Pos() = realPos->Pos();
		sequence = 1;
	}
}

void Valphalk::S_StabAtk()
{
	static int whichPattern = 0;

	if (sequence == 0) // 사이드스탭 할지 앞다리 찍기 할지 판단
	{
		if ((realPos->Pos() - target->GlobalPos()).Length() < 1000)
			sequence = 6;
		else
			sequence++;
	}

	if (sequence == 1) // 날개찌르기 각도 정하기
	{
		whichPattern = SetRadAndMirror(false);
		sequence++;
	}

	if (sequence == 2) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2040);  E2040();  break;
		case 2:		SetState(E_2041);  E2041(-XM_PIDIV2);  break;
		case 3:		SetState(E_2042);  E2042(-XM_PI);  break;
		case 4:		SetState(E_2040);  E2040();  break;
		case 5:		SetState(E_2044);  E2044(XM_PIDIV2);  break;
		case 6:		SetState(E_2045);  E2045(XM_PI);  break;
		}
	}

	if (sequence == 3) // 공격 모션
	{
		SetState(E_2038);	E2038();
	}

	if (sequence == 4) // 공격 모션2 - 휘두르기
	{
		SetState(E_2056);	E2056();
	}

	if (sequence == 5)
	{
		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 6) // 백스탭 위치 계산
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 2500 + realPos->Right() * 1106 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 7) // 백스탭
	{
		SetState(E_2124);
		E2124(vecToTagt);
	}

	if (sequence == 8) // 백스탭마무리
	{
		vecToTagt = { 0,0,0 };
		Pos() = realPos->Pos();
		sequence = 1;
	}
}

void Valphalk::S_BackWingAtk()
{
	static int whichPattern = 0;

	if (sequence == 0) //각도 정하기
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		sequence = 3;
		case 2:		SetState(E_2210);	E2210();  break;
		case 3:		SetState(E_2210);	E2210();  break;
		case 4:		sequence = 3;
		case 5:		SetState(E_2210);	E2210();  break;
		case 6:		SetState(E_2210);	E2210();  break;
		}
	}

	if (sequence == 2) // 공격모션
	{
		switch (whichPattern)
		{
		case 1:		sequence = 3;
		case 2:		SetState(E_2211);	E2211(-XM_PIDIV2);  break;
		case 3:		SetState(E_2211);	E2211(-XM_PIDIV2);  break;
		case 4:		sequence = 3;
		case 5:		SetState(E_2211);	E2211(XM_PIDIV2);  break;
		case 6:		SetState(E_2211);	E2211(XM_PIDIV2);  break;
		}
	}

	if (sequence == 3)
	{
		if (whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		whichPattern = 0;
		ChooseNextPattern();
	}
}

void Valphalk::S_SRush()
{
	static int whichPattern = 0;
	if (sequence == 0) // 각도 정하기
	{
		whichPat = SetRadAndMirror(false);
		sequence++;
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{

		switch (whichPat)
		{
		case 1:	SetState(E_2188); E2188();  break;
		case 2:	SetState(E_2189); E2189();  break; // 왼 90
		case 3:	SetState(E_2190); E2190();  break; // 왼 180
		case 4:	SetState(E_2188); E2188();  break;
		case 5:	SetState(E_2192); E2192();  break; // 오 90
		case 6:	SetState(E_2193); E2193();  break; // 오 180
		}
	}

	if (sequence == 2) // 공격 모션
	{
		SetState(E_2200);
		E2200();
	}

	if (sequence == 3) // 마무리
	{
		whichPat = 0;
		ChooseNextPattern();
	}

}

void Valphalk::S_JetRush()
{
	static int whichPattern = 0;
	isReverse = false;

	if (sequence == 0) //각도 정하기
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2001);	E2001();  break;
		case 2:		SetState(E_2002);	E2002(-XM_PIDIV2);  break;
		case 3:		SetState(E_2003);	E2003(-XM_PI);  break;
		case 4:		SetState(E_2001);	E2001();  break;
		case 5:		SetState(E_2002);	E2002(XM_PIDIV2);  break;
		case 6:		SetState(E_2003);	E2003(XM_PI);  break;
		}
	}

	if (sequence == 2) // 돌진모션
	{
		SetState(E_2013);	E2013();
	}

	if (sequence == 3) // 돌진 브레이크 모션
	{
		SetState(E_2017);	E2017();
	}

	if (sequence == 4) // 바닥에 착지 모션
	{
		SetState(E_2019);	E2019();
	}

	if (sequence == 5) // 마무리
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		whichPattern = 0;
		ChooseNextPattern();
	}
}

void Valphalk::S_Bite()
{
	static int whichPattern = 0;

	if (sequence == 0) // 사이드스탭 할지 앞다리 찍기 할지 판단
	{
		if ((realPos->Pos() - target->GlobalPos()).Length() < 500)
			sequence = 5;
		else
			sequence++;
	}

	if (sequence == 1) // 꺠물기 각도 정하기
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 2) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2173);  E2173();  break;
		case 2:		SetState(E_2174);  E2174(-XM_PIDIV2);  break;
		case 3:		SetState(E_2175);  E2175(-XM_PI);	break;
		case 4:		SetState(E_2173);  E2173();  break;
		case 5:		SetState(E_2174);  E2174(XM_PIDIV2);  break;
		case 6:		SetState(E_2175);  E2175(XM_PI);	break;
		}
	}

	if (sequence == 3) // 공격 모션
	{
		SetState(E_2185);	E2185();
	}

	if (sequence == 4)
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 5) // 백스탭 위치 계산
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 200 + realPos->Right() * 606 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 6) // 백스탭
	{
		SetState(E_2124);
		E2124(vecToTagt);
	}

	if (sequence == 7) // 백스탭마무리
	{
		vecToTagt = { 0,0,0 };
		Pos() = realPos->Pos();
		sequence = 1;
	}
}

void Valphalk::S_Transform()
{
}

void Valphalk::S_RunAndBite()
{
	static int whichPattern = 0;

	if (sequence == 0) // 각도 정하기
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_0059);  E0059();				break;
		case 2:		SetState(E_0060);  E0060(-XM_PIDIV2);	break; // 왼쪽 90
		case 3:		SetState(E_0061);  E0061(-XM_PI);		break; // 왼쪽 180
		case 4:		SetState(E_0059);  E0059();				break;
		case 5:		SetState(E_0060);  E0060(XM_PIDIV2);	break;
		case 6:		SetState(E_0061);  E0061(XM_PI);		break;
		}
	}

	if (sequence == 2) // 공격 모션
	{
		SetState(E_0071);
		E0071();
	}

	if (sequence == 3) // 공격 모션
	{
		SetState(E_2171);
		E2171();
	}

	if (sequence == 4) // 마무리
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		whichPattern = 0;
		ChooseNextPattern();
	}


}

void Valphalk::B_SwingAtk() 
{
	static int whichPattern = 0;
	
	if (sequence == 0) // 각도 정하기
	{
		if ((realPos->Pos() - target->GlobalPos()).Length() < 900) // 지나치게 가까운 경우
			sequence = 4;
		else
		{
			whichPattern = SetRadAndMirror(true);
			sequence++;
		}
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2091);  E2091();				break;
		case 2:		SetState(E_2092);  E2092(-XM_PIDIV2);	break; // 왼쪽 90
		case 3:		SetState(E_2093);  E2093(-XM_PI);		break; // 왼쪽 180
		case 4:		SetState(E_2091);  E2091();				break;
		case 5:		SetState(E_2092);  E2092(XM_PIDIV2);	break;
		case 6:		SetState(E_2093);  E2093(XM_PI);		break;
		}
	}

	if (sequence == 2) // 공격 모션
	{
		SetState(E_2103);
		if(whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			E2103(XM_PIDIV2);
		else 
			E2103(-XM_PIDIV2);
	}

	if (sequence == 3) // 마무리
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 4) // 백스탭
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 1600 + realPos->Right() * 1106 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 5) // 백스탭
	{
		SetState(E_2253);
		E2253(vecToTagt);
	}

	if (sequence == 6) // 백스탭마무리
	{
		sequence = 0;
	}
}

void Valphalk::B_WingAtk()
{
	static int whichPattern = 0;
	if (sequence == 0) // 각도 정하기
	{
		whichPattern = SetRadAndMirror(false);
		if ((realPos->Pos() - target->GlobalPos()).Length() < 400)
			sequence = 4;
		else
			sequence++;
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:	SetState(E_2129); E2129();  break;
		case 2:	SetState(E_2130); E2130();  break;
		case 3:	SetState(E_2131); E2131();  break;
		case 4:	SetState(E_2129); E2129();  break;
		case 5:	SetState(E_2133); E2133();  break;
		case 6:	SetState(E_2134); E2134();  break;
		}
	}

	if (sequence == 2) // 공격 모션
	{
		SetState(E_2141);
		E2141();
	}

	if (sequence == 3) // 마무리
	{
		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 4) // 백스탭
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 900 + realPos->Right() * 1106 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 5) // 백스탭
	{
		SetState(E_2253);
		E2253(vecToTagt);
	}

	if (sequence == 6) // 백스탭마무리
	{
		sequence = 0;
	}


}

void Valphalk::B_DownBlast()
{
	static int whichPattern = 0;
	if (sequence == 0) // 각도 정하기
	{
		whichPattern = SetRadAndMirror(false);
		sequence++;
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:	SetState(E_2381); E2381();  break;
		case 2:	SetState(E_2382); E2382();  break;
		case 3:	SetState(E_2131); E2381();  break;
		case 4:	SetState(E_2381); E2381();  break;
		case 5:	SetState(E_2383); E2383();  break;
		case 6:	SetState(E_2381); E2381();  break;
		}
	}

	if (sequence == 2) // 공격 모션
	{
		SetState(E_2082);
		E2082();
	}

	if (sequence == 3) // 마무리
	{
		whichPattern = 0;
		ChooseNextPattern();
	}

}

void Valphalk::B_FwdBlast()
{
}

void Valphalk::B_EnergyBlast()
{
}

void Valphalk::B_Dumbling()
{
	static int whichPattern = 0;
	if (sequence == 0) // 각도 정했으면 방향 전환함수
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_0151);  E0151();				break;
		case 2:		SetState(E_0152);  E0152(-XM_PIDIV2);	break; // 왼쪽 90
		case 3:		SetState(E_0153);  E0153(-XM_PI);		break; // 왼쪽 180
		case 4:		SetState(E_0151);  E0151();				break;
		case 5:		SetState(E_0152);  E0152(XM_PIDIV2);	break;
		case 6:		SetState(E_0153);  E0153(XM_PI);		break;
		}
	}

	if (sequence == 2) // 공격 모션
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		sequence++;
	}

	if (sequence == 3) // 공격 모션
	{

		SetState(E_2151);
		E2151();

	}

	if (sequence == 4) // 공격 모션 + 포격
	{
		forwardBoom->Pos() = 0;		
		SetState(E_2152);
		E2152();
	}


	if (sequence == 5) // 공격 모션
	{
		forwardBoom->Pos() = forwardBoomPosInit;
		SetState(E_2153);
		E2153();
	}

	if (sequence == 6) // 마무리
	{
		ChooseNextPattern();
	}
}

void Valphalk::B_Trnasform()
{
}

void Valphalk::HS_FlyBlast()
{
	OtherPlay2 = true;
	static int whichPattern = 0;

	if (sequence == 0)
	{
		SetState(E_2265);
		E2265();
	}

	if (sequence == 1)
	{
		SetState(E_2267);
		E2267();
	}

	if (sequence == 2)
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 3)
	{
		switch (whichPattern)
		{
		case 1: SetState(E_2280); E2280(); break;
		case 2:	SetState(E_2281); E2281(-XM_PIDIV2); break;
		case 3:	SetState(E_2282); E2282(-XM_PI); break;
		case 4:	SetState(E_2280); E2280(); break;
		case 5:	SetState(E_2281); E2281(XM_PIDIV2); break;
		case 6:	SetState(E_2282); E2282(XM_PI); break;
		}
	}

	if (sequence == 4)
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		sequence++;
	}

	if (sequence == 5)
	{
		SetState(E_2286); E2286();
	}

	if (sequence == 6)
	{
		SetState(E_2288); E2288();
	}

	if (sequence == 7)
	{
		SetState(E_2290); E2290();
	}

	if (sequence == 8) // 마무리
	{
		whichPattern = 0;
		ChooseNextPattern();
	}
}

void Valphalk::HS_FlyFallAtk()
{
	static int whichPattern = 0;

	if (sequence == 0) 
	{
		SetState(E_2265);
		EX2265();
		
	}

	if (sequence == 1) 
	{
		SetState(E_2267);
		EX2267();
	}


	if (sequence == 2) // 각도 정했으면 방향 전환함수
	{
		whichPattern = SetRadAndMirror(false);

		Vector3 groundPos = Vector3(realPos->Pos().x, 0, realPos->Pos().z);
		float length = (target->GlobalPos() - groundPos).Length();

		if (length < 2000)
			sequence = 8;
		else
			sequence++;
	}

	if (sequence == 3) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2270);  EX2270();			break;
		case 2:		SetState(E_2271);  EX2271(-XM_PIDIV2);	break; // 왼쪽 90
		case 3:		SetState(E_2272);  EX2272(-XM_PI);		break; // 왼쪽 180
		case 4:		SetState(E_2270);  EX2270();			break;
		case 5:		SetState(E_2274);  EX2274(XM_PIDIV2);	break;
		case 6:		SetState(E_2275);  EX2275(XM_PI);		break;
		}
	}

	if (sequence == 4) // 공격 모션
	{
		SetState(E_2276);
		EX2276();
	}

	if (sequence == 5) // 공격 모션
	{
		SetState(E_2277);
		EX2277(yDifference);
	}


	if (sequence == 6) // 공격 모션
	{
		Pos().y = 0;
		EX2278();
	}

	if (sequence == 7) // 마무리
	{

		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 8)
	{
		if (radBtwTarget > -XM_PIDIV2 && radBtwTarget <= 0) // 왼쪽 90도
		{
			whichPattern = 1;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > -XM_PI && radBtwTarget <= -XM_PIDIV2) // 왼뒤쪽 90도 
		{
			whichPattern = 2;
			radDifference = radBtwTarget + XM_PI;
		}
		else if (radBtwTarget > 0 && radBtwTarget <= XM_PIDIV2) // 전방 오쪽 90도
		{
			whichPattern = 3;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > XM_PIDIV2&& radBtwTarget <= XM_PI) // 오른뒤쪽 90도
		{
			whichPattern = 4;
			radDifference = radBtwTarget - XM_PI;
		}

		sequence++;
	}

	if (sequence == 9)
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2371);  EX2371();		break;
		case 2:		SetState(E_2372);  EX2372(-XM_PI);	break;
		case 3:		SetState(E_2371);  EX2371();		break;
		case 4:		SetState(E_2373);  EX2373(XM_PI);	break;
		}
	}

	if (sequence == 10) // 공격 모션
	{
		SetState(E_2374);
		EX2374();
	}

	if (sequence == 11) // 공격 모션
	{
		SetState(E_2375);
		EX2375();
	}

	if (sequence == 12) // 공격 모션
	{
		Pos().y = 0;
		EX2376();
	}

	if (sequence == 13) // 마무리
	{
		whichPattern = 0;
		ChooseNextPattern();
	}

}

void Valphalk::HS_FlyWingBlast() // 호버링 후 전방 손바닥 폭발
{

}

void Valphalk::HB_LaserBlast() // 날개 찍기 오래 유지
{
	static int whichPattern = 0;
	//combo = true;
	if (sequence == 0) // 각도 정하기
	{
		whichPattern = SetRadAndMirror(false);
		sequence++;
	}

	if (sequence == 1) // 각도 정했으면 방향 전환함수
	{
		switch (whichPattern)
		{
		case 1:	SetState(E_2129); E2129();  break;
		case 2:	SetState(E_2130); E2130();  break;
		case 3:	SetState(E_2131); E2131();  break;
		case 4:	SetState(E_2129); E2129();  break;
		case 5:	SetState(E_2133); E2133();  break;
		case 6:	SetState(E_2134); E2134();  break;
		}
	}

	if (sequence == 2) // 공격 모션
	{
		SetState(E_2403);
		E2403();
	}

	if (sequence == 3) // 마무리
	{
		whichPattern = 0;
		ChooseNextPattern();
	}
}

void Valphalk::FindRoar()
{
}

void Valphalk::AngerRoar()
{
}

void Valphalk::E0003() // 평상시 대기
{
	PLAY;

	if (RATIO > 0.98)
		sequence++;
}

void Valphalk::E0007() // 탈진
{
	PLAY;
}

void Valphalk::E0043() // 앞으로 전진
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0055);
}

void Valphalk::E0044() // 좌회전
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0045() // 뒤로 회전
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0055()//걷기 Loop
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
		// 계속 걷게 하려면 수정 필요
}

void Valphalk::E0059()//앞으로 뛰기
{
	PLAY;

	if (RATIO > 0.0134f && RATIO < 0.5)
		RotateToTarget(0.0134f, 0.414f);


	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::E0060(float degree)//앞으로 뛰다가 좌회전
{
	PLAY;

	if (RATIO > 0.0134f && RATIO < 0.5f)
		RotateToTarget(0.0134f, 0.414f);


	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E0061(float degree)//앞으로 뛰다가 뒤돌기(좌회전)
{
	PLAY;

	if (RATIO > 0.0134f && RATIO < 0.5f)
		RotateToTarget(0.0134f, 0.414f);


	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E0071()//뛰기Loop
{
	PLAY;
	
	if ((target->GlobalPos() - realPos->Pos()).Length() < 4500.0f)
	{
		if (!playOncePerPattern)
		{
			if (RATIO < 0.106)
				playRatioForE0071 = 0.106;
			else if (RATIO > 0.106 && RATIO < 0.36)
				playRatioForE0071 = 0.36;
			else if (RATIO > 0.36 && RATIO < 0.62)
				playRatioForE0071 = 0.62;
			else if (RATIO > 0.62 && RATIO < 0.88)
				playRatioForE0071 = 0.88;
			else 
				playRatioForE0071 = 0.106;

			playOncePerPattern = true;
		}

		if (RATIO > playRatioForE0071)
		{
			sequence++;
			playRatioForE0071 = 0.0f;
			playOncePerPattern = false;
		}
	}


	if (RATIO > 0.96)
	{
		Loop();
	}
		//계속 뛰게 하려면 수정 필요
}

void Valphalk::E0097() // 정지 (공격 준비)
{
	PLAY;
}

void Valphalk::E0098(float degree) // 급좌회전 턴
{
	PLAY;
	if (RATIO > 0.0176f && RATIO < 0.176f)
		RotateToTarget(0.0176f, 0.176f);

	if (RATIO > 0.98)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E0099(float degree) // 급뒤로 턴
{
	PLAY;
	if (RATIO > 0.99)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E0146() //대기상태에서 포격모드로 변환
{
	PLAY;
	if (RATIO > 0.98)
		//SetState(E_2144); --> 변환 후 바로 공격해야한다면 수정 필요
		SetState(E_0151);
		//SetState(E_0003);
}

void Valphalk::E0147()//포격형 -> 참격형 변환
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0151()//포격상태 Idle
{
	PLAY;

	if (RATIO > 0.22f && RATIO < 0.62f)
		RotateToTarget(0.22f, 0.49f);

	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E0152(float degree)//포격상태 좌회전
{
	PLAY;

	if (RATIO > 0.22f && RATIO < 0.62f)
		RotateToTarget(0.22f, 0.49f);

	if (RATIO > 0.98)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E0153(float degree)//포격상태 뒤로회전
{
	PLAY;

	if (RATIO > 0.22f && RATIO < 0.62f)
		RotateToTarget(0.22f, 0.49f);

	if (RATIO > 0.99)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E0164()//뒷걸음질
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0165()//뒷걸음질 치고 왼쪽봄
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0166()//뒷걸음질 치고 오른쪽 봄
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0171()//포격형 뒷걸음질
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0151);
}

void Valphalk::E0172()//포격형 뒷걸음질 치고 왼쪽봄
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0151);
}

void Valphalk::E0173()//포격형 뒷걸음질 치고 오른쪽 봄
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0151);
}

void Valphalk::E0178()//포격형->참격형 변환하면서 뒷걸음질
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0179()//포격형->참격형 변환하면서 뒷걸음질 치고 왼쪽봄
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0180()//포격형->참격형 변환하면서 뒷걸음질 치고 오른쪽 봄
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0186()//포격형->참격형 변환하면서 앞으로 뛰기
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0187()//포격형->참격형 변환하면서 앞으로 뛰다가 좌회전
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0188()//포격형->참격형 변환하면서 앞으로 뛰다가 뒤돌기
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E1151() // 습격준비
{
	PLAY;
	if (RATIO < 0.1)
		Sounds::Get()->Play("em086_05_fx_media_25", 0.5f);
	if (RATIO > 0.99)
	{
		sequence++;
	}
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

	if (stormTime > 12 && sequence == 1)
		sequence++;
}

void Valphalk::E1163() // 하강
{	
	Rot().x = -.8f;
	Pos().y -= 25000 * DELTA;
	Pos().z += 1000 * DELTA;
	if (Pos().y > target->Pos().y)
	{
		Pos().x = target->Pos().x;
		Pos().z = target->Pos().z - 500;
		//Pos().y = realPos->Pos().y;
		//realPos->Pos().y = Pos().y;
		//Pos() = realPos->Pos();
		//Pos().y = realPos->Pos().y;
		PLAY;
	}
	else
	{
		sequence++;
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
		ChooseNextPattern();
	}

}

void Valphalk::E2001()//뒤로 후퇴 후 돌진 준비
{
	PLAY;

	if (RATIO > 0.070f && RATIO < 0.581f)
		RotateToTarget(0.070f, 0.581f);

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2002(float degree)//2001를 왼쪽 90도로 방향틀고 실행
{
	PLAY;

	if (RATIO > 0.070f && RATIO < 0.581f)
		RotateToTarget(0.070f, 0.581f);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2003(float degree)//2001를 왼쪽 180도로 방향틀고 실행
{
	PLAY;
	
	if (RATIO > 0.098f && RATIO < 0.637f)
		RotateToTarget(0.098f, 0.637f);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2013()//돌진 시작
{
	PLAY;

	SetColliderAttack(HEAD, 0.95);
	SetColliderAttack(NECK, 0.95);
	SetColliderAttack(CHEST, 0.95);

	if (RATIO > 0.95)
	{
		sequence++;
	}
}

void Valphalk::E2015()//돌진중 Loop
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_2017);
}

void Valphalk::E2017()//돌진 브레이크
{
	Pos().y = 0;

	SetColliderAttack(HEAD, 0.263);
	SetColliderAttack(NECK, 0.263);
	SetColliderAttack(CHEST, 0.263);

	PLAY;

	if (RATIO > 0.95)
	{
		sequence++;
	}
}

void Valphalk::E2019()//브레이크 후 바닥 착지 완료
{
	Pos().y = 0;

	PLAY;

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2020()//2017 동작을 하고 뒤를 쳐다봄
{
	PLAY;

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2022()//2020 후 브레이크하고 뒤를 쳐다봄
{
	Pos().y = 0;

	PLAY;

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2027()//앞으로 뛰다가 돌진준비
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2032()//왼쪽으로 뛰다가 돌진준비
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2033()//오른쪽으로 뛰다가 돌진준비
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2038() // 날개 찌르기
{
	combo = false;

	PLAY;

	if (RATIO > 0.644 && RATIO < 0.95)
	{
		SetColliderAttack(RWING, 0.95);
	}

	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E2040() // 찌르기 준비
{
	PLAY;

	if (RATIO > 0.358f && RATIO < 0.698f)
		RotateToTarget(0.358f, 0.698f);

	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E2041(float degree)//왼쪽보고 찌르기 준비
{
	PLAY;

	if (RATIO > 0.293f && RATIO < 0.724f)
		RotateToTarget(0.293f, 0.724f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2042(float degree)//왼쪽으로 뒤돌고 찌르기 준비
{
	PLAY;

	if (RATIO > 0.286f && RATIO < 0.746f)
		RotateToTarget(0.286f, 0.746f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2044(float degree)//오른쪽보고 찌르기 준비
{
	PLAY;

	if (RATIO > 0.293f && RATIO < 0.724f)
		RotateToTarget(0.293f, 0.724f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2045(float degree)//오른쪽으로 뒤돌고 찌르기 준비
{
	PLAY;

	if (RATIO > 0.286f && RATIO < 0.746f)
		RotateToTarget(0.286f, 0.746f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2054() // 찌르기 날개 회수
{
	PLAY;

	if (RATIO > 0.97)
		sequence++;
}

void Valphalk::E2079()
{
	PLAY;
	float randX = Random(target->Pos().x - 10, target->Pos().x + 10);
	float randY = Random(target->Pos().z - 10, target->Pos().z + 10);	
	
	for (int i = 0; i < bullets.size(); ++i)
	{
		if (RATIO > 0.1 + ((DELTA + (float)i) * 0.03f))
		{
			bullets[i]->Pos().x = Lerp(bullets[i]->Pos().x, randX, 0.0007f);
			bullets[i]->Pos().z = Lerp(bullets[i]->Pos().z, randY, 0.0007f);

			bullets[i]->Pos().y -= 500 * DELTA;
		}

		if (bullets[i]->Pos().y < 0)
			bullets[i]->SetActive(false);
	}
	
	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::E2056() // 찌르고 그 날개 로 한바퀴 돌기
{
	PLAY;

	if (RATIO > 0.361 && RATIO < 0.617)
	{
		SetColliderAttack(RWING, 0.617);
	}

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += XM_PIDIV2;
	}
}

void Valphalk::E2106()// 오른발 들고 정면 찍기 준비 자세
{
	combo = true;

	PLAY;

	if (RATIO > 0.222f && RATIO < 0.481f)
		RotateToTarget(0.222f, 0.481f);

	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E2107(float degree)//오른발 들고 정면에서 왼쪽 보고 찍기 준비 자세
{
	combo = true;

	PLAY;

	if (RATIO > 0.222f && RATIO < 0.481f)
		RotateToTarget(0.222f, 0.481f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2108(float degree)//오른발 들고 정면에서 뒤쪽 보고 찍기 준비 자세
{
	combo = true;

	PLAY;

	if (RATIO > 0.250f && RATIO < 0.730f)
		RotateToTarget(0.250f, 0.730f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2118()//앞다리 찍기 공격
{
	PLAY;

	if (RATIO > 0.167 && RATIO < 0.367)
	{
		SetColliderAttack(RLEG1_FOOT, 0.367);
	}

	if (RATIO > 0.97)
		sequence++;
}

void Valphalk::E2121()//왼쪽 날개 들었다가 찍은다음 살짝 일어나서 다시 자세잡음
{
	PLAY;

	if (RATIO > 0.277 && RATIO < 0.408)
	{
		SetColliderAttack(LWING, 0.408);
	}

	if (RATIO > 0.97)
	{
		sequence++;
		combo = false;
	}
}

void Valphalk::E2124(Vector3 destVec)
{
	PLAY;

	if (RATIO > 0.074f && RATIO < 0.37f)
	{
		Pos() = Lerp(Pos(), destVec, 3 * DELTA);

	}


	if (RATIO > 0.95)
	{
		Rot().y -= XM_PIDIV4;
		sequence++;
	}
}

void Valphalk::E2091()
{
	PLAY;

	if (RATIO > 0.0134f && RATIO < 0.414f)
		RotateToTarget(0.0134f, 0.414f);

	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::E2092(float degree) //90도 회전 
{
	PLAY;

	if (RATIO > 0.0176f && RATIO < 0.176f)
		RotateToTarget(0.0176f, 0.176f);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2093(float degree) // 180도
{
	PLAY;

	if (RATIO > 0.0176f && RATIO < 0.53f)
		RotateToTarget(0.0176f, 0.53f);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2103(float degree) // 휘두르기 공격
{
	PLAY;

	if (RATIO < 0.15)
	{
		SetColliderAttack(RWING, 0.15);
	}

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2144() // 전방 폭격 시작
{
	combo = true;
	PLAY;
	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::E2145() // 전방 폭격 시전 후 백스텝
{
	forwardBoom->SetActive(true);
	PLAY;
	if (RATIO > 0.6f)
		forwardBoom->SetActive(false);

	if (RATIO > 0.98)
	{
		sequence++;
		//SetState(E_2146);
	}
}

void Valphalk::E2146() // 전방 폭격 후 날개 접으면서 착지
{
	PLAY;
	if (RATIO > 0.98)
	{
		combo = false;
		sequence++;
		ChooseNextPattern();
		//SetState(E_0003);
	}
}

void Valphalk::E2171()
{
	PLAY;

	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E2129()  // 전방 앞다리 치기 준비
{
	PLAY;

	if (RATIO > 0.26f)
		RotateToTarget(0.26, 0.98f);

	if (RATIO > 0.97)
	{
		sequence++;
		Pos() = realPos->Pos();
	}
}

void Valphalk::E2130() // 왼 90
{
	PLAY;

	if (RATIO < 0.2f)
		RotateToTarget(0, 0.2f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y -= XM_PIDIV2;
	}
}

void Valphalk::E2131() //왼 180
{
	PLAY;

	if (RATIO < 0.435f)
		RotateToTarget(0, 0.435f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y -= XM_PI;
	}
}

void Valphalk::E2133() // 오 90
{
	PLAY;

	if (RATIO < 0.2f)
		RotateToTarget(0, 0.2f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += XM_PIDIV2;
	}
}

void Valphalk::E2134() // 오 180
{
	PLAY;

	if (RATIO < 0.435f)
		RotateToTarget(0, 0.435f);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += XM_PI;
	}
}

void Valphalk::E2141()
{
	PLAY;

	if (RATIO > 0.056 && RATIO < 0.09)
	{
		SetColliderAttack(RLEG1_FOOT, 0.09);
	}

	if (RATIO > 0.256 && RATIO < 0.296)
	{
		SetColliderAttack(RWING, 0.296);
	}


	if (RATIO > 0.97)
	{
		sequence++;
	}

}

void Valphalk::E2151()
{
	PLAY;
	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E2152()
{
	PLAY;
	if (RATIO > 0.5 && RATIO < 0.51)
		forwardBoom->SetActive(true);
	if (RATIO > 0.6)
		forwardBoom->SetActive(false);

	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E2153()
{
	PLAY;

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += XM_PI;
	}
}

void Valphalk::E2173()
{
	combo = true;

	PLAY;

	if (RATIO > 0.056 && RATIO < 0.733f)
		RotateToTarget(0.056, 0.733f);

	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E2174(float degree)// 정면 보다가 왼쪽 보고 오른발 들기
{
	combo = true;

	PLAY;

	if (RATIO > 0.056 && RATIO < 0.733f)
		RotateToTarget(0.056, 0.733f);

	if (RATIO > 0.97)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E2175(float degree)// 정면 보다가 오른쪽 보고 오른발 들기
{
	combo = true;

	PLAY;

	if (RATIO > 0.056 && RATIO < 0.733f)
		RotateToTarget(0.056, 0.733f);

	if (RATIO > 0.97)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E2185()// 들었던 발을 내려찍으며 깨물기
{
	PLAY;
	
	if (RATIO > 0.121 && RATIO < 0.331)
	{
		SetColliderAttack(HEAD, 0.331);
	}

	if (RATIO > 0.97)
	{
		combo = false;
		sequence++;
	}
}

void Valphalk::E2188()//정면 보고 왼발 들기
{
	PLAY;

	if (RATIO > 0.16 && RATIO > 0.8) 
		RotateToTarget(0.16, 0.7);


	if (RATIO > 0.97)
		sequence++;
}

void Valphalk::E2189()//정면에서 왼쪽 보고 왼발 들기
{
	PLAY;

	if (RATIO > 0.19 && RATIO > 0.8)
		RotateToTarget(0.19, 0.7);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y -= XM_PIDIV2;
	}
}

void Valphalk::E2190()//정면에서 왼쪽으로 돌면서 뒤보고 왼발 들기
{
	PLAY;

	if (RATIO > 0.1 && RATIO > 0.8)
		RotateToTarget(0.1, 0.7);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y -= XM_PI;
	}
}

void Valphalk::E2192()//정면에서 오른쪽 보고 왼발 들기
{
	PLAY;

	if (RATIO > 0.19 && RATIO > 0.8)
		RotateToTarget(0.19, 0.7);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += XM_PIDIV2;
	}
}

void Valphalk::E2193()//정면에서 오른쪽으로 돌면서 뒤보고 왼발 들기
{
	PLAY;

	if (RATIO > 0.1 && RATIO > 0.8)
		RotateToTarget(0.1, 0.7);

	if (RATIO > 0.97)
	{
		sequence++;
		Rot().y += XM_PI;
	}
}

void Valphalk::E2200()//S자 몸통박치기
{
	PLAY;


	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::E2210()//왼쪽 90도 날개찍기 준비동작
{
	combo = true;

	PLAY;

	if (RATIO > 0.700f && RATIO < 0.97f)
		RotateToTarget(0.700f, 0.97f);

	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E2211(float degree)//왼쪽 90도 날개찍기 공격동작
{
	PLAY;

	if (RATIO < 0.105f)
		RotateToTarget(0.000f, 0.105f);

	if (RATIO > 0.117 && RATIO < 0.185)
	{
		SetColliderAttack(RWING, 0.185);
	}

	if (RATIO > 0.97)
	{
		combo = false;
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E2265()
{
	PLAY;

	if (RATIO > 0.97f)
	{
		sequence++;
		Count = 1;
	}
}

void Valphalk::E2267()
{
	PLAY;

	if (RATIO < 0.16f)
	{
		Pos().y = Lerp(Pos().y, 600, 10 * DELTA);
	}

	if (RATIO > 0.98f)
	{
		Rot().y -= 2.0933f;
		sequence++;
		Count = 1;
	}
}

void Valphalk::EX2265()
{
	PLAY;

	if (RATIO > 0.98)
	{
		sequence++;
	}

}

void Valphalk::EX2267()
{
	PLAY;

	if (RATIO < 0.16)
	{
		Pos().y = Lerp(Pos().y, 600, 10 * DELTA);
	}

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y -= 2.0933f;
	}
}

void Valphalk::EX2270(float degree)
{
	PLAY;

	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::EX2271(float degree) // 왼 90
{
	PLAY;

	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::EX2272(float degree)
{
	PLAY;

	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::EX2274(float degree)
{
	PLAY;

	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::EX2275(float degree)
{
	PLAY;

	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::EX2276()
{
	PLAY;

	if (RATIO > 0.995)
	{
		sequence++;
		Vector3 groundPos = Vector3(realPos->Pos().x, 0, realPos->Pos().z);
		float length = (target->GlobalPos() - groundPos).Length();
		yDifference = (1 - (length / 3427)) * 1000;
		if (yDifference > 500)
			yDifference = 500;
		if (yDifference < 0)
			yDifference = 0;
	}
}

void Valphalk::EX2277(float y)
{
	PLAY;
	SetColliderAttack(BODY, 0.93);
	SetColliderAttack(CHEST, 0.93);
	SetColliderAttack(HEAD, 0.93);
	SetColliderAttack(RLEG1, 0.93);

	Pos().y -= y * DELTA;

	if (realPos->Pos().y < 0)
	{
		preState = curState;
		curState = E_2278;
		colliders[BODY]->isAttack = false;
		colliders[CHEST]->isAttack = false;
		colliders[HEAD]->isAttack = false;
		colliders[RLEG1]->isAttack = false;


		sequence++;
		return;
	}


	if (RATIO > 0.93)
	{
		Loop();
	}
}

void Valphalk::EX2278()
{
	PLAY;

	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::E2270()
{
	PLAY;

	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		SetState(E_2276);
		Count = 1;
	}
}

void Valphalk::E2271()
{
}

void Valphalk::E2272()
{
}

void Valphalk::E2274()
{
}

void Valphalk::E2275()
{
}

void Valphalk::E2276()
{
	PLAY;

	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		SetState(E_2277);
		Count = 1;
	}
}

void Valphalk::E2277()
{
	if (Pos().y > 400.0f)
	{
		//Pos().y = GetTranslationByNode(1).y;
		Pos() = GetTranslationByNode(1);
		//SetState(E_2277);
		//SetState(E_2277);
	}
	else
	{
		SetState(E_2278);
		Pos().y = 0.0f;
		Count = 1;
	}
}

void Valphalk::E2278()
{

	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		SetState(E_4013);
		combo = false;
	}
}

void Valphalk::E2280()
{
	PLAY;

	if (RATIO > 0.17f && RATIO < 0.66f)
		RotateToTarget(0.17f, 0.56f);


	if (RATIO > 0.97f)
	{
		sequence++;
		Count = 1;
	}
}

void Valphalk::E2281(float degree)
{
	PLAY;

	if (RATIO > 0.17f && RATIO < 0.66f)
		RotateToTarget(0.17f, 0.56f);


	if (RATIO > 0.97f)
	{
		Rot().y += degree;
		sequence++;
		Count = 1;
	}
}

void Valphalk::E2282(float degree)
{
	PLAY;

	if (RATIO > 0.17f && RATIO < 0.66f)
		RotateToTarget(0.17f, 0.56f);


	if (RATIO > 0.97f)
	{
		Rot().y += degree;
		Count = 1;
		sequence++;
	}
}

void Valphalk::E2286()
{
	PLAY;

	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		sequence++;

	}
}

void Valphalk::E2288()
{
	PLAY;


	if (realPos->Pos().y < 0.0f)
	{
		Pos().y = 0.0f;

		sequence++;
		return;
	}
	if (RATIO > 0.93)
	{
		Loop();
	}
}

void Valphalk::E2290()
{
	PLAY;

	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		combo = false;
		sequence++;
	}
}

void Valphalk::E2354(float degree) // 풀버스트 전방
{
	combo = false;
	PLAY;
	if (RATIO > 0.0176f && RATIO < 0.876f)
		RotateToTarget(0.0176f, 0.876f);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;

		//Pos() = realPos->Pos();
	}
		
}

void Valphalk::E2356(float degree) // 풀버스트 좌회전 뒤로 돌기
{
	PLAY;
	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2359(float degree) // 풀버스트 우회전 뒤로 돌기
{
	PLAY;
	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2361() // 풀버스트 준비
{
	PLAY;
	//fullBurst->Rot().y = head->Rot().y;
	fullBurst->Rot() = fullBurstRot;
	if (RATIO > 0.98)
	{
		sequence++;
		//Pos() = realPos->Pos();
	}

}

void Valphalk::E2367() // 풀버스트 발사
{
	PLAY;

	if(RATIO>0.2)
	fullBurst->SetActive(true);

	if (RATIO > 0.8)
	{
		fullBurst->Pos().y += 7000 * DELTA;
		fullBurst->Rot().x += 0.82 * DELTA;
	}
	if (RATIO > 0.98)
	{
		sequence++;
		//Pos() = realPos->Pos();
	}
	
}

void Valphalk::E2368() // 풀버스트 마무리
{
	PLAY;
	if(RATIO>0.2)
	fullBurst->SetActive(false);

	if (RATIO > 0.98)
	{
		combo = false;		
		Pos() = realPos->Pos();
		fullBurst->Pos() = fullBurstPos;
		fullBurst->Rot() = fullBurstRot;
		fullBurst->Scale() = fullBurstScale;		
		ChooseNextPattern();
	}
}

void Valphalk::E2253(Vector3 destVec)//왼쪽 보면서 오른쪽으로 백스탭
{
	PLAY;

	if (RATIO > 0.074f && RATIO < 0.37f)
	{
		Pos() = Lerp(Pos(), destVec, 3 * DELTA);
	}


	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y -= XM_PIDIV4;
	}
}

void Valphalk::E2371()
{
	if (Count == 1)
	{
		Rot().y = Rot().y - 1.9f;
		Count = 2;
	}

	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		SetState(E_2374);
		Count = 1;
	}
}

void Valphalk::E2372()
{
}

void Valphalk::E2373()
{
}

void Valphalk::EX2371()
{
	PLAY;

	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::EX2372(float degree)
{
	PLAY;

	if (RATIO > 0.16 && RATIO < 0.79)
		RotateToTarget(0.16, 0.79);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::EX2373(float degree)
{
	PLAY;

	if (RATIO > 0.16 && RATIO < 0.79)
		RotateToTarget(0.16, 0.79);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2374()
{
	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);

		SetState(E_2375);
		Count = 1;
	}
}

void Valphalk::E2375()
{
	if (Pos().y > 0.98f)
	{
		Pos().y = GetTranslationByNode(1).y;
		Count = 1;

	}
	else
	{
		Pos().y = 0.0f;
		SetState(E_2376);
		Count = 1;

	}
}

void Valphalk::E2376()
{
	if (RATIO > 0.98f)
	{
		SetState(E_4013);
		combo = false;
		Count = 1;
	}
}

void Valphalk::EX2374()
{
	PLAY;

	if (RATIO > 0.95)
		sequence++;
}

void Valphalk::EX2375()
{
	PLAY;

	if (realPos->Pos().y < 0)
	{
		preState = curState;
		curState = E_2376;

		sequence++;
		return;
	}

	if (RATIO > 0.93)
	{
		Loop();
	}
}

void Valphalk::EX2376()
{
	PLAY;

	if (RATIO > 0.98)
		sequence++;
}

void Valphalk::E2381()
{
	PLAY;

	if (RATIO > 0.98)
		sequence++;
}

void Valphalk::E2382()
{
	PLAY;

	if (RATIO > 0.98)
	{
		Rot().y -= XM_PIDIV2;
		sequence++;
	}
}

void Valphalk::E2383()
{
	PLAY;

	if (RATIO > 0.98)
	{
		Rot().y += XM_PIDIV2;
		sequence++;
	}
}

void Valphalk::E2082()
{
	PLAY;

	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::E2403()
{
	PLAY;

	if (RATIO > 0.056f && RATIO < 0.09f)
	{
		SetColliderAttack(RLEG1_FOOT, 0.09f);
	}

	if (RATIO > 0.256f && RATIO < 0.684f)
	{
		SetColliderAttack(RWING, 0.684f);
	}

	if (RATIO > 0.97f)
	{
		sequence++;
		combo = false;
		Count = 1;
	}
}

void Valphalk::E3001() // 작은 데미지 피격
{
	PLAY;
}

void Valphalk::E3023() // 사망
{
	PLAY;
	if (RATIO > 0.99)			
	isPlay = false;
	
	//if (RATIO > 0.98)
		
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
