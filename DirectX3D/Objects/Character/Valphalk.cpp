#include "Framework.h"
#include "Scenes/FightTestScene.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/FightTestScene.h"

Valphalk::Valphalk() : ModelAnimator("Valphalk")
{
	srand(static_cast<unsigned int>(time(NULL)));

	head = new Transform();
	jetpos = new Transform();
	jetposend = new Transform();
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
	ReadClip("E_3006");
	ReadClip("E_3015");
	ReadClip("E_3016");
	ReadClip("E_3017");
	ReadClip("E_3023");
	ReadClip("E_3101");
	ReadClip("E_3106");
	ReadClip("E_3114");
	ReadClip("E_3118");
	// �Ʒ� �ִ°� ù ��ȿ
	ReadClip("E_4001");
	ReadClip("E_4013");
	ReadClip("E_4071");
	ReadClip("E_4073");
	ReadClip("E_4074");
	//	ReadClip("E_22005");

	ColliderAdd();

	Pos().z += 5000;
	UpdateWorld();

	realPos = new CapsuleCollider(1, 0.1);
	realPos->Scale() *= 6.0f;
	realPos->UpdateWorld();

	tempCollider = new CapsuleCollider(6, 0.1);
	tempCollider->UpdateWorld();

	realPosition = new Transform();
	realPosition->UpdateWorld();

	/////////////////////////////////////////////
	// ���� �ݶ��̴� (����ü, ���� ��)	
	bullets.resize(6);
	FOR(6)
	{
		bullets[i] = new SphereCollider();
		bullets[i]->Scale() *= 100;
		bullets[i]->SetColor(1, 0, 0);
		bullets[i]->SetActive(false);
		bullets[i]->atkDmg = 30;
		sphereColliders.push_back(bullets[i]);
	}

	forwardBoom = new BoxCollider();
	forwardBoom->Scale() *= 1000;
	forwardBoom->SetColor(1, 0, 0);
	forwardBoom->Pos() = forwardBoomPosInit;
	forwardBoom->SetParent(head);
	forwardBoom->SetActive(false);
	forwardBoom->atkDmg = 35;
	{//fullBurst
		fullBurst = new BoxCollider();
		fullBurst->Scale() *= 500;
		fullBurst->Scale().z *= 20;
		fullBurst->SetParent(head);
		fullBurst->Pos().z -= 5000;
		fullBurst->SetColor(1, 0, 0);
		fullBurst->SetActive(false);
		fullBurst->atkDmg = 55;
		fullBurstScale = fullBurst->Scale();
		fullBurstPos = fullBurst->Pos();
		fullBurstRot = fullBurst->Rot();
	}

	effectBox1 = new BoxCollider();
	effectBox2 = new BoxCollider();
	effectBox3 = new BoxCollider();
	effectBox1->Scale().x = 1500;
	effectBox1->Scale().y = 450;
	effectBox1->Scale().z = 400;
	effectBox1->SetParent(transforms[RWING]);
	effectBox1->Pos().x -= 1500;
	effectBox1->Pos().z -= 250;
	effectBox1->Rot().x = 0.1f;
	effectBox1->Rot().y -= 0.25f;
	effectBox1->SetColor(1, 0, 0);
	effectBox1->UpdateWorld();
	effectBox1->atkDmg = 40;
	effectBox1->SetActive(false);
	effectBox2->Scale().x = 1500;
	effectBox2->Scale().y = 450;
	effectBox2->Scale().z = 400;
	effectBox2->SetParent(transforms[RWING]);
	effectBox2->Pos().x -= 1230;
	effectBox2->Pos().y -= 830;
	effectBox2->Pos().z -= 265;
	effectBox2->Rot().x = 0.1f;
	effectBox2->Rot().y -= 0.25f;
	effectBox2->Rot().z = 0.6f;
	effectBox2->SetColor(1, 0, 0);
	effectBox2->UpdateWorld();
	effectBox2->atkDmg = 40;
	effectBox2->SetActive(false);
	effectBox3->Scale().x = 1500;
	effectBox3->Scale().y = 450;
	effectBox3->Scale().z = 400;
	effectBox3->SetParent(transforms[RWING]);
	effectBox3->Pos().x -= 1270;
	effectBox3->Pos().y = 830;
	effectBox3->Pos().z -= 110;
	effectBox3->Rot().x = 0.1f;
	effectBox3->Rot().y -= 0.25f;
	effectBox3->Rot().z -= 0.6f;
	effectBox3->SetColor(1, 0, 0);
	effectBox3->UpdateWorld();
	effectBox3->atkDmg = 40;
	effectBox3->SetActive(false);
	boxColliders.push_back(forwardBoom);
	boxColliders.push_back(fullBurst);
	boxColliders.push_back(effectBox1);
	boxColliders.push_back(effectBox2);
	boxColliders.push_back(effectBox3);

	effectSphere1 = new SphereCollider();
	effectSphere2 = new SphereCollider();
	effectSphere1->UpdateWorld();
	effectSphere1->atkDmg = 40;
	effectSphere1->SetActive(false);
	effectSphere2->UpdateWorld();
	effectSphere2->atkDmg = 40;
	effectSphere2->SetActive(false);
	sphereColliders.push_back(effectSphere1);
	sphereColliders.push_back(effectSphere2);

	// ��ƼŬ
	FOR(6)
	{
		zetPos.push_back(new Transform());
		ValZet* valzet = new ValZet();
		if (i < 3)
			valzet->Rot().z -= XM_PIDIV2;
		else
			valzet->Rot().z += XM_PIDIV2;
		valZets.push_back(valzet);
		valZets[i]->SetParent(zetPos[i]);
	}

	//FOR(6) jetParticle.push_back(new Val_Jet_Particle());
	
	FOR(6) jetParticle.push_back(new Val_Jet_Particle());
	FOR(6) fireParticle.push_back(new Val_fire());
	FOR(8) hupgiFire.push_back(new HupgiFire());
	{
		//jetParticle[0]->Play(bullets[0]->Pos(),GetRotationByNode(61));
		//jetParticle[1]->Play(bullets[1]->Pos(),GetRotationByNode(64));
		//jetParticle[2]->Play(bullets[2]->Pos(),GetRotationByNode(61));
		//jetParticle[3]->Play(bullets[3]->Pos(),GetRotationByNode(81));
		//jetParticle[4]->Play(bullets[4]->Pos(),GetRotationByNode(84));
		//jetParticle[5]->Play(bullets[5]->Pos(),GetRotationByNode(87));
		/*jetParticle[0]->Pos() = GetTranslationByNode(61);
		jetParticle[1]->Pos() = GetTranslationByNode(64);
		jetParticle[2]->Pos() = GetTranslationByNode(67);
		jetParticle[3]->Pos() = GetTranslationByNode(81);
		jetParticle[4]->Pos() = GetTranslationByNode(84);
		jetParticle[5]->Pos() = GetTranslationByNode(87);*/
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
	delete effectBox1;
	delete effectBox2;
	delete effectBox3;
	delete effectSphere1;
	delete effectSphere2;
	jetParticle.clear();
	fireParticle.clear();
	hupgiFire.clear();
}

void Valphalk::Update()
{
	UpdateWorld();
	if (preState != curState)
		GetClip(preState)->ResetPlayTime();

	GetRadBtwTrgt();
	PlayPattern();
	ConditionCheck();
	DeathCheck();
	PartDestroyCheck();
	PushPlayer();
	head->Pos() = realPos->Pos() + Vector3::Up() * 200;
	head->UpdateWorld();

	realPos->Pos() = GetTranslationByNode(1);
	Vector3 fwd = (GetTranslationByNode(3) - GetTranslationByNode(5)).GetNormalized();
	realPos->Rot().y = atan2(fwd.x, fwd.z);
	realPos->UpdateWorld();

	realPosition->Pos() = GetTranslationByNode(1);
	realPosition->UpdateWorld();

	tempCollider->Pos() = realPos->Pos() + (realPos->Back() + realPos->Right()).GetNormalized() * 1000;
	tempCollider->UpdateWorld();

	velocity = target->GlobalPos() - GlobalPos();

	for (CapsuleCollider* capsulCollider : colliders)
		capsulCollider->Update();

	for (BoxCollider* boxCollider : wings)
		boxCollider->Update();

	for (SphereCollider* bullet : bullets)
		bullet->Update();

	//for (BoxCollider* boxCollider : boxColliders)
	//	boxCollider->Update();

	forwardBoom->Update();
	fullBurst->Update();

	effectBox1->Update();
	effectBox2->Update();
	effectBox3->Update();

	effectSphere1->Update();
	effectSphere2->Update();

	head->Rot().y = Rot().y;

	ColliderNodePos();

	FOR(jetParticle.size()) jetParticle[i]->Update();
	FOR(fireParticle.size()) fireParticle[i]->Update();
	//Jet();

	jetpos->Pos() = GetTranslationByNode(61);
	jetposend->Pos() = GetTranslationByNode(60);
	jetpos->UpdateWorld();
	jetpos->SetParent(jetposend);

	zetPos[0]->SetWorld(GetTransformByNode(61));
	zetPos[1]->SetWorld(GetTransformByNode(64));
	zetPos[2]->SetWorld(GetTransformByNode(67));
	zetPos[3]->SetWorld(GetTransformByNode(81));
	zetPos[4]->SetWorld(GetTransformByNode(84));
	zetPos[5]->SetWorld(GetTransformByNode(87));

	FOR(6)
		valZets[i]->Update();

	if (isHupGi == true)
		FlameOn();
	else
		FlameOff();
	FOR(hupgiFire.size()) hupgiFire[i]->Update();

	ModelAnimator::Update();
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
	effectBox1->Render();
	effectBox2->Render();
	effectBox3->Render();
	effectSphere1->Render();
	effectSphere2->Render();
	ModelAnimator::Render();
	realPos->Render();

	if (renderJet)
		FOR(6) valZets[i]->Render();
	if (renderJetRight)
		FOR(3) valZets[i+3]->Render();


	FOR(jetParticle.size()) jetParticle[i]->Render();
	FOR(fireParticle.size()) fireParticle[i]->Render();
	FOR(hupgiFire.size()) hupgiFire[i]->Render();
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
	ImGui::Text("headHP : %f", colliders[HEAD]->partHp);
	ImGui::Text("chestHP : %f", colliders[CHEST]->partHp);
	ImGui::Text("llegHP : %f", colliders[LLEG1]->partHp);
	ImGui::Text("rlegHP : %f", colliders[RLEG1]->partHp);
	//for (int i = 0; i < colliders.size(); i++)
	//{
	//	colliders[i]->GUIRender();
	//}
	//ImGui::DragFloat("radBtwTrgt", &radBtwTarget);
	//ImGui::SliderFloat3("ValphalkScale", (float*)&colliders[i]->Scale(), 0, 1000);
	ImGui::DragFloat("radDifference", &radDifference);

	ImGui::DragFloat3("effectsphere1pos", (float*)&effectSphere1->Pos());
	ImGui::DragFloat3("effectsphere2pos", (float*)&effectSphere2->Pos());
	ImGui::DragFloat3("effectsphere1rot", (float*)&effectSphere1->Rot());
	ImGui::DragFloat3("effectsphere2rot", (float*)&effectSphere2->Rot());

	//jetParticle[0]->GUIRender();
	//jetParticle[1]->GUIRender();
	//jetParticle[2]->GUIRender();
	//jetParticle[3]->GUIRender();
	//jetParticle[4]->GUIRender();
	//jetParticle[5]->GUIRender();
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

Vector3 Valphalk::GetPlayerPos() // �÷��̾� ��ġ ���� �Լ�
{
	Player* player = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetPlayer();
	Vector3 pos;
	pos = player->Pos();
	return pos;
}

void Valphalk::Jet()
{
	timer2 += DELTA;

	jetpos1_1 = GetTranslationByNode(60);
	jetpos1_2 = GetTranslationByNode(61);
	jetpos1 = jetpos1_2 - jetpos1_1;
	jetpos1.GetNormalized();
	jetpos2_1 = GetTranslationByNode(63);
	jetpos2_2 = GetTranslationByNode(64);
	jetpos2 = jetpos1_2 - jetpos1_1;
	jetpos2.GetNormalized();
	jetpos3_1 = GetTranslationByNode(66);
	jetpos3_2 = GetTranslationByNode(67);
	jetpos3 = jetpos1_2 - jetpos1_1;
	jetpos3.GetNormalized();
	jetpos4_1 = GetTranslationByNode(80);
	jetpos4_2 = GetTranslationByNode(81);
	jetpos4 = jetpos1_2 - jetpos1_1;
	jetpos4.GetNormalized();
	jetpos5_1 = GetTranslationByNode(83);
	jetpos5_2 = GetTranslationByNode(84);
	jetpos5 = jetpos1_2 - jetpos1_1;
	jetpos5.GetNormalized();
	jetpos6_1 = GetTranslationByNode(86);
	jetpos6_2 = GetTranslationByNode(87);
	jetpos6 = jetpos1_2 - jetpos1_1;
	jetpos6.GetNormalized();

	if (timer2 >= 2)
	{
		jetParticle[0]->Play(GetTranslationByNode(61), jetpos1);
		jetParticle[1]->Play(GetTranslationByNode(64), jetpos2);
		jetParticle[2]->Play(GetTranslationByNode(67), jetpos3);
		jetParticle[3]->Play(GetTranslationByNode(81), jetpos4);
		jetParticle[4]->Play(GetTranslationByNode(84), jetpos5);
		jetParticle[5]->Play(GetTranslationByNode(87), jetpos6);
		timer2 = 0;
	}
}

void Valphalk::Storm()
{
	stormTime += DELTA;
	combo = true;
	if (sequence == 0) { SetState(E_1151); E1151(); }

	if (sequence == 1) { SetState(E_1155); E1155(); }

	//if (sequence == 2) { SetState(E_1163); E1163();	}

	if (stormTime > 6 && curState != E_1164 && sequence == 2) { SetState(E_1163); E1163(); }
	if (sequence == 3) { SetState(E_1164); E1164(); }
}

void Valphalk::EnergyBullets()
{
	static int whichPattern = 0;
	FOR(6) fireParticle[i]->SetVortex(bullets[i]->Pos());

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
	Vector3 fire1 = GetTranslationByNode(61) - GetTranslationByNode(60);
	Vector3 fire2 = GetTranslationByNode(64) - GetTranslationByNode(63);
	Vector3 fire3 = GetTranslationByNode(67) - GetTranslationByNode(66);
	Vector3 fire4 = GetTranslationByNode(81) - GetTranslationByNode(80);
	Vector3 fire5 = GetTranslationByNode(84) - GetTranslationByNode(83);
	Vector3 fire6 = GetTranslationByNode(87) - GetTranslationByNode(86);
	fire1.GetNormalized();
	fire2.GetNormalized();
	fire3.GetNormalized();
	fire4.GetNormalized();
	fire5.GetNormalized();
	fire6.GetNormalized();

	if (sequence == 3) // ź�� ������ ����ֱ�
	{
		Sounds::Get()->Play("em086_05_fx_media_32", .3f);
		bullets[0]->Pos() = GetTranslationByNode(61) + fire1 * .81f;
		bullets[1]->Pos() = GetTranslationByNode(64) + fire2 * .81f;
		bullets[2]->Pos() = GetTranslationByNode(67) + fire3 * .81f;
		bullets[3]->Pos() = GetTranslationByNode(81) + fire4 * .81f;
		bullets[4]->Pos() = GetTranslationByNode(84) + fire5 * .81f;
		bullets[5]->Pos() = GetTranslationByNode(87) + fire6 * .81f;
		FOR(6)
		{
			fireParticle[i]->Play(bullets[i]->Pos(), bullets[i]->Rot());
			fireParticle[i]->PlaySpark(bullets[i]->Pos());
		}

		for (int i = 0; i < bullets.size(); ++i)
		{
			bullets[i]->SetActive(true);
		}
		sequence++;
	}
	if (sequence == 4) // ���� ź�� ������ ���� �������� �����ϱ�
	{
		for (int i = 0; i < 6; ++i)
		{
			randX[i] = Random(target->Pos().x - 250, target->Pos().x + 250);
			randZ[i] = Random(target->Pos().z - 250, target->Pos().z + 250);
		}
		sequence++;
	}
	if (sequence == 5)
	{
		SetState(E_2079); E2079();
	}
	if (sequence == 6) // �� �ʱ�ȭ �� ���� �ѱ��
	{
		for (int i = 0; i < 6; ++i)
		{
			if (bullets[i]->Pos().y >= 0)
				fireParticle[i]->Play(bullets[i]->Pos(), bullets[i]->Rot());

			randX[i] = 0;
			randZ[i] = 0;
		}
		whichPattern = 0;
		ChooseNextPattern();
	}
}

void Valphalk::ForwardBoom()
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
	if (sequence == 6)
	{
		isSlashMode = true;
		ChooseNextPattern();
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
	if (sequence == 1)
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
		else if (radBtwTarget > XM_PIDIV2 && radBtwTarget <= XM_PI) // �������� 90��
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
	//if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
	//{
	//	switch (whichPattern)
	//	{
	//	case 1:		SetState(E_2354);  E2354(); break;// SetState(E_0098);  E0098(-0.1f);  break;
	//	case 2:		SetState(E_2354);  E2354(-XM_PIDIV2);  break; // ���� 90
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
	if (sequence == 4) { SetState(E_2361); E2361(); }
	if (sequence == 5) { SetState(E_2367); E2367(); }
	if (sequence == 6) { SetState(E_2368); E2368(); }
	if (sequence == 7)
	{
		isSlashMode = true;
		ChooseNextPattern();
	}
}

void Valphalk::Hupgi()
{
	if (sequence == 0)
	{
		static float timer = 0.0f;	
		curState = E_4071;
		E4071();
		checkHp = curHP;
	}
	if (sequence == 1)
	{
		timer += DELTA;
		curState = E_4073;
		E4073(timer, checkHp);
	}
	if (sequence == 2)
	{
		curState = E_4074;
		E4074();
	}
	if (sequence == 3)
	{
		isHupGi = true;
		ChooseNextPattern();
	}
	if (sequence == 4)
	{
		curPattern = S_HUGESTAGGER;
		sequence = 0;
	}
}

void Valphalk::Sidestep()
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
		SetState(E_2124);
		E2124(vecToTagt);
	}

	if (sequence == 2) // ������
	{
		vecToTagt = { 0, 0, 0 };
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

void Valphalk::S_Dead()
{
	SetState(E_3023);	E3023();
}

void Valphalk::S_SmallStagger()
{
	if (sequence == 0)// �Ұ���
	{
		SetState(E_3001);	E3001();
	}

	if (sequence == 1)
	{
		isStagger = false;

		if (colliders[HEAD]->partHp < 0)
			colliders[HEAD]->partHp = 8000;
		else if (colliders[TAIL]->partHp < 0)
			colliders[TAIL]->partHp = 8000;
		ChooseNextPattern();
	}
}

void Valphalk::S_HugeStagger()
{
	if (sequence == 0)// ����� ����
	{
		SetState(E_3015);	E3015();
	}

	if (sequence == 1)// ����� ����
	{
		SetState(E_3016);	E3016();
	}

	if (sequence == 2)// ����� ȸ��
	{
		SetState(E_3017);	E3017();
	}

	if (sequence == 3)
	{
		isStagger = false;

		if (colliders[LLEG1]->partHp < 0)
			colliders[LLEG1]->partHp = 2500;
		else if (colliders[RLEG1]->partHp < 0)
			colliders[RLEG1]->partHp = 2500;
		else if (colliders[CHEST]->partHp < 0)
			colliders[CHEST]->partHp = 1500;
		ChooseNextPattern();
	}
}

void Valphalk::B_Dead()
{
	SetState(E_3118);	E3118();
}

void Valphalk::B_SmallStagger()
{
	if (sequence == 0)// �Ұ���
	{
		SetState(E_3101);	E3101();
	}

	if (sequence == 1)
	{
		isStagger = false;

		if (colliders[HEAD]->partHp < 0)
			colliders[HEAD]->partHp = 8000;
		else if (colliders[TAIL]->partHp < 0)
			colliders[TAIL]->partHp = 8000;
		ChooseNextPattern();
	}
}

void Valphalk::B_HugeStagger()
{
	if (sequence == 0)// ����� ����
	{
		SetState(E_3114);	E3114();
	}

	if (sequence == 1)// ����� ����
	{
		SetState(E_3016);	E3016();
	}

	if (sequence == 2)// ����� ȸ��
	{
		SetState(E_3017);	E3017();
	}

	if (sequence == 3)
	{
		isStagger = false;

		if (colliders[LLEG1]->partHp < 0)
			colliders[LLEG1]->partHp = 2500;
		else if (colliders[RLEG1]->partHp < 0)
			colliders[RLEG1]->partHp = 2500;
		else if (colliders[CHEST]->partHp < 0)
			colliders[CHEST]->partHp = 1500;
		ChooseNextPattern();
	}
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

void Valphalk::DeathCheck()
{
	if (curHP < 0)
	{
		if(isSlashMode)
			curPattern = S_DEAD;
		else
			curPattern = B_DEAD;
	}
}

void Valphalk::Patrol()
{
	static int whichPattern = 0;
	static int loopCount = 0;

	if (sequence == 0) // ������ ����
	{
		// �ɾ�� ������ �� �߾� ������ �����̾�
		Vector3 forward = Random(Vector3(-1, -1, -1), Vector3(1, 1, 1));
		UpdateWorld();
		Vector3 fwd = Forward();
		Vector3 rad = XMVector3AngleBetweenVectors(fwd, forward);
		Vector3 cross = Cross(fwd, forward);
		radBtwTarget = rad.x;
		if (Cross(fwd, forward).y < 0)
			radBtwTarget *= -1;

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

		loopCount = rand() % 2 + 1;
		initialRad = Rot().y;
		sequence++;
	}

	if (sequence == 1) // �������� �ȱ� ������
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_0043);  E0043();				break;
		case 2:		SetState(E_0044);  E0044(-XM_PIDIV2);	break; // ���� 90
		case 3:		SetState(E_0045);  E0045(-XM_PI);		break; // ���� 180
		case 4:		SetState(E_0043);  E0043();				break;
		case 5:		SetState(E_0044);  E0044(XM_PIDIV2);	break;
		case 6:		SetState(E_0045);  E0045(XM_PI);		break;
		}
	}

	if (sequence == 2) // ������
	{


		SetState(E_0055);

		// E_0055
		{
			PLAY;
			if (RATIO > 0.96)
			{
				Loop();
				loopCount -= 1;

				if (loopCount == 0)
					sequence++;
			}
		}
	}

	if (sequence == 3) // �θ���
	{
		SetState(E_4001);
		E4001();
	}

	if (sequence == 4) // ������
	{
		if (Scale().x == -1)
			Scale().x = 1;

		// �÷��̾ ��ó�� �ִ��� üũ��
		if ((target->GlobalPos() - realPos->Pos()).Length() < 4000)
			sequence++; // ������ ��ȿ��
		else
			sequence = 0; // ������ ������

	}

	if (sequence == 5) // ������ üũ��
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 6) // ���� ����
	{
		switch (whichPattern)
		{
		case 1:		SetState(E_0097);  E0097();				break;
		case 2:		SetState(E_0098);  E0098(-XM_PIDIV2);	break; // ���� 90
		case 3:		SetState(E_0099);  E0099(-XM_PI);		break; // ���� 180
		case 4:		SetState(E_0097);  E0097();				break;
		case 5:		SetState(E_0098);  E0098(XM_PIDIV2);	break;
		case 6:		SetState(E_0099);  E0099(XM_PI);		break;
		}
	}

	if (sequence == 7) // ��ȿ�� ��
	{
		if (Scale().x == -1)
			Scale().x = 1;

		SetState(E_4013);
		E4013();
	}

	if (sequence == 8) // ������ ��
	{
		ChooseNextPattern();
	}


}

