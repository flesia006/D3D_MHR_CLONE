
#include "Framework.h"
#include "Player.h"
#include "Scenes/ShadowScene.h"

Player::Player() : ModelAnimator("Player")
{
	mainHand = new Transform();
	swordCollider = new CapsuleCollider(2.0f, 100.0f);
	swordCollider->Rot().x += XM_PIDIV2;
	swordCollider->SetParent(mainHand);
	swordCollider->Pos().z -= 100.0f;
	swordCollider->Scale() *= 3.0f;

	head = new Transform();
	realPos = new Transform();
	lastPos = new Transform();
	root = new Transform();
	back = new Transform();

	swordStart = new Transform();
	swordEnd = new Transform();
	trail = new Trail(L"Textures/Effect/Snow.png", swordStart, swordEnd, 20, 85);
	hitParticle = new HitParticle();
	

	longSword = new Model("longSwd");
	longSword->SetParent(mainHand);

	//	longSword->Rot().x -= XM_PIDIV2;	

	tmpCollider = new SphereCollider();
	tmpCollider->Scale() *= 6.0f;

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
	delete hitParticle;
}

void Player::Update()
{
	Control();
	ResetPlayTime();
	UpdateWorlds();

	trail->Update();
	hitParticle->Update();

	ModelAnimator::Update();
	UIManager::Get()->Update();
	Potion();	
}

void Player::Render()
{
	ModelAnimator::Render();
	tmpCollider->Render();
	//swordCollider->Render();
	longSword->Render();

	if (renderEffect)
	{
		trail->Render();
		hitParticle->Render();
	}		
		
}

