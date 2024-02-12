
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
	trail = new Trail(L"Textures/Effect/Snow.png", swordStart, swordEnd, 20, 70);
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

	//캐릭터용 UI 추가

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

	if (curState != S_003)
	{
		mainHand->SetWorld(GetTransformByNode(108));
		longSword->Pos() = {};
		longSword->Rot() = {};
	}
	if (curState == S_003)
	{
		mainHand->SetWorld(GetTransformByNode(190));
		longSword->Pos() = { -32,32,23 };
		longSword->Rot() = { -0.86f,-1.2f,+1.46f };
	}
	realPos->Pos() = GetTranslationByNode(1);

	head->Pos() = realPos->Pos() + Vector3::Up() * 200;

	back->SetWorld(GetTransformByNode(node));
	
	lastSwordEnd = swordStart->Pos();

	swordStart->Pos() = longSword->GlobalPos() + longSword->Back() * 271.0f; // 20.0f : 10% 크기 반영
	swordEnd->Pos() = longSword->GlobalPos() + longSword->Back() * 260.0f;

	swordStart->UpdateWorld();
	swordEnd->UpdateWorld();

	swordSwingDir = lastSwordEnd - swordStart->GlobalPos();

	trail->Update();
	hitParticle->Update();

	tmpCollider->Pos() = GetTranslationByNode(node);

	ModelAnimator::Update();
	root->UpdateWorld();
	realPos->UpdateWorld();
	lastPos->UpdateWorld();
	longSword->UpdateWorld();
	head->UpdateWorld();
	back->UpdateWorld();
	tmpCollider->UpdateWorld();
	swordCollider->UpdateWorld();

	time += DELTA;

	if (KEY_DOWN('E'))
	{
		cure = true;
		time = 0;
	}
	if (cure == true)
	{
		if (time < 3)
		{
			UIManager::Get()->HealthPotion();
		}
		else if(time>=3)
		{
			cure = false;
			return;
		}
	}

	if (KEY_DOWN('R'))
	{
		Lcure = true;
		time = 0;
	}
	if(Lcure==true)
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

	UIManager::Get()->Update();
	
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

	ImGui::SliderFloat("rotation", &rotation, 0, 20.0f);
		
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

	strStatus.push_back("L_001 발도 상태 대기");
	strStatus.push_back("L_002 발도");
	strStatus.push_back("L_003 서서납도");
	strStatus.push_back("L_004 발도상태 걷기");
	strStatus.push_back("L_005 발도상태 걷기 시작");
	strStatus.push_back("L_006 발도상태 좌로 걷기 시작");
	strStatus.push_back("L_007 발도상태 우로 걷기 시작");
	strStatus.push_back("L_008 멈춤");
	strStatus.push_back("L_009 걸으면서 납도 ");
	strStatus.push_back("L_010 앞구르기");
	strStatus.push_back("L_011 왼쪽구르기");
	strStatus.push_back("L_012 오른쪽구르기");
	strStatus.push_back("L_013 뒤구르기");
	strStatus.push_back("L_014 구른후걷기");
	strStatus.push_back("L_015 구른후뒤걷기");
	strStatus.push_back("L_071 낮은높이언덕파쿠르");
	strStatus.push_back("L_072 중간높이언덕파쿠르");
	strStatus.push_back("L_073 높은높이언덕파쿠르");
	strStatus.push_back("L_077 ?");
	strStatus.push_back("L_078 ?");
	strStatus.push_back("L_079 ?");
	strStatus.push_back("L_101 내디뎌베기");
	strStatus.push_back("L_102 세로베기");
	strStatus.push_back("L_103 베어내리기");
	strStatus.push_back("L_104 찌르기");
	strStatus.push_back("L_105 베어올리기");
	strStatus.push_back("L_106 기인베기1");
	strStatus.push_back("L_107 기인베기2");
	strStatus.push_back("L_108 기인베기3");
	strStatus.push_back("L_109 기인큰회전베기");
	strStatus.push_back("L_110 기인내디뎌베기");
	strStatus.push_back("L_111 일자베기");

	strStatus.push_back("S_003 납도 달리기");
	strStatus.push_back("S_008 제자리 납도");
	strStatus.push_back("S_009 걸으면서 납도");

	//string fps = "Status : " + strStatus.at((UINT)curState);
	//Font::Get()->RenderText(fps, { 150, WIN_HEIGHT - 30 });


}

