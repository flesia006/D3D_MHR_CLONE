#include "Framework.h"
#include "Scenes/ShadowScene.h"

Valphalk::Valphalk() : ModelAnimator("Valphalk")
{
	srand(static_cast<unsigned int>(time(NULL)));

	head = new Transform();
	ReadClip("E_0003");
	ReadClip("E_0007");
	// �÷��̾� �߰� ��
	ReadClip("E_0043");
	ReadClip("E_0044");
	ReadClip("E_0045");
	ReadClip("E_0055");
	// �÷��̾� �߰� ��
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
	// �Ʒ� �ִ°� ù ��ȿ
	ReadClip("E_4013");
//	ReadClip("E_22005");

	ColliderAdd();

	realPos = new CapsuleCollider(1, 0.1);
	realPos->Scale() *= 6.0f;
	realPos->UpdateWorld();

	tempCollider = new CapsuleCollider(6, 0.1);
	tempCollider->UpdateWorld();
	/////////////////////////////////////////////
	// ���� �ݶ��̴� (����ü, ���� ��)	
	bullets.resize(6);
	FOR(6)
	{
		bullets[i] = new SphereCollider();
		bullets[i]->Scale() *= 100;
		bullets[i]->SetColor(1, 0, 0);
		bullets[i]->SetActive(true);
	}

	forwardBoom = new CapsuleCollider();
	forwardBoom->Scale() *=500;
	forwardBoom->SetColor(1, 0, 0);
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
	/*
	if (KEY_DOWN('1'))
	{
		curState = E_2265;
		LookatPlayer = false;
	}

	if (KEY_DOWN('2'))
	{
		curState = E_2265;
		LookatPlayer = true;
	}

	if (KEY_DOWN('3'))
	{
		curState = E_2265;
		OtherPlay = true;
	}
	if (KEY_DOWN('4'))
	{
		curState = E_2129;
	}
	

	if (KEY_DOWN('7'))
		FullBurst();
		//SetState(E_2001);
	if (KEY_DOWN('8'))
		ForwardBoom();

	if (KEY_DOWN('9'))
		SetState(E_2173);
	*/
	//Pos().x = 2000; // �ӽ� ������
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
	
	forwardBoom->Update();
	fullBurst->UpdateWorld();

	head->Rot().y = Rot().y;
	
	ColliderNodePos();

	GetRadBtwTrgt();

	ModelAnimator::Update();
	patrolTime += DELTA;

	// Test ���� �ڵ�
	//===================================
	//if (Count <= 0)
	//{
	////	colliders[TARGETDOME]->Pos() = GetTranslationByNode(4); // Ÿ�� ���� ����
	//	StartRoar();
	//}
	//
	//// �� ���� Ȯ���ϱ� �� �ڵ�
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
	//Vector3 realpos = realPos->Pos();
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
	//	for (int i = 0; i < wings.size(); i++)
	//	{
	//		wings[i]->GUIRender();
	//	}
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

Vector3 Valphalk::GetPlayerPos() // �÷��̾� ��ġ ���� �Լ�
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
	if (sequence == 0) // ���� ���ϱ�
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}
	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
	{		
		switch (whichPattern)
		{
		case 1:		SetState(E_0151);  E0151();				break;// SetState(E_2091);  E2091();  break;
		case 2:		SetState(E_0152);  E0152(-XM_PIDIV2);	break; // ���� 90
		case 3:		SetState(E_0153);  E0153(-XM_PI);		break;
		case 4:		SetState(E_0151);  E0151();				break;//;  E2091();  break;
		case 5:		SetState(E_0152);  E0152(XM_PIDIV2);	break;
		case 6:		SetState(E_0153);  E0153(XM_PI);		break;
		}	
	}
	if (sequence == 2)
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
	if (sequence == 3)
	{
		bulletTime += DELTA;
		SetState(E_2079); E2079();		

		if (bulletTime > 2.5f)
			sequence++;
	}

	if (sequence == 4)
	{ 
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		bulletTime = 0; 
		whichPattern = 0; 
		ChooseNextPattern(); 
	}
}

void Valphalk::ForwardBoom()
{
	static int whichPattern = 0;
	if (sequence == 0) // ���� ���ϱ�
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}
	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_0151);  E0151();				break;// SetState(E_2091);  E2091();  break;
		case 2:		SetState(E_0152);  E0152(-XM_PIDIV2);	break; // ���� 90
		case 3:		SetState(E_0153);  E0153(-XM_PI);		break;
		case 4:		SetState(E_0151);  E0151();				break;//;  E2091();  break;
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
	if (sequence == 0) // ���� ���ϱ�
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}
	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2354);  E2354(); break;// SetState(E_0098);  E0098(-0.1f);  break;
		case 2:		SetState(E_0098);  E0098(-XM_PIDIV2);  break; // ���� 90
		case 3:		SetState(E_0099);  E0099(-XM_PI);  break;
		case 4:		SetState(E_2354);  E2354(); break; //SetState(E_0098);  E0098(0.1f);  break;
		case 5:		SetState(E_0098);  E0098(+XM_PIDIV2);  break;
		case 6:		SetState(E_0099);  E0099(+XM_PI);  break;
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
		if (whichPattern != 1 && whichPattern != 4) { SetState(E_2361); E2361(); }
	}
	if (sequence == 4) { SetState(E_2367); E2367(); }
	if (sequence == 5) 
	{ 
		SetState(E_2368); E2368(); 
	}
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
	
	if (sequence == 1) // ���� ���
	{
		SetState(E_2124);
		E2124(vecToTagt);
	}

	if (sequence == 2) // ������
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

	if (sequence == 1) // ���� ���
	{
		SetState(E_2253);
		E2253(vecToTagt);
	}

	if (sequence == 2) // ������
	{
		vecToTagt = { 0, 0, 0 };
		ChooseNextPattern();
	}
}