void Player::GUIRender()
{
	//	ModelAnimator::GUIRender();

	trail->GetMaterial()->GUIRender();
	hitParticle->GUIRender();

	//particle->GetMaterial()->GUIRender();

//	Vector3 Forward = root->Forward();
//	float t = atan2(Forward.x, Forward.z);
//	float t = root->Rot().y;
//	ImGui::DragFloat("Player.y", &t); 
//
//	Vector3 CAMForward = CAM->Forward();	
//	float y = atan2(CAMForward.x, CAMForward.z);
//	ImGui::DragFloat("CAM.y", &y);

	//Vector3 pos = realPos->Pos();
	//
	//ImGui::DragFloat3("RealPos", (float*)&pos);
	//
	//int U = Keyboard::Get()->ReturnFirst();
	//ImGui::SliderInt("keyboard", &U, 0, 200);
	//
	//
	ImGui::SliderInt("node", &node, 100, 300);

	ImGui::SliderInt("temp", &temp, 100, 200.0f);
		
	longSword->GUIRender();


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

	//string fps = "Status : " + strStatus.at((UINT)curState);
	//Font::Get()->RenderText(fps, { 150, WIN_HEIGHT - 30 });


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
	case Player::L_014:					break;
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
	case Player::L_111:					break;
	case Player::L_112:					break;
	case Player::L_113:					break;
	case Player::L_114:					break;
	case Player::L_115:					break;
	case Player::L_116:					break;
	case Player::L_117:					break;
	case Player::L_118:					break;
	case Player::L_119:					break;
	case Player::L_120:					break;
	case Player::L_121:					break;
	case Player::L_122:					break;
	case Player::L_123:					break;
	case Player::L_147:		L147();		break;
	case Player::L_151:		L151();		break;
	case Player::L_152:		L152();		break;
	case Player::L_153:		L153();		break;
	case Player::L_154:		L154();		break;
	case Player::L_155:		L155();		break;
	case Player::L_156:		L156();		break;
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
	if (KEY_PRESS('A') && KEY_PRESS('W') || KEY_PRESS('W') && KEY_PRESS('A'))
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
	if (KEY_PRESS('D') && KEY_PRESS('W') || KEY_PRESS('W') && KEY_PRESS('D'))
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
	if (KEY_PRESS('A') && KEY_PRESS('S') || KEY_PRESS('S') && KEY_PRESS('A'))
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
	if (KEY_PRESS('D') && KEY_PRESS('S') || KEY_PRESS('S') && KEY_PRESS('D'))
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

	if (KEY_PRESS('W') && KEY_PRESS('S') || KEY_PRESS('S') && KEY_PRESS('W'))
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

	if (KEY_PRESS('D') && KEY_PRESS('A') || KEY_PRESS('A') && KEY_PRESS('D'))
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

void Player::UpdateWorlds()
{
	if (curState != S_003)
	{
		mainHand->SetWorld(GetTransformByNode(108));
		longSword->Pos() = {};
		longSword->Rot() = {};
	}
	if (curState == S_001 || curState == S_003 || curState == S_005 || curState == S_014)
	{
		mainHand->SetWorld(GetTransformByNode(190));
		longSword->Pos() = { -32,32,23 };
		longSword->Rot() = { -0.86f,-1.2f,+1.46f };
	}
	realPos->Pos() = GetTranslationByNode(1);

	head->Pos() = realPos->Pos() + Vector3::Up() * 200;

	back->SetWorld(GetTransformByNode(node));

	lastSwordEnd = swordStart->Pos();

	swordStart->Pos() = longSword->GlobalPos() + longSword->Back() * 271.0f; // 20.0f : 10% ũ�� �ݿ�
	swordEnd->Pos() = longSword->GlobalPos() + longSword->Back() * 260.0f;

	swordStart->UpdateWorld();
	swordEnd->UpdateWorld();

	swordSwingDir = lastSwordEnd - swordStart->GlobalPos();
	tmpCollider->Pos() = GetTranslationByNode(node);
	root->UpdateWorld();
	realPos->UpdateWorld();
	lastPos->UpdateWorld();
	longSword->UpdateWorld();
	head->UpdateWorld();
	back->UpdateWorld();
	tmpCollider->UpdateWorld();
	swordCollider->UpdateWorld();
}

void Player::Potion()
{
	time += DELTA;

	if (KEY_DOWN('E'))
	{
		cure = true;
		time = 0;
		Sounds::Get()->Play("health_potion", 0.3f);

	}
	if (cure == true)
	{
		if (time < 3)
		{
			UIManager::Get()->HealthPotion();
		}
		else if (time >= 3)
		{
			cure = false;
			return;
		}
	}

	if (KEY_DOWN('R'))
	{
		Lcure = true;
		time = 0;
		Sounds::Get()->Play("health_potion", 0.3f);

	}
	if (Lcure == true)
	{
		if (time < 5)
		{
			UIManager::Get()->HealthPotion();
		}
		else if (time >= 5)
		{
			Lcure = false;
			return;
		}
	}
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

void Player::Attack(float power) // �浹���� �Լ�
{
	renderEffect = true;

	Valphalk* val =
		dynamic_cast<ShadowScene*>(SceneManager::Get()->Add("ShadowScene"))->GetValphalk();

	Contact contact;

	if (swordCollider->IsCapsuleCollision(val->GetCollider()[Valphalk::HEAD], &contact) && !attackOnlyOncePerMotion)
	{
		hitParticle->Play(contact.hitPoint, swordSwingDir);
		attackOnlyOncePerMotion = true;
	}
}

void Player::SetAnimation()
{
}

void Player::Roll()
{
	Vector3 CAMLeftForward = CAM->Back() + CAM->Right();
	Vector3 CAMRightForward = CAM->Back() + CAM->Left();
	Vector3 CAMLeftBack = CAM->Right() + CAM->Forward();
	Vector3 CAMRightBack = CAM->Left() + CAM->Forward();

	Vector3 forward = Back();
	Vector3 newForward;

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

	SetState(L_010);
}

void Player::SetState(State state)
{
	if (curState == state)
		return;

	Pos() = realPos->Pos();
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

	if (effectTimer > 0.2f)
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
	ReadClip(" _014");
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
	ReadClip(" _111");
	ReadClip(" _112");
	ReadClip(" _113");
	ReadClip(" _114");
	ReadClip(" _115");
	ReadClip(" _116");
	ReadClip(" _117");
	ReadClip(" _118");
	ReadClip(" _119");
	ReadClip(" _120");
	ReadClip(" _121");
	ReadClip(" _122");
	ReadClip(" _123");

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
	moveSpeed = 0;
}

void Player::S003() // �������� �޸���
{
	PLAY;
	Move();
	Rotate();

	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D')) // �̵� �� Ű�� �� ��
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D')) // �ٸ� Ű�� ���� ���������� ���ư���.
			return;
		// ��� �̵�Ű�� �Էµ��� ���� �� ����
		SetState(S_014);
		return;
	}

	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}

	if (KEY_DOWN(VK_SPACE))
		Roll();
}

