
#include "Framework.h"
#include "Player.h"
#include "Scenes/ShadowScene.h"

Player::Player() : ModelAnimator("Player")
{
	head			= new Transform();
	realPos			= new Transform();
	backPos			= new Transform();
	forwardPos		= new Transform();
	swordStart		= new Transform();
	swordEnd		= new Transform();
	mainHand		= new Transform();
	backSwd			= new Transform();

	swordCollider	= new CapsuleCollider(2.0f, 100.0f);
	swordCollider->Rot().x += XM_PIDIV2;
	swordCollider->SetParent(mainHand);
	swordCollider->Pos().z -= 100.0f;
	swordCollider->Scale() *= 3.0f;

	trail = new Trail(L"Textures/Effect/Snow.png", swordStart, swordEnd, 20, 85);
	
	/////////////////////////////////////////////////////////////
	// Particles
	
	FOR(7) 
		hitParticle.push_back(new HitParticle());
	hitBoomParticle = new HitBoomParticle();
	criticalParticle = new CriticalParticle();
	spAtkParticle = new Sp_atk_ready_Particle();

	/////////////////////////////////////////////////////////////
	longSword = new Model("kal");
	longSword->SetParent(mainHand);

	kalzip = new Model("kalzip");
	kalzip->SetParent(backSwd);

	//	longSword->Rot().x -= XM_PIDIV2;	

	tmpCollider = new CapsuleCollider(1,0.1);
	tmpCollider->Scale() *= 6.0f;

	tmpCollider2 = new CapsuleCollider(1, 0.1);
	tmpCollider2->Scale() *= 6.0f;
	tmpCollider2->SetParent(backPos);

	tmpCollider3 = new CapsuleCollider(1, 0.1);
	tmpCollider3->Scale() *= 24.0f;
	tmpCollider3->SetParent(forwardPos);

	//	tmpCollider->SetParent(head);
	//	tmpCollider->SetParent(back);

	ReadClips();

	CAM->SetTarget(head);
	

	//ĳ���Ϳ� UI �߰�

}

Player::~Player()
{
	delete mainHand;
	delete head;
	delete realPos;
	delete tmpCollider;
	hitParticle.clear();
	delete hitBoomParticle;
	delete criticalParticle;
	delete spAtkParticle;
}

void Player::Update()
{	
	Control();
	ResetPlayTime();
	UpdateWorlds();
	TermAttackUpdate();	

	trail->Update();
	FOR(hitParticle.size())		hitParticle[i]->Update();
	hitBoomParticle->Update();
	criticalParticle->Update();
	spAtkParticle->Update();

	ModelAnimator::Update();
	//UIManager::Get()->Update();
	Potion();	
	GroundCheck();

}

void Player::Render()
{
	ModelAnimator::Render();
	tmpCollider->Render();
	tmpCollider2->Render();
//	tmpCollider3->Render();
	//swordCollider->Render();
	longSword->Render();
	kalzip->Render();

	if (renderEffect)
	{
		trail->Render();
	}		
	
	FOR(hitParticle.size())
		hitParticle[i]->Render();
	hitBoomParticle->Render();
	criticalParticle->Render();
	spAtkParticle->Render();
}


void Player::UpdateWorlds()
{
	if (!State_S())
	{
		mainHand->SetWorld(GetTransformByNode(rightHandNode));
		longSword->Pos() = {};
		longSword->Rot() = {};
	}
	else if (State_S())
	{
		mainHand->SetWorld(GetTransformByNode(backSwdNode));
		longSword->Pos() = { -32,32,23 };
		longSword->Rot() = { -0.86f,-1.2f,+1.46f };
	}

	if (holdingSword)
	{
		backSwd->SetWorld(GetTransformByNode(lefeHandNode));
		kalzip->Pos() = { };
		kalzip->Rot() = { };
	}
	else
	{
		backSwd->SetWorld(GetTransformByNode(backSwdNode));
		kalzip->Pos() = { -32,32,23 };
		kalzip->Rot() = { -0.86f,-1.2f,+1.46f };
	}

	realPos->Pos() = GetTranslationByNode(1);

	realPos->UpdateWorld();

	backPos->Pos() = GetTranslationByNode(1) + Forward() * 100;
	forwardPos->Pos() = GetTranslationByNode(1) + Back() * 50 + Vector3::Up() * 80 ;

	head->Pos() = realPos->Pos() + Vector3::Up() * 200;

	lastSwordEnd = swordStart->Pos();

	swordStart->Pos() = longSword->GlobalPos() + longSword->Back() * 271.0f; // 20.0f : 10% ũ�� �ݿ�
	swordEnd->Pos() = longSword->GlobalPos() + longSword->Back() * 260.0f;

	swordStart->UpdateWorld();
	swordEnd->UpdateWorld();

	swordSwingDir = lastSwordEnd - swordStart->GlobalPos();
	tmpCollider->Pos() = GetTranslationByNode(node);

	backPos->UpdateWorld();
	forwardPos->UpdateWorld();

	longSword->UpdateWorld();
	kalzip->UpdateWorld();
	head->UpdateWorld();
	tmpCollider->UpdateWorld();
	tmpCollider2->UpdateWorld();
	tmpCollider3->UpdateWorld();

	swordCollider->Update();
}

void Player::Potion()
{
	time += DELTA;

	if (KEY_DOWN('E'))
	{
		Sounds::Get()->Play("health_potion", 0.3f);
		cure = true;
		time = 0;
	}
	if (cure == true)
	{
		if (time < 2)
		{
			UIManager::Get()->HealthPotion();
		}
		else if (time >= 2)
		{
			cure = false;
			return;
		}
	}

	if (KEY_DOWN('R'))
	{
		Sounds::Get()->Play("health_potion", 0.3f);
		Lcure = true;
		time = 0;
	}
	if (Lcure == true)
	{
		if (time < 3)
		{
			UIManager::Get()->HealthPotion();
		}
		else if (time >= 3)
		{
			Lcure = false;
			return;
		}
	}
	if (KEY_DOWN('T'))
	{
		Sounds::Get()->Play("health_potion", 0.3f);
		UIManager::Get()->curStamina = 100;
	}
}


void Player::GUIRender()
{
	ModelAnimator::GUIRender();
//	trail->GetMaterial()->GUIRender();
//	hitParticle->GUIRender();

	//particle->GetMaterial()->GUIRender();

//	Vector3 Forward = root->Forward();
//	float t = atan2(Forward.x, Forward.z);
//	float t = root->Rot().y;
//	ImGui::DragFloat("Player.y", &t); 
//
//	Vector3 CAMForward = CAM->Forward();	
//	float y = atan2(CAMForward.x, CAMForward.z);
//	ImGui::DragFloat("CAM.y", &y);

	Vector3 realpos = realPos->Pos();
	
	ImGui::DragFloat3("RealPos", (float*)&realpos);

	Vector3 pos = Pos();
	ImGui::DragFloat3("RealPos", (float*)&pos);
	//
	//int U = Keyboard::Get()->ReturnFirst();
	//ImGui::SliderInt("keyboard", &U, 0, 200);
	//
	//
//	ImGui::SliderInt("node", &node, 1, 10);
//	ImGui::SliderFloat("temp", &temp, -10, 10);
//	ImGui::SliderFloat("temp2", &temp2, -10, 10);
//	ImGui::SliderFloat("temp3", &temp3, 10, 15);
//		
//	//longSword->GUIRender();
//	kalzip->GUIRender();

	// t = GetClip(1)->GetRatio();
	// ImGui::DragFloat("ratio_1", &t);

	//Matrix x = GetTransformByNode(0);
	//Vector3 S, R, T;
	//XMMatrixDecompose(S.GetValue(), R.GetValue(), T.GetValue(), x);
	//
	//string temp = "_Pos";
	//ImGui::DragFloat3(temp.c_str(), (float*)&T, 0.1f);
	//
	//temp = "_GlobalPos";
	//Vector3 globalPos = GetTranslationByNode(0);
	//ImGui::DragFloat3(temp.c_str(), (float*)&globalPos, 0.1f);
	//
	//temp = "Real_GlobalPos";
	//Vector3 Pos = root->GlobalPos();
	//ImGui::DragFloat3(temp.c_str(), (float*)&Pos, 0.1f);
}

void Player::PostRender()
{
//	StatusRender(); // ��� �߰����̹Ƿ� �ּ�
	DamageRender();
}