void Valphalk::Dead()
{
	SetState(E_3023);
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

	if (combo == false) // ����������϶��� ����X
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
	// Ÿ�ٰ��� �Ÿ��� ���� �Ÿ� �̻��̸� ��Ʈ�� = �����Ÿ� ������ ������ ��Ʈ���� ������, ���� �¼�	
	//preran �������� ���������� ���� �ι��̻� ������ �ʵ��� ��������.
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
	// 1. ���� ��⿭�� ������� ������ �ִ°�? (�г� ��ȿ, ���, �ʻ��) 
	// 2. �ο�� ���ΰ�? (������ �ÿ��� ��Ʈ��, �ν��ϸ� ��ȿ)
	// 
	// 3. �Ÿ��� ����? (�ʹ� �ָ� �̵� ����) 
	// 4. ���ݸ���ΰ� ���ݸ���ΰ�?
	// 5. ��� �����ΰ�?
	// 
	// 6. �г��ߴ°�? // �̰� ���Ͽ��� �����°� ���� ��
	// 7. �׷��ٸ� ������ ������ ����Ʈ�� �Ŀ� ������ ���� ����

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
	case Valphalk::S_TRANSFORM:		S_Transform();		break;
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
		if (radBtwTarget > -rot45 && radBtwTarget <= 0) // ���� ���� 45��
		{
			whichPattern = 1;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > -rot135 && radBtwTarget <= -rot45) // ���� 90��
		{
			whichPattern = 2;
			radDifference = radBtwTarget + XM_PIDIV2;
		}
		else if (radBtwTarget > -XM_PI && radBtwTarget <= -rot135) // �޵��� 45��
		{
			whichPattern = 3;
			radDifference = radBtwTarget + XM_PI;
		}
		else if (radBtwTarget > 0 && radBtwTarget <= rot45) // ���� ���� 45��
		{
			whichPattern = 4;
			radDifference = radBtwTarget;
			Scale().x *= -1;
		}
		else if (radBtwTarget > rot45 && radBtwTarget <= rot135) // ������ 90��
		{
			whichPattern = 5;
			radDifference = radBtwTarget - XM_PIDIV2;
			Scale().x *= -1;
		}
		else if (radBtwTarget > rot135 && radBtwTarget <= XM_PI) // �������� 45��
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
		if (radBtwTarget > -rot45 && radBtwTarget <= 0) // ���� 90��
		{
			whichPattern = 1;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > -rot135 && radBtwTarget <= -rot45) // ���� 90�� 
		{
			whichPattern = 2;
			radDifference = radBtwTarget + XM_PIDIV2;
		}
		else if (radBtwTarget > -XM_PI && radBtwTarget <= -rot135) // �޵��� 45��
		{
			whichPattern = 3;
			radDifference = radBtwTarget + XM_PI;
		}
		else if (radBtwTarget > 0 && radBtwTarget <= rot45) // ���� ���� 45��
		{
			whichPattern = 4;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > rot45 && radBtwTarget <= rot135) // ������ 90��
		{
			whichPattern = 5;
			radDifference = radBtwTarget - XM_PIDIV2;
		}
		else if (radBtwTarget > rot135 && radBtwTarget <= XM_PI) // �������� 45��
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

	if (sequence == 0) // ���̵彺�� ���� �մٸ� ��� ���� �Ǵ�
	{
		if ((realPos->Pos() - target->GlobalPos()).Length() < 500)
			sequence = 6;
		else
			sequence++;
	}

	if (sequence == 1) // �մٸ� ��� ���� ���ϱ�
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 2) // ���� �������� ���� ��ȯ�Լ�
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

	if (sequence == 3) // ���� ���
	{
		SetState(E_2118);	E2118();
	}

	if (sequence == 4) // �մٸ� ��� ������ + �޳��� ���
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

	if (sequence == 6) // �齺�� ��ġ ���
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 300 + realPos->Right() * 606 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 7) // �齺��
	{
		SetState(E_2124);
		E2124(vecToTagt);
	}

	if (sequence == 8) // �齺�Ǹ�����
	{
		vecToTagt = { 0,0,0 };
		sequence = 1;
	}
}

