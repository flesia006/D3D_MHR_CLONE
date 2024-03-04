
#include "Framework.h"
#include "Player.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/PlayerTestScene.h"
#include "Scenes/ValphalkTestScene.h"
#include "Scenes/FightTestScene.h"

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
	potionParticle = new PotionParticle();
	haloTransform = new Transform();
	haloCollider = new CapsuleCollider();
	haloCollider->SetParent(swordStart);	
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

	bodyCollider = new CapsuleCollider(35, 100);
	bodyCollider->SetParent(realPos);
	bodyCollider->Pos().y += 75.0f;
	bodyCollider->UpdateWorld();

	evadeCheckCollider = new CapsuleCollider(35, 100);
	evadeCheckCollider->Pos().y += 75.0f;
	evadeCheckCollider->SetActive(false);
	evadeCheckCollider->UpdateWorld();
	//	tmpCollider->SetParent(head);
	//	tmpCollider->SetParent(back);

	ReadClips();

	CAM->SetTarget(head);
}

Player::~Player()
{
	delete evadeCheckCollider;
	delete bodyCollider;
	delete tmpCollider3;
	delete tmpCollider2;
	delete tmpCollider;
	delete kalzip;
	delete longSword;
	delete haloCollider;
	delete potionParticle;
	delete spAtkParticle;
	delete criticalParticle;
	delete hitBoomParticle;
	hitParticle.clear();
	delete trail;
	delete swordCollider;
	delete backSwd;
	delete mainHand;
	delete swordEnd;
	delete swordStart;
	delete forwardPos;
	delete backPos;
	delete realPos;
	delete head;
}

void Player::Update()
{	
	if (!DeathCheck())
	{
		TermAttackUpdate();
		HurtCheck();
		Potion();
	}

	Control();
	ResetPlayTime();
	UpdateWorlds();
	trail->Update();
	FOR(hitParticle.size())		hitParticle[i]->Update();
	hitBoomParticle->Update();
	criticalParticle->Update();
	spAtkParticle->Update();	
	potionParticle->Update();
	//potionParticle->SetParent(realPos);
	potionParticle->SetPos(realPos->Pos());
	potionParticle->SetVortex({ realPos->Pos().x,realPos->Pos().y+100,realPos->Pos().z });

	ModelAnimator::Update();
	UIManager::Get()->Update();
	Potion();
	GroundCheck();

	if (KEY_DOWN('5'))/// ����� Ȯ�ο��̶� �ʿ������ ������ ��
		UI->curHP -= 30;
}

void Player::Render()
{
	ModelAnimator::Render();
	tmpCollider->Render();
	tmpCollider2->Render();
	bodyCollider->Render();
	evadeCheckCollider->Render();
//	tmpCollider3->Render();
	//swordCollider->Render();
	longSword->Render();
	kalzip->Render();

	if (renderEffect)
	{
		trail->Render();
	}		
	////////////////////////////////////////////
	// Particles
	FOR(hitParticle.size())
		hitParticle[i]->Render();
	hitBoomParticle->Render();
	criticalParticle->Render();
	haloCollider->Render();
	spAtkParticle->Render();	
	potionParticle->Render();

	spAtkParticle->Render();

	if (isSetState)
	{
		Pos() = realPos->Pos();
		isSetState = false;
	}
		
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

	if (Rot().y < -3.14)
		Rot().y += XM_2PI;

	if (Rot().y > 3.14)
		Rot().y -= XM_2PI;

	Vector3 camRot = CAM->Rot();
	camRot.y += XM_PI;

	if		(KEY_DP('W') && KEY_DP('D'))
		keyboardRot = camRot.y + XM_PIDIV4;
	else if (KEY_DP('W') && KEY_DP('A'))
		keyboardRot = camRot.y - XM_PIDIV4;
	else if (KEY_DP('S') && KEY_DP('D'))
		keyboardRot = camRot.y + XM_PIDIV4 * 3;
	else if (KEY_DP('S') && KEY_DP('A'))
		keyboardRot = camRot.y - XM_PIDIV4 * 3;
	else if (KEY_DP('W'))
		keyboardRot = camRot.y;
	else if (KEY_DP('A'))
		keyboardRot = camRot.y - XM_PIDIV2;
	else if (KEY_DP('S'))
		keyboardRot = camRot.y - XM_PI;
	else if (KEY_DP('D'))
		keyboardRot = camRot.y + XM_PIDIV2;
	else
		keyboardRot = 0.0f;

	if (keyboardRot < -3.14)
		keyboardRot += XM_2PI;

	if (keyboardRot > 3.14)
		keyboardRot -= XM_2PI;


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
	bodyCollider->Update();
	swordCollider->Update();

	haloTransform->Pos() = longSword->GlobalPos() + longSword->Back() * 55.f;
	haloCollider->Pos() = haloTransform->Pos();
}