void Valphalk::ConditionCheck()
{
	// ���ǿ� ���� bool ����
	if ((curHP / maxHP) < 0.9 && !angerRoar90Threshold)
	{
		angerRoar90 = true;
		angerRoar90Threshold = true;
	}

	if ((curHP / maxHP) < 0.4 && !angerRoar40Threshold)
	{
		angerRoar40 = true;
		angerRoar40Threshold = true;
	}

	if ((curHP / maxHP) < 0.5 && !ult50Threshold)
	{
		ult50 = true;
		ult50Threshold = true;
	}

	// Ÿ�̸� ����
	if (isAnger)
		angerTimer += DELTA;

	if (isFindTrgt)
		roarAfterTimer += DELTA;  // �ν� ��ȿ ���ĺ��� Ÿ�̸� ����

	if (isHupGi)
		hupGiTimer += DELTA;

	// Ÿ�̸ӿ� ���� ���� ����

	if (angerTimer > 120.0f)	// �г� 2�� ���� �� ����
	{
		isAnger = false;
		angerTimer = 0.0f;
	}

	if (roarAfterTimer > 60.0f && !needHupGi)  // �ν� ��ȿ 1�� �� ��� ����
	{
		needHupGi = true;
		isFindTrgt = false;
		roarAfterTimer = 0.0f;
	}

	if (hupGiTimer > 120.0f)   // ��� 2�� ���� �� ����
	{
		isHupGi = false;
		hupGiTimer = 0.0f;
	}
}