void Valphalk::S_StabAtk()
{
	static int whichPattern = 0;

	if (sequence == 0) // ���̵彺�� ���� �մٸ� ��� ���� �Ǵ�
	{
		if ((realPos->Pos() - target->GlobalPos()).Length() < 1000)
			sequence = 6;
		else
			sequence++;
	}

	if (sequence == 1) // ������� ���� ���ϱ�
	{
		whichPattern = SetRadAndMirror(false);
		sequence++;
	}

	if (sequence == 2) // ���� �������� ���� ��ȯ�Լ�
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

	if (sequence == 3) // ���� ���
	{
		SetState(E_2038);	E2038();
	}

	if (sequence == 4) // ���� ���2 - �ֵθ���
	{
		SetState(E_2056);	E2056();
	}

	if (sequence == 5)
	{
		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 6) // �齺�� ��ġ ���
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 2500 + realPos->Right() * 1106 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 7) // �齺��
	{
		SetState(E_2124);
		E2124(vecToTagt);
	}

	if (sequence == 8) // �齺�Ǹ�����
	{
		vecToTagt = { 0,0,0 };
		sequence = 1;
	}
}

void Valphalk::S_BackWingAtk()
{
}

void Valphalk::S_SRush()
{
	static int whichPattern = 0;
	if (sequence == 0) // ���� ���ϱ�
	{
		whichPat = SetRadAndMirror(false);
		sequence++;
	}

	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
	{

		switch (whichPat)
		{
		case 1:	SetState(E_2188); E2188();  break;
		case 2:	SetState(E_2189); E2189();  break; // �� 90
		case 3:	SetState(E_2190); E2190();  break; // �� 180
		case 4:	SetState(E_2188); E2188();  break;
		case 5:	SetState(E_2192); E2192();  break; // �� 90
		case 6:	SetState(E_2193); E2193();  break; // �� 180
		}
	}

	if (sequence == 2) // ���� ���
	{
		SetState(E_2200);
		E2200();
	}

	if (sequence == 3) // ������
	{
		whichPat = 0;
		ChooseNextPattern();
	}

}

void Valphalk::S_JetRush()
{
}

void Valphalk::S_Transform()
{
}

void Valphalk::B_SwingAtk() 
{
	static int whichPattern = 0;
	
	if (sequence == 0) // ���� ���ϱ�
	{
		if ((realPos->Pos() - target->GlobalPos()).Length() < 900) // ����ġ�� ����� ���
			sequence = 4;
		else
		{
			whichPattern = SetRadAndMirror(true);
			sequence++;
		}
	}

	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2091);  E2091();				break;
		case 2:		SetState(E_2092);  E2092(-XM_PIDIV2);	break; // ���� 90
		case 3:		SetState(E_2093);  E2093(-XM_PI);		break; // ���� 180
		case 4:		SetState(E_2091);  E2091();				break;
		case 5:		SetState(E_2092);  E2092(XM_PIDIV2);	break;
		case 6:		SetState(E_2093);  E2093(XM_PI);		break;
		}
	}

	if (sequence == 2) // ���� ���
	{
		SetState(E_2103);
		if(whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			E2103(XM_PIDIV2);
		else 
			E2103(-XM_PIDIV2);
	}

	if (sequence == 3) // ������
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 4) // �齺��
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 1600 + realPos->Right() * 1106 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 5) // �齺��
	{
		SetState(E_2253);
		E2253(vecToTagt);
	}

	if (sequence == 6) // �齺�Ǹ�����
	{
		sequence = 0;
	}
}

void Valphalk::B_WingAtk()
{
	static int whichPattern = 0;
	if (sequence == 0) // ���� ���ϱ�
	{
		whichPattern = SetRadAndMirror(false);
		if ((realPos->Pos() - target->GlobalPos()).Length() < 400)
			sequence = 4;
		else
			sequence++;
	}

	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
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

	if (sequence == 2) // ���� ���
	{
		SetState(E_2141);
		E2141();
	}

	if (sequence == 3) // ������
	{
		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 4) // �齺��
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 900 + realPos->Right() * 1106 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 5) // �齺��
	{
		SetState(E_2253);
		E2253(vecToTagt);
	}

	if (sequence == 6) // �齺�Ǹ�����
	{
		sequence = 0;
	}


}

void Valphalk::B_DownBlast()
{
	static int whichPattern = 0;
	if (sequence == 0) // ���� ���ϱ�
	{
		whichPattern = SetRadAndMirror(false);
		sequence++;
	}

	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
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

	if (sequence == 2) // ���� ���
	{
		SetState(E_2082);
		E2082();
	}

	if (sequence == 3) // ������
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
	if (sequence == 0) // ���� �������� ���� ��ȯ�Լ�
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_0151);  E0151();				break;
		case 2:		SetState(E_0152);  E0152(-XM_PIDIV2);	break; // ���� 90
		case 3:		SetState(E_0153);  E0153(-XM_PI);		break; // ���� 180
		case 4:		SetState(E_0151);  E0151();				break;
		case 5:		SetState(E_0152);  E0152(XM_PIDIV2);	break;
		case 6:		SetState(E_0153);  E0153(XM_PI);		break;
		}
	}

	if (sequence == 2) // ���� ���
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		sequence++;
	}

	if (sequence == 3) // ���� ���
	{

		SetState(E_2151);
		E2151();

	}

	if (sequence == 4) // ���� ���
	{
		SetState(E_2152);
		E2152();
	}


	if (sequence == 5) // ���� ���
	{
		SetState(E_2153);
		E2153();
	}

	if (sequence == 6) // ������
	{
		ChooseNextPattern();
	}
}