void Player::Potion()
{
	time += DELTA;	

	if (UIManager::Get()->useQuickSlot1 && UIManager::Get()->haveGPotion > 0 && !Lcure && !cure
		|| UIManager::Get()->useDragSlot1 && UIManager::Get()->haveGPotion > 0 && KEY_DOWN('E') && !Lcure && !cure)
	{		
		Sounds::Get()->Play("health_potion", 0.3f);
		UIManager::Get()->haveGPotion--;
		Lcure = true;
		time = 0;
	}
	if (Lcure == true)
	{
		UIManager::Get()->useQuickSlot1 = false;
		UIManager::Get()->useQuickSlot2 = false;
		if (time < 0.1f)
			potionParticle->Play({ Pos().x,Pos().y+100,Pos().z }, { 0,0,0 });

		if (time < 3)
		{
			UIManager::Get()->LargeHealthPotion();
		}
		else if (time >= 3)
		{
			Lcure = false;
		}
	}

	if (UIManager::Get()->useQuickSlot2 && UIManager::Get()->havePotion > 10 && !cure && !Lcure
		|| UIManager::Get()->useDragSlot3 && UIManager::Get()->havePotion > 10 && KEY_DOWN('E') && !cure && !Lcure)
	{
		Sounds::Get()->Play("health_potion", 0.3f);
		UIManager::Get()->havePotion--;
		cure = true;
		time = 0;
	}
	if (cure == true)
	{
		UIManager::Get()->useQuickSlot1 = false;
		UIManager::Get()->useQuickSlot2 = false;
		if (time < 0.1f)
			potionParticle->Play({ Pos().x,Pos().y+100,Pos().z }, { 0,0,0 });

		if (time < 2)
		{
			UIManager::Get()->HealthPotion();
		}
		else if (time >= 2)
		{
			cure = false;
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

	Vector3 rot = Rot();
	ImGui::DragFloat3("Rot", (float*)&rot);

	Vector3 camRot = CAM->Rot();
	camRot.y += XM_PI;
	if (camRot.y < -3.14)
		camRot.y += XM_2PI;

	if (camRot.y > 3.14)
		camRot.y -= XM_2PI;

	ImGui::DragFloat3("camRot", (float*)&camRot);

	float keyDir = keyboardRot;
	ImGui::DragFloat("KeyDir", &keyDir);


	float ratio = RATIO;
	ImGui::DragFloat("clipRatio", &ratio);

	ImGui::DragFloat("Speed", &temp4);

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
	case Player::S_011:		S011();		break;
	case Player::S_014:		S014();		break;
	case Player::S_017:		S017();		break;
	case Player::S_018:		S018();		break;
	case Player::S_019:		S019();		break;
	case Player::S_020:		S020();		break;
	case Player::S_026:		S026();		break;
	case Player::S_029:		S029();		break;
	case Player::S_038:		S038();		break;
	case Player::S_118:		S118();		break;
	case Player::S_119:		S119();		break;
	case Player::S_120:		S120();		break;
	case Player::S_122:		S122();		break;

	// �̵� ���
	case Player::L_001:		L001();		break;
	case Player::L_002:					break;
	case Player::L_003:					break;
	case Player::L_004:		L004();		break;
	case Player::L_005:		L005();		break;
	case Player::L_006:					break;
	case Player::L_007:					break;
	case Player::L_008:		L008();		break;
	case Player::L_009:		L009();		break;
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

	// �ǰ� ���
	case Player::L_400:		L400();		break;
	case Player::L_403:		L403();		break;
	case Player::L_451:		L451();		break;
	case Player::L_453:		L453();		break;
	case Player::L_455:		L455();		break;

	case Player::D_001:		D001();		break;
	case Player::D_004:		D004();		break;
	case Player::D_007:		D007();		break;
	case Player::D_011:		D011();		break;
	case Player::D_015:		D015();		break;
	case Player::D_016:		D016();		break;
	case Player::D_021:		D021();		break;
	case Player::D_022:		D022();		break;
	case Player::D_026:		D026();		break;
	case Player::D_029:		D029();		break;
	case Player::D_030:		D030();		break;
	case Player::D_031:		D031();		break;
	case Player::D_032:		D032();		break;
	case Player::D_033:		D033();		break;
	case Player::D_045:		D045();		break;
	case Player::D_046:		D046();		break;
	case Player::D_066:		D066();		break;
	case Player::D_078:		D078();		break;
	case Player::D_079:		D079();		break;
	case Player::D_080:		D080();		break;
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

void Player::Rotate(float rotateSpeed)
{
	if (keyboardRot != 0.0f)
	{
		if (abs(Rot().y - keyboardRot) > 3.14)
		{
			if (keyboardRot < 0)	keyboardRot += XM_2PI;
			else					keyboardRot -= XM_2PI;
		}

		if (keyboardRot > Rot().y)
			RealRotate(rotateSpeed * DELTA);
		else
			RealRotate(-rotateSpeed * DELTA);
	}

}

void Player::LimitRotate(float limit)
{
	if (keyboardRot != 0.0f)
	{
		if (abs(Rot().y - keyboardRot) > 3.14)
		{
			if (keyboardRot < 0)	keyboardRot += XM_2PI;
			else					keyboardRot -= XM_2PI;
		}		


		if (keyboardRot > Rot().y)
		{
			sumRot += 5* DELTA;
			if (sumRot < unitRad * limit)
			{
				RealRotate(5 * DELTA);
			}
		}
		else
		{
			sumRot += 5 * DELTA;
			if (sumRot < unitRad * limit)
			{
				RealRotate(-5 * DELTA);
			}
		}
	}
}

bool Player::Attack(float power, bool push, UINT useOtherCollider) // �浹���� �Լ�
{
	renderEffect = true;

	if (SceneManager::Get()->Add("ShadowScene") == nullptr && SceneManager::Get()->Add("PlayerTestScene") != nullptr)
		return AttackDummy(power, push, useOtherCollider);

	Valphalk* val = nullptr;
	if(SceneManager::Get()->Add("ShadowScene") == nullptr && SceneManager::Get()->Add("FightTestScene") != nullptr)
		val = dynamic_cast<FightTestScene*>(SceneManager::Get()->Add("FightTestScene"))->GetValphalk();
	else
		val = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetValphalk();


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
			if (curState == L_147 && isEvaded) // ���ĺ��� ȸ�Ǽ��� �� ���߽ÿ���
			{
				UIManager::Get()->SetMaxGauge(); // ���� �������� �ִ�� �����
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
			
			val->minusCurHP(deal);

			if (collider->part == Valphalk::HEAD
				|| collider->part == Valphalk::LLEG1
				|| collider->part == Valphalk::RLEG1
				|| collider->part == Valphalk::TAIL)
				collider->minusPartHP(deal);

			if (collider->part == Valphalk::CHEST && val->GetIsHupgi())
				collider->minusPartHP(deal);

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

bool Player::AttackDummy(float power, bool push, UINT useOtherCollider)
{

	DummyValphalk* val = nullptr;

	if (SceneManager::Get()->Add("PlayerTestScene"))
		val = dynamic_cast<PlayerTestScene*>(SceneManager::Get()->Add("PlayerTestScene"))->GetValphalk();

	Contact contact;

	vector<CapsuleCollider*> colliders = val->GetCollider();

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
			criticalParticle->Play(contact.hitPoint, swordSwingDir);
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

			if (push)
				damages.push_back(damage);

			return true;;
		}
	}

	return false;
}

void Player::AttackWOCollision(float power)
{
	if (SceneManager::Get()->Add("ShadowScene") == nullptr)
		return;

	Valphalk* val =
		dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetValphalk();
	//Valphalk* val =
	//	dynamic_cast<ValphalkTestScene*>(SceneManager::Get()->Add("ValphalkTestScene"))->GetValphalk();

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

void Player::HurtCheck()
{
	Valphalk* val = nullptr;
	if (SceneManager::Get()->Add("ShadowScene") == nullptr && SceneManager::Get()->Add("FightTestScene") != nullptr)
		val = dynamic_cast<FightTestScene*>(SceneManager::Get()->Add("FightTestScene"))->GetValphalk();
	else if(SceneManager::Get()->Add("ShadowScene") != nullptr)
		val = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetValphalk();
	else
		return;

	auto colliders = val->GetCollider();

	for (auto collider : colliders)
	{
		if (bodyCollider->IsCapsuleCollision(collider))  /// �浹�� �߾�
		{
			Vector3 fwd = Forward();
			Vector3 atkDir = -1 * collider->direction;
			atkDir.y = 0;
			Vector3 reDir = -1 * atkDir;
			Vector3 rad = XMVector3AngleBetweenVectors(fwd, atkDir);

			if (collider->isAttack)						// �ٵ� �� �ݸ����� ���� �ݸ�����
			{
				if (curState >= L_400)
					return;

				if (curState == L_155 && RATIO < 0.36)
				{
					isEvaded = true;
					return;
				}

				int str = collider->atkStrength;
				if (rad.x > XM_PIDIV2)
				{
					Rot().y = atan2(reDir.x, reDir.z);
					UpdateWorld();

					switch (str)
					{
					case 1:   SetState(D_001); 	break;
					case 2:   SetState(D_015); 	break;
					default:  SetState(D_015); 	break;
					}
				}
				else
				{
					Rot().y = atan2(atkDir.x, atkDir.z);
					UpdateWorld();

					switch (str)
					{
					case 1:   SetState(D_004); 	break;
					case 2:   SetState(D_021); 	break;
					default:  SetState(D_021); 	break;
					}
				}
				UI->curHP -= collider->atkDmg;
			}
		}
	}
}

void Player::EvadeCheck()
{
	Valphalk* val = nullptr;
	if (SceneManager::Get()->Add("ShadowScene") == nullptr && SceneManager::Get()->Add("FightTestScene") != nullptr)
		val = dynamic_cast<FightTestScene*>(SceneManager::Get()->Add("FightTestScene"))->GetValphalk();
	else if (SceneManager::Get()->Add("ShadowScene") != nullptr)
		val = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetValphalk();
	else
		return;

	auto colliders = val->GetCollider();

	Contact contact;

	for (auto collider : colliders)
	{
		if (evadeCheckCollider->IsCapsuleCollision(collider, &contact))  // ĸ�� �浹ü�� �浹�� ���
		{
			if (collider->isAttack)	// �ٵ� �� �ݸ����� ���� �ݸ�����
			{
				isEvaded = true;
				collider->isAttack = false;
			}
		}
	}
}

bool Player::CollisionCheck()
{
	Valphalk* val =
		dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetValphalk();
	//Valphalk* val =
	//	dynamic_cast<ValphalkTestScene*>(SceneManager::Get()->Add("ValphalkTestScene"))->GetValphalk();
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

	if (UIManager::Get()->curStamina < 20) // ���¹̳� ������ġ �̸������� ������ ����
		return;
	UIManager::Get()->Roll();


	Rot().y = keyboardRot;


	if (State_S())
		SetState(S_018);

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

bool Player::DeathCheck()
{
	if (UI->curHP < 0)
	{
		SetState(D_066);
		return true;
	}
	else
		return false;
}

void Player::RealRotate(float rad)
{
	Rot().y += rad;
	Pos().x = ((Pos().x - realPos->Pos().x) * cos(-rad) - (Pos().z - realPos->Pos().z) * sin(-rad)) + realPos->Pos().x;
	Pos().z = ((Pos().x - realPos->Pos().x) * sin(-rad) + (Pos().z - realPos->Pos().z) * cos(-rad)) + realPos->Pos().z;

}

void Player::SetState(State state)
{
	if (curState == state)
		return;

	//Pos() = realPos->Pos();

	isSetState = true;

	if (curState == L_155)
	{
		Vector3 realForward = forwardPos->GlobalPos() - backPos->GlobalPos();
		Rot().y = atan2(realForward.x, realForward.z);
	}

	sumRot = 0.0f;
	preState = curState;
	curState = state;
	attackOnlyOncePerMotion = false;
	playOncePerMotion = false;
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
	ReadClip("S_011");
	ReadClip("S_014");
	ReadClip("S_017");
	ReadClip("S_018");
	ReadClip("S_019");
	ReadClip("S_020");
	ReadClip("S_026");
	ReadClip("S_029");
	ReadClip("S_038");
	ReadClip("S_118");
	ReadClip("S_119");
	ReadClip("S_120");
	ReadClip("S_122");

	ReadClip("L_400");
	ReadClip("L_403");
	ReadClip("L_451");
	ReadClip("L_453");
	ReadClip("L_455");
	
	ReadClip("D_001");
	ReadClip("D_004");
	ReadClip("D_007");
	ReadClip("D_011");
	ReadClip("D_015");
	ReadClip("D_016");
	ReadClip("D_021");
	ReadClip("D_022");
	ReadClip("D_026");
	ReadClip("D_029");
	ReadClip("D_030");
	ReadClip("D_031");
	ReadClip("D_032");
	ReadClip("D_033");
	ReadClip("D_045");
	ReadClip("D_046");
	ReadClip("D_066");
	ReadClip("D_078");
	ReadClip("D_079");
	ReadClip("D_080");
}

void Player::RecordLastPos()
{
	//Pos() = root->GlobalPos();
	Pos() = GetTranslationByNode(1);
}

void Player::S001() // ���� Idle
{
	PLAYLOOP;
	if (K_MOVE)
		SetState(S_005);

	// �� Ŭ�� ���� ���� �ϴ°� �߰�
	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}

	if (RATIO > 0.95)
		Loop();
}

void Player::S003() // �������� �޸���
{
//	PLAY;
//	Move();
//	Rotate();
//
//	if (UIManager::Get()->curStamina < 0.1f)
//		SetState(S_118);
//
//	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D')) // �̵� �� Ű�� �� ��
//	{
//		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D')) // �ٸ� Ű�� ���� ���������� ���ư���.
//			return;
//		// ��� �̵�Ű�� �Էµ��� ���� �� ����
//		SetState(S_014);
//		return;
//	}
//
//	if (KEY_PRESS(VK_LSHIFT)) // ����Ʈ ������ ��������
//	{
//		SetState(S_038);
//		return;
//	}
//
//	if (KEY_FRONT(Keyboard::LMB))
//	{
//		SetState(L_101);
//		return;
//	}
//
//	if (KEY_DOWN(VK_SPACE))
//		Roll();
//	UIManager::Get()->staminaActive = false;
//
}

void Player::S005() // ����� �޸��� ����
{
	PLAY;

	Rotate();

	if (!K_MOVE)
	{
		SetState(S_014);
	}

	// 101 ���� ����
	if		(K_LMB)			SetState(L_101);
	else if (K_CTRL)	SetState(L_106);
	else if (K_SPACE)	Roll();
	
	if (RATIO > 0.97 )
	{
		SetState(S_011);
	}	
}

void Player::S008() // ���� ����
{
	PLAY;

	if(RATIO>0.6)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);

	if (RATIO > 0.95 && K_MOVE)
		SetState(S_005);

	if (RATIO > 0.96)
		SetState(S_001);

}

void Player::S009() // �����鼭 ����
{
//	PLAY;
//	Rotate();
//
//	if (RATIO > 0.4)
//		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);
//
//	if (RATIO > 0.94 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
//	{
//		SetState(S_011);
//	}
//
//	if (RATIO > 0.96)
//	{
//		SetState(S_001);
//	}
}

void Player::S011() // �޸��� ����
{
	PLAYLOOP;

	Rotate();

	if (KEY_DP(VK_LSHIFT))
		SetState(S_122);

	if (!K_MOVE)
	{
		SetState(S_014);
	}

	// 101 ���� ����
	if		(K_LMB)		SetState(L_101);
	else if (K_CTRL)	SetState(L_106);
	else if (K_SPACE)	Roll();


	if (RATIO > 0.95)
	{
		Loop();
		
	}

}

void Player::S014() // �޸��� ����
{
	PLAY;

	if (K_MOVE)
		SetState(S_005);



	
	if (RATIO > 0.96)
	{
		SetState(S_001);
	}
}

void Player::S017() 
{

}

void Player::S018() // ������ �� ���ڸ�
{
	PLAY;

	if (!playOncePerMotion)
	{

	}

	if (RATIO < 0.40)
		bodyCollider->SetActive(false);
	else
		bodyCollider->SetActive(true);

	if (GetClip(S_018)->GetRatio() > 0.6f && K_MOVE)
	{
		SetState(S_020);
	}

	if (GetClip(S_017)->GetRatio() > 0.96)
	{
		SetState(S_001);
	}
}

void Player::S019()// �������� ������ �� �̵�Ű ������
{

}

void Player::S020()
{
	PLAY;

	Rotate();


	if (RATIO > 0.48)
	{
		if (!K_MOVE)			SetState(S_014);
		else if (K_SPACE)		Roll();

	}

	if (RATIO > 0.96)
		SetState(S_011);
}

void Player::S026() // ����� �ȱ����
{
}

void Player::S029() // �ȴ���
{
}

void Player::S038() // ��������
{
//	PLAY;
//	Move();
//	Rotate();
//	if (moveSpeed <= 650)
//		moveSpeed += 500 * DELTA;
//	if (UIManager::Get()->curStamina < 0.1f) // ���¹̳� ������ġ �̸������� �޸��� ����
//	{
//		SetState(S_118);
//		return;
//	}
//	UIManager::Get()->Running();
//	/*if (RATIO > 0.96)
//		moveSpeed++;*/
//
//	if (KEY_UP(VK_LSHIFT))
//	{
//		moveSpeed = 400;
//		SetState(S_003);
//		return;
//	}
//
//	//Rotate();
//	/*if (RATIO > 0.96 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
//	{
//		SetState(S_003);
//		moveSpeed = 500;
//		return;
//	}*/
//
//	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D'))
//	{
//		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
//			return;
//
//		moveSpeed = 400;
//		SetState(S_014);
//		return;
//	}
//
//
//	// 101 ���� ����
//	if (KEY_FRONT(Keyboard::LMB))
//	{
//		SetState(L_101);
//		return;
//	}
//
//	//if (KEY_PRESS(VK_LSHIFT))
//	//	SetState(S_008);
//	if (KEY_DOWN(VK_SPACE))
//		Roll();
//	UIManager::Get()->staminaActive = true;

}

void Player::S118() // Ż�� ����
{
	PLAY;
	UIManager::Get()->curStamina += 2.0f * DELTA;
	if (RATIO > 0.96f)
		SetState(S_120);
}

void Player::S119() // Ż�� ��
{	
	PLAY;
	UIManager::Get()->curStamina += 2.0f * DELTA;
	if (RATIO > 0.96f)
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

void Player::S122()   // ��������
{
	PLAYLOOP;
	Rotate();

	if (UIManager::Get()->curStamina < 0.1f)
		SetState(S_118);

	if (KEY_UP(VK_LSHIFT))
		SetState(S_011);

	if (!K_MOVE)
		SetState(S_014);

	
	if		(K_LMB)		SetState(L_101);
	else if (K_SPACE)	Roll();

	if (RATIO > 0.95)
		Loop();

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
	Rotate();
}

void Player::L004() // �ߵ����� �ȱ� �� // ����
{
	PLAYLOOP;

	if (KEY_PRESS(VK_LSHIFT))		SetState(L_009); // ����	
	else if (K_LMB)		SetState(L_101);	// 101 ���� ����	
	else if (K_RMB)		SetState(L_104);	// 104 ���	
	else if (K_LMBRMB)	SetState(L_103);	// 103 �������
	else if (K_CTRL)	SetState(L_106);	// 106 ���� ����	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
	else if (K_SPACE)	Roll();				// 010 ������

	Rotate();

	if (!K_MOVE) // �̵� �� Ű�� �� ��
		SetState(L_008);


	if (RATIO > 0.95)
		Loop();
}

void Player::L005() // �ߵ����� �ȱ� ���� (�ߵ���)
{
	PLAY;
	
	if (KEY_PRESS(VK_LSHIFT))		SetState(L_009); // ����	
	else if (K_LMB)		SetState(L_101);	// 101 ���� ����	
	else if (K_RMB)		SetState(L_104);	// 104 ���	
	else if (K_LMBRMB)	SetState(L_103);	// 103 �������
	else if (K_CTRL)	SetState(L_106);	// 106 ���� ����	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
	else if (K_SPACE)	Roll();				// 010 ������

	Rotate();

	if (!K_MOVE)
		SetState(L_008);


	if (RATIO > 0.96 )
	{
		if(K_MOVE)
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

	if (KEY_PRESS(VK_LSHIFT))		SetState(L_009); // ����	
	else if (K_LMB)		SetState(L_101);	// 101 ���� ����	
	else if (K_RMB)		SetState(L_104);	// 104 ���	
	else if (K_LMBRMB)	SetState(L_103);	// 103 �������
	else if (K_CTRL)	SetState(L_106);	// 106 ���� ����	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
	else if (K_SPACE)	Roll();				// 010 ������

	if (RATIO > 0.5 && RATIO <= 0.95)
	{
		if (K_MOVE)
		{
			SetState(L_005);
		}
	}

	if (RATIO > 0.95)
	{
		GetClip(L_008)->SetPlayTime(-100.3f);
		ReturnIdle();
	}
}

void Player::L009() // �����鼭 ����
{
	PLAY;
	Rotate();

	if (RATIO > 0.4)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);

	if (RATIO > 0.95 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
	{
		SetState(S_011);
	}

	if (RATIO > 0.96)
	{
		SetState(S_014);
	}
}

void Player::L010() // ������
{
	PLAY;

	if (RATIO < 0.40)
		bodyCollider->SetActive(false);
	else
		bodyCollider->SetActive(true);

	// �� ����ȭ
	{
		if (RATIO > 0 && RATIO < 0.9)
			CAM->Zoom(300, 5);
	}

	if (RATIO > 0.45f && K_MOVE)
		SetState(L_014);


	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
	
}

void Player::L014() // �ߵ����� ������ �� �̵�Ű ������
{
	PLAY;
	Rotate();
	// �� ����ȭ
	{
		if (RATIO > 0 && RATIO < 0.9)
			CAM->Zoom(300, 5);
	}

	if (!K_MOVE)
		SetState(L_008);


	if (RATIO > 0.48 && K_SPACE)
	{
		Roll();
	}

	if (RATIO > 0.96)
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
		initRotY = Rot().y;
	}
	if(RATIO>0.3 && RATIO<0.35)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if(RATIO>0.18 && RATIO<0.21)
		Sounds::Get()->Play("Heeee", .5f);

	if (RATIO < 0.3)
	{
		LimitRotate(15);
	}


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
	if (RATIO > 0.6 && RATIO < 0.96)
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
	if (RATIO > 0.96)
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
		initRotY = Rot().y;
	}
	if (RATIO > 0.25 && RATIO < 0.28)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// ���� ���� ���� ������
	{
		if (RATIO < 0.3)
			LimitRotate(15);
	}

	// �������� ������
	{
		if (RATIO > 0.3 && RATIO < 0.375)
			Attack(26);
		else
			EndEffect();
	}

	// �Ļ� ���� ������
	if (RATIO > 0.5 && RATIO < 0.96)
	{
		if		(K_LMB || K_RMB)	SetState(L_104);	// ���
		else if (K_LMBRMB)			SetState(L_103);	// �������
		else if (K_CTRL)			SetState(L_106);	// ���κ���1		
		else if (K_CTRLRMB)			SetState(L_147);	// ���� ����
		else if (K_CTRLSPACE)		SetState(L_151);	// Ư�� ����
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)			Roll();
	}

	if (RATIO > 0.96)
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
		initRotY = Rot().y;
	}

	if (RATIO > 0.2 && RATIO < 0.25)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO < 0.272)
		LimitRotate(15);
		
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

	if (RATIO > 0.96)
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

	if (RATIO < 0.1)
		LimitRotate(15);


	// �������� ������
	{
		UIManager::Get()->staminaActive = false;
		if (RATIO > 0.1 && RATIO < 0.213)
			Attack(14);
		else
			EndEffect();
	}

	if (RATIO > 0.40 && RATIO < 0.96)
	{
		if		(K_LMB || K_RMB)	SetState(L_105);	// ����ø���
		else if (K_LMBRMB)			SetState(L_103);	// �������
		else if (K_CTRL)			SetState(L_106);	// ���κ���1		
		else if (K_CTRLRMB)			SetState(L_147);	// ���� ����
		else if (K_CTRLSPACE)		SetState(L_151);	// Ư�� ����
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// ��������
		else if (K_SPACE)			Roll();
		
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L105() // ���� �ø���
{
	PLAY;
	if(INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);

	if (RATIO < 0.1)
		LimitRotate(15);

	if (RATIO > 0.1 && RATIO < 0.12)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);		
	}

	// �������� ������
	{
		if (RATIO > 0.1 && RATIO < 0.2)
			Attack(18);
		else
			EndEffect();
	}

	if (RATIO > 0.4 && RATIO < 0.96)
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

	if (RATIO > 0.96)
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

	// ������ȯ �Լ�
	{
		if (RATIO < 0.3)
			LimitRotate(15);
	}

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

	if (RATIO > 0.96)
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

	// ������ȯ �Լ�
	{
		if (RATIO < 0.26)
			LimitRotate(15);
	}


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


	if (RATIO > 0.96)
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

		if (RATIO < 0.40)
			LimitRotate(15);
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

	if (RATIO > 0.96)
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
		{
			CAM->Zoom(150);
			LimitRotate(15);
		}
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

	if (RATIO > 0.96)
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

	if (RATIO < 0.30)
		LimitRotate(15);


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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO < 0.2)
		LimitRotate(180);


	// �� ����ȭ (�ɾ� ���� ȸ�� ���⿡�� �Ѿ�� ���)
	{
		if (RATIO > 0 && RATIO < 0.9)
			CAM->Zoom(300, 5);
	}


	if (RATIO > 0.96)
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
					if (K_CTRL && UI->GetCotingLevel() > 0)
					{
						UI->MinusCotingLevel();
						SetState(L_133);  // ��������
					}
					else	 	SetState(L_136);  // �������
				}
			}

			if (RATIO > 0.96)
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

			if (RATIO > 0.96)
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

	if (RATIO < 0.35)
		LimitRotate(180);

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

		if (RATIO > 0.96)
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
		if (RATIO > 0.96)
		{
			ReturnIdle();
		}
	}
}

