
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

	if (KEY_DOWN('5'))/// 디버그 확인용이라 필요없으면 지워도 됨
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

	swordStart->Pos() = longSword->GlobalPos() + longSword->Back() * 271.0f; // 20.0f : 10% 크기 반영
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
//	StatusRender(); // 모션 추가중이므로 주석
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

	// 이동 모션
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

	// 피격 모션
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

	if (rotSpeed >= 0)
	{
		rotSpeed -= 0.05f;
		if (rotSpeed <= 3)
			rotSpeed = 3;
	}
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

bool Player::Attack(float power, bool push, UINT useOtherCollider) // 충돌판정 함수
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

			if (curState == L_101 || curState == L_102 || curState == L_103 || curState == L_104 || curState == L_105) // 기인베기 아니라면 게이지 증가
				UIManager::Get()->PlusSpritGauge();

			if (curState == L_109) // 기인 큰 회전베기 적중시에만
			{
				UIManager::Get()->PlusCotingLevel(); // 코팅 레벨을 1 올린다
				UIManager::Get()->SetMaxCoting(); // 동시에 코팅 게이지 100으로 초기화
			}
			if (curState == L_147 && isEvaded) // 간파베기 회피성공 후 적중시에만
			{
				UIManager::Get()->SetMaxGauge(); // 기인 게이지를 최대로 만든다
			}
			if (curState == L_154) // 앉아발도 베기 적중시 기인게이지 상승 버프
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
			// ((공격력/무기배율) * 모션 배율 * (육질/100 )) * 예리도 보정 계수 * 기인 보정 계수
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

			if (hardness >= 30)				// 육질이 30 이상으로 노란데미지가 뜨는 상황
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

			if (curState == L_101 || curState == L_102 || curState == L_103 || curState == L_104 || curState == L_105) // 기인베기 아니라면 게이지 증가
				UIManager::Get()->PlusSpritGauge();

			if (curState == L_109) // 기인 큰 회전베기 적중시에만
			{
				UIManager::Get()->PlusCotingLevel(); // 코팅 레벨을 1 올린다
				UIManager::Get()->SetMaxCoting(); // 동시에 코팅 게이지 100으로 초기화
			}
			if (curState == L_154) // 앉아발도 베기 적중시 기인게이지 상승 버프
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
			// ((공격력/무기배율) * 모션 배율 * (육질/100 )) * 예리도 보정 계수 * 기인 보정 계수
			damage.pos = contact.hitPoint;
			damage.hitPart = collider->part;
			lastHitPart = collider->part;
			lastSwordDir = swordSwingDir;

			if (hardness >= 30)				// 육질이 30 이상으로 노란데미지가 뜨는 상황
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
	// ((공격력/무기배율) * 모션 배율 * (육질/100 )) * 예리도 보정 계수 * 기인 보정 계수
	damage.pos = RandomPos;

	if (hardness >= 30)				// 육질이 30 이상으로 노란데미지가 뜨는 상황
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
		if (bodyCollider->IsCapsuleCollision(collider))  /// 충돌을 했어
		{
			Vector3 fwd = Forward();
			Vector3 atkDir = -1 * collider->direction;
			atkDir.y = 0;
			Vector3 reDir = -1 * atkDir;
			Vector3 rad = XMVector3AngleBetweenVectors(fwd, atkDir);

			if (collider->isAttack)						// 근데 그 콜리더가 공격 콜리더야
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
		if (evadeCheckCollider->IsCapsuleCollision(collider, &contact))  // 캡슐 충돌체와 충돌한 경우
		{
			if (collider->isAttack)	// 근데 그 콜리더가 공격 콜리더야
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

	if (UIManager::Get()->curStamina < 20) // 스태미나 일정수치 미만에서는 구르기 막기
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
	// 빈클립 만들고 싶으면 알파벳 지우면 됨!! 아니면 "" << 이렇게

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

void Player::S001() // 납도 Idle
{
	PLAYLOOP;
	if (K_MOVE)
		SetState(S_005);

	// 왼 클릭 으로 공격 하는거 추가
	if (KEY_FRONT(Keyboard::LMB))
	{
		SetState(L_101);
		return;
	}

	if (RATIO > 0.95)
		Loop();
}

void Player::S003() // 납도상태 달리기
{
//	PLAY;
//	Move();
//	Rotate();
//
//	if (UIManager::Get()->curStamina < 0.1f)
//		SetState(S_118);
//
//	if (KEY_UP('W') || KEY_UP('S') || KEY_UP('A') || KEY_UP('D')) // 이동 중 키를 뗄 때
//	{
//		if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D')) // 다른 키가 아직 눌려있으면 돌아간다.
//			return;
//		// 모든 이동키가 입력되지 않을 시 멈춤
//		SetState(S_014);
//		return;
//	}
//
//	if (KEY_PRESS(VK_LSHIFT)) // 시프트 누르면 전력질주
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

void Player::S005() // 대기중 달리기 시작
{
	PLAY;

	Rotate();

	if (!K_MOVE)
	{
		SetState(S_014);
	}

	// 101 내디뎌 베기
	if		(K_LMB)			SetState(L_101);
	else if (K_CTRL)	SetState(L_106);
	else if (K_SPACE)	Roll();
	
	if (RATIO > 0.97 )
	{
		SetState(S_011);
	}	
}

void Player::S008() // 서서 납도
{
	PLAY;

	if(RATIO>0.6)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);

	if (RATIO > 0.95 && K_MOVE)
		SetState(S_005);

	if (RATIO > 0.96)
		SetState(S_001);

}

void Player::S009() // 걸으면서 납도
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

void Player::S011() // 달리기 루프
{
	PLAYLOOP;

	Rotate();

	if (KEY_DP(VK_LSHIFT))
		SetState(S_122);

	if (!K_MOVE)
	{
		SetState(S_014);
	}

	// 101 내디뎌 베기
	if		(K_LMB)		SetState(L_101);
	else if (K_CTRL)	SetState(L_106);
	else if (K_SPACE)	Roll();


	if (RATIO > 0.95)
	{
		Loop();
		
	}

}

void Player::S014() // 달리다 멈춤
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

void Player::S018() // 구르기 후 제자리
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

void Player::S019()// 납도상태 구르기 후 이동키 유지시
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

void Player::S026() // 대기중 걷기시작
{
}

void Player::S029() // 걷는중
{
}

void Player::S038() // 전력질주
{
//	PLAY;
//	Move();
//	Rotate();
//	if (moveSpeed <= 650)
//		moveSpeed += 500 * DELTA;
//	if (UIManager::Get()->curStamina < 0.1f) // 스태미나 일정수치 미만에서는 달리기 막기
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
//	// 101 내디뎌 베기
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

void Player::S118() // 탈진 시작
{
	PLAY;
	UIManager::Get()->curStamina += 2.0f * DELTA;
	if (RATIO > 0.96f)
		SetState(S_120);
}

void Player::S119() // 탈진 끝
{	
	PLAY;
	UIManager::Get()->curStamina += 2.0f * DELTA;
	if (RATIO > 0.96f)
	{
		SetState(S_001);
		return;
	}	
}

void Player::S120() // 탈진 중
{
	PLAY;
	UIManager::Get()->curStamina += 12.0f * DELTA;
	if (UIManager::Get()->curStamina > 40)
		SetState(S_119);
}

void Player::S122()   // 전력질주
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

void Player::L001() // 발도상태 대기
{
	PLAY;
	moveSpeed = 400;
	if (KEY_PRESS('W') || KEY_PRESS('A') || KEY_PRESS('S') || KEY_PRESS('D'))
		SetState(L_005);

	else if (KEY_PRESS(VK_LSHIFT))		SetState(S_008); // 납도	
	else if (K_LMB)		SetState(L_101);	// 101 내디뎌 베기	
	else if (K_RMB)		SetState(L_104);	// 104 찌르기	
	else if (K_LMBRMB)	SetState(L_103);	// 103 베어내리기
	else if (K_CTRL)	SetState(L_106);	// 106 기인 베기	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
	else if (K_SPACE)	Roll();				// 010 구르기

	UIManager::Get()->staminaActive = false;

}

void Player::L002() // 발도
{
	Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
	PLAY;
}

void Player::L003() // 서서 납도
{
	PLAY;
	Rotate();
}

void Player::L004() // 발도상태 걷기 중 // 루프
{
	PLAYLOOP;

	if (KEY_PRESS(VK_LSHIFT))		SetState(L_009); // 납도	
	else if (K_LMB)		SetState(L_101);	// 101 내디뎌 베기	
	else if (K_RMB)		SetState(L_104);	// 104 찌르기	
	else if (K_LMBRMB)	SetState(L_103);	// 103 베어내리기
	else if (K_CTRL)	SetState(L_106);	// 106 기인 베기	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
	else if (K_SPACE)	Roll();				// 010 구르기

	Rotate();

	if (!K_MOVE) // 이동 중 키를 뗄 때
		SetState(L_008);


	if (RATIO > 0.95)
		Loop();
}

void Player::L005() // 발도상태 걷기 시작 (발돋움)
{
	PLAY;
	
	if (KEY_PRESS(VK_LSHIFT))		SetState(L_009); // 납도	
	else if (K_LMB)		SetState(L_101);	// 101 내디뎌 베기	
	else if (K_RMB)		SetState(L_104);	// 104 찌르기	
	else if (K_LMBRMB)	SetState(L_103);	// 103 베어내리기
	else if (K_CTRL)	SetState(L_106);	// 106 기인 베기	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
	else if (K_SPACE)	Roll();				// 010 구르기

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

void Player::L006() // 더미 (사용X)
{
}

void Player::L007() // 더미 (사용X)
{
}

void Player::L008() // 멈춤
{
	PLAY;

	if (KEY_PRESS(VK_LSHIFT))		SetState(L_009); // 납도	
	else if (K_LMB)		SetState(L_101);	// 101 내디뎌 베기	
	else if (K_RMB)		SetState(L_104);	// 104 찌르기	
	else if (K_LMBRMB)	SetState(L_103);	// 103 베어내리기
	else if (K_CTRL)	SetState(L_106);	// 106 기인 베기	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
	else if (K_SPACE)	Roll();				// 010 구르기

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

void Player::L009() // 걸으면서 납도
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

void Player::L010() // 구르기
{
	PLAY;

	if (RATIO < 0.40)
		bodyCollider->SetActive(false);
	else
		bodyCollider->SetActive(true);

	// 줌 정상화
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

void Player::L014() // 발도상태 구르기 후 이동키 유지시
{
	PLAY;
	Rotate();
	// 줌 정상화
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

void Player::L101() // 내디뎌베기
{	
	// PlayClip 하는데 계속 반복해서 호출되면 모션 반복되니까 방지 + 딱 한번만 실행되는거 놓기
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


	// 줌 정상화 (앉아 기인 회전 베기에서 넘어온 경우)
	{
		if (RATIO > 0 && RATIO < 0.45)
			CAM->Zoom(300, 5);
	}


	// 공격판정 프레임
	{
		if (RATIO > 0.264 && RATIO < 0.44)
			Attack(26);
		else
			EndEffect();
	}


	// 캔슬 가능 프레임
	if (RATIO > 0.6 && RATIO < 0.96)
	{

		if		(K_LMB)				SetState(L_102);	// 세로베기		
		else if (K_RMB)				SetState(L_104);	// 찌르기
		else if (K_LMBRMB)			SetState(L_103);	// 베어내리기
		else if (K_CTRL)			SetState(L_106);	// 기인베기1		
		else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
 		else if (K_SPACE)			Roll();		
	}

	// 복귀 프레임
	if (RATIO > 0.96)
	{
		ReturnIdle();
	}

}

void Player::L102() // 세로베기
{
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
		PlayClip(L_102);
		initRotY = Rot().y;
	}
	if (RATIO > 0.25 && RATIO < 0.28)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// 방향 조정 가능 프레임
	{
		if (RATIO < 0.3)
			LimitRotate(15);
	}

	// 공격판정 프레임
	{
		if (RATIO > 0.3 && RATIO < 0.375)
			Attack(26);
		else
			EndEffect();
	}

	// 파생 연계 프레임
	if (RATIO > 0.5 && RATIO < 0.96)
	{
		if		(K_LMB || K_RMB)	SetState(L_104);	// 찌르기
		else if (K_LMBRMB)			SetState(L_103);	// 베어내리기
		else if (K_CTRL)			SetState(L_106);	// 기인베기1		
		else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (K_SPACE)			Roll();
	}

	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::L103() // 베어내리기
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
		
	// 공격판정 프레임
	{
		if (RATIO > 0.272 && RATIO < 0.456)
			Attack(24);
		else
			EndEffect();
	}

	if (RATIO > 0.87)
	{
		if		(K_RMB)				SetState(L_104);	// 찌르기
		else if (K_CTRL)			SetState(L_110);	// 기인내디뎌베기		
		else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (K_SPACE)			Roll();
	}

	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::L104() // 찌르기
{
	PLAY;
	if(INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);

	if (RATIO > 0.1 && RATIO < 0.15)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);

	if (RATIO < 0.1)
		LimitRotate(15);


	// 공격판정 프레임
	{
		UIManager::Get()->staminaActive = false;
		if (RATIO > 0.1 && RATIO < 0.213)
			Attack(14);
		else
			EndEffect();
	}

	if (RATIO > 0.40 && RATIO < 0.96)
	{
		if		(K_LMB || K_RMB)	SetState(L_105);	// 베어올리기
		else if (K_LMBRMB)			SetState(L_103);	// 베어내리기
		else if (K_CTRL)			SetState(L_106);	// 기인베기1		
		else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (K_SPACE)			Roll();
		
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L105() // 베어 올리기
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

	// 공격판정 프레임
	{
		if (RATIO > 0.1 && RATIO < 0.2)
			Attack(18);
		else
			EndEffect();
	}

	if (RATIO > 0.4 && RATIO < 0.96)
	{		
		if		(K_LMB)			SetState(L_102);	// 세로베기		
		else if (K_RMB)			SetState(L_104);	// 찌르기		
		else if (K_LMBRMB)		SetState(L_103);	// 베어내리기		
		else if (K_CTRL)		SetState(L_106);	// 기인베기1		
		else if (K_CTRLRMB)		SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)	SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (K_SPACE)		Roll();
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L106() // 기인 베기 1
{
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		PlayClip(curState);
		initForward = Forward();
		UIManager::Get()->MinusSpiritGauge() ; // 기인게이지 소모하기( 단 1번 )
	}
	if (RATIO > 0.3 && RATIO < 0.31)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	UIManager::Get()->staminaActive = false;

	// 방향전환 함수
	{
		if (RATIO < 0.3)
			LimitRotate(15);
	}

	// 공격판정 프레임
	{
		if (RATIO > 0.33 && RATIO < 0.416)
			Attack(31);
		else
			EndEffect();
	}

	if (RATIO > 0.43)
	{
		
		if		(K_RMB)			SetState(L_104);	// 찌르기		
		else if (K_LMBRMB)		SetState(L_103);	// 베어내리기		
		else if (K_CTRL)		SetState(L_107);	// 기인 베기2		
		else if (K_CTRLRMB)		SetState(L_147);	// 간파 베기		
		else if (K_CTRLSPACE)	SetState(L_151);	// 특수 납도		
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (K_SPACE)		Roll();				// 구르기
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L107() // 기인베기 2
{
	PLAY;
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		UIManager::Get()->MinusSpiritGauge(); // 기인게이지 소모하기( 단 1번 )
	}
	if (RATIO > 0.25 && RATIO < 0.26)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);

	// 방향전환 함수
	{
		if (RATIO < 0.26)
			LimitRotate(15);
	}


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
			if		(K_LMB || K_RMB)	SetState(L_105);	// 베어올리기
			else if (K_LMBRMB)			SetState(L_103);	// 베어내리기		
			else if (K_CTRL)			SetState(L_108);	// 기인 베기3		
			else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
			else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도		
			else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
			else if (K_SPACE)			Roll();				// 구르기		
		}
	}


	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L108() // 기인베기 3
{
	if (INIT)
	{
		PlayClip(curState);		
		initForward = Forward();
		UIManager::Get()->MinusSpiritGauge(); // 기인게이지 소모하기( 단 1번 )
	}
	if (RATIO > 0.1 && RATIO < 0.11)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.21)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.4 && RATIO < 0.46)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// 줌 정상화 (앉아 기인 회전 베기에서 넘어온 경우)
	{
		if (RATIO > 0 && RATIO < 0.45)
			CAM->Zoom(300, 5);
	}

	// 공격판정 프레임 (이 모션은 3번 베기 동작이 있음)
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
		if		(K_RMB || K_LMB)	SetState(L_104);  // 찌르기		
		else if (K_LMBRMB)			SetState(L_103);  // 베어내리기		
		else if (K_CTRL)			SetState(L_109);  // 기인 큰회전베기
		else if (K_CTRLRMB)			SetState(L_147);  // 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);  // 특수 납도		
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (K_SPACE)			Roll();			  // 구르기		
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L109() // 기인 큰회전베기
{
	PLAY;
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		UIManager::Get()->MinusSpiritGauge(); // 기인게이지 소모하기( 단 1번 )
	}
	if (RATIO > 0.2 && RATIO < 0.21)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.1 && RATIO < 0.15)
		Sounds::Get()->Play("Heeee", .5f);
	if (RATIO > 0.7 && RATIO < 0.75)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);



	// 줌인
	{
		if (RATIO > 0 && RATIO < 0.16)
		{
			CAM->Zoom(150);
			LimitRotate(15);
		}
	}


	// 공격판정 프레임 
	{
		if (RATIO > 0.16 && RATIO < 0.24)
		{
			Attack(42);
			// 줌아웃
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


	if (RATIO > 0.30) // 특납 연계 가능 타이밍 언제?
	{
		 if (K_CTRLSPACE)	SetState(L_151);	// 특수 납도
		 else if(KEY_DOWN(VK_XBUTTON1)) SetState(L_101);
	}

	if (RATIO > 0.96)
		SetState(S_001);
}

void Player::L110() // 기인 내디뎌베기
{
	PLAY;
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		UIManager::Get()->MinusSpiritGauge(); // 기인게이지 소모하기( 단 1번 )
	}
	if (RATIO > 0.3 && RATIO < 0.31)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);

	if (RATIO < 0.30)
		LimitRotate(15);


	// 공격판정 프레임 
	{
		if (RATIO > 0.30f && RATIO < 0.406f)
			Attack(27);
		else
			EndEffect();
	}


	if (RATIO > 0.52) // 캔슬 가능 타이밍
	{
		if (K_LMB || K_RMB)							SetState(L_105);    // 베어올리기		
		else if (K_CTRLRMB)							SetState(L_147);    // 간파 베기
		else if (K_CTRLSPACE)						SetState(L_151);	// 특수 납도
		else if (K_CTRL)							SetState(L_108);	// 기인베기3
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (K_SPACE)							Roll();				// 구르기
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

void Player::L119() // 날라차기 착지
{
	PLAY;	
	if (RATIO > 0.001 && RATIO < 0.002)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);



	// 공격판정 프레임 
	{
		if (RATIO > 0.03f && RATIO < 0.19f)
			Attack(30);
		else
			EndEffect();
	}


	if (RATIO > 0.54) // 캔슬 가능 타이밍
	{
		if (K_LMB || K_RMB || K_LMBRMB)
			SetState(L_104);    // 찌르기
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L122()
{
	PLAY;
	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	// 공격판정 프레임 
	{
		if (RATIO > 0.03f && RATIO < 0.19f)
			Attack(30);
		else
			EndEffect();
	}


	if (RATIO > 0.81) // 캔슬 가능 타이밍
	{
		if (K_LMB || K_RMB || K_LMBRMB)
			SetState(L_104);    // 찌르기
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L128()	// 날라차기 시작
{
	PLAY;
	if (!playOncePerMotion)
	{		
		UI->UseBugSkill();
		playOncePerMotion = true;		
	}

	if (RATIO < 0.2)
		LimitRotate(180);


	// 줌 정상화 (앉아 기인 회전 베기에서 넘어온 경우)
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

void Player::L130()	// 날라차기 체공중
{
	PLAY;

	// 체공중
	{
		if(Jump(850))
		// 공격판정 프레임
		{
			if ( Pos().y > 50 )
			{
				if (Attack(2, true, 3))
				{
					if (K_CTRL && UI->GetCotingLevel() > 0)
					{
						UI->MinusCotingLevel();
						SetState(L_133);  // 투구깨기
					}
					else	 	SetState(L_136);  // 낙하찌르기
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

void Player::L131() // 체공 루프
{
	PLAY;
	// 체공중
	{
		if (Jump(850))
			// 공격판정 프레임
		{
			if (Attack(2,true, 3))
			{
				if (K_CTRL && UIManager::Get()->GetCotingLevel() > 0) 
				{
					UIManager::Get()->MinusCotingLevel();
					SetState(L_133);
				}  // 투구깨기
				else	 	SetState(L_136);  // 낙하찌르기
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

void Player::L133()	// 투구깨기
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

	// 체공중
	{
		if (RATIO < 0.38) // 줌아웃
			CAM->Zoom(650, 5);

		// 공격판정 타이밍
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

void Player::L134()	// 투구깨기 루프
{

}

void Player::L135()	// 투구깨기 끝
{
	PLAY;
	EndEffect();
	CAM->Zoom(300, 5);	
	{
		if (RATIO > 0.23)
		{
			if (K_LMB || K_RMB)		SetState(L_104);	// 찌르기
			else if(K_CTRLSPACE)	SetState(L_151);	// 특수납도
			else if (K_SPACE)		Roll();				// 구르기
		}

		if (RATIO > 0.96)
		{
			SetState(L_001);
		}
	}
}

void Player::L136() // 낙하찌르기
{
	PLAY;
	if(INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);

	if (RATIO > 0.2 && RATIO < 0.3)
		Sounds::Get()->Play("Heeee", .5f);
	if(RATIO>0.5&&RATIO<0.54)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);

	// 체공중
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

void Player::L137() // 낙하찌르기 루프
{
}

void Player::L138() // 낙하찌르기 끝
{
	PLAY;

	// 체공중
	{
		if (RATIO > 0.96)
		{
			ReturnIdle();
		}
	}
}

void Player::L147() // 간파베기
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
	// 줌아웃 && 회피 판정 프레임
	{
		if (RATIO > 0 && RATIO < 0.30)
		{
			CAM->Zoom(450);
			EvadeCheck(); // 성공하면 띵 소리 나야함
		}

		if (RATIO > 0.30)
			evadeCheckCollider->SetActive(false);
	}

	// 특납 캔슬 가능 타이밍
	{
		if (RATIO > 0.205f && RATIO < 0.30f && K_CTRLSPACE)
		{
			if (isEvaded)
				isEvaded = false;
			SetState(L_151);	// 특수 납도
		}
	}


	// 공격판정 프레임 
	{
		if (RATIO > 0.33 && RATIO < 0.43)
			Attack(27);
		else
			EndEffect();
	}

	// 줌 정상화
	{
		if (RATIO > 0.33 && RATIO < 0.56)
			CAM->Zoom(300);
	}

	if (RATIO > 0.56)
	{
		if (isEvaded)
			isEvaded = false;
	}

	if (RATIO > 0.56) // 캔슬 가능 타이밍
	{
		if		(K_LMB)			SetState(L_101);    // 세로베기		
		else if (K_RMB)			SetState(L_104);	// 찌르기		
		else if (K_LMBRMB)		SetState(L_103);	// 베어내리기		
		else if (K_CTRLSPACE)	SetState(L_151);	// 특수 납도
		else if (K_CTRL)		SetState(L_109);	// 기인큰회전베기 (TODO :: 이건 조건 따져야함)	
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (K_SPACE)		Roll();				// 구르기
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L151() // 특수 납도
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


	// 줌 정상화 (기인 큰회전 베기에서 넘어온 경우)
	{
		if (RATIO > 0 && RATIO < 0.45)
			CAM->Zoom(300, 5);
	}	

	// 캔슬 가능 프레임
	{
		if (RATIO > 0.72)
		{
			if		(K_LMB)		SetState(L_154); // 앉아발도베기					
			else if (K_CTRL)	SetState(L_155); // 앉아발도기인베기
		}
	}

	if (RATIO > 0.96)
	{
		SetState(L_152);
	}
}

void Player::L152() // 특수납도대기
{
	PLAY;

	if		(K_LMB)		SetState(L_154); // 앉아발도베기					
	else if (K_CTRL)	SetState(L_155); // 앉아발도기인베기
	else if (K_SPACE)   Roll();


	L152Timer += DELTA;
	if (L152Timer >= 3.0)
	{
		L152Timer = 0.0f;
		SetState(L_153);
	}
}

void Player::L153() // 특수납도 취소 동작
{
	PLAY;

	if (RATIO > 0.96)
	{
		holdingSword = false;
		SetState(S_001);
	}
}

void Player::L154() // 앉아발도 베기
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

	// 공격판정 프레임 (이 모션은 2번 베기 동작이 있음)
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

	// 캔슬 가능 프레임
	{
		if (RATIO > 0.40)
		{
			if		(K_LMB)			SetState(L_102); // 세로베기
			else if (K_RMB)			SetState(L_104); // 찌르기
			else if (K_CTRL)		SetState(L_106); // 기인 베기 1		
			else if (K_CTRLRMB)		SetState(L_147); // 간파 베기
			else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
			else if (K_SPACE)		Roll();			 // 구르기
		}
	}

	if (RATIO > 0.96)
		ReturnIdle();

}

void Player::L155() // 앉아발도 기인베기
{
	PLAY;
	
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_8", .5f);
	}
	if (RATIO > 0.11 && RATIO < 0.15)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// 줌아웃 && 회피 판정 프레임
	{
		if (RATIO > 0.1 && RATIO < 0.18)
			CAM->Zoom(450);
	}

	if (RATIO < 0.1)
		LimitRotate(15);

	static bool isHit = false;	// hit 하고 바로 3번 공격 들어가면 어색하니까 넣어주는 bool 

	// 공격판정 프레임 
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

	// 카운터 성공 시 추가 공격 프레임
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

	// 캔슬 가능 프레임
	{
		if (RATIO > 0.39)
		{
			isEvaded = false; // 만약 앞에서 true로 남아있는 경우 보험용

			if		(K_LMB)			SetState(L_101); // 내디뎌베기
			else if (K_CTRL)		SetState(L_108); // 기인 베기 3		
			else if (K_CTRLSPACE)	SetState(L_151); // 특수 납도
			else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
			else if (K_SPACE)		Roll();			 // 구르기
		}
	}

	// 줌 정상화
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

	// 캔슬 가능 프레임
	{
		if (RATIO > 0.745)
		{
			if (K_SPACE)		Roll();			 // 구르기
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

	// 캔슬 가능 프레임
	{
		if (RATIO > 0.745)
		{
			if (K_SPACE)		Roll();			 // 구르기
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

void Player::D001()  // 소경직
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle2();
	}
}

void Player::D004() // 뒤에서 맞고 앞으로 소경직
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle2();
	}
}

void Player::D007() // 누운 상태에서 일어나기 시작
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(L_453);
	}
}

void Player::D011()  // 7의 반대
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(L_451);
	}
}

void Player::D015() // 쳐맞고 덤블링 날라가기
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

void Player::D016()  //덤블링하고 착지하며 두손으로 땅짚은 상태
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(L_451);
	}
}

void Player::D021() // 앞보고 앞으로 날라가기
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

bool Player::State_S() // 납도 스테이트 목록
{
	return curState >= S_001 && curState <= S_122;
}

void Player::StatusRender()
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