void Valphalk::B_Trnasform()
{
}

void Valphalk::HS_FlyBlast()
{
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


	if (sequence == 2) // ���� �������� ���� ��ȯ�Լ�
	{
		whichPattern = SetRadAndMirror(false);

		Vector3 groundPos = Vector3(realPos->Pos().x, 0, realPos->Pos().z);
		float length = (target->GlobalPos() - groundPos).Length();

		if (length < 2000)
			sequence = 8;
		else
			sequence++;
	}

	if (sequence == 3) // ���� �������� ���� ��ȯ�Լ�
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_2270);  EX2270();			break;
		case 2:		SetState(E_2271);  EX2271(-XM_PIDIV2);	break; // ���� 90
		case 3:		SetState(E_2272);  EX2272(-XM_PI);		break; // ���� 180
		case 4:		SetState(E_2270);  EX2270();			break;
		case 5:		SetState(E_2274);  EX2274(XM_PIDIV2);	break;
		case 6:		SetState(E_2275);  EX2275(XM_PI);		break;
		}
	}

	if (sequence == 4) // ���� ���
	{
		SetState(E_2276);
		EX2276();
	}

	if (sequence == 5) // ���� ���
	{
		SetState(E_2277);
		EX2277(yDifference);
	}


	if (sequence == 6) // ���� ���
	{
		Pos().y = 0;
		EX2278();
	}

	if (sequence == 7) // ������
	{

		whichPattern = 0;
		ChooseNextPattern();
	}

	if (sequence == 8)
	{
		if (radBtwTarget > -XM_PIDIV2 && radBtwTarget <= 0) // ���� 90��
		{
			whichPattern = 1;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > -XM_PI && radBtwTarget <= -XM_PIDIV2) // �޵��� 90�� 
		{
			whichPattern = 2;
			radDifference = radBtwTarget + XM_PI;
		}
		else if (radBtwTarget > 0 && radBtwTarget <= XM_PIDIV2) // ���� ���� 90��
		{
			whichPattern = 3;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > XM_PIDIV2&& radBtwTarget <= XM_PI) // �������� 90��
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

	if (sequence == 10) // ���� ���
	{
		SetState(E_2374);
		EX2374();
	}

	if (sequence == 11) // ���� ���
	{
		SetState(E_2375);
		EX2375();
	}

	if (sequence == 12) // ���� ���
	{
		Pos().y = 0;
		EX2376();
	}

	if (sequence == 13) // ������
	{
		whichPattern = 0;
		ChooseNextPattern();
	}

}

void Valphalk::HS_FlyWingBlast()
{
}

void Valphalk::HB_LaserBlast()
{
}

void Valphalk::FindRoar()
{
}

void Valphalk::AngerRoar()
{
}

void Valphalk::E0003() // ���� ���
{
	PLAY;

	if (RATIO > 0.98)
		sequence++;
}

void Valphalk::E0007() // Ż��
{
	PLAY;
}

void Valphalk::E0043() // ������ ����
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0055);
}

void Valphalk::E0044() // ��ȸ��
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0045() // �ڷ� ȸ��
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0055()//�ȱ� Loop
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
		// ��� �Ȱ� �Ϸ��� ���� �ʿ�
}

void Valphalk::E0059()//������ �ٱ�
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0071);
}

void Valphalk::E0060()//������ �ٴٰ� ��ȸ��
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0071);
}

void Valphalk::E0061()//������ �ٴٰ� �ڵ���(��ȸ��)
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0071);
}

void Valphalk::E0071()//�ٱ�Loop
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
		//��� �ٰ� �Ϸ��� ���� �ʿ�
}

void Valphalk::E0097() // ���� (���� �غ�)
{
	PLAY;
}

void Valphalk::E0098(float degree) // ����ȸ�� ��
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

void Valphalk::E0099(float degree) // �޵ڷ� ��
{
	PLAY;
	if (RATIO > 0.99)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E0146() //�����¿��� ���ݸ��� ��ȯ
{
	PLAY;
	if (RATIO > 0.98)
		//SetState(E_2144); --> ��ȯ �� �ٷ� �����ؾ��Ѵٸ� ���� �ʿ�
		SetState(E_0151);
		//SetState(E_0003);
}

void Valphalk::E0147()//������ -> ������ ��ȯ
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0151()//���ݻ��� Idle
{
	PLAY;

	if (RATIO > 0.22f && RATIO < 0.49f)
		RotateToTarget(0.22f, 0.49f);

	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::E0152(float degree)//���ݻ��� ��ȸ��
{
	PLAY;

	if (RATIO > 0.32f && RATIO < 0.53f)
		RotateToTarget(0.32f, 0.53f);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E0153(float degree)//���ݻ��� �ڷ�ȸ��
{
	PLAY;

	if (RATIO > 0.0879f && RATIO < 0.495f)
		RotateToTarget(0.0879f, 0.495f);

	if (RATIO > 0.98)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E0164()//�ް�����
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0165()//�ް����� ġ�� ���ʺ�
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0166()//�ް����� ġ�� ������ ��
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0171()//������ �ް�����
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0151);
}

void Valphalk::E0172()//������ �ް����� ġ�� ���ʺ�
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0151);
}