void Player::L147() // ���ĺ���
{
	PLAY;
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
		evadeCheckCollider->SetParent(realPos);
		evadeCheckCollider->SetActive(true);
		evadeCheckCollider->UpdateWorld();
	}

	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	UIManager::Get()->staminaActive = false;
	// �ܾƿ� && ȸ�� ���� ������
	{
		if (RATIO > 0 && RATIO < 0.30)
		{
			CAM->Zoom(450);
			EvadeCheck(); // �����ϸ� �� �Ҹ� ������
		}

		if (RATIO > 0.30)
			evadeCheckCollider->SetActive(false);
	}

	// Ư�� ĵ�� ���� Ÿ�̹�
	{
		if (RATIO > 0.205f && RATIO < 0.30f && K_CTRLSPACE)
		{
			if (isEvaded)
				isEvaded = false;
			SetState(L_151);	// Ư�� ����
		}
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

	if (RATIO > 0.56)
	{
		if (isEvaded)
			isEvaded = false;
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

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L151() // Ư�� ����
{
	if (GetClip(curState)->isFirstPlay()) 
	{
		PlayClip(curState, 2.8);
		initForward = Forward();
		holdingSword = true;
		EndEffect();
		UIManager::Get()->staminaActive = false;
	}
	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);	

	if (RATIO > 0.5 && RATIO < 0.6)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);

	if (RATIO > 0.56 && RATIO < 0.57)
		spAtkParticle->Play(haloCollider->Pos() + Right() * 1.0f, { 0,1,0 });

	if (RATIO < 0.2)
		LimitRotate(180);


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

	if (RATIO > 0.96)
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

	if (RATIO > 0.96)
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

	if (RATIO < 0.1)
		LimitRotate(30);

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

	if (RATIO > 0.96)
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

	if (RATIO < 0.1)
		LimitRotate(15);

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

	// ī���� ���� �� �߰� ���� ������
	{
		if (isEvaded && isHit && (RATIO >0.385  && RATIO < 0.39))
		{
			if(isHitL155==false)
			UIManager::Get()->PlusCotingLevel();

			isHitL155 = true;
			Sounds::Get()->Play("pl_wp_l_swd_epv_media.bnk.2_8", .5f);			
			isEvaded = false;
		}
	}

	// ĵ�� ���� ������
	{
		if (RATIO > 0.39)
		{
			isEvaded = false; // ���� �տ��� true�� �����ִ� ��� �����

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

	if (RATIO > 0.96)
	{
		ReturnIdle();
		isDoubleStrikeMotion = false;
		isHit = false;
	}
}

void Player::L156()
{


}

void Player::L400()
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::L403()
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::L451()
{
	PLAY;

	// ĵ�� ���� ������
	{
		if (RATIO > 0.745)
		{
			if (K_SPACE)		Roll();			 // ������
		}
	}

	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::L453()
{
	PLAY;

	// ĵ�� ���� ������
	{
		if (RATIO > 0.745)
		{
			if (K_SPACE)		Roll();			 // ������
		}
	}

	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::L455()
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::D001()  // �Ұ���
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle2();
	}
}

void Player::D004() // �ڿ��� �°� ������ �Ұ���
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle2();
	}
}