void Player::Control()
{
	switch (curState)
	{
	case Player::S_001:		S001();		break;
	case Player::S_003:		S003();		break;
	case Player::S_005:		S005();		break;
	case Player::S_008:		S008();		break;
	case Player::S_009:		S009();		break;
	case Player::S_014:		S014();		break;
	case Player::S_017:		S017();		break;
	case Player::S_018:		S018();		break;
	case Player::S_026:		S026();		break;
	case Player::S_029:		S029();		break;
	case Player::S_038:		S038();		break;
	case Player::S_118:		S118();		break;
	case Player::S_119:		S119();		break;
	case Player::S_120:		S120();		break;

	// �̵� ���
	case Player::L_001:		L001();		break;
	case Player::L_002:					break;
	case Player::L_003:					break;
	case Player::L_004:		L004();		break;
	case Player::L_005:		L005();		break;
	case Player::L_006:					break;
	case Player::L_007:					break;
	case Player::L_008:		L008();		break;
	case Player::L_009:					break;
	case Player::L_010:		L010();		break;
	case Player::L_011:					break;
	case Player::L_012:					break;
	case Player::L_013:					break;
	case Player::L_014:		L014();		break;
	case Player::L_015:					break;
	case Player::L_071:					break;
	case Player::L_072:					break;
	case Player::L_073:					break;
	case Player::L_077:					break;
	case Player::L_078:					break;
	case Player::L_079:					break;
	// ���� ���
	case Player::L_101:		L101();		break;
	case Player::L_102:		L102();		break;
	case Player::L_103:		L103();		break;
	case Player::L_104:		L104();		break;
	case Player::L_105:		L105();		break;
	case Player::L_106:		L106();		break;
	case Player::L_107:		L107();		break;
	case Player::L_108:		L108();		break;
	case Player::L_109:		L109();		break;
	case Player::L_110:		L110();		break;

	case Player::L_113:		L113();		break;
	case Player::L_114:		L114();		break;
	case Player::L_115:		L115();		break;
	case Player::L_116:		L116();		break;
	case Player::L_119:		L119();		break;
	case Player::L_122:		L122();		break;
	case Player::L_128:		L128();		break;
	case Player::L_130:		L130();		break;
	case Player::L_131:		L131();		break;
	case Player::L_132:		L132();		break;
	case Player::L_133:		L133();		break;
	case Player::L_134:		L134();		break;
	case Player::L_135:		L135();		break;
	case Player::L_136:		L136();		break;
	case Player::L_137:		L137();		break;
	case Player::L_138:		L138();		break;



	case Player::L_147:		L147();		break;
	case Player::L_151:		L151();		break;
	case Player::L_152:		L152();		break;
	case Player::L_153:		L153();		break;
	case Player::L_154:		L154();		break;
	case Player::L_155:		L155();		break;
	case Player::L_156:		L156();		break;
	}

	if (KEY_UP('W') || KEY_UP('A') || KEY_UP('S') || KEY_UP('D'))
	{
		rotSpeed = 10;
	}
}

void Player::Move()
{
	bool isMoveZ = false; // ���� �̵� �� �ƴ�
	bool isMoveX = false; // �¿� �̵� �� �ƴ�

	if (KEY_PRESS('W'))
	{
		//Pos() += Back() * moveSpeed * DELTA;
		velocity.z = 1;//+= DELTA; // �ӵ�(���뺯��)�� ��Ÿ��ŭ ���İ� �ֱ�		
		isMoveZ = true; //���� �̵� ���� ��
	}

	if (KEY_PRESS('S'))
	{
		velocity.z = 1;
		isMoveZ = true;
	}

	if (KEY_PRESS('A'))
	{
		velocity.z = 1;
		isMoveX = true;
	}

	if (KEY_PRESS('D'))
	{
		velocity.z = 1;
		isMoveX = true;
	}

	if (velocity.Length() > 1) //�ӵ��� ��ü ��ġ�� 1�� ������ (������ ǥ���� ������ ���̰� 1 �ʰ�)
		velocity.Normalize(); //����ȭ
	// ������ �Ÿ� : �� �ڵ尡 ���� ������....?

			//�¿�ȸ���� ��İ�꿡 ���� ����� ���� ( = ���� ���ϱ�)
	Matrix rotY = XMMatrixRotationY(Rot().y); ;
	Vector3 direction = XMVector3TransformCoord(velocity, rotY); // ������ ������ ������ "����"�� ���� ���� ����

	Pos() += direction * -1 * moveSpeed * DELTA; //"����" ������ �̵�

	Vector3 CAMForward = CAM->Back();
	Vector3 CAMBack = CAM->Back() * -1;
	Vector3 CAMLeft = CAM->Right();
	Vector3 CAMRight = CAM->Right() * -1;

	Vector3 CAMLeftForward = CAM->Back() + CAM->Right();
	Vector3 CAMRightForward = CAM->Back() + CAM->Left();
	Vector3 CAMLeftBack = CAM->Right() + CAM->Forward();
	Vector3 CAMRightBack = CAM->Left() + CAM->Forward();

	Vector3 forward = Back();//�� �������� �� ������

	if (rotSpeed >= 0)
	{
		rotSpeed -= 0.05f;
		if (rotSpeed <= 3)
			rotSpeed = 3;
	}
		if (KEY_PRESS('W'))
	{
		Vector3 cross = Cross(forward, CAMForward);//�������̿��� ���� ����

		if (cross.y < 0)//������ ���̴� --> ���� ���� ���⺸�� �������� ���� ���̴� ----> ����
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)//�ݴ��� ���
		{			
			Rot().y -= rotSpeed * DELTA;
		}			
	}
	if (KEY_PRESS('S'))
	{
		Vector3 cross = Cross(forward, CAMBack);

		if (cross.y < 0)
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			Rot().y -= rotSpeed * DELTA;
		}
	}
	if (KEY_PRESS('A'))
	{
		Vector3 cross = Cross(forward, CAMLeft);

		if (cross.y < 0)
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			Rot().y -= rotSpeed * DELTA;
		}
	}
	if (KEY_PRESS('D'))
	{
		Vector3 cross = Cross(forward, CAMRight);

		if (cross.y < 0)
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			Rot().y -= rotSpeed * DELTA;
		}
	}
	if (KEY_PRESS('A') && KEY_PRESS('W') )
	{
		Vector3 cross = Cross(forward, CAMLeftForward);

		if (cross.y < 0)
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			Rot().y -= rotSpeed * DELTA;
		}
	}
	if (KEY_PRESS('D') && KEY_PRESS('W'))
	{
		Vector3 cross = Cross(forward, CAMRightForward);

		if (cross.y < 0)
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			Rot().y -= rotSpeed * DELTA;
		}
	}
	if (KEY_PRESS('A') && KEY_PRESS('S'))
	{
		Vector3 cross = Cross(forward, CAMLeftBack);

		if (cross.y < 0)
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			Rot().y -= rotSpeed * DELTA;
		}
	}
	if (KEY_PRESS('D') && KEY_PRESS('S'))
	{
		Vector3 cross = Cross(forward, CAMRightBack);

		if (cross.y < 0)
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			Rot().y -= rotSpeed * DELTA;
		}
	}

	if (KEY_PRESS('W') && KEY_PRESS('S'))
	{
		Vector3 cross = Cross(forward, CAMRightBack);

		if (cross.y < 0)
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			Rot().y -= rotSpeed * DELTA;
		}
	}

	if (KEY_PRESS('D') && KEY_PRESS('A'))
	{
		Vector3 cross = Cross(forward, CAMRightBack);

		if (cross.y < 0)
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)
		{
			Rot().y -= rotSpeed * DELTA;
		}
	}

	if (KEY_FRONT(Keyboard::CTRL))
	{
		SetState(L_106);
		return;
	}
	//if (!isMoveZ) // ���� �̵� ���� �ƴϸ�
	//	velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //������ ���� ����
	//
	//if (!isMoveX) // �¿��̵��� ����
	//	velocity.x = Lerp(velocity.x, 0, deceleration * DELTA);	
}

void Player::ResetPlayTime()
{
	if (preState != curState)
		GetClip(preState)->ResetPlayTime();
}

void Player::Rotate()
{
	Vector3 newForward;
	newForward = Lerp(Forward(), CAM->Back(), rotSpeed * DELTA);
	float rot = atan2(newForward.x, newForward.z);
	//Rot().y = rot;

	//ĳ���� ���� ���� ���� ���ϱ� �� �������̸� Forward(),CAM->Forawrd �ϵ�
	//newForward = Cross(Back(), CAM->Back);
	//float rot = atan2(newForward.x, newForward.z);
	//Rot().y = rot;

}