void Valphalk::E0173()//������ �ް����� ġ�� ������ ��
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0151);
}

void Valphalk::E0178()//������->������ ��ȯ�ϸ鼭 �ް�����
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0179()//������->������ ��ȯ�ϸ鼭 �ް����� ġ�� ���ʺ�
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0180()//������->������ ��ȯ�ϸ鼭 �ް����� ġ�� ������ ��
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0186()//������->������ ��ȯ�ϸ鼭 ������ �ٱ�
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0187()//������->������ ��ȯ�ϸ鼭 ������ �ٴٰ� ��ȸ��
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E0188()//������->������ ��ȯ�ϸ鼭 ������ �ٴٰ� �ڵ���
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E1151() // �����غ�
{
	PLAY;
	if (RATIO < 0.1)
		Sounds::Get()->Play("em086_05_fx_media_25", 0.5f);
	if (RATIO > 0.99)
	{
		sequence++;
	}
}

void Valphalk::E1155() // ���
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

void Valphalk::E1163() // �ϰ�
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

void Valphalk::E1164() // ����
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

void Valphalk::E2001()//�ڷ� ���� �� ���� �غ�
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2002()//2001�� ���� 90���� ����Ʋ�� ����
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2003()//2001�� ���� 180���� ����Ʋ�� ����
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2013()//���� ����
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2015);
}

void Valphalk::E2015()//������ Loop
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2017);
}

void Valphalk::E2017()//���� �극��ũ
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2019);
}

void Valphalk::E2019()//�극��ũ �� �ٴ� ���� �Ϸ�
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_0003);
}

void Valphalk::E2020()//2017 ������ �ϰ� �ڸ� �Ĵٺ�
{
	PLAY;
	if (RATIO > 0.98)
		SetState(E_2022);
}

void Valphalk::E2022()//2020 �� �극��ũ�ϰ� �ڸ� �Ĵٺ�
{
	PLAY;
	if (RATIO > 0.98)
	{
		SetState(E_0003);
		combo = false;
	}
}

void Valphalk::E2027()//������ �ٴٰ� �����غ�
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2032()//�������� �ٴٰ� �����غ�
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2033()//���������� �ٴٰ� �����غ�
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2013);
}

void Valphalk::E2038() // ���� ���
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

void Valphalk::E2040() // ��� �غ�
{
	PLAY;

	if (RATIO > 0.358f && RATIO < 0.698f)
		RotateToTarget(0.358f, 0.698f);

	if (RATIO > 0.97)
	{
		sequence++;
	}
}

void Valphalk::E2041(float degree)//���ʺ��� ��� �غ�
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

void Valphalk::E2042(float degree)//�������� �ڵ��� ��� �غ�
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

void Valphalk::E2044(float degree)//�����ʺ��� ��� �غ�
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

void Valphalk::E2045(float degree)//���������� �ڵ��� ��� �غ�
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

void Valphalk::E2054() // ��� ���� ȸ��
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
		SetState(E_0151);
	}
}

void Valphalk::E2056() // ��� �� ���� �� �ѹ��� ����
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

void Valphalk::E2106()// ������ ��� ���� ��� �غ� �ڼ�
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

void Valphalk::E2107(float degree)//������ ��� ���鿡�� ���� ���� ��� �غ� �ڼ�
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

void Valphalk::E2108(float degree)//������ ��� ���鿡�� ���� ���� ��� �غ� �ڼ�
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

void Valphalk::E2118()//�մٸ� ��� ����
{
	PLAY;

	if (RATIO > 0.167 && RATIO < 0.367)
	{
		SetColliderAttack(RLEG1_FOOT, 0.367);
	}

	if (RATIO > 0.97)
		sequence++;
}

void Valphalk::E2121()//���� ���� ����ٰ� �������� ��¦ �Ͼ�� �ٽ� �ڼ�����
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


	if (RATIO > 0.97)
	{
		sequence++;

		Rot().y -= XM_PIDIV4;
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

void Valphalk::E2092(float degree) //90�� ȸ�� 
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

void Valphalk::E2093(float degree) // 180��
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

void Valphalk::E2103(float degree) // �ֵθ��� ����
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

void Valphalk::E2144() // ���� ���� ����
{
	combo = true;
	PLAY;
	if (RATIO > 0.98)
	{
		sequence++;
	}
}

void Valphalk::E2145() // ���� ���� ���� �� �齺��
{
	forwardBoom->Pos() = { Pos().x,Pos().y - 700,Pos().z + 1000 };

	forwardBoom->SetActive(true);
	PLAY;
	if (RATIO > 0.8f)
		forwardBoom->SetActive(false);

	if (RATIO > 0.98)
	{
		sequence++;
		//SetState(E_2146);
	}
}

void Valphalk::E2146() // ���� ���� �� ���� �����鼭 ����
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

void Valphalk::E2129()  // ���� �մٸ� ġ�� �غ�
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

void Valphalk::E2130() // �� 90
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

void Valphalk::E2131() //�� 180
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

void Valphalk::E2133() // �� 90
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

void Valphalk::E2134() // �� 180
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
	if (RATIO > 0.98)
		SetState(E_2185);
}