void Valphalk::PartDestroyCheck()
{
	if (curPattern == HS_FLYFALLATK)
		return;

	if (isStagger)
		return;

	if (curHP < 0)
		return;

	if (colliders[HEAD]->partHp < 0)
	{
		sequence = 0;
		radDifference = 0;
		initialRad = Rot().y;
		isStagger = true;

		for (auto collider : colliders)
			if (collider->isAttack)
				collider->isAttack = false;

		if (isSlashMode)
			curPattern = S_SMALLSTAGGER;
		else
			curPattern = B_SMALLSTAGGER;
	}

	if (colliders[LLEG1]->partHp < 0)
	{
		sequence = 0;
		radDifference = 0;
		initialRad = Rot().y;
		isStagger = true;

		for (auto collider : colliders)
			if (collider->isAttack)
				collider->isAttack = false;

		if (isSlashMode)
			curPattern = S_HUGESTAGGER;
		else
			curPattern = B_HUGESTAGGER;
	}

	if (colliders[RLEG1]->partHp < 0)
	{
		sequence = 0;
		radDifference = 0;
		initialRad = Rot().y;
		isStagger = true;

		for (auto collider : colliders)
			if (collider->isAttack)
				collider->isAttack = false;

		if (isSlashMode)
			curPattern = S_HUGESTAGGER;
		else
			curPattern = B_HUGESTAGGER;
	}

	if (colliders[CHEST]->partHp < 0)
	{
		sequence = 0;
		radDifference = 0;
		initialRad = Rot().y;
		isStagger = true;

		for (auto collider : colliders)
			if (collider->isAttack)
				collider->isAttack = false;

		if (isSlashMode)
			curPattern = S_HUGESTAGGER;
		else
			curPattern = B_HUGESTAGGER;
	}

	if (colliders[TAIL]->partHp < 0)
	{
		sequence = 0;
		radDifference = 0;
		initialRad = Rot().y;
		isStagger = true;

		for (auto collider : colliders)
			if (collider->isAttack)
				collider->isAttack = false;

		if (isSlashMode)
			curPattern = S_SMALLSTAGGER;
		else
			curPattern = B_SMALLSTAGGER;
	}
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

	if (Scale().x == -1)
		Scale().x = 1;

	SetState(E_2091);
	sequence = 0;
	radDifference = 0;
	initialRad = Rot().y;
	float distance = (target->GlobalPos() - Pos()).Length();

	//switch (0)
	//{
	//case 0: curPattern = HS_FLYBLAST; break;
	//}

	// ��� : �ν� ��ȿ�κ���  1�� ��
	// �г� : 90 ������    40 �϶� �ѹ�
	// �ʻ�� : ü�� 50 ������

	if (isStagger)
		return;

	if (curHP < 0)
		return;

	if (needHupGi)
	{
		curPattern = HUPGI;
		needHupGi = false;
		return;
	}

	if (angerRoar90)
	{
		curPattern = ANGERROAR;
		angerRoar90 = false;
		return;
	}

	if (angerRoar40)
	{
		curPattern = ANGERROAR;
		angerRoar40 = false;
		return;
	}

	if (ult50)
	{
		curPattern = STORM;
		ult50 = false;
		return;
	}
	
	/*int i = rand() % 3;
	switch (i)
	{
	case 0:	curPattern = S_STABATK;	 break;
	case 1:	curPattern = B_DOWNBLAST;		 break;
	case 2:	curPattern = B_ENERGYBLAST;		 break;
	}*/
	
	if (!needHupGi && !angerRoar90 && !angerRoar40 && !ult50)
	{
	
		if (distance < 2000)    // ��
		{
			if (isSlashMode)	   // ��
			{
				if (isHupGi)    // ��
				{
					int i = rand() % 4;
					switch (i)
					{
					case 0:	curPattern = S_LEGATK;		 break;
					case 1:	curPattern = S_STABATK;		 break;
					case 2:	curPattern = S_BACKWINGATK;  break;
					case 3:	curPattern = HS_FLYFALLATK;  break;  // ȣ����
					}
				}
				else           // ����
				{
					int i = rand() % 4;
					switch (i)
					{
					case 0:	curPattern = S_LEGATK;	  break;
					case 1:	curPattern = S_STABATK;	  break;
					case 2:	curPattern = S_BACKWINGATK;  break;
					case 3:	curPattern = S_BITE;		break;
					}
				}
			}
			else               // ��
			{
				if (isHupGi)   // ��
				{
					int i = rand() % 5;
					switch (i)
					{
					case 0:	curPattern = HB_WINGATK;	  break;
					case 1:	curPattern = B_DOWNBLAST;	  break;
					case 2:	curPattern = FORWARDBOOM;	break;
					case 3:	curPattern = HS_FLYFALLATK;	break;
					case 4:	curPattern = FULLBURST;	break;
					}
				}
				else           // ����
				{
					int i = rand() % 4;
					switch (i)
					{
					case 0:	curPattern = B_SWINGATK;	  break;
					case 1:	curPattern = B_WINGATK;	  break;
					case 2:	curPattern = B_DOWNBLAST;  break;
					case 3:	curPattern = FORWARDBOOM;  break;
					}
				}
			}
	
		}
	
		else if (distance >= 2000 && distance < 4000)  // ��
		{
			if (isSlashMode) // ��
			{
				if (isHupGi) // ��
				{
					int i = rand() % 4;
					switch (i)
					{
					case 0:	curPattern = S_STABATK;	  break;
					case 1:	curPattern = S_SRUSH;  break;
					case 2:	curPattern = HS_FLYFALLATK;	  break;
					case 3:
						if (curPattern != B_TRANSFORM)
							curPattern = S_TRANSFORM;
						else curPattern = HS_FLYFALLATK;
						break;
					}
				}
				else		// ��
				{
					int i = rand() % 3;
					switch (i)
					{
					case 0:	curPattern = S_STABATK;	  break;
					case 1:	curPattern = S_SRUSH;	  break;
					case 2:
						if (curPattern != B_TRANSFORM)
							curPattern = S_TRANSFORM;
						else curPattern = S_STABATK;
						break;
					}
				}
			}
			else			  // ��
			{
				if (isHupGi)  // ��
				{
					int i = rand() % 5;
					switch (i)
					{
					case 0:	curPattern = B_DOWNBLAST;	  break;
					case 1:	curPattern = FORWARDBOOM;	  break;
					case 2:	curPattern = HS_FLYFALLATK;	  break;
					case 3:	curPattern = FULLBURST;	break;
					case 4:	curPattern = B_DUMBLING;  break;
					}
				}
				else		  // �� ��
				{
					int i = rand() % 5;
					switch (i)
					{
					case 0:	curPattern = B_SWINGATK;	  break;
					case 1:	curPattern = FORWARDBOOM;	  break;
					case 2:	curPattern = B_ENERGYBLAST;  break;
					case 3:	curPattern = B_DUMBLING;  break;
					case 4:
						if (curPattern != S_TRANSFORM)
							curPattern = B_TRANSFORM;
						else curPattern = B_SWINGATK;
						break;
					}
				}
			}
	
		}
	
		else if (distance > 2000)   // ��
		{
			if (isSlashMode)        // ��
			{
				if (isHupGi)        // ��
				{
					int i = rand() % 2;
					switch (i)
					{
					case 0:	curPattern = S_JETRUSH;	  break;
					case 1:	curPattern = HS_FLYFALLATK;	  break;
					}
				}
				else                // ��
				{
					int i = rand() % 3;
					switch (i)
					{
					case 0:	curPattern = S_JETRUSH;	  break;
					case 1:	curPattern = S_RUNANDBITE;	  break;
						//case 2:	curPattern = S_RUNTOTRGT;  break; //TODO
					case 2:
						if (curPattern != B_TRANSFORM)
							curPattern = S_TRANSFORM;
						else curPattern = S_STABATK;
						break;
					}
				}
			}
			else                   //��
			{
				if (isHupGi)       // ��
				{
					int i = rand() % 3;
					switch (i)
					{
					case 0:	curPattern = FULLBURST;		break;
					case 1:	curPattern = B_DUMBLING;  break;
					case 2:	curPattern = HS_FLYFALLATK;  break; // Ʈ������ �ϰ� ���� ����
					}
				}
				else              // ��
				{
					int i = rand() % 3;
					switch (i)
					{
					case 0:	curPattern = B_ENERGYBLAST;		break;
					case 1:	curPattern = B_DUMBLING;		break;
					case 2:
						if (curPattern != S_TRANSFORM)
							curPattern = B_TRANSFORM;
						else curPattern = B_SWINGATK;
						break;
					}
				}
			}
	
		}
	}
	
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
	case Valphalk::B_DUMBLING:		B_Dumbling();		break;
	case Valphalk::B_TRANSFORM:		B_Trnasform();		break;
	case Valphalk::B_SIDESTEP:		B_Sidestep();		break;
	case Valphalk::B_ENERGYBLAST:	EnergyBullets();	break;
	case Valphalk::HS_FLYBLAST:		HS_FlyBlast();		break;
	case Valphalk::HS_FLYFALLATK:	HS_FlyFallAtk();	break;
	case Valphalk::HB_WINGATK:		HB_WingAtk();		break;
	case Valphalk::ANGERROAR:	    AngerRoar();  		break;
	case Valphalk::HUPGI:		    Hupgi();			break;
	case Valphalk::STORM:		    Storm();			break;
	case Valphalk::FULLBURST:		FullBurst();		break;
	case Valphalk::SIDESTEP:		Sidestep();			break;
	case Valphalk::FORWARDBOOM:		ForwardBoom();		break;
	case Valphalk::S_DEAD:			S_Dead();			break;
	case Valphalk::S_SMALLSTAGGER:	S_SmallStagger();	break;
	case Valphalk::S_HUGESTAGGER:	S_HugeStagger();	break;
	case Valphalk::B_DEAD:			B_Dead();			break;
	case Valphalk::B_SMALLSTAGGER:	B_SmallStagger();	break;
	case Valphalk::B_HUGESTAGGER:	B_HugeStagger();	break;
	case Valphalk::PATROL:			Patrol();			break;
	default:		break;
	}
}