bool Player::Attack(float power, bool push, UINT useOtherCollider) // �浹���� �Լ�
{
	renderEffect = true;

	Valphalk* val =
		dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetValphalk();

	Contact contact;

	auto colliders = val->GetCollider();
	
	CapsuleCollider* playerCollider = swordCollider;
	if (useOtherCollider != 0)
	{
		renderEffect = false;
		switch (useOtherCollider)
		{
		case 1:	playerCollider = tmpCollider; break;
		case 2:	playerCollider = tmpCollider2; break;
		case 3:	playerCollider = tmpCollider3; break;
		default: playerCollider = swordCollider; break;
		}
	}



	for (auto collider : colliders)
	{
		if (playerCollider->IsCapsuleCollision(collider, &contact) && !attackOnlyOncePerMotion)
		{			
			criticalParticle->ParticleRotate();
			hitBoomParticle->Play(contact.hitPoint, swordSwingDir);
			criticalParticle->Play(contact.hitPoint, swordSwingDir );
			hitParticle[lastParticleIndex]->Play(contact.hitPoint, swordSwingDir);
			lastParticleIndex++;
			if (lastParticleIndex >= hitParticle.size())
				lastParticleIndex = 0;

			attackOnlyOncePerMotion = true;

			if (curState == L_101 || curState == L_102 || curState == L_103 || curState == L_104 || curState == L_105) // ���κ��� �ƴ϶�� ������ ����
				UIManager::Get()->PlusSpritGauge();

			if (curState == L_109) // ���� ū ȸ������ ���߽ÿ���
			{
				UIManager::Get()->PlusCotingLevel(); // ���� ������ 1 �ø���
				UIManager::Get()->SetMaxCoting(); // ���ÿ� ���� ������ 100���� �ʱ�ȭ
			}
			if (curState == L_154) // �ɾƹߵ� ���� ���߽� ���ΰ����� ��� ����
			{
				UIManager::Get()->Bonus154True();
			}

			float hardness = 1.0f;
			switch (collider->part)
			{
				case Valphalk::HEAD  : hardness = 55; break;
				case Valphalk::BODY	 : hardness = 30; break;
				case Valphalk::LWING : hardness = 22; break;
				case Valphalk::RWING : hardness = 22; break;
				case Valphalk::LLEG1 : hardness = 25; break;
				case Valphalk::LLEG2 : hardness = 25; break;
				case Valphalk::RLEG1 : hardness = 25; break;
				case Valphalk::RLEG2 : hardness = 25; break;
				case Valphalk::TAIL  : hardness = 45; break;
				default				 : hardness = 1 ; break;
			}
			UIManager::Get()->MinusDurability();
			

			Damage damage;
			float deal = 300 * 0.06 * power * hardness * 0.01f * UIManager::Get()->GetCotingLevelCoefft() * UIManager::Get()->GetDurabilityLevelCoefft();
			damage.damage = (int)deal;
			// ((���ݷ�/�������) * ��� ���� * (����/100 )) * ������ ���� ��� * ���� ���� ���
			damage.pos = contact.hitPoint;
			damage.hitPart = collider->part;
			lastHitPart = collider->part;
			lastSwordDir = swordSwingDir;

			if (hardness >= 30)				// ������ 30 �̻����� ����������� �ߴ� ��Ȳ
				damage.isWeakness = true;
			else
				damage.isWeakness = false;

			if(push)
				damages.push_back(damage);

			return true;;
		}
	}

	return false;
}

void Player::AttackWOCollision(float power)
{
	Valphalk* val =
		dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetValphalk();
	auto colliders = val->GetCollider();

	int hitPart = lastHitPart;

	Vector3 hitPos    = colliders[hitPart]->GetHitPointPos();
	Vector3 MinHitPos = hitPos + Vector3::Down() * 30;
	Vector3 MaxHitPos = hitPos + Vector3::Up() * 30;
	Vector3 RandomPos = Random(MinHitPos, MaxHitPos);

	Vector3 MinSwdDir = lastSwordDir + Vector3(-0.1, -0.1, -0.1);
	Vector3 MaxSwdDir = lastSwordDir + Vector3(0.1, 0.1, 0.1);
	Vector3 RandomSwdDir = Random(MinSwdDir, MaxSwdDir);
	hitBoomParticle->Play(RandomPos, RandomSwdDir);
	criticalParticle->ParticleRotate();
	criticalParticle->Play(RandomPos, RandomSwdDir);
	hitParticle[lastParticleIndex]->Play(RandomPos, RandomSwdDir);
	lastParticleIndex++;
	if (lastParticleIndex >= hitParticle.size())
		lastParticleIndex = 0;

	float hardness = 1.0f;
	switch (lastHitPart)
	{
	case Valphalk::HEAD: hardness = 55; break;
	case Valphalk::BODY: hardness = 30; break;
	case Valphalk::LWING: hardness = 22; break;
	case Valphalk::RWING: hardness = 22; break;
	case Valphalk::LLEG1: hardness = 25; break;
	case Valphalk::LLEG2: hardness = 25; break;
	case Valphalk::RLEG1: hardness = 25; break;
	case Valphalk::RLEG2: hardness = 25; break;
	case Valphalk::TAIL: hardness = 45; break;
	default: hardness = 1; break;
	}

	Damage damage;
	float deal = 300 * 0.06 * power * hardness * 0.01f * UIManager::Get()->GetCotingLevelCoefft() * UIManager::Get()->GetDurabilityLevelCoefft();
	damage.damage = (int)deal;
	// ((���ݷ�/�������) * ��� ���� * (����/100 )) * ������ ���� ��� * ���� ���� ���
	damage.pos = RandomPos;

	if (hardness >= 30)				// ������ 30 �̻����� ����������� �ߴ� ��Ȳ
		damage.isWeakness = true;
	else
		damage.isWeakness = false;

	damages.push_back(damage);
}

bool Player::CollisionCheck()
{
	Valphalk* val =
		dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetValphalk();
	auto colliders = val->GetCollider();

	for (auto collider : colliders)
		if (tmpCollider3->IsCapsuleCollision(collider))
			return true;;

	return false;
}

void Player::SetAnimation()
{
}