void Valphalk::E2174()// ���� ���ٰ� ���� ���� ������ ���
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2185);
}

void Valphalk::E2175()// ���� ���ٰ� ������ ���� ������ ���
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2185);
}

void Valphalk::E2185()// ����� ���� ���������� ������
{
	PLAY;
	if (RATIO > 0.98)
	{
		combo = false;
		SetState(E_0003);
	}
}

void Valphalk::E2188()//���� ���� �޹� ���
{
	PLAY;

	if (RATIO > 0.16 && RATIO > 0.8)
		RotateToTarget(0.16, 0.7);


	if (RATIO > 0.97)
		sequence++;
}

void Valphalk::E2189()//���鿡�� ���� ���� �޹� ���
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

void Valphalk::E2190()//���鿡�� �������� ���鼭 �ں��� �޹� ���
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

void Valphalk::E2192()//���鿡�� ������ ���� �޹� ���
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

void Valphalk::E2193()//���鿡�� ���������� ���鼭 �ں��� �޹� ���
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

void Valphalk::E2200()//S�� �����ġ��
{
	PLAY;


	if (RATIO > 0.98)
	{
		sequence++;
	}
}


void Valphalk::E2210()//�ڵ��� ������� �غ���
{
	combo = true;

	PLAY;
	if (RATIO > 0.98)
		SetState(E_2211);
}

void Valphalk::E2211()//�ڵ��� ������� ���ݵ���
{
	PLAY;
	//���� �ٲ��ִ� Ratio : 0.04 ~ 0.10
	if (RATIO > 0.98)
	{
		combo = false;
		SetState(E_0003);
	}
}

void Valphalk::E2265()
{
	PLAY;

	if (Count == 0 || Count == 1)
	{
		combo = true;
		//GetClip(E_2265)->SetPlayTime(0.0f);
		Count == 2;
	}

	if (RATIO > 0.98f)
	{
		SetState(E_2267);

		Count = 1;
	}
}

void Valphalk::E2267()
{
	PLAY;

	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		if (!LookatPlayer)
		{
			SetState(E_2371);
		}
		if (LookatPlayer)
		{
			SetState(E_2270);
		}
		if (OtherPlay)
		{
			SetState(E_2280);
		}
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

void Valphalk::EX2271(float degree) // �� 90
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
	if (Count == 1)
	{
		Rot().y = Rot().y - 1.9f;
		Count = 2;
	}
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
	if (Count == 1)
	{
		Rot().y = Rot().y - 1.9f;
		Count = 2;
	}

	if (RATIO > 0.98f)
	{
		SetState(E_2286);
		Count = 1;
	}
}

void Valphalk::E2286()
{
	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		SetState(E_2288);
	}
}

void Valphalk::E2288()
{
	PLAY;


	if (Pos().y > 500.0f)
	{
		Count = 1;

		Pos().y -= GetTranslationByNode(1).y * 10.0f * DELTA;
	}
	else
	{
		OtherPlay = false;
		Pos().y = GetTranslationByNode(1).y - 500.0f;
		//Pos().y = 0.0f;
		SetState(E_2290);
		Count = 1;

	}
}

void Valphalk::E2290()
{
	if (Count == 1)
	{
		Pos() = GetTranslationByNode(1);
		Count = 2;
	}

	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		combo = false;
		SetState(E_4013);
	}
}

void Valphalk::E2354() // Ǯ����Ʈ ����
{
	combo = false;
	PLAY;
	if (RATIO > 0.0176f && RATIO < 0.176f)
		RotateToTarget(0.0176f, 0.176f);
	if (RATIO > 0.98)
	{
		sequence++;
		Pos() = realPos->Pos();
	}
		
}

void Valphalk::E2356() // Ǯ����Ʈ ��ȸ�� �ڷ� ����
{
	PLAY;
}

void Valphalk::E2359() // Ǯ����Ʈ ��ȸ�� �ڷ� ����
{
	PLAY;
}

void Valphalk::E2361() // Ǯ����Ʈ �غ�
{
	PLAY;
	//fullBurst->Rot().y = head->Rot().y;
	fullBurst->Rot() = fullBurstRot;
	if (RATIO > 0.98)
	{
		sequence++;
		Pos() = realPos->Pos();
	}

}

void Valphalk::E2367() // Ǯ����Ʈ �߻�
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
		Pos() = realPos->Pos();
	}
	
}

void Valphalk::E2368() // Ǯ����Ʈ ������
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

void Valphalk::E2253(Vector3 destVec)//���� ���鼭 ���������� �齺��
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
	if (RATIO > 0.98f)
	{
		Pos() = GetTranslationByNode(1);
		combo = false;
		SetState(E_4013);
		Count = 1;
	}
}

void Valphalk::E3001() // ���� ������ �ǰ�
{
	PLAY;
}

void Valphalk::E3023() // ���
{
	PLAY;
	if (RATIO > 0.99)			
	isPlay = false;
	
	//if (RATIO > 0.98)
		
}

void Valphalk::E4013() // ���� ��ȿ
{
	PLAY;
	if (RATIO > 0.2 && RATIO < 0.28)
		Sounds::Get()->Play("em086_05_vo_media_10", 0.5f);
	if (RATIO > 0.98)
		SetState(E_2040);
}