void Valphalk::PushPlayer()
{
	if (curPattern == S_DEAD || curPattern == B_DEAD)
		return;

	Player* player;

	if (SceneManager::Get()->Add("FightTestScene") != nullptr)
		player = dynamic_cast<FightTestScene*>
			(SceneManager::Get()->Add("FightTestScene"))->GetPlayer();

	else if (SceneManager::Get()->Add("ShadowScene") != nullptr)
		player = dynamic_cast<ShadowScene*>
			(SceneManager::Get()->Add("ShadowScene"))->GetPlayer();

	else
		return;

	Collider* playerCollider = player->getCollider();
	

	for (auto collider : colliders)
	{
		if (collider->IsCollision(playerCollider))
		{
			Vector3 dir = (playerCollider->GlobalPos() - collider->GlobalPos()).GetNormalized();

			player->Pos().x += dir.x * 500 * DELTA;
			player->Pos().z += dir.z * 500 * DELTA;
		}
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

void Valphalk::SetColliderAttack(ColliderName name, float ratio, float dmg, UINT atkStrength)
{
	static bool ON = false;
	if (!ON)
	{
		colliders[name]->isAttack = true;
		colliders[name]->SetColor(Float4(1, 0, 1, 1));
		colliders[name]->atkDmg = dmg;
		colliders[name]->atkStrength = atkStrength;
		ON = true;
	}

	if (RATIO > ratio - 0.01)
	{
		colliders[name]->isAttack = false;
		colliders[name]->SetColor(Float4(0, 1, 0, 1));
		colliders[name]->atkDmg = 10;
		colliders[name]->atkStrength = 2;
		ON = false;
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

void Valphalk::FlameOn()
{
	// ������ ���� �ҹ���
	hupgiFire[0]->Play(GetTranslationByNode(15), 0); // ���� ���
	hupgiFire[1]->Play(GetTranslationByNode(35), 0); // ������ ���
	hupgiFire[2]->Play(GetTranslationByNode(61), 0); // ����
	hupgiFire[3]->Play(GetTranslationByNode(64), 0); // ����
	hupgiFire[4]->Play(GetTranslationByNode(67), 0); // ����
	hupgiFire[5]->Play(GetTranslationByNode(81), 0); // ����
	hupgiFire[6]->Play(GetTranslationByNode(84), 0); // ����
	hupgiFire[7]->Play(GetTranslationByNode(87), 0); // ����		
}

void Valphalk::FlameOff()
{
	FOR(hupgiFire.size()) hupgiFire[i]->Stop();
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
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		vecToTagt = { 0,0,0 };
		Pos() = realPos->Pos();
		sequence = 1;
	}
}

void Valphalk::S_StabAtk()
{
	static int whichPattern = 0;
	int randSound = rand() % 2;
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
		if (RATIO > 0.18 && RATIO < 0.2)
		{
			if (randSound == 0)
				Sounds::Get()->Play("em086_05_vo_media_1", 0.3f);
			if (randSound == 1)
				Sounds::Get()->Play("em086_05_vo_media_5", 0.3f);
		}		
		if (RATIO < 0.8 && RATIO > 0.79)
		{
			Sounds::Get()->Play("em086_05_fx_media_25", 0.1f);
			randSound = 0;
		}
	}

	if (sequence == 3) // ���� ���
	{
		if (!renderJetRight)
			renderJetRight = true;
		SetState(E_2038);	E2038();
		
		if (RATIO > 0.18 && RATIO < 0.2)
			Sounds::Get()->Play("em086_05_se_media_20", 0.4f);

	}

	if (sequence == 4) // ���� ���2 - �ֵθ���
	{
		SetState(E_2056);	E2056();
		if (RATIO > 0.30 && RATIO < 0.31)
			Sounds::Get()->Play("em086_05_se_media_32", 0.4f);
	}

	if (sequence == 5)
	{
		if (renderJetRight)
			renderJetRight = false;
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
		Pos() = realPos->Pos();
		sequence = 1;
	}
}

void Valphalk::S_BackWingAtk()
{
	static int whichPattern = 0;

	if (sequence == 0) //���� ���ϱ�
	{
		GetRadBtwTrgt();
		if (radBtwTarget > -rot45 && radBtwTarget <= 0) // ���� ���� 45��
		{
			whichPattern = 1;
			radDifference = radBtwTarget;
		}
		else if (radBtwTarget > -XM_PI && radBtwTarget <= -rot45) // ���� 90�� && �޵��� 45��
		{
			whichPattern = 2;
			radDifference = radBtwTarget + XM_PIDIV2;
		}
		else if (radBtwTarget > 0 && radBtwTarget <= rot45) // ���� ������ 45��
		{
			whichPattern = 3;
			radDifference = radBtwTarget;
			Scale().x *= -1;
		}
		else if (radBtwTarget > rot45 && radBtwTarget <= XM_PI) // ������ 90�� && �������� 45��
		{
			whichPattern = 4;
			radDifference = radBtwTarget - XM_PIDIV2;
			Scale().x *= -1;
		}
		else
			whichPattern = 1;

		initialRad = Rot().y;
		sequence++;
	}

	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
	{
		switch (whichPattern)
		{
		case 1:		sequence = 3;
		case 2:		SetState(E_2210);	E2210();  break;
		case 3:		sequence = 3;
		case 4:		SetState(E_2210);	E2210();  break;
		}
	}

	if (sequence == 2) // ���ݸ��
	{
		switch (whichPattern)
		{
		case 1:		sequence = 3;
		case 2:		SetState(E_2211);	E2211(-XM_PIDIV2);  break;
		case 3:		sequence = 3;
		case 4:		SetState(E_2211);	E2211(XM_PIDIV2);  break;
		}
	}

	if (sequence == 3)
	{
		if (whichPattern == 3 || whichPattern == 4)
			Scale().x *= -1;
		whichPattern = 0;
		ChooseNextPattern();
	}
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
	static int whichPattern = 0;
	isReverse = false;

	if (sequence == 0) //���� ���ϱ�
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
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

	if (sequence == 2) // �������
	{
		if (!renderJet)
			renderJet = true;
		SetState(E_2013);	E2013();
	}

	if (sequence == 3) // ���� �극��ũ ���
	{

		SetState(E_2017);	E2017();
	}

	if (sequence == 4) // �ٴڿ� ���� ���
	{
		SetState(E_2019);	E2019();
	}

	if (sequence == 5) // ������
	{
		if (renderJet)
			renderJet = false;
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		whichPattern = 0;
		ChooseNextPattern();
	}
}

void Valphalk::S_Bite()
{
	static int whichPattern = 0;

	if (sequence == 0) // ���̵彺�� ���� �մٸ� ��� ���� �Ǵ�
	{
		if ((realPos->Pos() - target->GlobalPos()).Length() < 500)
			sequence = 5;
		else
			sequence++;
	}

	if (sequence == 1) // �ƹ��� ���� ���ϱ�
	{
		whichPattern = SetRadAndMirror(true);
		sequence++;
	}

	if (sequence == 2) // ���� �������� ���� ��ȯ�Լ�
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

	if (sequence == 3) // ���� ���
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

	if (sequence == 5) // �齺�� ��ġ ���
	{
		Vector3 dir = (realPos->Back() + realPos->Right()).GetNormalized();
		vecToTagt = target->GlobalPos() - dir * 200 + realPos->Right() * 606 + realPos->Forward() * 120;
		vecToTagt.y = 0;

		sequence++;
	}

	if (sequence == 6) // �齺��
	{
		SetState(E_2124);
		E2124(vecToTagt);
	}

	if (sequence == 7) // �齺�Ǹ�����
	{
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			Scale().x *= -1;
		vecToTagt = { 0,0,0 };
		Pos() = realPos->Pos();
		sequence = 1;
	}
}

void Valphalk::S_Transform()
{
	if (sequence == 0) // ���
	{
		SetState(E_0146);    E0146();
	}

	if (sequence == 1)
	{
		isSlashMode = false;
		ChooseNextPattern();
	}
}

void Valphalk::S_RunAndBite()
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
		case 1:		SetState(E_0059);  E0059();				break;
		case 2:		SetState(E_0060);  E0060(-XM_PIDIV2);	break; // ���� 90
		case 3:		SetState(E_0061);  E0061(-XM_PI);		break; // ���� 180
		case 4:		SetState(E_0059);  E0059();				break;
		case 5:		SetState(E_0060);  E0060(XM_PIDIV2);	break;
		case 6:		SetState(E_0061);  E0061(XM_PI);		break;
		}
	}

	if (sequence == 2) // �޸��� ���
	{
		SetState(E_0071);
		E0071();
	}

	if (sequence == 3) // ���� ���
	{
		SetState(E_2171);
		E2171();
	}

	if (sequence == 4) // ������
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
		if (whichPattern == 4 || whichPattern == 5 || whichPattern == 6)
			E2103(XM_PIDIV2);
		else
			E2103(-XM_PIDIV2);
	}

	if (sequence == 3) // ������
	{

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
		case 1:	SetState(E_2383); E2383();  break;
		case 2:	SetState(E_2381); E2381();  break;
		case 3:	SetState(E_2383); E2383();  break;
		case 4:	SetState(E_2382); E2382();  break;
		case 5:	SetState(E_2381); E2381();  break;
		case 6:	SetState(E_2382); E2382();  break;
		}
			if (RATIO < 0.15 && RATIO > 0.13)
				Sounds::Get()->Play("em086_05_vo_media_14", 0.3f);
			if (RATIO < 0.65 && RATIO > 0.63)
				Sounds::Get()->Play("em086_05_fx_media_32", 0.3f);
	}

	if (sequence == 2) // ���� ���
	{

		SetState(E_2082);
		E2082();
	}

	if (sequence == 3) // ������
	{
		forwardBoom->Pos() = forwardBoomPosInit;
		forwardBoom->Scale().x = 700;

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

	if (sequence == 4) // ���� ��� + ����otherplay
	{
		forwardBoom->Pos() = 0;
		forwardBoom->Pos().z = +500;
		SetState(E_2152);
		E2152();
	}


	if (sequence == 5) // ���� ���
	{
		forwardBoom->Pos() = forwardBoomPosInit;
		SetState(E_2153);
		E2153();
	}

	if (sequence == 6) // ������
	{
		isSlashMode = true;
		ChooseNextPattern();
	}
}