void Player::Roll()
{
	moveSpeed = 400;
	Vector3 CAMLeftForward = CAM->Back() + CAM->Right();
	Vector3 CAMRightForward = CAM->Back() + CAM->Left();
	Vector3 CAMLeftBack = CAM->Right() + CAM->Forward();
	Vector3 CAMRightBack = CAM->Left() + CAM->Forward();
	Vector3 forward = Back();
	Vector3 newForward;
	if (UIManager::Get()->curStamina < 20) // ���¹̳� ������ġ �̸������� ������ ����
		return;
	UIManager::Get()->Roll();

	if (KEY_PRESS('W'))
	{
		newForward = Lerp(Forward(), CAM->Back(), rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('S'))
	{
		newForward = Lerp(Back(), CAM->Forward(), rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('A'))
	{
		newForward = Lerp(Left(), CAM->Right(), rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('D'))
	{
		newForward = Lerp(Right(), CAM->Left(), rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('W') && KEY_PRESS('A') || KEY_PRESS('A') && KEY_PRESS('W')) // �»� ������
	{
		newForward = Lerp(Left() + Forward(), CAMLeftForward, rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('W') && KEY_PRESS('D') || KEY_PRESS('D') && KEY_PRESS('W')) // ��� ������
	{
		newForward = Lerp(Right() + Forward(), CAMRightForward, rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('S') && KEY_PRESS('A') || KEY_PRESS('A') && KEY_PRESS('S')) // ���� ������
	{
		newForward = Lerp(Left() + Back(), CAMLeftBack, rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('S') && KEY_PRESS('D') || KEY_PRESS('D') && KEY_PRESS('S')) // ���� ������
	{
		newForward = Lerp(Right() + Back(), CAMRightBack, rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}

	holdingSword = false;

	if (State_S())
		SetState(S_017);
	else if (!State_S())
		SetState(L_010);

	UIManager::Get()->staminaActive = true;

}

void Player::TermAttackUpdate()
{
	if (!isHitL155 && !isHitL133 && !isHitL136)
		return;

	if (isHitL155)
	{
		TermAttackTimer += DELTA;

		if (TermAttackTimer > 0.4 && TermAttackTimer < 0.5)
		{
			if (!playOncePerTerm)
			{
				AttackWOCollision(17);
				playOncePerTerm = true;
			}
		}
		else if (TermAttackTimer > 0.55f && TermAttackTimer < 0.65f)
		{
			if (playOncePerTerm)
			{
				AttackWOCollision(17);
				playOncePerTerm = false;
			}
		}
		else if (TermAttackTimer > 0.7f && TermAttackTimer < 0.8f)
		{
			if (!playOncePerTerm)
			{
				AttackWOCollision(17);
				playOncePerTerm = true;
			}
		}
		else if (TermAttackTimer > 0.8f)
		{
			isHitL155 = false;
			playOncePerTerm = false;
			TermAttackTimer = 0.0;
		}
	}


	if (isHitL133)
	{
		TermAttackTimer2 += DELTA;
		int dmg = 0;
		if		(UI->cotingLevel == 2) dmg = 28;
		else if (UI->cotingLevel == 1) dmg = 17.5f;
		else if (UI->cotingLevel == 0) dmg = 10.5f;


		if (TermAttackTimer2 > 0.6 && TermAttackTimer2 < 0.65)
		{
			if (!playOncePerTerm2)
			{
				AttackWOCollision(dmg);
				playOncePerTerm2 = true;
			}
		}
		else if (TermAttackTimer2 > 0.70f && TermAttackTimer2 < 0.75f)
		{
			if (playOncePerTerm2)
			{
				AttackWOCollision(dmg);
				playOncePerTerm2 = false;
			}
		}
		else if (TermAttackTimer2 > 0.80f && TermAttackTimer2 < 0.85f)
		{
			if (!playOncePerTerm2)
			{
				AttackWOCollision(dmg);
				playOncePerTerm2 = true;
			}
		}
		if (TermAttackTimer2 > 0.9 && TermAttackTimer2 < 0.95)
		{
			if (playOncePerTerm2)
			{
				AttackWOCollision(dmg);
				playOncePerTerm2 = false;
			}
		}
		else if (TermAttackTimer2 > 1.0f && TermAttackTimer2 < 1.05f)
		{
			if (!playOncePerTerm2)
			{
				AttackWOCollision(dmg);
				playOncePerTerm2 = true;
			}
		}
		else if (TermAttackTimer2 > 1.1f && TermAttackTimer2 < 1.15f)
		{
			if (playOncePerTerm2)
			{
				AttackWOCollision(dmg);
				playOncePerTerm2 = false;
			}
		}
		else if (TermAttackTimer2 > 1.2f)
		{
			isHitL133 = false;
			TermAttackTimer2 = 0.0;
		}
	}

	if (isHitL136)
	{
		TermAttackTimer2 += DELTA;

		if (TermAttackTimer2 > 0.1 && TermAttackTimer2 < 0.15)
		{
			if (!playOncePerTerm2)
			{
				AttackWOCollision(19);
				playOncePerTerm2 = true;
			}
		}
		else if (TermAttackTimer2 > 0.2f && TermAttackTimer2 < 0.25f)
		{
			if (playOncePerTerm2)
			{
				AttackWOCollision(19);
				playOncePerTerm2 = false;
			}
		}
		else if (TermAttackTimer2 > 0.3f)
		{
			isHitL136 = false;
			TermAttackTimer2 = 0.0;
		}
	}

}

void Player::SetState(State state)
{
	if (curState == state)
		return;
	Pos() = realPos->Pos();
	if (Pos().y < 0)
		Pos().y = 0;

	if (curState == L_155)
	{
		Vector3 realForward = forwardPos->GlobalPos() - backPos->GlobalPos();
		Rot().y = atan2(realForward.x, realForward.z);
	}

	preState = curState;
	curState = state;
	attackOnlyOncePerMotion = false;
	//	PlayClip(state);
}

void Player::EndEffect()
{
	if (!renderEffect)
		return;

	effectTimer += DELTA;

	if (effectTimer > 0.1f)
	{
		renderEffect = false;
		effectTimer = 0;
	}

}

void Player::ReadClips()
{
	// ��Ŭ�� ����� ������ ���ĺ� ����� ��!! �ƴϸ� "" << �̷���

	ReadClip("L_001");
	ReadClip("L_002");
	ReadClip("L_003");
	ReadClip("L_004");
	ReadClip("L_005");
	ReadClip("L_006");
	ReadClip("L_007");
	ReadClip("L_008");
	ReadClip("L_009");
	ReadClip("L_010");
	ReadClip(" _011");
	ReadClip(" _012");
	ReadClip(" _013");
	ReadClip("L_014");
	ReadClip(" _015");
	ReadClip(" _071");
	ReadClip(" _072");
	ReadClip(" _073");
	ReadClip(" _077");
	ReadClip(" _078");
	ReadClip(" _079");
	ReadClip("L_101");
	ReadClip("L_102");
	ReadClip("L_103");
	ReadClip("L_104");
	ReadClip("L_105");
	ReadClip("L_106");
	ReadClip("L_107");
	ReadClip("L_108");
	ReadClip("L_109");
	ReadClip("L_110");

	ReadClip("L_113");
	ReadClip("L_114");
	ReadClip("L_115");
	ReadClip("L_116");
	ReadClip("L_119");
	ReadClip("L_122");
	ReadClip("L_128");
	ReadClip("L_130");
	ReadClip("L_131");
	ReadClip("L_132");
	ReadClip("L_133");
	ReadClip("L_134");
	ReadClip("L_135");
	ReadClip("L_136");
	ReadClip("L_137");
	ReadClip("L_138");

	ReadClip("L_147");
	ReadClip("L_151");
	ReadClip("L_152");
	ReadClip("L_153");
	ReadClip("L_154");
	ReadClip("L_155");
	ReadClip("L_156");

	ReadClip("S_001");
	ReadClip("S_003");
	ReadClip("S_005");
	ReadClip("S_008");
	ReadClip("S_009");
	ReadClip("S_014");
	ReadClip("S_017");
	ReadClip("S_018");
	ReadClip("S_026");
	ReadClip("S_029");
	ReadClip("S_038");
	ReadClip("S_118");
	ReadClip("S_119");
	ReadClip("S_120");
}

void Player::RecordLastPos()
{
	//Pos() = root->GlobalPos();
	Pos() = GetTranslationByNode(1);
}

void Player::S001() // ���� Idle
{
	PLAY;
	if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
		SetState(S_005);
	moveSpeed = 10;

	// �� Ŭ�� ���� ���� �ϴ°� �߰�
	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}
	UIManager::Get()->staminaActive = false;
}

void Player::S003() // �������� �޸���
{
	PLAY;
	Move();
	Rotate();

	if (UIManager::Get()->curStamina < 0.1f)
		SetState(S_118);

	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D')) // �̵� �� Ű�� �� ��
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D')) // �ٸ� Ű�� ���� ���������� ���ư���.
			return;
		// ��� �̵�Ű�� �Էµ��� ���� �� ����
		SetState(S_014);
		return;
	}

	if (KEY_PRESS(VK_LSHIFT)) // ����Ʈ ������ ��������
	{
		SetState(S_038);
		return;
	}

	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}

	if (KEY_DOWN(VK_SPACE))
		Roll();
	UIManager::Get()->staminaActive = false;

}

void Player::S005() // ����� �޸���
{
	PLAY;
	Move();
	
	if (moveSpeed <= 400)
		moveSpeed += 500 * DELTA;
	
	//Rotate();
	if (RATIO > 0.97 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
	{
		SetState(S_003);
		moveSpeed = 400;
		return;
	}

	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D'))
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
			return;

		SetState(S_014);
		return;
	}


	// 101 ���� ����
	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}
	
	//if (KEY_PRESS(VK_LSHIFT))
	//	SetState(S_008);
	if (KEY_DOWN(VK_SPACE))
		Roll();
}

void Player::S008() // ���� ����
{
	PLAY;
	//Move();
	Rotate();
	if(RATIO>0.6)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);

	if (RATIO > 0.94 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
	{
		SetState(S_003);
		return;
	}

	if (RATIO > 0.98)
	{
		//ReturnIdle();
		SetState(S_001);
	}

}

void Player::S009() // �����鼭 ����
{
	PLAY;
	Move();
	Rotate();
	if (RATIO > 0.4)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);

	if (RATIO > 0.94 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
	{
		SetState(S_003);
		return;
	}
	if (RATIO > 0.98)
	{
		//ReturnIdle();
		SetState(S_001);
	}


}

void Player::S014() // �޸��� ����
{
	PLAY;
	Move();
	if (preState == S_001)
		moveSpeed = 400;

	if (moveSpeed >= 0)
		moveSpeed -= 500 * DELTA;

	//Rotate();
	if (RATIO > 0.97)
	{
		SetState(S_001);
	}
}

void Player::S017() // ������ �� ���ڸ�
{
	PLAY;

	if (GetClip(S_017)->GetRatio() > 0.6f && KEY_PRESS('W') ||
		GetClip(S_017)->GetRatio() > 0.6f && KEY_PRESS('S') ||
		GetClip(S_017)->GetRatio() > 0.6f && KEY_PRESS('A') ||
		GetClip(S_017)->GetRatio() > 0.6f && KEY_PRESS('D'))
	{
		SetState(S_018);
	}

	if (GetClip(S_017)->GetRatio() > 0.98)
	{
		ReturnIdle2();
	}
}

void Player::S018() // �������� ������ �� �̵�Ű ������
{
	PLAY;
	Move();
	Rotate();
	// �� ����ȭ
	{
		if (RATIO > 0 && RATIO < 0.9)
			CAM->Zoom(300, 5);
	}

	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D'))
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
			return;

		SetState(S_014);
		return;
	}
	if (GetClip(S_018)->GetRatio() > 0.48 && KEY_DOWN(VK_SPACE))
	{
		Roll();
	}
	if (GetClip(S_018)->GetRatio() > 0.98)
	{
		SetState(S_003);
		UIManager::Get()->staminaActive = false;
	}
}

void Player::S026() // ����� �ȱ����
{
}

void Player::S029() // �ȴ���
{
}

void Player::S038() // ��������
{
	PLAY;
	Move();
	Rotate();
	if (moveSpeed <= 650)
		moveSpeed += 500 * DELTA;
	if (UIManager::Get()->curStamina < 0.1f) // ���¹̳� ������ġ �̸������� �޸��� ����
	{
		SetState(S_118);
		return;
	}
	UIManager::Get()->Running();
	/*if (RATIO > 0.97)
		moveSpeed++;*/

	if (KEY_UP(VK_LSHIFT))
	{
		moveSpeed = 400;
		SetState(S_003);
		return;
	}

	//Rotate();
	/*if (RATIO > 0.97 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
	{
		SetState(S_003);
		moveSpeed = 500;
		return;
	}*/

	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D'))
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
			return;

		moveSpeed = 400;
		SetState(S_014);
		return;
	}


	// 101 ���� ����
	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}

	//if (KEY_PRESS(VK_LSHIFT))
	//	SetState(S_008);
	if (KEY_DOWN(VK_SPACE))
		Roll();
	UIManager::Get()->staminaActive = true;

}

void Player::S118() // Ż�� ����
{
	PLAY;
	UIManager::Get()->curStamina += 2.0f * DELTA;
	if (RATIO > 0.98f)
		SetState(S_120);
}

void Player::S119() // Ż�� ��
{	
	PLAY;
	UIManager::Get()->curStamina += 2.0f * DELTA;
	if (RATIO > 0.98f)
	{
		SetState(S_001);
		return;
	}	
}

void Player::S120() // Ż�� ��
{
	PLAY;
	UIManager::Get()->curStamina += 12.0f * DELTA;
	if (UIManager::Get()->curStamina > 40)
		SetState(S_119);
}

void Player::L001() // �ߵ����� ���
{
	PLAY;
	moveSpeed = 400;
	if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
		SetState(L_005);

	else if (KEY_PRESS(VK_LSHIFT))		SetState(S_008); // ����	
	else if (K_LMB)		SetState(L_101);	// 101 ���� ����	
	else if (K_RMB)		SetState(L_104);	// 104 ���	
	else if (K_LMBRMB)	SetState(L_103);	// 103 �������
	else if (K_CTRL)	SetState(L_106);	// 106 ���� ����	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
	else if (K_SPACE)	Roll();				// 010 ������

	UIManager::Get()->staminaActive = false;

}

void Player::L002() // �ߵ�
{
	Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
	PLAY;
}

void Player::L003() // ���� ����
{
	PLAY;
	Move();
	Rotate();
}

void Player::L004() // �ߵ����� �ȱ� �� // ����
{
	PLAY;
	//

	if (KEY_PRESS(VK_LSHIFT))		SetState(S_009); // ����	
	else if (K_LMB)		SetState(L_101);	// 101 ���� ����	
	else if (K_RMB)		SetState(L_104);	// 104 ���	
	else if (K_LMBRMB)	SetState(L_103);	// 103 �������
	else if (K_CTRL)	SetState(L_106);	// 106 ���� ����	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
	else if (K_SPACE)	Roll();				// 010 ������


	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D')) // �̵� �� Ű�� �� ��
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D')) // �ٸ� Ű�� ���� ���������� ���ư���.
			return;
		// ��� �̵�Ű�� �Էµ��� ���� �� ����
		SetState(L_008);
		return;
	}

	Move();
	Rotate();

	if (RATIO > 0.98)
	{
		Loop();
	}
}