void Player::Control()
{
	switch (curState)
	{
	case Player::S_003:		S003();		break;
	case Player::S_008:		S008();		break;
	case Player::S_009:		S009();		break;
	// 이동 모션
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
	// 공격 모션
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
	}
}

void Player::Move()
{
	bool isMoveZ = false; // 전후 이동 중 아님
	bool isMoveX = false; // 좌우 이동 중 아님

	if (KEY_PRESS('W'))
	{
		//Pos() += Back() * moveSpeed * DELTA;
		velocity.z = 1;//+= DELTA; // 속도(범용변수)에 델타만큼 전후값 주기		
		isMoveZ = true; //전후 이동 수행 중
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

	if (velocity.Length() > 1) //속도의 전체 가치가 1을 넘으면 (선으로 표현한 벡터의 길이가 1 초과)
		velocity.Normalize(); //정규화
	// 생각할 거리 : 이 코드가 만약 없으면....?

			//좌우회전과 행렬계산에 의한 면법선 내기 ( = 정면 구하기)
	Matrix rotY = XMMatrixRotationY(Rot().y); ;
	Vector3 direction = XMVector3TransformCoord(velocity, rotY); // 현재의 공간이 가지는 "정면"의 실제 벡터 방향

	Pos() += direction * -1 * moveSpeed * DELTA; //"정면" 방향대로 이동

	Vector3 CAMForward = CAM->Back();
	Vector3 CAMBack = CAM->Back() * -1;
	Vector3 CAMLeft = CAM->Right();
	Vector3 CAMRight = CAM->Right() * -1;

	Vector3 CAMLeftForward = CAM->Back() + CAM->Right();
	Vector3 CAMRightForward = CAM->Back() + CAM->Left();
	Vector3 CAMLeftBack = CAM->Right() + CAM->Forward();
	Vector3 CAMRightBack = CAM->Left() + CAM->Forward();

	Vector3 forward = Back();//모델 기준으로 앞 따오기
	if (KEY_PRESS('W'))
	{
		Vector3 cross = Cross(forward, CAMForward);//방향차이에서 나온 법선

		if (cross.y < 0)//법선이 밑이다 --> 내가 목적 방향보다 오른쪽을 보는 중이다 ----> 외적
		{
			Rot().y += rotSpeed * DELTA;
		}
		else if (cross.y > 0)//반대의 경우
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

	//if (!isMoveZ) // 전후 이동 중이 아니면
	//	velocity.z = Lerp(velocity.z, 0, deceleration * DELTA); //보간에 의해 감속
	//
	//if (!isMoveX) // 좌우이동에 적용
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

	//캐릭터 기준 왼쪽 법선 구하기 식 오른쪽이면 Forward(),CAM->Forawrd 일듯
	//newForward = Cross(Back(), CAM->Back);
	//float rot = atan2(newForward.x, newForward.z);
	//Rot().y = rot;

}

void Player::Attack(float power) // 충돌판정 함수
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
	if (KEY_PRESS('W') && KEY_PRESS('A') || KEY_PRESS('A') && KEY_PRESS('W')) // 좌상 구르기
	{
		newForward = Lerp(Left() + Forward(), CAMLeftForward, rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('W') && KEY_PRESS('D') || KEY_PRESS('D') && KEY_PRESS('W')) // 우상 구르기
	{
		newForward = Lerp(Right() + Forward(), CAMRightForward, rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('S') && KEY_PRESS('A') || KEY_PRESS('A') && KEY_PRESS('S')) // 좌하 구르기
	{
		newForward = Lerp(Left() + Back(), CAMLeftBack, rotSpeed * 10);
		float rot = atan2(newForward.x, newForward.z);
		Rot().y = rot;
	}
	if (KEY_PRESS('S') && KEY_PRESS('D') || KEY_PRESS('D') && KEY_PRESS('S')) // 우하 구르기
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
	ReadClip("L_011");
	ReadClip("L_012");
	ReadClip("L_013");
	ReadClip("L_014");
	ReadClip("L_015");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
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
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("");
	ReadClip("S_003");
	ReadClip("S_008");
	ReadClip("S_009");
}

void Player::RecordLastPos()
{
	//Pos() = root->GlobalPos();
	Pos() = GetTranslationByNode(1);
}

void Player::S003() // 납도상태 달리기
{
	PLAY;
	Move();
	Rotate();

	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D')) // 이동 중 키를 뗄 때
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D')) // 다른 키가 아직 눌려있으면 돌아간다.
			return;
		// 모든 이동키가 입력되지 않을 시 멈춤
		SetState(L_008);
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

void Player::S008() // 서서 납도
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
		ReturnIdle();
	}

}

void Player::S009() // 걸으면서 납도
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

void Player::L001() // 발도상태 대기
{
	PLAY;

	if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
		SetState(L_005);

	// 101 내디뎌 베기
	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}
	// 104 찌르기
	if (KEY_FRONT(Keyboard::RMB))
	{
		SetState(L_104);
		return;
	}
	// 103 베어내리기
	if (KEY_FRONT(Keyboard::LMBRMB))
	{
		SetState(L_103);
		return;
	}
	if (KEY_PRESS(VK_LSHIFT))
		SetState(S_008);
	if (KEY_DOWN(VK_SPACE))
		Roll();
}

void Player::L002() // 발도
{
	PLAY;
}

void Player::L003() // 서서 납도
{
	PLAY;
	Move();
	Rotate();
}

void Player::L004() // 발도상태 걷기 중
{
	PLAY;
	//
	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D')) // 이동 중 키를 뗄 때
	{
		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D')) // 다른 키가 아직 눌려있으면 돌아간다.
			return;
		// 모든 이동키가 입력되지 않을 시 멈춤
		SetState(L_008);
		return;
	}

	Move();
	Rotate();
	if (KEY_PRESS(VK_LSHIFT))
		SetState(S_009);
	// 101 내디뎌 베기
	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}
	// 104 찌르기
	if (KEY_FRONT(Keyboard::RMB))
	{
		SetState(L_104);
		return;
	}
	// 103 베어내리기
	if (KEY_FRONT(Keyboard::LMBRMB))
	{
		SetState(L_103);
		return;
	}

	// 106 기인 베기
	{

	}

	// 이동 : 
	{

	}
	// 010 구르기
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

void Player::L005() // 발도상태 걷기 시작 (발돋움)
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

void Player::L006() // 더미 (사용X)
{
}

void Player::L007() // 더미 (사용X)
{
}

void Player::L008() // 멈춤
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

void Player::L009() // 걸으면서 납도
{
	PLAY;
}

void Player::L010() // 구르기
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

void Player::L101() // 내디뎌베기
{
	// PlayClip 하는데 계속 반복해서 호출되면 모션 반복되니까 방지 + 딱 한번만 실행되는거 놓기
	if (INIT)
	{
		PlayClip(L_101);
		MotionRotate(30);
	}

	if (RATIO < 0.3)
		Rot().y = Lerp(Rot().y, rad, 0.001f);


	// 공격판정 프레임
	{
		if (RATIO > 0.264 && RATIO < 0.44)
			Attack(26);
		else
			EndEffect();
	}

	// 캔슬 가능 프레임
	if (RATIO > 0.6)
	{
		if (KEY_FRONT(Keyboard::LMB))		
			SetState(L_102);

		
		else if (KEY_FRONT(Keyboard::RMB))		
			SetState(L_104);

		
		else if (KEY_FRONT(Keyboard::LMBRMB))		
			SetState(L_103);

		// 기인베기1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);


		else if (KEY_FRONT(Keyboard::SPACE))		
			Roll();
		
	}

	// 복귀 프레임
	if (RATIO > 0.98)
	{
		ReturnIdle();
	}

}

void Player::L102() // 세로베기
{
	if (INIT)
	{
		PlayClip(L_102);
		MotionRotate(30);
	}

	// 방향 조정 가능 프레임
	{
		if (RATIO < 0.3)
			Rot().y = Lerp(Rot().y, rad, 0.001f);
	}


	// 공격판정 프레임
	{
		if (RATIO > 0.3 && RATIO < 0.375)
			Attack(26);
		else
			EndEffect();
	}

	// 파생 연계 프레임
	if (RATIO > 0.5)
	{
		// 찌르기
		if (KEY_FRONT(Keyboard::LMB) || KEY_FRONT(Keyboard::RMB))
			SetState(L_104);

		// 베어내리기
		else if (KEY_FRONT(Keyboard::LMBRMB))
			SetState(L_103);

		// 기인베기1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);

		// 구르기
		else if (KEY_FRONT(Keyboard::SPACE))
			Roll();
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L103() // 베어내리기
{
	if (INIT)
	{
		PlayClip(L_103);
		MotionRotate(30);
	}

	if (RATIO < 0.272)
		Rot().y = Lerp(Rot().y, rad, 0.001f);

	// 공격판정 프레임
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

		// 기인베기1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);


		else if (KEY_FRONT(Keyboard::SPACE))
		{
			Roll();
		}
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L104() // 찌르기
{
	PLAY;

	// 공격판정 프레임
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

		// 기인베기1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);


		else if (KEY_FRONT(Keyboard::SPACE))		
			Roll();
		
	}

	if (RATIO > 0.98)
	{
		ReturnIdle();
	}
}

void Player::L105() // 베어 올리기
{
	PLAY;

	// 공격판정 프레임
	{
		if (RATIO > 0.1 && RATIO < 0.2)
			Attack(18);
		else
			EndEffect();
	}

	if (RATIO > 0.6)
	{
		// 세로베기
		if (KEY_FRONT(Keyboard::LMB))
			SetState(L_102);

		// 찌르기
		else if (KEY_FRONT(Keyboard::RMB))
			SetState(L_104);

		// 베어내리기
		else if (KEY_FRONT(Keyboard::LMBRMB))
			SetState(L_103);

		// 기인베기1
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_106);


		else if (KEY_FRONT(Keyboard::SPACE))
			Roll();
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L106() // 기인 베기 1
{
	PLAY;

	// 공격판정 프레임
	{
		if (RATIO > 0.33 && RATIO < 0.416)
			Attack(31);
		else
			EndEffect();
	}

	if (RATIO > 0.43)
	{
		// 찌르기
		if (KEY_FRONT(Keyboard::RMB))		
			SetState(L_104);
				
		// 베어내리기
		else if (KEY_FRONT(Keyboard::LMBRMB))		
			SetState(L_103);
		
		// 기인 베기2
		else if (KEY_FRONT(Keyboard::CTRL))
			SetState(L_107);
		
		// 구르기
		else if (KEY_FRONT(Keyboard::SPACE))
			Roll();		
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L107() // 기인베기 2
{
	PLAY;

	// 공격판정 프레임
	{
		if (RATIO > 0.26 && RATIO < 0.38)
			Attack(33);
		else // 
			EndEffect(); 
	}

	// 캔슬 가능 프레임
	{
		if (RATIO > 0.41)
		{
			// 베어 올리기
			if (KEY_FRONT(Keyboard::RMB) || KEY_FRONT(Keyboard::LMB))
				SetState(L_105);

			// 베어내리기
			else if (KEY_FRONT(Keyboard::LMBRMB))
				SetState(L_103);

			// 기인 베기3
			else if (KEY_FRONT(Keyboard::CTRL))
				SetState(L_108);

			// 구르기
			else if (KEY_FRONT(Keyboard::SPACE))
				Roll();
		}
	}


	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L108()
{
	PLAY;

	// 공격판정 프레임 (이 모션은 3번 베기 동작이 있음)
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
		// 찌르기
		if (KEY_FRONT(Keyboard::RMB) || KEY_FRONT(Keyboard::LMB))		
			SetState(L_104);
		
		// 베어내리기
		else if (KEY_FRONT(Keyboard::LMBRMB))		
			SetState(L_103);
		
		// 기인 베기3
		else if (KEY_FRONT(Keyboard::CTRL))		
			SetState(L_109);

		
		else if (KEY_FRONT(Keyboard::SPACE))		
			Roll();
		
	}

	if (RATIO > 0.98)
		ReturnIdle();
}

void Player::L109()
{
	PLAY;

	// 줌인
	{
		if (RATIO > 0 && RATIO < 0.16)
			CAM->Zoom(150);
	}


	// 공격판정 프레임 
	{
		if (RATIO > 0.16 && RATIO < 0.24)
		{
			Attack(42);
			CAM->Zoom(650);
		}
		else
			EndEffect();
	}

	// 줌 정상화
	{
		if (RATIO > 0.47 && RATIO < 0.84)
			CAM->Zoom(300, 5);
	}


	if (RATIO > 0.50) // 특납 연계 가능 타이밍 언제?
	{
		// 찌르기
		if (KEY_FRONT(Keyboard::CTRLSPACE))
		{
		//	SetState(L_104);
		}
	}

	if (RATIO > 0.98)
		SetState(S_003);
}

void Player::L110()
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