void Valphalk::B_Trnasform()
{
	if (sequence == 0) // ���
	{
		SetState(E_0147);
		E0147();
	}

	if (sequence == 1)
	{
		isSlashMode = true;
		ChooseNextPattern();
	}
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

	if (sequence == 3 &&
		GetClip(E_2280)->GetPlaytime() > 0.723f ||
		GetClip(E_2281)->GetPlaytime() > 0.723f ||
		GetClip(E_2282)->GetPlaytime() > 0.723f)
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
		//sequence++;
		LookatPlayer = true;

		if (LookatPlayer)
		{
			timer += DELTA;
		}
	}

	if (LookatPlayer)
	{
		float randX = Random(target->Pos().x - 10, target->Pos().x + 10);
		float randZ = Random(target->Pos().z - 10, target->Pos().z + 10);

		if (sequence >= 3)
		{
			for (int i = 0; i < bullets.size(); ++i)
			{
				bullets[i]->Pos().x = Lerp(bullets[i]->Pos().x, randX, 0.0024f);
				bullets[i]->Pos().z = Lerp(bullets[i]->Pos().z, randZ, 0.0024f);

				bullets[i]->Pos().y -= 1500 * DELTA;
			}
		}
		for (int i = 0; i < bullets.size(); ++i)
		{
			if (bullets[i]->Pos().y < 0)
			{
				bullets[i]->SetActive(false);
				LookatPlayer = false;
			}
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

	if (sequence == 8) // ������
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
		if (!renderJet)
			renderJet = true;
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
		if (renderJet)
			renderJet = false;
		Pos().y = 0;
		EX2278();
	}

	if (sequence == 7) // ������
	{
		whichPattern = 0;

		isSlashMode = false;
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
		else if (radBtwTarget > XM_PIDIV2 && radBtwTarget <= XM_PI) // �������� 90��
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
		if (renderJet)
			renderJet = false;
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
		isSlashMode = false;
		ChooseNextPattern();
	}

}

void Valphalk::HS_FlyWingBlast() // ȣ���� �� ���� �չٴ� ����
{

}

void Valphalk::HB_WingAtk() // ���� ��� ���� ����
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
		SetState(E_2403);
		E2403();
	}

	if (sequence == 3) // ������
	{
		isSlashMode = true;
		whichPattern = 0;
		ChooseNextPattern();
	}
}

void Valphalk::AngerRoar()
{
	if (sequence == 0) // ���� ���ϱ�
	{
		SetState(E_4013); E4013();
	}

	if (sequence == 1) // ���� �������� ���� ��ȯ�Լ�
	{
		isAnger = true;
		ChooseNextPattern();
	}
}