void Player::L005() // �ߵ����� �ȱ� ���� (�ߵ���)
{
	PLAY;
	
	if (KEY_PRESS(VK_LSHIFT))		SetState(S_009); // ����	
	else if (K_LMB)		SetState(L_101);	// 101 ���� ����	
	else if (K_RMB)		SetState(L_104);	// 104 ���	
	else if (K_LMBRMB)	SetState(L_103);	// 103 �������
	else if (K_CTRL)	SetState(L_106);	// 106 ���� ����	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
	else if (K_SPACE)	Roll();				// 010 ������

	Move();
	Rotate();

	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D'))
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
			return;

		SetState(L_008);
		return;
	}

	if (RATIO < 0.6)
		Rotate();

	if (RATIO > 0.98 )
	{
		if((KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
			SetState(L_004);
		else 
			ReturnIdle();
	}

}

void Player::L006() // ���� (���X)
{
}

void Player::L007() // ���� (���X)
{
}

void Player::L008() // ����
{
	PLAY;

	if (KEY_PRESS(VK_LSHIFT))		SetState(S_009); // ����	
	else if (K_LMB)		SetState(L_101);	// 101 ���� ����	
	else if (K_RMB)		SetState(L_104);	// 104 ���	
	else if (K_LMBRMB)	SetState(L_103);	// 103 �������
	else if (K_CTRL)	SetState(L_106);	// 106 ���� ����	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
	else if (K_SPACE)	Roll();				// 010 ������

	if (RATIO > 0.5 && RATIO <= 0.98)
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
		{
			SetState(L_005);
		}
	}

	if (RATIO > 0.98)
	{
		GetClip(L_008)->SetPlayTime(-100.3f);
		ReturnIdle();
		SetState(L_001);
	}
}

void Player::L009() // �����鼭 ����
{
	PLAY;
}

void Player::L010() // ������
{
	PLAY;

	//if (GetClip(L_010)->GetRatio() > 0.65 && GetClip(L_010)->GetRatio() <= 0.94)
	//	if (KEY_PRESS('W'))
	//		SetState(L_005);

	// �� ����ȭ
	{
		if (RATIO > 0 && RATIO < 0.9)
			CAM->Zoom(300, 5);
	}
	if (GetClip(L_010)->GetRatio() > 0.45f && KEY_PRESS('W')||
		GetClip(L_010)->GetRatio() > 0.45f && KEY_PRESS('S')||
		GetClip(L_010)->GetRatio() > 0.45f && KEY_PRESS('A')||
		GetClip(L_010)->GetRatio() > 0.45f && KEY_PRESS('D'))
	{
		SetState(L_014);
	}


	if (GetClip(L_010)->GetRatio() > 0.98)
	{
		ReturnIdle();
	}
	
}

void Player::L014() // �ߵ����� ������ �� �̵�Ű ������
{
	PLAY;
	Move();
	Rotate();
	// �� ����ȭ
	{
		if (RATIO > 0 && RATIO < 0.9)
			CAM->Zoom(300, 5);
	}

	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D'))
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
			return;

		SetState(L_008);
		return;
	}

	if (GetClip(L_014)->GetRatio() > 0.48 && KEY_DOWN(VK_SPACE))
	{
		Roll();
	}
	if (GetClip(L_014)->GetRatio() > 0.98)
	{
		SetState(L_004);
		UIManager::Get()->staminaActive = false;
	}
}

void Player::L101() // ���𵮺���
{	
	// PlayClip �ϴµ� ��� �ݺ��ؼ� ȣ��Ǹ� ��� �ݺ��Ǵϱ� ���� + �� �ѹ��� ����Ǵ°� ����
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
		UIManager::Get()->staminaActive = false;
		PlayClip(L_101);
		MotionRotate(30);
	}
	if(RATIO>0.3 && RATIO<0.35)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if(RATIO>0.18 && RATIO<0.21)
		Sounds::Get()->Play("Heeee", .5f);

	if (RATIO < 0.3)
		Rot().y = Lerp(Rot().y, rad, 0.001f);


	// �� ����ȭ (�ɾ� ���� ȸ�� ���⿡�� �Ѿ�� ���)
	{
		if (RATIO > 0 && RATIO < 0.45)
			CAM->Zoom(300, 5);
	}


	// �������� ������
	{
		if (RATIO > 0.264 && RATIO < 0.44)
			Attack(26);
		else
			EndEffect();
	}


	// ĵ�� ���� ������
	if (RATIO > 0.6 && RATIO < 0.98)
	{

		if		(K_LMB)				SetState(L_102);	// ���κ���		
		else if (K_RMB)				SetState(L_104);	// ���
		else if (K_LMBRMB)			SetState(L_103);	// �������
		else if (K_CTRL)			SetState(L_106);	// ���κ���1		
		else if (K_CTRLRMB)			SetState(L_147);	// ���� ����
		else if (K_CTRLSPACE)		SetState(L_151);	// Ư�� ����
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)			Roll();		
	}

	// ���� ������
	if (RATIO > 0.98)
	{
		ReturnIdle();
	}

}