void Player::S005() // ����� �޸���
{
	PLAY;
	Move();
	
	if (moveSpeed <= 500)
		moveSpeed++;

	if (RATIO > 0.97)
		moveSpeed++;
	
	//Rotate();
	if (RATIO > 0.97 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
	{
		SetState(S_003);
		moveSpeed = 500;
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

	if (RATIO > 0.94 && (KEY_PRESS('W') || KEY_PRESS('S') || KEY_PRESS('A') || KEY_PRESS('D')))
	{
		SetState(S_003);
		return;
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}


}

void Player::S014() // �޸��� ����
{
	PLAY;
	Move();
	if (preState == S_001)
		moveSpeed = 500;

	if (moveSpeed >= 0)
		moveSpeed-=2;

	//Rotate();
	if (RATIO > 0.97)
	{
		SetState(S_001);
	}
}

void Player::S017() // ������ �� ���ڸ�
{
}

void Player::S018() // ������ �� �޸���
{
}

void Player::S026() // ����� �ȱ����
{
}

void Player::S029() // �ȴ���
{
}

void Player::L001() // �ߵ����� ���
{
	PLAY;

	if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
		SetState(L_005);

	// 101 ���� ����
	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}
	// 104 ���
	if (KEY_FRONT(Keyboard::RMB))
	{
		SetState(L_104);
		return;
	}
	// 103 �������
	if (KEY_FRONT(Keyboard::LMBRMB))
	{
		SetState(L_103);
		return;
	}
	// 106 ���κ���
	if (KEY_FRONT(Keyboard::CTRL))
	{
		SetState(L_106);
		return;
	}
	if (KEY_PRESS(VK_LSHIFT))
		SetState(S_008);
	if (KEY_DOWN(VK_SPACE))
		Roll();
}

void Player::L002() // �ߵ�
{
	PLAY;
}

void Player::L003() // ���� ����
{
	PLAY;
	Move();
	Rotate();
}

void Player::L004() // �ߵ����� �ȱ� ��
{
	PLAY;
	//
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
	if (KEY_PRESS(VK_LSHIFT))
		SetState(S_009);
	// 101 ���� ����
	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}
	// 104 ���
	if (KEY_FRONT(Keyboard::RMB))
	{
		SetState(L_104);
		return;
	}
	// 103 �������
	if (KEY_FRONT(Keyboard::LMBRMB))
	{
		SetState(L_103);
		return;
	}

	// 106 ���� ����
	{

	}

	// �̵� : 
	{

	}
	// 010 ������
	if (KEY_DOWN(VK_SPACE))
	{
		Roll();
		return;
	}

	if (RATIO > 0.98)
	{
		GetClip(L_004)->SetPlayTime(-100.3f);
	}
}

void Player::L005() // �ߵ����� �ȱ� ���� (�ߵ���)
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

void Player::L006() // ���� (���X)
{
}

void Player::L007() // ���� (���X)
{
}