void Valphalk::E0003() // ���� ���
{
	PLAY;

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E0007() // Ż��
{
	PLAY;
}

void Valphalk::E0043() // ������ ����
{
	PLAY;

	if (RATIO < 0.4)
		RotateToTarget(0.0, 0.3);

	if (RATIO > 0.96)
	{
		sequence++;

	}
}

void Valphalk::E0044(float degree) // ��ȸ��
{
	PLAY;

	if (RATIO < 0.4)
		RotateToTarget(0.0, 0.3);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E0045(float degree) // �ڷ� ȸ��
{
	PLAY;

	if (RATIO < 0.4)
		RotateToTarget(0.0, 0.3);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E0055()//�ȱ� Loop
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0003);
	// ��� �Ȱ� �Ϸ��� ���� �ʿ�
}

void Valphalk::E0059()//������ �ٱ�
{
	PLAY;

	if (RATIO > 0.0134f && RATIO < 0.5)
		RotateToTarget(0.0134f, 0.414f);

	if ((target->GlobalPos() - realPos->Pos()).Length() < 2500.0f)
	{
		if (!playOncePerPattern)
		{
			if (RATIO < 0.54)
				playRatioForE0071 = 0.54;
			else if (RATIO > 0.54 && RATIO < 0.84)
				playRatioForE0071 = 0.84;

			playOncePerPattern = true;
		}

		if (RATIO > playRatioForE0071)
		{
			sequence += 2;
			playRatioForE0071 = 0.0f;
			playOncePerPattern = false;
		}
	}

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E0060(float degree)//������ �ٴٰ� ��ȸ��
{
	PLAY;

	if (RATIO > 0.0134f && RATIO < 0.5f)
		RotateToTarget(0.0134f, 0.414f);

	if ((target->GlobalPos() - realPos->Pos()).Length() < 2500.0f)
	{
		if (!playOncePerPattern)
		{
			if (RATIO < 0.56)
				playRatioForE0071 = 0.56;
			else if (RATIO > 0.56 && RATIO < 0.85)
				playRatioForE0071 = 0.85;

			playOncePerPattern = true;
		}

		if (RATIO > playRatioForE0071)
		{
			sequence += 2;
			playRatioForE0071 = 0.0f;
			playOncePerPattern = false;
		}
	}

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E0061(float degree)//������ �ٴٰ� �ڵ���(��ȸ��)
{
	PLAY;

	if (RATIO > 0.0134f && RATIO < 0.5f)
		RotateToTarget(0.0134f, 0.414f);

	if ((target->GlobalPos() - realPos->Pos()).Length() < 2500.0f)
	{
		if (!playOncePerPattern)
		{
			if (RATIO < 0.57)
				playRatioForE0071 = 0.57;
			else if (RATIO > 0.57 && RATIO < 0.85)
				playRatioForE0071 = 0.85;

			playOncePerPattern = true;
		}

		if (RATIO > playRatioForE0071)
		{
			sequence += 2;
			playRatioForE0071 = 0.0f;
			playOncePerPattern = false;
		}
	}

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E0071()//�ٱ�Loop
{
	PLAY;

	if ((target->GlobalPos() - realPos->Pos()).Length() < 2500.0f)
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
	//��� �ٰ� �Ϸ��� ���� �ʿ�
}

void Valphalk::E0097() // ���� (���� �غ�)
{
	PLAY;

	if (RATIO > 0.0176f && RATIO < 0.3f)
		RotateToTarget(0.0176f, 0.176f);

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E0098(float degree) // ����ȸ�� ��
{
	PLAY;
	if (RATIO > 0.0176f && RATIO < 0.176f)
		RotateToTarget(0.0176f, 0.176f);

	if (RATIO > 0.96)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E0099(float degree) // �޵ڷ� ��
{
	PLAY;

	if (RATIO > 0.0176f && RATIO < 0.3f)
		RotateToTarget(0.0176f, 0.176f);


	if (RATIO > 0.96)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E0146() //�����¿��� ���ݸ��� ��ȯ
{
	PLAY;
	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E0147()//������ -> ������ ��ȯ
{
	PLAY;

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E0151()//���ݻ��� Idle
{
	PLAY;

	if (RATIO > 0.22f && RATIO < 0.62f)
		RotateToTarget(0.22f, 0.49f);

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E0152(float degree)//���ݻ��� ��ȸ��
{
	PLAY;

	if (RATIO > 0.22f && RATIO < 0.62f)
		RotateToTarget(0.22f, 0.49f);

	if (RATIO > 0.96)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E0153(float degree)//���ݻ��� �ڷ�ȸ��
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

void Valphalk::E0164()//�ް�����
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0003);
}

void Valphalk::E0165()//�ް����� ġ�� ���ʺ�
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0003);
}

void Valphalk::E0166()//�ް����� ġ�� ������ ��
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0003);
}

void Valphalk::E0171()//������ �ް�����
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0151);
}

void Valphalk::E0172()//������ �ް����� ġ�� ���ʺ�
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0151);
}

void Valphalk::E0173()//������ �ް����� ġ�� ������ ��
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0151);
}

void Valphalk::E0178()//������->������ ��ȯ�ϸ鼭 �ް�����
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0003);
}

void Valphalk::E0179()//������->������ ��ȯ�ϸ鼭 �ް����� ġ�� ���ʺ�
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0003);
}

void Valphalk::E0180()//������->������ ��ȯ�ϸ鼭 �ް����� ġ�� ������ ��
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0003);
}

void Valphalk::E0186()//������->������ ��ȯ�ϸ鼭 ������ �ٱ�
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0003);
}

void Valphalk::E0187()//������->������ ��ȯ�ϸ鼭 ������ �ٴٰ� ��ȸ��
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_0003);
}

void Valphalk::E0188()//������->������ ��ȯ�ϸ鼭 ������ �ٴٰ� �ڵ���
{
	PLAY;
	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
	{
		combo = false;
		ChooseNextPattern();
	}

}