void Player::L102() // ���κ���
{
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
		PlayClip(L_102);
		MotionRotate(30);
	}
	if (RATIO > 0.25 && RATIO < 0.28)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// ���� ���� ���� ������
	{
		if (RATIO < 0.3)
			Rot().y = Lerp(Rot().y, rad, 0.001f);
	}

	// �������� ������
	{
		if (RATIO > 0.3 && RATIO < 0.375)
			Attack(26);
		else
			EndEffect();
	}

	// �Ļ� ���� ������
	if (RATIO > 0.5 && RATIO < 0.98)
	{
		if		(K_LMB || K_RMB)	SetState(L_104);	// ���
		else if (K_LMBRMB)			SetState(L_103);	// �������
		else if (K_CTRL)			SetState(L_106);	// ���κ���1		
		else if (K_CTRLRMB)			SetState(L_147);	// ���� ����
		else if (K_CTRLSPACE)		SetState(L_151);	// Ư�� ����
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)			Roll();
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L103() // �������
{
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
		UIManager::Get()->staminaActive = false;
		PlayClip(L_103);
		MotionRotate(30);
	}

	if (RATIO > 0.2 && RATIO < 0.25)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO < 0.272)
		Rot().y = Lerp(Rot().y, rad, 0.001f);
		
	// �������� ������
	{
		if (RATIO > 0.272 && RATIO < 0.456)
			Attack(24);
		else
			EndEffect();
	}

	if (RATIO > 0.87)
	{
		if		(K_RMB)				SetState(L_104);	// ���
		else if (K_CTRL)			SetState(L_110);	// ���γ��𵮺���		
		else if (K_CTRLRMB)			SetState(L_147);	// ���� ����
		else if (K_CTRLSPACE)		SetState(L_151);	// Ư�� ����
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)			Roll();
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L104() // ���
{
	PLAY;
	if(INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);

	if (RATIO > 0.1 && RATIO < 0.15)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// �������� ������
	{
		UIManager::Get()->staminaActive = false;
		if (RATIO > 0.1 && RATIO < 0.213)
			Attack(14);
		else
			EndEffect();
	}

	if (RATIO > 0.40 && RATIO < 0.98)
	{
		if		(K_LMB || K_RMB)	SetState(L_105);	// ����ø���
		else if (K_LMBRMB)			SetState(L_103);	// �������
		else if (K_CTRL)			SetState(L_106);	// ���κ���1		
		else if (K_CTRLRMB)			SetState(L_147);	// ���� ����
		else if (K_CTRLSPACE)		SetState(L_151);	// Ư�� ����
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)			Roll();
		
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L105() // ���� �ø���
{
	PLAY;
	if(INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
	if (RATIO > 0.1 && RATIO < 0.12)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// �������� ������
	{
		if (RATIO > 0.1 && RATIO < 0.2)
			Attack(18);
		else
			EndEffect();
	}

	if (RATIO > 0.4 && RATIO < 0.98)
	{		
		if		(K_LMB)			SetState(L_102);	// ���κ���		
		else if (K_RMB)			SetState(L_104);	// ���		
		else if (K_LMBRMB)		SetState(L_103);	// �������		
		else if (K_CTRL)		SetState(L_106);	// ���κ���1		
		else if (K_CTRLRMB)		SetState(L_147);	// ���� ����
		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)		Roll();
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L106() // ���� ���� 1
{
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		PlayClip(curState);
		initForward = Forward();
		UIManager::Get()->MinusSpiritGauge() ; // ���ΰ����� �Ҹ��ϱ�( �� 1�� )
	}
	if (RATIO > 0.3 && RATIO < 0.31)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	UIManager::Get()->staminaActive = false;

	// �������� ������
	{
		if (RATIO > 0.33 && RATIO < 0.416)
			Attack(31);
		else
			EndEffect();
	}

	if (RATIO > 0.43)
	{
		
		if		(K_RMB)			SetState(L_104);	// ���		
		else if (K_LMBRMB)		SetState(L_103);	// �������		
		else if (K_CTRL)		SetState(L_107);	// ���� ����2		
		else if (K_CTRLRMB)		SetState(L_147);	// ���� ����		
		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����		
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)		Roll();				// ������
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L107() // ���κ��� 2
{
	PLAY;
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		UIManager::Get()->MinusSpiritGauge(); // ���ΰ����� �Ҹ��ϱ�( �� 1�� )
	}
	if (RATIO > 0.25 && RATIO < 0.26)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// �������� ������
	{
		if (RATIO > 0.26 && RATIO < 0.38)
			Attack(33);
		else // 
			EndEffect(); 
	}

	// ĵ�� ���� ������
	{
		if (RATIO > 0.41)
		{
			if		(K_LMB || K_RMB)	SetState(L_105);	// ����ø���
			else if (K_LMBRMB)			SetState(L_103);	// �������		
			else if (K_CTRL)			SetState(L_108);	// ���� ����3		
			else if (K_CTRLRMB)			SetState(L_147);	// ���� ����
			else if (K_CTRLSPACE)		SetState(L_151);	// Ư�� ����		
			else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
			else if (K_SPACE)			Roll();				// ������		
		}
	}


	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L108() // ���κ��� 3
{
	if (INIT)
	{
		PlayClip(curState);		
		initForward = Forward();
		UIManager::Get()->MinusSpiritGauge(); // ���ΰ����� �Ҹ��ϱ�( �� 1�� )
	}
	if (RATIO > 0.1 && RATIO < 0.11)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.21)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.4 && RATIO < 0.46)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// �� ����ȭ (�ɾ� ���� ȸ�� ���⿡�� �Ѿ�� ���)
	{
		if (RATIO > 0 && RATIO < 0.45)
			CAM->Zoom(300, 5);
	}

	// �������� ������ (�� ����� 3�� ���� ������ ����)
	{
		if (RATIO > 0.05 && RATIO < 0.12)
			Attack(13);

		else if (RATIO > 0.14 && RATIO < 0.22)
		{
			if (!isDoubleStrikeMotion)
			{
				attackOnlyOncePerMotion = false;
				isDoubleStrikeMotion = true;
			}
			Attack(15);
		}
		else if (RATIO > 0.43 && RATIO < 0.47)
		{
			if (isDoubleStrikeMotion)
			{
				attackOnlyOncePerMotion = false;
				isDoubleStrikeMotion = false;
			}
			Attack(37);
		}
		else
			EndEffect();
	}

	if (RATIO > 0.50)
	{		
		if		(K_RMB || K_LMB)	SetState(L_104);  // ���		
		else if (K_LMBRMB)			SetState(L_103);  // �������		
		else if (K_CTRL)			SetState(L_109);  // ���� ūȸ������
		else if (K_CTRLRMB)			SetState(L_147);  // ���� ����
		else if (K_CTRLSPACE)		SetState(L_151);  // Ư�� ����		
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)			Roll();			  // ������		
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L109() // ���� ūȸ������
{
	PLAY;
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		UIManager::Get()->MinusSpiritGauge(); // ���ΰ����� �Ҹ��ϱ�( �� 1�� )
	}
	if (RATIO > 0.2 && RATIO < 0.21)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.1 && RATIO < 0.15)
		Sounds::Get()->Play("Heeee", .5f);
	if (RATIO > 0.7 && RATIO < 0.75)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);
	// ����
	{
		if (RATIO > 0 && RATIO < 0.16)
			CAM->Zoom(150);
	}


	// �������� ������ 
	{
		if (RATIO > 0.16 && RATIO < 0.24)
		{
			Attack(42);
			// �ܾƿ�
			CAM->Zoom(650);
		}
		else
			EndEffect();
	}

	// �� ����ȭ
	{
		if (RATIO > 0.47 && RATIO < 0.84)
			CAM->Zoom(300, 5);
	}


	if (RATIO > 0.30) // Ư�� ���� ���� Ÿ�̹� ����?
	{
		 if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����
		 else if(KEY_DOWN(VK_XBUTTON1)) SetState(L_101);
	}

	if (RATIO > 0.98)
		SetState(S_001);
}