void Player::D007() // ���� ���¿��� �Ͼ�� ����
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(L_453);
	}
}

void Player::D011()  // 7�� �ݴ�
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(L_451);
	}
}

void Player::D015() // �ĸ°� ���� ���󰡱�
{
	PLAY;
	if (Jump(1000))
	{
		Pos() += Back() * temp4 * DELTA;
	}
	else
	{
		SetState(D_016);
	}
}

void Player::D016()  //�����ϰ� �����ϸ� �μ����� ��¤�� ����
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(L_451);
	}
}

void Player::D021() // �պ��� ������ ���󰡱�
{
	PLAY;

	if (Jump(1000))
	{
		Pos() += Forward() * temp4 * DELTA;
	}
	else
	{
		SetState(D_022);
	}
}

void Player::D022()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(L_453);
	}
}

void Player::D026()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(D_007);
	}
}

void Player::D029()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(D_030);
	}
}

void Player::D030() // Loop
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(D_031);
	}
}

void Player::D031()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(D_007);
	}
}

void Player::D032()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(D_033);
	}
}

void Player::D033()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(D_026);
	}
}

void Player::D045()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(D_046);
	}
}

void Player::D046()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(L_455);
	}
}

void Player::D066()
{
	PLAY;

	if (RATIO > 0.96)
	{
		isPlay = false;
	}
}

void Player::D078()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(D_079);
	}
}

void Player::D079()
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(D_080);
	}
}

void Player::D080()
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
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
	return curState >= S_001 && curState <= S_122;
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
		static bool calculatedOnce;

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

	if (SceneManager::Get()->Add("ShadowScene") == nullptr)
	{
		if (Pos().y < 0)
			Pos().y = 0;
		return;
	}


	TerrainEditor* terrain = dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetTerrain();

	Vector3 pos1;
	terrain->ComputePicking(pos1, realPos->Pos() + Vector3::Up() * 200, Vector3::Down());

	//Vector3 pos2;
	//terrain->ComputePicking(pos2, realPos->Pos(), Vector3::Up());

//	float y = max(pos1.y, pos2.y);
	Pos().y = pos1.y;
}