void Valphalk::E22005() // ��ȿ
{
	PLAY;
	if (RATIO > 0.5 && RATIO < 0.58)
		Sounds::Get()->Play("em086_05_vo_media_10", 0.5f);
	if (RATIO > 0.98)
		SetState(E_0003);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Collider ���� �Լ���

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

	// ť��� �� ���
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

	// �Ӹ� �κ�
	{
		colliders[HEAD]->SetParent(transforms[HEAD]);
		colliders[HEAD]->Scale().x = 90.0f;
		colliders[HEAD]->Scale().y = 70.0f;
		colliders[HEAD]->Scale().z = 100.0f;
		colliders[HEAD]->Rot().x = 1.73f;
		colliders[HEAD]->part = HEAD;
		colliders[HEAD]->SetTag("HEAD");
	}

	// �� �κ�
	{
		colliders[NECK]->SetParent(transforms[NECK]);
		colliders[NECK]->Scale().x = 80.0f;
		colliders[NECK]->Scale().y = 60.0f;
		colliders[NECK]->Scale().z = 80.0f;
		colliders[NECK]->Rot().x = 1.80f;
		colliders[NECK]->SetTag("NECK");
	}

	// ���� �κ�
	{
		colliders[CHEST]->SetParent(transforms[CHEST]);
		colliders[CHEST]->Scale().x = 150.0f;
		colliders[CHEST]->Scale().y = 110.0f;
		colliders[CHEST]->Scale().z = 150.0f;
		colliders[CHEST]->Rot().x = 0.02;
		colliders[CHEST]->SetTag("CHEST");
	}

	// �� �κ�
	{
		colliders[BODY]->SetParent(transforms[BODY]);
		colliders[BODY]->Scale().x = 130.0f;
		colliders[BODY]->Scale().y = 120.0f;
		colliders[BODY]->Scale().z = 120.0f;
		colliders[BODY]->Rot().x = 1.65f;
		colliders[BODY]->part = BODY;
		colliders[BODY]->SetTag("BODY");
	}

	// ���� ����
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

	// ���� ���� ���� �κ�
	{
		colliders[LWING_RADIUS]->SetParent(transforms[LWING_RADIUS]);
		colliders[LWING_RADIUS]->Scale().x = 80.0f;
		colliders[LWING_RADIUS]->Scale().y = 70.0f;
		colliders[LWING_RADIUS]->Scale().z = 80.0f;
		colliders[LWING_RADIUS]->Rot().x = 1.22f;
		colliders[LWING_RADIUS]->SetTag("LWING_RADIUS");
	}

	// ������ ����
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

	// ������ ���� ���� �κ�
	{
		colliders[RWING_RADIUS]->SetParent(transforms[RWING_RADIUS]);
		colliders[RWING_RADIUS]->Scale().x = 80.0f;
		colliders[RWING_RADIUS]->Scale().y = 70.0f;
		colliders[RWING_RADIUS]->Scale().z = 80.0f;
		colliders[RWING_RADIUS]->Rot().x = 1.22f;
		colliders[RWING_RADIUS]->SetTag("RWING_RADIUS");
	}

	// ���� �ٸ� (��)
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

	// ���� �߹ٴ� (��)
	{
		colliders[LLEG1_FOOT]->SetParent(transforms[LLEG1_FOOT]);
		colliders[LLEG1_FOOT]->Scale().x = 80.0f;
		colliders[LLEG1_FOOT]->Scale().y = 90.0f;
		colliders[LLEG1_FOOT]->Scale().z = 100.0f;
		colliders[LLEG1_FOOT]->Rot().x = 2.55f;
		colliders[LLEG1_FOOT]->SetTag("LLEG1_FOOT");
	}

	// ���� �ٸ� (��)
	{
		colliders[LLEG2]->SetParent(transforms[LLEG2]);
		colliders[LLEG2]->Scale().x = 70.0f;
		colliders[LLEG2]->Scale().y = 60.0f;
		colliders[LLEG2]->Scale().z = 70.0f;
		//colliders[LLEG2]->Rot().x = 0.64f;
		colliders[LLEG2]->part = LLEG2;
		colliders[LLEG2]->SetTag("LLEG2");
	}

	// ���� �ٸ� �߹ٴ� (��)
	{
		colliders[LLEG2_FOOT]->SetParent(transforms[LLEG2_FOOT]);
		colliders[LLEG2_FOOT]->Scale().x = 70.0f;
		colliders[LLEG2_FOOT]->Scale().y = 60.0f;
		colliders[LLEG2_FOOT]->Scale().z = 70.0f;
		colliders[LLEG2_FOOT]->Rot().x = -0.74f;
		colliders[LLEG2_FOOT]->SetTag("LLEG2_FOOT");
	}

	// ������ �ٸ� (��)
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

	// ������ �ٸ� �߹ٴ�(��)
	{
		colliders[RLEG1_FOOT]->SetParent(transforms[RLEG1_FOOT]);
		colliders[RLEG1_FOOT]->Scale().x = 80.0f;
		colliders[RLEG1_FOOT]->Scale().y = 90.0f;
		colliders[RLEG1_FOOT]->Scale().z = 100.0f;
		colliders[RLEG1_FOOT]->Rot().x = -0.45f;
		//colliders[RLEG1_FOOT]->Rot().y = 22.0f;
		colliders[RLEG1_FOOT]->SetTag("RLEG1_FOOT");
	}

	// ������ �ٸ� (��)
	{
		colliders[RLEG2]->SetParent(transforms[RLEG2]);
		colliders[RLEG2]->Scale().x = 70.0f;
		colliders[RLEG2]->Scale().y = 60.0f;
		colliders[RLEG2]->Scale().z = 70.0f;
		//colliders[RLEG2]->Rot().x = 50.0f;
		colliders[RLEG2]->SetTag("RLEG2");
	}

	// ������ �߹ٴ� (��)
	{
		colliders[RLEG2_FOOT]->SetParent(transforms[RLEG2_FOOT]);
		colliders[RLEG2_FOOT]->Scale().x = 70.0f;
		colliders[RLEG2_FOOT]->Scale().y = 60.0f;
		colliders[RLEG2_FOOT]->Scale().z = 70.0f;
		colliders[RLEG2_FOOT]->Rot().x = -0.74f;
		colliders[RLEG2_FOOT]->SetTag("RLEG2_FOOT");
	}

	// ���� ����
	{
		colliders[TAIL_START]->SetParent(transforms[TAIL_START]);
		colliders[TAIL_START]->Scale().x = 120.0f;
		colliders[TAIL_START]->Scale().y = 100.0f;
		colliders[TAIL_START]->Scale().z = 120.0f;
		colliders[TAIL_START]->Rot().x = 1.78f;
		colliders[TAIL_START]->SetTag("TAIL_START");
	}

	// ���� 1/4 �κ�
	{
		colliders[TAIL_1]->SetParent(transforms[TAIL_1]);
		colliders[TAIL_1]->Scale() *= 80.0f;
		colliders[TAIL_1]->Rot().x = 1.55f;
		colliders[TAIL_1]->SetTag("TAIL_1");
	}

	// ���� 1/2 �κ�
	{
		colliders[TAIL_2]->SetParent(transforms[TAIL_2]);
		colliders[TAIL_2]->Scale().x = 50.0f;
		colliders[TAIL_2]->Scale().y = 60.0f;
		colliders[TAIL_2]->Scale().z = 50.0f;
		colliders[TAIL_2]->Rot().x += 1.6f;
		colliders[TAIL_2]->SetTag("TAIL_2");
	}

	// ���� �� �κ�
	{
		colliders[TAIL]->SetParent(transforms[TAIL]);
		colliders[TAIL]->Scale() *= 80.0f; // ����
		colliders[TAIL]->Rot().x += 4.8f;
		colliders[TAIL]->part = TAIL;
		colliders[TAIL]->SetTag("TAIL");
	}
}