void Player::L110() // ���� ���𵮺���
{
	PLAY;
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		UIManager::Get()->MinusSpiritGauge(); // ���ΰ����� �Ҹ��ϱ�( �� 1�� )
	}
	if (RATIO > 0.3 && RATIO < 0.31)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);

	// �������� ������ 
	{
		if (RATIO > 0.30f && RATIO < 0.406f)
			Attack(27);
		else
			EndEffect();
	}


	if (RATIO > 0.52) // ĵ�� ���� Ÿ�̹�
	{
		if (K_LMB || K_RMB)							SetState(L_105);    // ����ø���		
		else if (K_CTRLRMB)							SetState(L_147);    // ���� ����
		else if (K_CTRLSPACE)						SetState(L_151);	// Ư�� ����
		else if (K_CTRL)							SetState(L_108);	// ���κ���3
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)							Roll();				// ������
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L113()
{
}

void Player::L114()
{
}

void Player::L115()
{

}

void Player::L116()
{

}

void Player::L119() // �������� ����
{
	PLAY;	
	if (RATIO > 0.001 && RATIO < 0.002)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	// �������� ������ 
	{
		if (RATIO > 0.03f && RATIO < 0.19f)
			Attack(30);
		else
			EndEffect();
	}


	if (RATIO > 0.54) // ĵ�� ���� Ÿ�̹�
	{
		if (K_LMB || K_RMB || K_LMBRMB)
			SetState(L_104);    // ���
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L122()
{
	PLAY;
	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	// �������� ������ 
	{
		if (RATIO > 0.03f && RATIO < 0.19f)
			Attack(30);
		else
			EndEffect();
	}


	if (RATIO > 0.81) // ĵ�� ���� Ÿ�̹�
	{
		if (K_LMB || K_RMB || K_LMBRMB)
			SetState(L_104);    // ���
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L128()	// �������� ����
{
	PLAY;
	if (!playOncePerMotion)
	{		
		UI->UseBugSkill();
		playOncePerMotion = true;		
	}

	// �� ����ȭ (�ɾ� ���� ȸ�� ���⿡�� �Ѿ�� ���)
	{
		if (RATIO > 0 && RATIO < 0.9)
			CAM->Zoom(300, 5);
	}


	if (RATIO > 0.98)
	{
		SetState(L_130);
		playOncePerMotion = false;
	}
}

void Player::L130()	// �������� ü����
{
	PLAY;

	// ü����
	{
		if(Jump(850))
		// �������� ������
		{
			if ( Pos().y > 50 )
			{
				if (Attack(2, true, 3))
				{
					if (K_CTRL && UIManager::Get()->GetCotingLevel() > 0)
					{
						UIManager::Get()->MinusCotingLevel();
						SetState(L_133);  // ��������
					}
					else	 	SetState(L_136);  // �������
				}
			}

			if (RATIO > 0.98)
			{
				SetState(L_131);
			}
		}
		else
		{
			SetState(L_119);
		}
	}
}

void Player::L131() // ü�� ����
{
	PLAY;
	// ü����
	{
		if (Jump(850))
			// �������� ������
		{
			if (Attack(2,true, 3))
			{
				if (K_CTRL && UIManager::Get()->GetCotingLevel() > 0) 
				{
					UIManager::Get()->MinusCotingLevel();
					SetState(L_133);
				}  // ��������
				else	 	SetState(L_136);  // �������
			}

			if (RATIO > 0.98)
				Loop();
		}
		else
		{
			SetState(L_119);
		}
	}

}

void Player::L132()
{

}

void Player::L133()	// ��������
{
	PLAY;
	if(INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);

	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	if (RATIO > 0.4 && RATIO < 0.44)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// ü����
	{
		if (RATIO < 0.38) // �ܾƿ�
			CAM->Zoom(650, 5);

		// �������� Ÿ�̹�
		if (RATIO > 0.38)
		{
			if (Attack(0, false))
				isHitL133 = true;
			CAM->Zoom(300, 5);
		}


		if (realPos->Pos().y < 0)
		{
			Pos().y = 0.0f;
			jumpVelocity = originJumpVelocity;
			SetState(L_135);
		}
	}
}

void Player::L134()	// �������� ����
{

}

void Player::L135()	// �������� ��
{
	PLAY;
	EndEffect();
	CAM->Zoom(300, 5);	
	{
		if (RATIO > 0.23)
		{
			if (K_LMB || K_RMB)		SetState(L_104);	// ���
			else if(K_CTRLSPACE)	SetState(L_151);	// Ư������
			else if (K_SPACE)		Roll();				// ������
		}

		if (RATIO > 0.98)
		{
			SetState(L_001);
		}
	}
}

void Player::L136() // �������
{
	PLAY;
	if(INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);

	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	if(RATIO>0.5&&RATIO<0.54)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);

	// ü����
	{
		if (RATIO > 0.55)
		{
			if (Attack(19))
				isHitL136 = true;
		}

		if (realPos->Pos().y < 0)
		{
			EndEffect();
			Pos().y = 0.0f;
			jumpVelocity = originJumpVelocity;
			SetState(L_138);
		}
	}
}

void Player::L137() // ������� ����
{
}

void Player::L138() // ������� ��
{
	PLAY;

	// ü����
	{
		if (RATIO > 0.98)
		{
			ReturnIdle();
		}
	}
}

void Player::L147() // ���ĺ���
{
	PLAY;
	if(INIT)
	Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);

	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	UIManager::Get()->staminaActive = false;
	// �ܾƿ� && ȸ�� ���� ������
	{
		if (RATIO > 0 && RATIO < 0.30)
			CAM->Zoom(450);
	}

	// Ư�� ĵ�� ���� Ÿ�̹�
	{
		if (RATIO > 0.205f && RATIO < 0.30f && K_CTRLSPACE)
			SetState(L_151);	// Ư�� ����
	}


	// �������� ������ 
	{
		if (RATIO > 0.33 && RATIO < 0.43)
			Attack(27);
		else
			EndEffect();
	}

	// �� ����ȭ
	{
		if (RATIO > 0.33 && RATIO < 0.56)
			CAM->Zoom(300);
	}

	if (RATIO > 0.56) // ĵ�� ���� Ÿ�̹�
	{
		if		(K_LMB)			SetState(L_101);    // ���κ���		
		else if (K_RMB)			SetState(L_104);	// ���		
		else if (K_LMBRMB)		SetState(L_103);	// �������		
		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����
		else if (K_CTRL)		SetState(L_109);	// ����ūȸ������ (TODO :: �̰� ���� ��������)	
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)		Roll();				// ������
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L151() // Ư�� ����
{
	if (GetClip(curState)->isFirstPlay()) 
	{
		PlayClip(curState);
		initForward = Forward();
		holdingSword = true;
		EndEffect();
		UIManager::Get()->staminaActive = false;
	}
	if (RATIO > 0.5 && RATIO < 0.6)
	{
		spAtkParticle->Play({ Pos().x,Pos().y+100,Pos().z }, { 0,1,0 }); // ������ ���� �ʿ� �����տ� ���̱� (�����ڵ忡 �ٿ��� �ȳ���;)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);
	}
	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	// �� ����ȭ (���� ūȸ�� ���⿡�� �Ѿ�� ���)
	{
		if (RATIO > 0 && RATIO < 0.45)
			CAM->Zoom(300, 5);
	}	

	// ĵ�� ���� ������
	{
		if (RATIO > 0.72)
		{
			if		(K_LMB)		SetState(L_154); // �ɾƹߵ�����					
			else if (K_CTRL)	SetState(L_155); // �ɾƹߵ����κ���
		}
	}

	if (RATIO > 0.98)
	{
		SetState(L_152);
	}
}

void Player::L152() // Ư���������
{
	PLAY;

	if		(K_LMB)		SetState(L_154); // �ɾƹߵ�����					
	else if (K_CTRL)	SetState(L_155); // �ɾƹߵ����κ���
	else if (K_SPACE)   Roll();


	L152Timer += DELTA;
	if (L152Timer >= 3.0)
	{
		L152Timer = 0.0f;
		SetState(L_153);
	}
}

void Player::L153() // Ư������ ��� ����
{
	PLAY;

	if (RATIO > 0.98)
	{
		holdingSword = false;
		SetState(S_001);
	}
}

void Player::L154() // �ɾƹߵ� ����
{
	PLAY;
	if(INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
	if (RATIO > 0.01 && RATIO < 0.05)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.17 && RATIO < 0.18)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	// �������� ������ (�� ����� 2�� ���� ������ ����)
	{
		if (RATIO > 0.04 && RATIO < 0.17)
		{
			holdingSword = false;
			Attack(25);
		}
		else if (RATIO > 0.2 && RATIO < 0.3)
		{
			if (!isDoubleStrikeMotion)
			{
				attackOnlyOncePerMotion = false;
				isDoubleStrikeMotion = true;
			}
			Attack(30);
		}
		else
		{
			EndEffect();
			isDoubleStrikeMotion = false;
		}
	}

	// ĵ�� ���� ������
	{
		if (RATIO > 0.40)
		{
			if		(K_LMB)			SetState(L_102); // ���κ���
			else if (K_RMB)			SetState(L_104); // ���
			else if (K_CTRL)		SetState(L_106); // ���� ���� 1		
			else if (K_CTRLRMB)		SetState(L_147); // ���� ����
			else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
			else if (K_SPACE)		Roll();			 // ������
		}
	}

	if (RATIO > 0.98)
		ReturnIdle();

}

void Player::L155() // �ɾƹߵ� ���κ���
{
	PLAY;
	
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_8", .5f);
	}
	if (RATIO > 0.11 && RATIO < 0.15)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// �ܾƿ� && ȸ�� ���� ������
	{
		if (RATIO > 0.1 && RATIO < 0.18)
			CAM->Zoom(450);
	}

	static bool isHit = false;	// hit �ϰ� �ٷ� 3�� ���� ���� ����ϴϱ� �־��ִ� bool 

	// �������� ������ 
	{
		if (RATIO > 0.1 && RATIO < 0.36)
		{
			holdingSword = false;
			if(Attack(35)) 
				isHit = true;
		}
		else
			EndEffect();
	}

	// ī���� ���� �� �߰� ���� ������ (TODO :: ī���� ������ ������ ��)
	{
		if (isHit && (RATIO >0.385  && RATIO < 0.39))
		{
			if(isHitL155==false)
			UIManager::Get()->PlusCotingLevel();

			isHitL155 = true;
			Sounds::Get()->Play("pl_wp_l_swd_epv_media.bnk.2_8", .5f);			

		}
	}


	// ĵ�� ���� ������
	{
		if (RATIO > 0.39)
		{
			if		(K_LMB)			SetState(L_101); // ���𵮺���
			else if (K_CTRL)		SetState(L_108); // ���� ���� 3		
			else if (K_CTRLSPACE)	SetState(L_151); // Ư�� ����
			else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
			else if (K_SPACE)		Roll();			 // ������
		}
	}

	// �� ����ȭ
	{
		if (RATIO > 0.40 && RATIO < 0.85)
			CAM->Zoom(300, 5);
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
		isDoubleStrikeMotion = false;
		isHit = false;
	}
}

void Player::L156()
{


}

void Player::LRunning()
{
	PLAY;

	Move();
	Rotate();

	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D'))
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
			return;

		SetState(L_008);
		return;
	}

	if (RATIO < 0.6)
		Rotate();

	if (RATIO > 0.94 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
	{
		SetState(L_004);
		return;
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}

	if (KEY_DOWN(VK_SPACE))
		Roll();
}

void Player::MotionRotate(float degree)
{
	Vector3 forword = CAM->Back();
	camRot = atan2(forword.x, forword.z);

	float radian = XMConvertToRadians(degree);

	if (camRot > Rot().y)
	{
		rad = abs(camRot - Rot().y) > radian ?
			Rot().y + radian : camRot;
	}
	else
	{
		rad = abs(camRot - Rot().y) > radian ?
			Rot().y - radian : camRot;
	}

}

bool Player::State_S() // ���� ������Ʈ ���
{
	if (curState == S_001 || curState == S_003 || curState == S_005 ||
		curState == S_014 || curState == S_017 || curState == S_018 ||
		curState == S_038 || curState == S_118 || curState == S_119 || 
		curState == S_120)
		return true;

	else return false;
}

void Player::StatusRender()
{
	vector<string> strStatus;

	strStatus.push_back("L_001 �ߵ� ���� ���");
	strStatus.push_back("L_002 �ߵ�");
	strStatus.push_back("L_003 ��������");
	strStatus.push_back("L_004 �ߵ����� �ȱ�");
	strStatus.push_back("L_005 �ߵ����� �ȱ� ����");
	strStatus.push_back("L_006 �ߵ����� �·� �ȱ� ����");
	strStatus.push_back("L_007 �ߵ����� ��� �ȱ� ����");
	strStatus.push_back("L_008 ����");
	strStatus.push_back("L_009 �����鼭 ���� ");
	strStatus.push_back("L_010 �ձ�����");
	strStatus.push_back("L_011 ���ʱ�����");
	strStatus.push_back("L_012 �����ʱ�����");
	strStatus.push_back("L_013 �ڱ�����");
	strStatus.push_back("L_014 �����İȱ�");
	strStatus.push_back("L_015 �����ĵڰȱ�");
	strStatus.push_back("L_071 �������̾������");
	strStatus.push_back("L_072 �߰����̾������");
	strStatus.push_back("L_073 �������̾������");
	strStatus.push_back("L_077 ?");
	strStatus.push_back("L_078 ?");
	strStatus.push_back("L_079 ?");
	strStatus.push_back("L_101 ���𵮺���");
	strStatus.push_back("L_102 ���κ���");
	strStatus.push_back("L_103 �������");
	strStatus.push_back("L_104 ���");
	strStatus.push_back("L_105 ����ø���");
	strStatus.push_back("L_106 ���κ���1");
	strStatus.push_back("L_107 ���κ���2");
	strStatus.push_back("L_108 ���κ���3");
	strStatus.push_back("L_109 ����ūȸ������");
	strStatus.push_back("L_110 ���γ��𵮺���");
	strStatus.push_back("L_111 ���ں���");

	strStatus.push_back("S_003 ���� �޸���");
	strStatus.push_back("S_008 ���ڸ� ����");
	strStatus.push_back("S_009 �����鼭 ����");

	string fps = "Status : " + strStatus.at((UINT)curState);
	Font::Get()->RenderText(fps, { 150, WIN_HEIGHT - 30 });
}

void Player::DamageRender()
{
	for (auto& d : damages)
	{
		d.timer += DELTA;

		if (d.timer < 1.5f)
		{
			wstring dmg = to_wstring(d.damage);
			Vector3 pos = CAM->WorldToScreen(d.pos);

			FOR(dmg.size())
				Font::Get()->RenderText(dmg.substr(i, 1), { pos.x + temp3 * i + temp ,  pos.y - temp2 }, "Black");

			if(d.isWeakness)
				Font::Get()->RenderText(dmg, { pos.x, pos.y }, "Yellow");
			else
				Font::Get()->RenderText(dmg, { pos.x, pos.y }, "Gray");
		}

		else if (d.timer >= 1.5f && d.timer < 2.0f)
		{
			d.pos += Vector3::Up() * 100 * DELTA;
			wstring dmg = to_wstring(d.damage);
			Vector3 pos = CAM->WorldToScreen(d.pos);

			float alpha = (2.0f - d.timer) / 0.5f;

			FOR(dmg.size())
				Font::Get()->RenderText(dmg.substr(i, 1), { pos.x + temp3 * i + temp ,  pos.y - temp2 }, "Black", Float2(), alpha);

			if(d.isWeakness)
				Font::Get()->RenderText(dmg, { pos.x, pos.y }, "Yellow", Float2(), alpha);
			else
				Font::Get()->RenderText(dmg, { pos.x, pos.y }, "Gray", Float2(), alpha);
		}

	}

	auto eraseiter = damages.end();
	for (auto iter = damages.begin(); iter != damages.end(); iter++)
	{
		if ((*iter).timer > 6.0f)
			eraseiter = iter;
	}
	if (eraseiter != damages.end())
		damages.erase(eraseiter);
}

bool Player::Jump(float moveSpeed)
{
	jumpVelocity -= 9.8f * gravityMult * DELTA;
	Pos() += -1 * initForward * moveSpeed * DELTA;
	Pos().y += jumpVelocity;

	if (realPos->Pos().y >= 0)
	{
		return true;
	}

	if (realPos->Pos().y < 0)
	{
		Pos().y = 0.0f;
		jumpVelocity = originJumpVelocity;
		return false;
	}
}

void Player::GroundCheck()
{
	TerrainEditor* terrain = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetTerrain();

	Vector3 pos1;
	terrain->ComputePicking(pos1, realPos->Pos() + Vector3::Up() * 200, Vector3::Down());

//	Vector3 pos2;
//	terrain->ComputePicking(pos2, realPos->Pos(), Vector3::Up());

//	float y = max(pos1.y, pos2.y);
	Pos().y = pos1.y;
}