void Valphalk::E2001()//�ڷ� ���� �� ���� �غ�
{
	PLAY;

	if (RATIO > 0.070f && RATIO < 0.581f)
		RotateToTarget(0.070f, 0.581f);

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2002(float degree)//2001�� ���� 90���� ����Ʋ�� ����
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

void Valphalk::E2003(float degree)//2001�� ���� 180���� ����Ʋ�� ����
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

void Valphalk::E2013()//���� ����
{
	PLAY;

	SetColliderAttack(HEAD, 0.95, 45, 2);
	SetColliderAttack(NECK, 0.95, 45, 2);
	SetColliderAttack(CHEST, 0.95, 45, 2);
	SetColliderAttack(BODY, 0.95, 45, 2);

	if (RATIO > 0.93)
	{
		sequence++;
	}
}

void Valphalk::E2015()//������ Loop
{
	PLAY;
	if (RATIO > 0.96)
		SetState(E_2017);
}

void Valphalk::E2017()//���� �극��ũ
{
	Pos().y = 0;

	SetColliderAttack(HEAD, 0.263, 45, 2);
	SetColliderAttack(NECK, 0.263, 45, 2);
	SetColliderAttack(CHEST, 0.263, 45, 2);
	SetColliderAttack(BODY, 0.263, 45, 2);

	PLAY;

	if (RATIO > 0.93)
	{
		sequence++;
	}
}

void Valphalk::E2019()//�극��ũ �� �ٴ� ���� �Ϸ�
{
	Pos().y = 0;

	PLAY;

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2020()//2017 ������ �ϰ� �ڸ� �Ĵٺ�
{
	PLAY;

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2022()//2020 �� �극��ũ�ϰ� �ڸ� �Ĵٺ�
{
	Pos().y = 0;

	PLAY;

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2027()//������ �ٴٰ� �����غ�
{
	combo = true;

	PLAY;
	if (RATIO > 0.96)
		SetState(E_2013);
}

void Valphalk::E2032()//�������� �ٴٰ� �����غ�
{
	combo = true;

	PLAY;
	if (RATIO > 0.96)
		SetState(E_2013);
}

void Valphalk::E2033()//���������� �ٴٰ� �����غ�
{
	combo = true;

	PLAY;
	if (RATIO > 0.96)
		SetState(E_2013);
}

void Valphalk::E2038() // ���� ���
{
	combo = false;

	PLAY;

	if (RATIO > 0.644 && RATIO < 0.95)
	{
		SetColliderAttack(RWING, 0.95, 35, 2);
		if (!playOncePerPattern)
		{
			colliders[RWING]->Scale().y *= 2.2f;
			playOncePerPattern = true;
		}
	}

	if (RATIO > 0.96)
	{
		colliders[RWING]->Scale().y *= 0.4f;
		playOncePerPattern = false;
		sequence++;
	}
}

void Valphalk::E2040() // ��� �غ�
{
	PLAY;

	if (RATIO > 0.358f && RATIO < 0.698f)
		RotateToTarget(0.358f, 0.698f);

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2041(float degree)//���ʺ��� ��� �غ�
{
	PLAY;

	if (RATIO > 0.293f && RATIO < 0.724f)
		RotateToTarget(0.293f, 0.724f);

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2054() // ��� ���� ȸ��
{
	PLAY;

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E2079()
{
	PLAY;
	if(RATIO<0.14f && RATIO > 0.13f)
		Sounds::Get()->Play("em086_05_fx_media_50", .3f);
	if (RATIO < 0.17 && RATIO > 0.16f)
		Sounds::Get()->Play("em086_05_fx_media_50_2", .3f);
	if (RATIO < 0.2f && RATIO > 0.19f)
		Sounds::Get()->Play("em086_05_fx_media_50", .3f);
	if (RATIO < 0.22f && RATIO > 0.21f)
		Sounds::Get()->Play("em086_05_fx_media_50_2", .3f);

	for (int i = 0; i < bullets.size(); ++i)
	{
		if (RATIO > 0.1 + ((DELTA + (float)i) * 0.03f))
		{
			bullets[i]->Pos().x = Lerp(bullets[i]->Pos().x, randX[i], 0.0167f);
			bullets[i]->Pos().z = Lerp(bullets[i]->Pos().z, randZ[i], 0.0167f);

			bullets[i]->Pos().y -= 420 * DELTA;
		}

		else if (bullets[i]->Pos().y < 0)
		{
			bullets[i]->SetActive(false);
			FOR(6) fireParticle[i]->Stop();
		}
	}

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2056() // ��� �� ���� �� �ѹ��� ����
{
	PLAY;

	if (RATIO > 0.361 && RATIO < 0.617)
	{
		SetColliderAttack(RWING, 0.617, 50, 2);
		if (!playOncePerPattern)
		{
			colliders[RWING]->Scale().y *= 2.2f;
			playOncePerPattern = true;
		}
	}

	if (RATIO > 0.96)
	{
		colliders[RWING]->Scale().y *= 0.4f;
		playOncePerPattern = false;
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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
		SetColliderAttack(RLEG1_FOOT, 0.367, 25, 1);
	}

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E2121()//���� ���� ����ٰ� �������� ��¦ �Ͼ�� �ٽ� �ڼ�����
{
	PLAY;

	if (RATIO > 0.277 && RATIO < 0.408)
	{
		SetColliderAttack(LWING, 0.408, 40, 2);
	}

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2092(float degree) //90�� ȸ�� 
{
	PLAY;

	if (RATIO > 0.0176f && RATIO < 0.176f)
		RotateToTarget(0.0176f, 0.176f);

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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
		SetColliderAttack(RWING, 0.15, 30, 2);
	}

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2144() // ���� ���� ����
{
	combo = true;
	PLAY;
	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2145() // ���� ���� ���� �� �齺��
{
	PLAY;

	if (RATIO < 0.6f)
		forwardBoom->SetActive(true);
	if (RATIO > 0.6f)
		forwardBoom->SetActive(false);

	if (RATIO > 0.96)
	{
		sequence++;
		//SetState(E_2146);
	}
}

void Valphalk::E2146() // ���� ���� �� ���� �����鼭 ����
{
	PLAY;
	if (RATIO > 0.96)
	{
		combo = false;
		sequence++;
		//SetState(E_0003);
	}
}

void Valphalk::E2171()
{
	PLAY;

	if (RATIO > 0.237 && RATIO < 0.417)
	{
		SetColliderAttack(HEAD, 0.417, 30, 1);
		SetColliderAttack(NECK, 0.417, 30, 1);
		SetColliderAttack(CHEST, 0.417, 30, 1);
	}

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2129()  // ���� �մٸ� ġ�� �غ�
{
	PLAY;

	if (RATIO > 0.26f)
		RotateToTarget(0.26, 0.96f);

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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
		SetColliderAttack(RLEG1_FOOT, 0.09, 25, 1);
	}

	if (RATIO > 0.256 && RATIO < 0.296)
	{
		SetColliderAttack(RWING, 0.296, 40, 2);
	}


	if (RATIO > 0.96)
	{
		sequence++;
	}

}

void Valphalk::E2151()
{
	PLAY;
	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2152()
{
	PLAY;
	if (RATIO > 0.5 && RATIO < 0.6)
		forwardBoom->SetActive(true);
	if (RATIO > 0.6)
		forwardBoom->SetActive(false);

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2153()
{
	PLAY;

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2174(float degree)// ���� ���ٰ� ���� ���� ������ ���
{
	combo = true;

	PLAY;

	if (RATIO > 0.056 && RATIO < 0.733f)
		RotateToTarget(0.056, 0.733f);

	if (RATIO > 0.96)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E2175(float degree)// ���� ���ٰ� ������ ���� ������ ���
{
	combo = true;

	PLAY;

	if (RATIO > 0.056 && RATIO < 0.733f)
		RotateToTarget(0.056, 0.733f);

	if (RATIO > 0.96)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E2185()// ����� ���� ���������� ������
{
	PLAY;

	if (RATIO > 0.121 && RATIO < 0.331)
	{
		SetColliderAttack(HEAD, 0.331, 25, 1);
	}

	if (RATIO > 0.96)
	{
		combo = false;
		sequence++;
	}
}

void Valphalk::E2188()//���� ���� �޹� ���
{
	PLAY;

	if (RATIO > 0.16 && RATIO < 0.8)
		RotateToTarget(0.16, 0.7);


	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E2189()//���鿡�� ���� ���� �޹� ���
{
	PLAY;

	if (RATIO > 0.19 && RATIO < 0.8)
		RotateToTarget(0.19, 0.7);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y -= XM_PIDIV2;
	}
}

void Valphalk::E2190()//���鿡�� �������� ���鼭 �ں��� �޹� ���
{
	PLAY;

	if (RATIO > 0.1 && RATIO < 0.8)
		RotateToTarget(0.1, 0.7);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y -= XM_PI;
	}
}

void Valphalk::E2192()//���鿡�� ������ ���� �޹� ���
{
	PLAY;

	if (RATIO > 0.19 && RATIO < 0.8)
		RotateToTarget(0.19, 0.7);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += XM_PIDIV2;
	}
}

void Valphalk::E2193()//���鿡�� ���������� ���鼭 �ں��� �޹� ���
{
	PLAY;

	if (RATIO > 0.1 && RATIO < 0.8)
		RotateToTarget(0.1, 0.7);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += XM_PI;
	}
}

void Valphalk::E2200()//S�� �����ġ��
{
	PLAY;

	if (RATIO > 0.073 && RATIO < 0.197)
	{
		SetColliderAttack(HEAD, 0.197, 25, 1);
		SetColliderAttack(NECK, 0.197, 25, 1);
		SetColliderAttack(CHEST, 0.197, 25, 1);
		SetColliderAttack(BODY, 0.197, 25, 1);
	}

	if (RATIO > 0.277 && RATIO < 0.445)
	{
		SetColliderAttack(HEAD, 0.445, 25, 1);
		SetColliderAttack(NECK, 0.445, 25, 1);
		SetColliderAttack(CHEST, 0.445, 25, 1);
		SetColliderAttack(BODY, 0.445, 25, 1);
	}

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2210()//���� 90�� ������� �غ���
{
	PLAY;

	if (RATIO > 0.700f && RATIO < 0.96f)
		RotateToTarget(0.700f, 0.96f);

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2211(float degree)//���� 90�� ������� ���ݵ���
{
	PLAY;

	if (RATIO < 0.105f)
		RotateToTarget(0.000f, 0.105f);

	if (RATIO > 0.117 && RATIO < 0.185)
	{
		SetColliderAttack(RWING, 0.185, 40, 2);
	}

	if (RATIO > 0.96)
	{
		Rot().y += degree;
		sequence++;
	}
}

void Valphalk::E2265()
{
	PLAY;

	if (RATIO > 0.96f)
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

	if (RATIO > 0.96f)
	{
		Rot().y -= 2.0933f;
		sequence++;
		Count = 1;
	}
}

void Valphalk::EX2265()
{
	PLAY;

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::EX2271(float degree) // �� 90
{
	PLAY;

	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::EX2276()
{
	PLAY;

	if (RATIO > 0.96)
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
	SetColliderAttack(BODY, 0.93, 40, 2);
	SetColliderAttack(CHEST, 0.93, 40, 2);
	SetColliderAttack(HEAD, 0.93, 40, 2);
	SetColliderAttack(RLEG1, 0.93, 40, 2);

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


	if (RATIO > 0.8)
	{
		Loop();
	}
}

void Valphalk::EX2278()
{
	PLAY;

	if (RATIO > 0.234f)
	{
		if (RATIO < 0.24f)
		{
			effectSphere1->Scale() = { 400, 400, 400 };
			effectSphere1->Pos() = GetTranslationByNode(83) + Back() * 100;
			effectSphere2->Scale() = { 400, 400, 400 };
			effectSphere2->Pos() = effectSphere1->Pos() + Back() * 700;
		}
		effectSphere1->SetActive(true);
		effectSphere2->SetActive(true);
	}

	if (RATIO > 0.4f)
	{
		effectSphere1->SetActive(false);
		effectSphere2->SetActive(false);
	}

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E2270()
{
	PLAY;

	if (RATIO > 0.96f)
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

	if (RATIO > 0.96f)
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

	if (RATIO > 0.96f)
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


	if (RATIO > 0.96f)
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


	if (RATIO > 0.96f)
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


	if (RATIO > 0.96f)
	{
		Rot().y += degree;
		Count = 1;
		sequence++;
	}
}

void Valphalk::E2286()
{
	PLAY;

	if (RATIO > 0.96f)
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

	if (RATIO > 0.96f)
	{
		//Pos() = GetTranslationByNode(1);
		combo = false;
		sequence++;
	}
}

void Valphalk::E2354(float degree) // Ǯ����Ʈ ����
{
	combo = false;
	PLAY;
	if (RATIO > 0.0176f && RATIO < 0.876f)
		RotateToTarget(0.0176f, 0.876f);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;

		//Pos() = realPos->Pos();
	}

}

void Valphalk::E2356(float degree) // Ǯ����Ʈ ��ȸ�� �ڷ� ����
{
	PLAY;
	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2359(float degree) // Ǯ����Ʈ ��ȸ�� �ڷ� ����
{
	PLAY;
	if (RATIO > 0.17 && RATIO < 0.56)
		RotateToTarget(0.17, 0.56);

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2361() // Ǯ����Ʈ �غ�
{
	PLAY;
	//fullBurst->Rot().y = head->Rot().y;
	fullBurst->Rot() = fullBurstRot;
	if (RATIO > 0.96)
	{
		sequence++;
		//Pos() = realPos->Pos();
	}

}

void Valphalk::E2367() // Ǯ����Ʈ �߻�
{
	PLAY;

	if (RATIO > 0.2)
		fullBurst->SetActive(true);

	if (RATIO > 0.8)
	{
		fullBurst->Pos().y += 7000 * DELTA;
		fullBurst->Rot().x += 0.82 * DELTA;
	}
	if (RATIO > 0.96)
	{
		sequence++;
		//Pos() = realPos->Pos();
	}

}

void Valphalk::E2368() // Ǯ����Ʈ ������
{
	PLAY;

	if (RATIO > 0.2)
		fullBurst->SetActive(false);

	if (RATIO > 0.96)
	{
		combo = false;
		Pos() = realPos->Pos();
		fullBurst->Pos() = fullBurstPos;
		fullBurst->Rot() = fullBurstRot;
		fullBurst->Scale() = fullBurstScale;
		sequence++;
	}
}

void Valphalk::E2253(Vector3 destVec)//���� ���鼭 ���������� �齺��
{
	PLAY;

	if (RATIO > 0.074f && RATIO < 0.37f)
	{
		Pos() = Lerp(Pos(), destVec, 3 * DELTA);
	}


	if (RATIO > 0.96)
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

	if (RATIO > 0.96f)
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

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::EX2372(float degree)
{
	PLAY;

	if (RATIO > 0.16 && RATIO < 0.79)
		RotateToTarget(0.16, 0.79);

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
	{
		sequence++;
		Rot().y += degree;
	}
}

void Valphalk::E2374()
{
	if (RATIO > 0.96f)
	{
		Pos() = GetTranslationByNode(1);

		SetState(E_2375);
		Count = 1;
	}
}

void Valphalk::E2375()
{
	if (Pos().y > 0.96f)
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
	if (RATIO > 0.96f)
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

	if (RATIO > 0.19f)
	{
		if (RATIO < 0.20f)
		{
			effectSphere1->Scale() = { 500, 500, 500 };
			effectSphere1->Pos() = GetTranslationByNode(64) + Back() * 100;
			effectSphere2->Scale() = { 500, 500, 500 };
			effectSphere2->Pos() = GetTranslationByNode(84) + Back() * 100;
		}
		effectSphere1->SetActive(true);
		effectSphere2->SetActive(true);;
	}

	if (RATIO > 0.4f)
	{
		effectSphere1->SetActive(false);
		effectSphere2->SetActive(false);
	}

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E2381()
{
	PLAY;
	if (RATIO > 0.16 && RATIO < 0.79)
		RotateToTarget(0.16, 0.59);
	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E2382()
{
	PLAY;
	if (RATIO > 0.16 && RATIO < 0.79)
		RotateToTarget(0.16, 0.59);
	if (RATIO > 0.96)
	{
		Rot().y -= XM_PIDIV2;
		sequence++;
	}
}

void Valphalk::E2383()
{
	PLAY;
	if (RATIO > 0.16 && RATIO < 0.79)
		RotateToTarget(0.16, 0.59);
	if (RATIO > 0.96)
	{
		Rot().y += XM_PIDIV2;
		sequence++;
	}
}

void Valphalk::E2082()
{
	PLAY;
	forwardBoom->Pos() = 0;
	forwardBoom->Scale().x = 3000;	

	if (RATIO > 0.2 && RATIO < 0.21)
	{
		forwardBoom->SetActive(true);
		Sounds::Get()->Play("em086_05_se_media_10", 0.5f);
	}
	if(RATIO>0.22 && RATIO < 0.23)
		Sounds::Get()->Play("em086_05_se_media_10_2", 0.5f);

	if (RATIO > 0.4 && RATIO < 0.41)
		forwardBoom->SetActive(false);

	if (RATIO < 0.2 && RATIO > 0.18)
		Sounds::Get()->Play("em086_05_vo_media_1", 0.3f);

	if (RATIO > 0.96)
	{
		sequence++;
	}
}

void Valphalk::E2403()
{
	PLAY;

	if (RATIO > 0.056f && RATIO < 0.09f)
	{
		SetColliderAttack(RLEG1_FOOT, 0.09f, 25, 1);
	}

	if (RATIO > 0.256f && RATIO < 0.684f)
	{
		effectBox1->SetActive(true);
		effectBox2->SetActive(true);
		effectBox3->SetActive(true);
		SetColliderAttack(RWING, 0.684f, 40, 2);
	}

	if (RATIO > 0.69f)
	{
		effectBox1->SetActive(false);
		effectBox2->SetActive(false);
		effectBox3->SetActive(false);
	}

	if (RATIO > 0.96f)
	{
		sequence++;
		combo = false;
		Count = 1;
	}
}

void Valphalk::E3001() // ���� ������ �ǰ�
{
	PLAY;

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E3006()
{
}

void Valphalk::E3015()
{
	combo = true;

	PLAY;

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E3016()
{
	PLAY;

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E3017()
{
	PLAY;

	if (RATIO > 0.96)
	{
		combo = false;
		sequence++;
	}
}

void Valphalk::E3023() // ���
{
	PLAY;

	if (RATIO > 0.96)
		isPlay = false;
}

void Valphalk::E3101()
{
	PLAY;

	if (RATIO > 0.96)
		sequence++;
}

void Valphalk::E3106()
{
}

void Valphalk::E3114()
{
	combo = true;

	PLAY;

	if (RATIO > 0.96)
	{
		isSlashMode = true;
		sequence++;
	}
}

void Valphalk::E3118()
{
	PLAY;

	if (RATIO > 0.96)
		isPlay = false;
}

void Valphalk::E4001()
{
	PLAY;

	if (RATIO > 0.96)
		sequence++;

}

void Valphalk::E4013() // ���� ��ȿ
{
	PLAY;
	if (RATIO > 0.325 && RATIO < 0.375)
	{
		Sounds::Get()->Play("em086_05_vo_media_10", 0.5f);
		if (!playOncePerPattern)
		{
			colliders[ROAR]->SetActive(true);
			SetColliderAttack(ROAR, 0.375f, 0, 3);
			playOncePerPattern = true;
		}
	}

	if (RATIO > 0.375)
		colliders[ROAR]->SetActive(false);

	if (RATIO > 0.96)
	{
		playOncePerPattern = false;
		sequence++;
		isFindTrgt = true;
	}
}

void Valphalk::E4071()
{
	PLAY;
	if (RATIO < 0.76f && RATIO > 0.75f)
	{
		Sounds::Get()->Play("em086_05_vo_media_20", 0.5f); // ��� ���� voice
		Sounds::Get()->Play("em086_05_fx_media_40", 0.5f); // ��� ���� sfx
	}
	if (RATIO > 0.97f)
		sequence++;
}

void Valphalk::E4073(float timer, float checkHp)
{
	PLAY;
	if (timer <= 3.2f && curHP <= checkHp - 300.0f)
	{
		sequence = 4;
		timer = 0;
	}

	if (timer > 3.2f)
	{
		sequence++;
	}
}

void Valphalk::E4074()
{
	PLAY;
	if (RATIO < 0.1f)
		Sounds::Get()->Play("em086_05_fx_media_51", 0.5f); // ��� ��


	if (RATIO > 0.9f)
	{
		sequence++;
	}
}

void Valphalk::E22005() // ��ȿ
{
	PLAY;
	if (RATIO > 0.5 && RATIO < 0.58)
		Sounds::Get()->Play("em086_05_vo_media_10", 0.5f);
	if (RATIO > 0.96)
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

	// ROAR capsuleCollider ���� ������ַ��� ������
	Transform* transForm = new Transform();
	transforms.push_back(transForm);
	CapsuleCollider* capsuleCollider = new CapsuleCollider(1000, 0.1f);
	capsuleCollider->SetActive(false);
	colliders.push_back(capsuleCollider);

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
		colliders[HEAD]->partHp = 8000;
		colliders[HEAD]->SetTag("HEAD");
	}

	// �� �κ�
	{
		colliders[NECK]->SetParent(transforms[NECK]);
		colliders[NECK]->Scale().x = 80.0f;
		colliders[NECK]->Scale().y = 60.0f;
		colliders[NECK]->Scale().z = 80.0f;
		colliders[NECK]->Rot().x = 1.80f;
		colliders[NECK]->part = NECK;
		colliders[NECK]->SetTag("NECK");
	}

	// ���� �κ�
	{
		colliders[CHEST]->SetParent(transforms[CHEST]);
		colliders[CHEST]->Scale().x = 150.0f;
		colliders[CHEST]->Scale().y = 110.0f;
		colliders[CHEST]->Scale().z = 150.0f;
		colliders[CHEST]->Rot().x = 0.02;
		colliders[CHEST]->part = CHEST;
		colliders[CHEST]->partHp = 1500;
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
		colliders[LWING_RADIUS]->part = LWING_RADIUS;
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
		colliders[RWING_RADIUS]->part = RWING_RADIUS;
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
		colliders[LLEG1]->partHp = 2500;
		colliders[LLEG1]->SetTag("LLEG1");
	}

	// ���� �߹ٴ� (��)
	{
		colliders[LLEG1_FOOT]->SetParent(transforms[LLEG1_FOOT]);
		colliders[LLEG1_FOOT]->Scale().x = 80.0f;
		colliders[LLEG1_FOOT]->Scale().y = 90.0f;
		colliders[LLEG1_FOOT]->Scale().z = 100.0f;
		colliders[LLEG1_FOOT]->Rot().x = 2.55f;
		colliders[LLEG1_FOOT]->part = LLEG1_FOOT;
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
		colliders[LLEG2_FOOT]->part = LLEG2_FOOT;
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
		colliders[RLEG1]->partHp = 2500;
		colliders[RLEG1]->SetTag("RLEG1");
	}

	// ������ �ٸ� �߹ٴ�(��)
	{
		colliders[RLEG1_FOOT]->SetParent(transforms[RLEG1_FOOT]);
		colliders[RLEG1_FOOT]->Scale().x = 80.0f;
		colliders[RLEG1_FOOT]->Scale().y = 90.0f;
		colliders[RLEG1_FOOT]->Scale().z = 100.0f;
		colliders[RLEG1_FOOT]->Rot().x = -0.45f;
		colliders[RLEG1_FOOT]->part = RLEG1_FOOT;
		//colliders[RLEG1_FOOT]->Rot().y = 22.0f;
		colliders[RLEG1_FOOT]->SetTag("RLEG1_FOOT");
	}

	// ������ �ٸ� (��)
	{
		colliders[RLEG2]->SetParent(transforms[RLEG2]);
		colliders[RLEG2]->Scale().x = 70.0f;
		colliders[RLEG2]->Scale().y = 60.0f;
		colliders[RLEG2]->Scale().z = 70.0f;
		colliders[RLEG2]->part = RLEG2;
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
		colliders[RLEG2_FOOT]->part = RLEG2_FOOT;
		colliders[RLEG2_FOOT]->SetTag("RLEG2_FOOT");
	}

	// ���� ����
	{
		colliders[TAIL_START]->SetParent(transforms[TAIL_START]);
		colliders[TAIL_START]->Scale().x = 120.0f;
		colliders[TAIL_START]->Scale().y = 100.0f;
		colliders[TAIL_START]->Scale().z = 120.0f;
		colliders[TAIL_START]->Rot().x = 1.78f;
		colliders[TAIL_START]->part = TAIL_START;
		colliders[TAIL_START]->SetTag("TAIL_START");
	}

	// ���� 1/4 �κ�
	{
		colliders[TAIL_1]->SetParent(transforms[TAIL_1]);
		colliders[TAIL_1]->Scale() *= 80.0f;
		colliders[TAIL_1]->Rot().x = 1.55f;
		colliders[TAIL_1]->part = TAIL_1;
		colliders[TAIL_1]->SetTag("TAIL_1");
	}

	// ���� 1/2 �κ�
	{
		colliders[TAIL_2]->SetParent(transforms[TAIL_2]);
		colliders[TAIL_2]->Scale().x = 50.0f;
		colliders[TAIL_2]->Scale().y = 60.0f;
		colliders[TAIL_2]->Scale().z = 50.0f;
		colliders[TAIL_2]->Rot().x += 1.6f;
		colliders[TAIL_2]->part += TAIL_2;
		colliders[TAIL_2]->SetTag("TAIL_2");
	}

	// ���� �� �κ�
	{
		colliders[TAIL]->SetParent(transforms[TAIL]);
		colliders[TAIL]->Scale() *= 80.0f; // ����
		colliders[TAIL]->Rot().x += 4.8f;
		colliders[TAIL]->part = TAIL;
		colliders[TAIL]->partHp = 2500;
		colliders[TAIL]->SetTag("TAIL");
	}

	// ��ȿ �浹ü �κ�
	{
		colliders[ROAR]->SetParent(transforms[ROAR]);
		colliders[ROAR]->Scale() *= 80.0f; // ����
		colliders[ROAR]->part = ROAR;
		colliders[ROAR]->SetTag("ROAR");
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

	// ��ȿ �浹ü
	transforms[ROAR]->SetWorld(GetTransformByNode(3)); // body ��ġ ���
}