void Valphalk::ColliderNodePos()
{
	// �Ӹ�
	transforms[HEAD]->SetWorld(GetTransformByNode(14));

	// ��
	transforms[NECK]->SetWorld(GetTransformByNode(7));

	// ����
	transforms[CHEST]->SetWorld(GetTransformByNode(5));

	// ����
	transforms[BODY]->SetWorld(GetTransformByNode(3));

	// ���� ����
	transforms[LWING]->SetWorld(GetTransformByNode(63));
	//Wingtransforms[LWING1]->SetWorld(GetTransformByNode(64));

	// ���� ���� ����
	transforms[LWING_RADIUS]->SetWorld(GetTransformByNode(57));

	// ������ ����
	transforms[RWING]->SetWorld(GetTransformByNode(83));
	//Wingtransforms[RWING1]->SetWorld(GetTransformByNode(84));

	// ������ ���� ����
	transforms[RWING_RADIUS]->SetWorld(GetTransformByNode(77));

	// ���� �ٸ� (��)
	transforms[LLEG1]->SetWorld(GetTransformByNode(16));

	// ���� �߹ٴ� (��)
	transforms[LLEG1_FOOT]->SetWorld(GetTransformByNode(30));

	// ���� �ٸ� (��)
	transforms[LLEG2]->SetWorld(GetTransformByNode(98));

	// ���� �߹ٴ� (��)
	transforms[LLEG2_FOOT]->SetWorld(GetTransformByNode(100));

	// ������ �ٸ� (��)
	transforms[RLEG1]->SetWorld(GetTransformByNode(36));

	// ������ �߹ٴ� (��)
	transforms[RLEG1_FOOT]->SetWorld(GetTransformByNode(50));

	// ������ �ٸ� (��)
	transforms[RLEG2]->SetWorld(GetTransformByNode(112));

	// ������ �߹ٴ� (��)
	transforms[RLEG2_FOOT]->SetWorld(GetTransformByNode(114));

	// ���� ����
	transforms[TAIL_START]->SetWorld(GetTransformByNode(126));

	// ���� 1/4 ��
	transforms[TAIL_1]->SetWorld(GetTransformByNode(127));

	// ���� 1/2 ��
	transforms[TAIL_2]->SetWorld(GetTransformByNode(128));

	// ���� ��
	transforms[TAIL]->SetWorld(GetTransformByNode(130));

}