void Player::L008() // ����
{
	PLAY;

	if (RATIO > 0.5 && RATIO <= 0.94)
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
		{
			SetState(L_005);
		}
		if (KEY_DOWN(VK_SPACE))
		{
			Roll();
		}
	}

	if (RATIO > 0.94)
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

	if (GetClip(L_010)->GetRatio() > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L101() // ���𵮺���
{
	// PlayClip �ϴµ� ��� �ݺ��ؼ� ȣ��Ǹ� ��� �ݺ��Ǵϱ� ���� + �� �ѹ��� ����Ǵ°� ����
	if (INIT)
	{
		PlayClip(L_101);
		MotionRotate(30);
	}

	if (RATIO < 0.3)
		Rot().y = Lerp(Rot().y, rad, 0.001f);


	// �������� ������
	{
		if (RATIO > 0.264 && RATIO < 0.44)
			Attack(26);
		else
			EndEffect();
	}

	// ĵ�� ���� ������
	if (RATIO > 0.6)
	{
		if (KEY_FRONT(Keyboard::LMB))		
			SetState(L_102);

		
		else if (KEY_FRONT(Keyboard::RMB))		
			SetState(L_104);

		
		else if (KEY_FRONT(Keyboard::LMBRMB))		
			SetState(L_103);

		// ���κ���1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);

		// ���� ����
		else if (KEY_FRONT(Keyboard::CTRLRMB))
			SetState(L_147);

		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����

		else if (KEY_FRONT(Keyboard::SPACE))		
			Roll();
		
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
		PlayClip(L_102);
		MotionRotate(30);
	}

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
	if (RATIO > 0.5)
	{
		// ���
		if (KEY_FRONT(Keyboard::LMB) || KEY_FRONT(Keyboard::RMB))
			SetState(L_104);

		// �������
		else if (KEY_FRONT(Keyboard::LMBRMB))
			SetState(L_103);

		// ���κ���1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);

		// ���� ����
		else if (KEY_FRONT(Keyboard::CTRLRMB))
			SetState(L_147);

		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����

		// ������
		else if (KEY_FRONT(Keyboard::SPACE))
			Roll();
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
		PlayClip(L_103);
		MotionRotate(30);
	}

	if (RATIO < 0.272)
		Rot().y = Lerp(Rot().y, rad, 0.001f);

	// �������� ������
	{
		if (RATIO > 0.272 && RATIO < 0.456)
			Attack(24);
		else
			EndEffect();
	}

	if (RATIO > 0.95)
	{
		if (KEY_FRONT(Keyboard::RMB))
			SetState(L_104);

		// ���κ���1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);

		// ���� ����
		else if (KEY_FRONT(Keyboard::CTRLRMB))
			SetState(L_147);

		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����

		else if (KEY_FRONT(Keyboard::SPACE))
			Roll();
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L104() // ���
{
	PLAY;

	// �������� ������
	{
		if (RATIO > 0.1 && RATIO < 0.213)
			Attack(14);
		else
			EndEffect();
	}

	if (RATIO > 0.40)
	{
		if (KEY_FRONT(Keyboard::LMB))
			SetState(L_105);
		

		else if (KEY_FRONT(Keyboard::RMB))
			SetState(L_105);		


		else if (KEY_FRONT(Keyboard::LMBRMB))
			SetState(L_103);

		// ���κ���1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);

		// ���� ����
		else if (KEY_FRONT(Keyboard::CTRLRMB))
			SetState(L_147);

		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����

		else if (KEY_FRONT(Keyboard::SPACE))		
			Roll();
		
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L105() // ���� �ø���
{
	PLAY;

	// �������� ������
	{
		if (RATIO > 0.1 && RATIO < 0.2)
			Attack(18);
		else
			EndEffect();
	}

	if (RATIO > 0.4)
	{
		// ���κ���
		if (KEY_FRONT(Keyboard::LMB))
			SetState(L_102);

		// ���
		else if (KEY_FRONT(Keyboard::RMB))
			SetState(L_104);

		// �������
		else if (KEY_FRONT(Keyboard::LMBRMB))
			SetState(L_103);

		// ���κ���1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);

		// ���� ����
		else if (KEY_FRONT(Keyboard::CTRLRMB))
			SetState(L_147);

		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����

		else if (KEY_FRONT(Keyboard::SPACE))
			Roll();
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L106() // ���� ���� 1
{
	PLAY;

	// �������� ������
	{
		if (RATIO > 0.33 && RATIO < 0.416)
			Attack(31);
		else
			EndEffect();
	}

	if (RATIO > 0.43)
	{
		// ���
		if (KEY_FRONT(Keyboard::RMB))		
			SetState(L_104);
				
		// �������
		else if (KEY_FRONT(Keyboard::LMBRMB))		
			SetState(L_103);
		
		// ���� ����2
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_107);

		// ���� ����
		else if (KEY_FRONT(Keyboard::CTRLRMB))
			SetState(L_147);
		
		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����

		// ������
		else if (KEY_FRONT(Keyboard::SPACE))
			Roll();		
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L107() // ���κ��� 2
{
	PLAY;

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
			// ���� �ø���
			if (KEY_FRONT(Keyboard::RMB) || KEY_FRONT(Keyboard::LMB))
				SetState(L_105);

			// �������
			else if (KEY_FRONT(Keyboard::LMBRMB))
				SetState(L_103);

			// ���� ����3
			else if (KEY_FRONT(Keyboard::CTRL))
				SetState(L_108);

			// ���� ����
			else if (KEY_FRONT(Keyboard::CTRLRMB))
				SetState(L_147);

			else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����

			// ������
			else if (KEY_FRONT(Keyboard::SPACE))
				Roll();
		}
	}


	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L108() // ���κ��� 3
{
	PLAY;

	// �������� ������ (�� ����� 3�� ���� ������ ����)
	{
		if (RATIO > 0.05 && RATIO < 0.12)
		{
			Attack(13);
			attackOnlyOncePerMotion = false;
		}
		else if (RATIO > 0.14 && RATIO < 0.22)
		{
			Attack(15);
			attackOnlyOncePerMotion = false;
		}
		else if(RATIO > 0.43 && RATIO < 0.47)
			Attack(37);
		else
			EndEffect();
	}

	if (RATIO > 0.50)
	{
		// ���
		if (KEY_FRONT(Keyboard::RMB) || KEY_FRONT(Keyboard::LMB))		
			SetState(L_104);
		
		// �������
		else if (KEY_FRONT(Keyboard::LMBRMB))		
			SetState(L_103);
		
		// ���� ����3
		else if (KEY_FRONT(Keyboard::CTRL))		
			SetState(L_109);


		// ���� ����
		else if (KEY_FRONT(Keyboard::CTRLRMB))
			SetState(L_147);

		
		else if (K_CTRLSPACE)	SetState(L_151);	// Ư�� ����

		
		else if (KEY_FRONT(Keyboard::SPACE))		
			Roll();
		
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L109() // ���� ūȸ������
{
	PLAY;

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
	}

	if (RATIO > 0.98)
		SetState(S_003);
}

void Player::L110() // ���� ���𵮺���
{

}

void Player::L147() // ���ĺ���
{
	PLAY;

	// �ܾƿ� && ȸ�� ���� ������
	{
		if (RATIO > 0 && RATIO < 0.30)
			CAM->Zoom(450);
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
		if		(K_LMB)		SetState(L_101);    // ���κ���		
		else if (K_RMB)		SetState(L_104);	// ���		
		else if (K_LMBRMB)	SetState(L_103);	// �������		
		else if (K_CTRL)	SetState(L_109);	// ����ūȸ������ (TODO :: �̰� ���� ��������)		
		else if (K_SPACE)	Roll();				// ������
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L151() // Ư�� ����
{
	PLAY;

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
		Pos() = realPos->Pos() + Back() * temp;
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
		Pos() = realPos->Pos() + Back() * temp;
	}
}

void Player::L153() // Ư������ ��� ����
{
	PLAY;

	if (RATIO > 0.98)
		SetState(S_001);
}

void Player::L154() // �ɾƹߵ� ����
{
	PLAY;

	// �������� ������ (�� ����� 2�� ���� ������ ����)
	{
		if (RATIO > 0.04 && RATIO < 0.17)
		{
			Attack(25);
			attackOnlyOncePerMotion = false;
		}
		else if (RATIO > 0.2 && RATIO < 0.3)
			Attack(30);
		else
			EndEffect();
	}

	// ĵ�� ���� ������
	{
		if (RATIO > 0.43)
		{
			if		(K_LMB)			SetState(L_102); // ���κ���
			else if (K_RMB)			SetState(L_104); // ���
			else if (K_CTRL)		SetState(L_106); // ���� ���� 1		
			else if (K_CTRLRMB)		SetState(L_147); // ���� ����
			else if (K_SPACE)		Roll();			 // ������
		}
	}

	if (RATIO > 0.98)
		ReturnIdle();

}

void Player::L155() // �ɾƹߵ� ���κ���
{


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
