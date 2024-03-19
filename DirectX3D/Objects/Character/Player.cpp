
#include "Framework.h"
#include "Player.h"
#include "Scenes/ShadowScene.h"
#include "Scenes/PlayerTestScene.h"
#include "Scenes/ValphalkTestScene.h"
#include "Scenes/FightTestScene.h"

Player::Player() : ModelAnimator("Player")
{
	head = new Transform();
	realPos = new Transform();
	backPos = new Transform();
	forwardPos = new Transform();
	swordStart = new Transform();
	swordEnd = new Transform();
	mainHand = new Transform();
	backSwd = new Transform();
	playerWireBugHead = new Transform();
	playerWireBugTail = new Transform();

	swordCollider = new CapsuleCollider(2.0f, 100.0f);
	swordCollider->Rot().x += XM_PIDIV2;
	swordCollider->SetParent(mainHand);
	swordCollider->Pos().z -= 100.0f;
	swordCollider->Scale() *= 3.0f;

	trail = new Trail(L"Textures/Effect/Snow.png", swordStart, swordEnd, 20, 85);
	wireBugTrail = new Trail(L"Textures/Effect/bluelight.png", playerWireBugHead, playerWireBugTail, 20, 45);

	/////////////////////////////////////////////////////////////
	// Particles

	FOR(7)
		hitParticle.push_back(new HitParticle());
	hitBoomParticle = new HitBoomParticle();
	criticalParticle = new CriticalParticle();
	spAtkParticle = new Sp_atk_ready_Particle();
	spStartParticle = new Sp_atk_start();
	spSuccessParticle = new Sp_atk_success();
	spiritParticle = new SpiritFlame();
	potionParticle = new PotionParticle();
	haloTransform = new Transform();
	haloCollider = new CapsuleCollider();
	wireBugParticle = new Wire_Bug();
	sutdol = new Sutdol();
	usebug = new UseBug();

	FOR(4)
	{
		CircleEft* cir = new CircleEft();
		cir->SetParent(realPos);
		if (i == 1) cir->Rot().z += unitRad * 50;
		if (i == 2) cir->Rot().z -= unitRad * 50;
		if (i == 3)
		{
			cir->Rot().z += XM_PIDIV2;
			cir->Scale() *= 0.9f;
		}
		cir->Pos().y += 70;
		circle.push_back(cir);
	}

	haloCollider->SetParent(swordStart);

	suwol = new Suwol();
	suwol->SetParent(realPos);

	slice = new SliceEft();
	slice->SetParent(realPos);

	tuguAtk = new headBreakAtk();

	/////////////////////////////////////////////////////////////
	longSword = new Model("kal");
	longSword->SetParent(mainHand);

	kalzip = new Model("kalzip");
	kalzip->SetParent(backSwd);

	//	longSword->Rot().x -= XM_PIDIV2;	

	tmpCollider = new CapsuleCollider(1, 0.1);
	tmpCollider->Scale().x *= 6.0f;

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

	playerWireBug = new PlayerWireBug();
	playerWireBug->SetActive(false);

	ReadClips();

	captureUI = new Quad(L"Textures/UI/CaptureUI.png");
	captureUI->Scale() *= 2.0f;

	mapChangeUI = new Quad(L"Textures/UI/MapChangeUI.png");
	mapChangeUI->Scale() *= 1.5f;

	CAM->SetTarget(head);
}

Player::~Player()
{
	delete sutdol;
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
	delete spStartParticle;
	delete spSuccessParticle;
	delete spiritParticle;
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
	delete playerWireBug;
	delete wireBugTrail;
	delete playerWireBugHead;
	delete playerWireBugTail;
	delete captureUI;
	delete mapChangeUI;
}

void Player::Update()
{
	if (UIManager::Get()->isLoading == true) return;

	if (KEY_DOWN('B'))
		SetState(L_001);

	//if (!DeathCheck())
	//{
	//	TermAttackUpdate();
	//	HurtCheck();
	//	Potion();
	//	SharpeningStone();
	//}
	///////////////////////////////////
	//디버깅을 위해서 DeathCheck() 밖으로 빼둔것.
	if (callGaruk)
		ReadyRide();

	TermAttackUpdate();
	HurtCheck();
	time += DELTA;
	if (isRiding)
		Potion();
	SharpeningStone();
	UseBlueBox();
	GetWireBug();
	Capture();
	NearMapChangeArea();
	////////////////////////////////////
	Control();
	ResetPlayTime();


	UpdateWorlds();
	EffectUpdates();

	ModelAnimator::Update();
	GroundCheck();

	///////////////////////////////
	//디버그용
	if (KEY_DOWN('5'))
		UI->PlusCotingLevel();
	if (KEY_DOWN('8'))
		isEvaded = true;
	///////////////////////////////
}

void Player::PreRender()
{
	if (renderEffect)
		trail->Render();
	if (playerWireBug->GetisMoving())
		wireBugTrail->Render();
	////////////////////////////////////////////
	// Particles
	sutdol->Render();
	hitBoomParticle->Render();
	criticalParticle->Render();
	haloCollider->Render();
	spAtkParticle->Render();
	spStartParticle->Render();
	spSuccessParticle->Render();
	spiritParticle->Render();
	potionParticle->Render();
	suwol->Render();
	slice->Render();
	FOR(circle.size()) circle[i]->Render();
	FOR(hitParticle.size()) hitParticle[i]->Render();
}

void Player::Render()
{
	if (UIManager::Get()->isLoading == true && isFirstRender == true) return;

	ModelAnimator::Render();
	tmpCollider->Render();
	tmpCollider2->Render();
	bodyCollider->Render();
	evadeCheckCollider->Render();
	//	tmpCollider3->Render();
		//swordCollider->Render();
	longSword->Render();
	kalzip->Render();


	if (playerWireBug->Active())
		playerWireBug->Render();


	if (isSetState)
	{
		Pos().x = realPos->Pos().x;
		Pos().z = realPos->Pos().z;

		if (curState < R_001 || curState > R_602)
			Pos().y = realPos->Pos().y;

		if (preState == L_155)
		{
			Rot().y += XM_PI;
		}

		isSetState = false;
	}
	isFirstRender = true;
	usebug->Render();
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
		backSwd->SetWorld(GetTransformByNode(leftHandNode));
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

	if (isRiding)
	{
		if (curState == R_031)
		{
			Pos().x = garuk->GlobalPos().x + Forward().x * 50;
			Pos().z = garuk->GlobalPos().z + Forward().z * 50;
		}
		else
		{
			if ((garuk->GlobalPos() - Pos()).Length() < 300)
			{				
				Pos().x = garuk->GlobalPos().x + Forward().x * 50;
				Pos().z = garuk->GlobalPos().z + Forward().z * 50;
			}
		}
		Rot().y = garuk->Rot().y;
		if (curState == R_600 || curState == R_601 || curState == R_602)
		{
			mainHand->SetWorld(GetTransformByNode(leftHandNode));
			longSword->Pos() = {};
			longSword->Rot() = {};
		}
		else
		{
			mainHand->SetWorld(GetTransformByNode(backSwdNode));
			longSword->Pos() = { -32,32,23 };
			longSword->Rot() = { -0.86f,-1.2f,+1.46f };
		}
	}

	Vector3 camRot = CAM->Rot();
	camRot.y += XM_PI;

	if (KEY_DP('W') && KEY_DP('D'))				keyboardRot = camRot.y + XM_PIDIV4;
	else if (KEY_DP('W') && KEY_DP('A'))		keyboardRot = camRot.y - XM_PIDIV4;
	else if (KEY_DP('S') && KEY_DP('D'))		keyboardRot = camRot.y + XM_PIDIV4 * 3;
	else if (KEY_DP('S') && KEY_DP('A'))		keyboardRot = camRot.y - XM_PIDIV4 * 3;
	else if (KEY_DP('W'))						keyboardRot = camRot.y;
	else if (KEY_DP('A'))						keyboardRot = camRot.y - XM_PIDIV2;
	else if (KEY_DP('S'))						keyboardRot = camRot.y - XM_PI;
	else if (KEY_DP('D'))						keyboardRot = camRot.y + XM_PIDIV2;
	else										keyboardRot = 0.0f;

	if (keyboardRot < -3.14)		keyboardRot += XM_2PI;
	if (keyboardRot > 3.14)			keyboardRot -= XM_2PI;


	realPos->Pos() = GetTranslationByNode(1);
	realPos->UpdateWorld();

	backPos->Pos() = GetTranslationByNode(1) + Forward() * 100;
	forwardPos->Pos() = GetTranslationByNode(1) + Back() * 50 + Vector3::Up() * 80;

	head->Pos().x = realPos->Pos().x;
	if (isRiding && curState != R_031)
		head->Pos().y = realPos->Pos().y + 100;
	else
		head->Pos().y = realPos->Pos().y + 200;
	head->Pos().z = realPos->Pos().z;

	lastSwordEnd = swordStart->Pos();

	swordStart->Pos() = longSword->GlobalPos() + longSword->Back() * 271.0f; // 20.0f : 10% 크기 반영
	swordEnd->Pos() = longSword->GlobalPos() + longSword->Back() * 260.0f;

	swordStart->UpdateWorld();
	swordEnd->UpdateWorld();

	playerWireBugHead->Pos() = playerWireBug->GlobalPos() + playerWireBug->Forward() * 2.0f + playerWireBug->Right() * 2.0f;
	playerWireBugTail->Pos() = playerWireBug->GlobalPos() + playerWireBug->Back() * 2.0f + playerWireBug->Left() * 2.0f;

	playerWireBugHead->UpdateWorld();
	playerWireBugTail->UpdateWorld();

	if (!playerWireBug->GetisMoving())
		playerWireBug->Pos() = GetTranslationByNode(leftHandNode);

	swordSwingDir = lastSwordEnd - swordStart->GlobalPos();
	tmpCollider->Pos() = GetTranslationByNode(node);
	tmpCollider->Rot() = GetRotationByNode(node);

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

	playerWireBug->Rot() = Rot();
	playerWireBug->Update();

	haloTransform->Pos() = longSword->GlobalPos() + longSword->Back() * 55.f;
	haloCollider->Pos() = haloTransform->Pos();

	if (KEY_DOWN('T'))
	{
		Sounds::Get()->Play("igonan2", 0.1f);
		UI->curHP = UI->maxHP;		
		UI->curStamina = 100;
		UI->curSpiritGauge = UI->maxSpiritGauge;
		UI->cotingLevel = 3;
		UI->curCoting = UI->maxCoting;
		UI->bugCount = 0;
	}
	if (KEY_DOWN('Y'))
	{
		UI->curHP -= 10;
		UI->recoverHP -= 5;
	}
}

void Player::Potion()
{
	if ((UI->useQuickSlot1 && UI->haveGPotion > 0 && time > 6.0f)
		|| (UI->useDragSlot && ItemManager::Get()->tag == "GreatePotion" && KEY_DOWN('E') && UI->haveGPotion > 0 && time > 6.0f)
		|| (UI->useNumberBar && UI->haveGPotion > 0 && KEY_DOWN('2') && time > 6.0f))
	{
		UI->haveGPotion--;
		Lcure = true;
		time = 0;
	}
	if (Lcure == true)
	{
		if (time > 2 && time < 4.2f)
		{
			UI->LargeHealthPotion();
		}
		else if (time >= 5)
		{
			Lcure = false;
		}
	}

	if ((UI->useQuickSlot2 && UI->havePotion > 10 && time > 6.0f)
		|| (UI->useDragSlot && ItemManager::Get()->tag == "Potion" && KEY_DOWN('E') && UI->havePotion > 10 && time > 6.0f)
		|| (UI->useNumberBar && UI->havePotion > 10 && KEY_DOWN('1') && time > 6.0f))
	{
		UI->havePotion--;
		cure = true;
		time = 0;
	}
	if (cure == true)
	{
		if (time > 2 && time < 4)
		{
			UI->HealthPotion();
		}
		else if (time >= 4)
		{
			cure = false;
		}
	}
}

void Player::SharpeningStone()
{
	if (UI->useQuickSlot3 && time > 6.0f
		|| UI->useDragSlot && ItemManager::Get()->tag == "Whetstone" && KEY_DOWN('E') && time > 6.0f
		|| UI->useNumberBar && KEY_DOWN('3') && time > 6.0f)
	{
		time = 0;
		//UI->SharpeningStone();
	}
}

void Player::UseBlueBox()
{
	ItemManager::Get()->UseBlueBox(realPos->Pos());
}


void Player::GUIRender()
{
	//	ModelAnimator::GUIRender();
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

//	Vector3 realpos = realPos->Pos();
//	ImGui::DragFloat3("Pos", (float*)&Pos());
//
//	ImGui::DragFloat3("RealPos", (float*)&realpos);
//
//	Vector3 rot = Rot();
//	ImGui::DragFloat3("Rot", (float*)&rot);

	Vector3 camRot = CAM->Rot();
	camRot.y += XM_PI;
	if (camRot.y < -3.14)
		camRot.y += XM_2PI;

	if (camRot.y > 3.14)
		camRot.y -= XM_2PI;

	ImGui::DragFloat3("camRot", (float*)&camRot);

	Vector3 sightRot = CAM->sightRot->Rot();
	ImGui::DragFloat3("sightRot", (float*)&sightRot);

//	float keyDir = keyboardRot;
//	ImGui::DragFloat("KeyDir", &keyDir);
//
//
//	float ratio = RATIO;
//	ImGui::DragFloat("clipRatio", &ratio);
//
//	ImGui::DragFloat("Speed", &temp4);
//
//	suwol->GUIRender();
//
//	//int U = Keyboard::Get()->ReturnFirst();
//	//ImGui::SliderInt("keyboard", &U, 0, 200);
//	//
//	//
//	ImGui::SliderInt("node", &node, 1, 210);
//	float value = UI->GetSpritGauge();
//	ImGui::DragFloat("SpiritGauge", &value);
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
	ImGui::DragFloat3("playerWireBug Pos", (float*)&playerWireBug->Pos());
}

void Player::PostRender()
{
	//	StatusRender(); // 모션 추가중이므로 주석
	DamageRender();
	tuguAtk->PostRender();

	if (isCaptureUIActive)
		captureUI->Render();

	if (isMapChangeUIActive)
		mapChangeUI->Render();
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

	case Player::L_126:		L126();		break;
	case Player::L_127:		L127();		break;

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

		// 가루크 탑승 모션
	case Player::R_001:		R001();		break;
	case Player::R_013:		R013();		break;
	case Player::R_024:		R024();		break;
	case Player::R_031:		R031();		break;
	case Player::R_041:		R041();		break;
	case Player::R_104:		R104();		break;
	case Player::R_142:		R142();		break;
	case Player::R_143:		R143();		break;
	case Player::R_144:		R144();		break;
	case Player::R_400:		R400();		break;
	case Player::R_401:		R401();		break;
	case Player::R_402:		R402();		break;
	case Player::R_600:		R600();		break;
	case Player::R_601:		R601();		break;
	case Player::R_602:		R602();		break;


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

	case Player::W_005:		W005();		break;
	case Player::W_006:		W006();		break;
	case Player::W_007:		W007();		break;
	case Player::W_009:		W009();		break;
	case Player::W_010:		W010();		break;
	case Player::W_020:		W020();		break;
	case Player::W_062:		W062();		break;
	case Player::W_063:		W063();		break;
	case Player::F_072:		F072();		break;
	case Player::F_073:		F073();		break;

	case Player::T_019:		T019();		break;
	case Player::T_020:		T020();		break;
	case Player::T_050:		T050();		break;
	case Player::T_051:		T051();		break;
	case Player::T_052:		T052();		break;

	case Player::E_092:		E092();		break;
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
	if (KEY_PRESS('A') && KEY_PRESS('W'))
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

	if (KEY_FRONT(Keyboard::CTRL) && UI->curSpiritGauge >= 10)
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

void Player::ReadyRide()
{
	// 가루크를 불러
	if (dog->isCallDog == false)
	{
		dog->SetFollow();
		dog->isCallDog = true;
	}

	// 가루크가 근처에 있나 확인해
	// 내가 납도 상태고 지상에 있어서 상태인지 체크해
	// 가능하면 탑승해
	if (dog->readyToRide == true)
	{
		// 탑승해도 안어색한 상태들
		if (State_S())
		{
			Ride();
		}
		else
		{
			dog->isCallDog = false;
			dog->readyToRide = false;
			callGaruk = false;
		}
	}
}

void Player::Ride()
{
	if (dog == nullptr)
		return;

	dog->SetRide();
	dog->SetRotPos(Rot(), realPos->Pos());
	dog->isCallDog = false;
	dog->readyToRide = false;
	callGaruk = false;
	isRiding = true;
	SetState(R_031);
}

void Player::EndRide()
{
	if (dog == nullptr)
		return;

	Rot().y += XM_PI;
	dog->SetFollow();
	isRiding = false;
}

void Player::ResetPlayTime()
{
	if (preState != curState)
		GetClip(preState)->ResetPlayTime();
}

void Player::EffectUpdates()
{
	trail->Update();
	wireBugTrail->Update();
	FOR(hitParticle.size())		hitParticle[i]->Update();
	hitBoomParticle->Update();
	criticalParticle->Update();
	spAtkParticle->Update();
	spStartParticle->Update();
	spSuccessParticle->Update();
	potionParticle->Update();
	//potionParticle->SetParent(realPos);
	potionParticle->SetPos(realPos->Pos());
	potionParticle->SetVortex({ realPos->Pos().x,realPos->Pos().y + 100,realPos->Pos().z });
	spSuccessParticle->SetPos({ realPos->Pos().x,realPos->Pos().y + 100,realPos->Pos().z });
	//spiritParticle->SetPos({ realPos->Pos().x,realPos->Pos().y + 100,realPos->Pos().z });
	spiritParticle->Update();
	sutdol->Update();
	suwol->Update();
	tuguAtk->Update();

	slice->Rot().y = atan2(Forward().x, Forward().z);
	slice->Update();
	FOR(circle.size())
	{

		if (curState == L_109)
		{
			circle[0]->Rot().x = 0;
			circle[0]->Rot().y += 30 * DELTA;
			circle[0]->Rot().z = 0;
		}
		else if (curState == L_108)
		{
			circle[i]->Rot().x += 50 * DELTA;
			circle[i]->Rot().y = atan2(Back().x, Back().z);
		}
		else
			circle[i]->Rot().y = atan2(Forward().x, Forward().z);
		circle[i]->Update();
	}
	usebug->Update();
	if (playerWireBug->Active())
	{
		isbugeffect = true;
	}
	if (isbugeffect)
	{
		bugtime += DELTA;
		if (bugtime <= 0.1f && bugtime > 0.01f)
			usebug->Play1(playerWireBug->Pos());
		if (bugtime <= 0.2f && bugtime > 0.11f)
			usebug->Play2(playerWireBug->Pos());
		if (bugtime <= 0.3f && bugtime > 0.21f)
			usebug->Play3(playerWireBug->Pos());
		if (bugtime <= 0.4f && bugtime > 0.31f)
			usebug->Play4(playerWireBug->Pos());
		if (bugtime <= 0.5f && bugtime > 0.41f)
			usebug->Play5(playerWireBug->Pos());
		if (bugtime <= 0.6f && bugtime > 0.51f)
			usebug->Play6(playerWireBug->Pos());
		if (bugtime <= 0.7f && bugtime > 0.61f)
			usebug->Play7(playerWireBug->Pos());
		if (bugtime <= 0.8f && bugtime > 0.71f)
			usebug->Play8(playerWireBug->Pos());
		if (bugtime <= 0.9f && bugtime > 0.81f)
			usebug->Play9(playerWireBug->Pos());
		if (bugtime >= 0.8f && bugtime <= .9f)
			usebug->Play10(playerWireBug->Pos());
	}
	if (bugtime > 3)
	{
		bugtime = 0;
		isbugeffect = false;
	}
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

		if (keyboardRot > Rot().y + unitRad)
			RealRotate(rotateSpeed * DELTA);
		else if (keyboardRot < Rot().y - unitRad)
			RealRotate(-rotateSpeed * DELTA);
	}

}

void Player::LimitRotate(float limit, float rotSpeed)
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
			sumRot += rotSpeed * DELTA;
			if (sumRot < unitRad * limit)
			{
				RealRotate(rotSpeed * DELTA);
			}
		}
		else
		{
			sumRot += rotSpeed * DELTA;
			if (sumRot < unitRad * limit)
			{
				RealRotate(-rotSpeed * DELTA);
			}
		}
	}
}

bool Player::Attack(float power, bool push, UINT useOtherCollider) // 충돌판정 함수
{
	renderEffect = true;

	if (val == nullptr && dumVal != nullptr)
		return AttackDummy(power, push, useOtherCollider);
	else if (val == nullptr && dumVal == nullptr)
		return false;

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
		case 3:	playerCollider = bodyCollider; break;
		default: playerCollider = swordCollider; break;
		}
	}



	for (auto collider : colliders)
	{
		if (playerCollider->IsCapsuleCollision(collider, &contact) && !attackOnlyOncePerMotion)
		{
			if (!collider->Active())
				return false;

			criticalParticle->ParticleRotate();
			hitBoomParticle->Play(contact.hitPoint, swordSwingDir);
			criticalParticle->Play(contact.hitPoint, swordSwingDir);
			hitParticle[lastParticleIndex]->Play(contact.hitPoint, swordSwingDir);
			lastParticleIndex++;
			if (lastParticleIndex >= hitParticle.size())
				lastParticleIndex = 0;

			attackOnlyOncePerMotion = true;

			if (curState == L_101 || curState == L_102 || curState == L_103) // 기인베기 아니라면 게이지 증가
				UI->DoublePlusSpritGauge();

			if (curState == L_104 || curState == L_105)
				UI->PlusSpritGauge();

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
			case Valphalk::HEAD: hardness = 55; break;
			case Valphalk::NECK: hardness = 55; break;
			case Valphalk::CHEST: hardness = 30; break;
			case Valphalk::BODY: hardness = 30; break;
			case Valphalk::LWING: hardness = 22; break;
			case Valphalk::LWING_RADIUS: hardness = 22; break;
			case Valphalk::RWING: hardness = 22; break;
			case Valphalk::RWING_RADIUS: hardness = 22; break;
			case Valphalk::LLEG1: hardness = 25; break;
			case Valphalk::LLEG1_FOOT: hardness = 25; break;
			case Valphalk::LLEG2: hardness = 25; break;
			case Valphalk::LLEG2_FOOT: hardness = 25; break;
			case Valphalk::RLEG1: hardness = 25; break;
			case Valphalk::RLEG1_FOOT: hardness = 25; break;
			case Valphalk::RLEG2: hardness = 25; break;
			case Valphalk::RLEG2_FOOT: hardness = 25; break;
			case Valphalk::TAIL_START: hardness = 45; break;
			case Valphalk::TAIL_1: hardness = 45; break;
			case Valphalk::TAIL_2: hardness = 45; break;
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

			RandHitSounds();
			val->minusCurHP(deal);

			if (collider->part == Valphalk::HEAD
				|| collider->part == Valphalk::NECK)
				val->minusHeadHP(deal);

			if ((collider->part == Valphalk::CHEST
				|| collider->part == Valphalk::BODY) && val->GetIsHupgi())
				val->minusChestHP(deal);

			if (collider->part == Valphalk::LLEG1
				|| collider->part == Valphalk::LLEG1_FOOT)
				val->minusLLegHP(deal);

			if (collider->part == Valphalk::RLEG1
				|| collider->part == Valphalk::RLEG1_FOOT)
				val->minusRLegHP(deal);

			if (collider->part == Valphalk::TAIL_START
				|| collider->part == Valphalk::TAIL_1
				|| collider->part == Valphalk::TAIL_2
				|| collider->part == Valphalk::TAIL)
				val->minusTailHP(deal);

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

bool Player::AttackDummy(float power, bool push, UINT useOtherCollider)
{

	DummyValphalk* val = dumVal;

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

			if (curState == L_101 || curState == L_102 || curState == L_103) // 기인베기 아니라면 게이지 증가
				UIManager::Get()->DoublePlusSpritGauge();

			if (curState == L_104 || curState == L_105) // 기인베기 아니라면 게이지 증가
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
	vector<CapsuleCollider*> colliders;

	if (val != nullptr)
		colliders = val->GetCollider();
	else if (dumVal != nullptr)
		colliders = dumVal->GetCollider();
	else
		return;

	int hitPart = lastHitPart;

	Vector3 hitPos = colliders[hitPart]->GetHitPointPos();
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
	case Valphalk::HEAD:			hardness = 55; break;
	case Valphalk::NECK:			hardness = 55; break;
	case Valphalk::CHEST:			 hardness = 30; break;
	case Valphalk::BODY:			hardness = 30; break;
	case Valphalk::LWING:			 hardness = 22; break;
	case Valphalk::LWING_RADIUS:	hardness = 22; break;
	case Valphalk::RWING:			hardness = 22; break;
	case Valphalk::RWING_RADIUS:	hardness = 22; break;
	case Valphalk::LLEG1:			hardness = 25; break;
	case Valphalk::LLEG1_FOOT:		hardness = 25; break;
	case Valphalk::LLEG2:			hardness = 25; break;
	case Valphalk::LLEG2_FOOT:		hardness = 25; break;
	case Valphalk::RLEG1:			hardness = 25; break;
	case Valphalk::RLEG1_FOOT:		hardness = 25; break;
	case Valphalk::RLEG2:			hardness = 25; break;
	case Valphalk::RLEG2_FOOT:		hardness = 25; break;
	case Valphalk::TAIL_START:		hardness = 45; break;
	case Valphalk::TAIL_1:			hardness = 45; break;
	case Valphalk::TAIL_2:			hardness = 45; break;
	case Valphalk::TAIL:			hardness = 45; break;
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
	if (!bodyCollider->Active() || val == nullptr)
		return;

	auto colliders = val->GetCollider();
	auto sphereColliders = val->GetSphereCollider();
	auto boxColliders = val->GetBoxCollider();

	for (auto collider : colliders)
	{
		if (bodyCollider->IsCapsuleCollision(collider))  /// 발파루크 캡슐들이랑 충돌을 했어
		{
			Vector3 fwd = Forward();
			Vector3 atkDir = -1 * collider->direction;
			if (collider->direction == Vector3(0, 0, 0))
				collider->direction = realPos->Pos() - collider->Pos();
			atkDir.y = 0;
			Vector3 reDir = -1 * atkDir;
			Vector3 rad = XMVector3AngleBetweenVectors(fwd, atkDir);

			if (collider->isAttack && collider->Active())						// 근데 그 콜리더가 공격 콜리더야
			{
				if (curState >= L_400)
					return;

				if (curState == L_155 && RATIO < 0.36)
				{
					isEvaded = true;
					return;
				}

				if (curState == L_126 && RATIO < 0.8)
				{
					isEvaded = true;
					return;
				}

				evadeCheckCollider->SetActive(false);
				evadeCheckCollider->UpdateWorld();

				int str = collider->atkStrength;
				holdingSword = false;
				if (rad.x > XM_PIDIV2)
				{
					Rot().y = atan2(reDir.x, reDir.z);
					UpdateWorld();

					switch (str)
					{
					case 1:   SetState(D_001); 	break;
					case 2:   SetState(D_015); 	break;
					case 3:   SetState(D_045); 	break;
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
					case 3:   SetState(D_045); 	break;
					default:  SetState(D_021); 	break;
					}
				}
				RandHurtVoice();
				UI->curHP -= collider->atkDmg;
				UI->recoverHP -= collider->atkDmg / 2;
			}
		}
	}

	for (auto collider : sphereColliders)
	{
		if (bodyCollider->IsSphereCollision(collider))  /// 구체 충돌을 했어
		{
			Vector3 fwd = Forward();
			Vector3 atkDir = -1 * collider->direction;
			if (collider->direction == Vector3(0, 0, 0))
				collider->direction = realPos->Pos() - collider->Pos();
			atkDir.y = 0;
			Vector3 reDir = -1 * atkDir;
			Vector3 rad = XMVector3AngleBetweenVectors(fwd, atkDir);

			if (collider->Active())
			{
				if (curState >= L_400)
					return;

				if (curState == L_155 && RATIO < 0.36)
				{
					isEvaded = true;
					return;
				}
				if (curState == L_126 && RATIO < 0.8)
				{
					isEvaded = true;
					return;
				}

				evadeCheckCollider->SetActive(false);
				evadeCheckCollider->UpdateWorld();

				holdingSword = false;

				if (rad.x > XM_PIDIV2)
				{
					Rot().y = atan2(reDir.x, reDir.z);
					UpdateWorld();

					SetState(D_015);
				}
				else
				{
					Rot().y = atan2(atkDir.x, atkDir.z);
					UpdateWorld();

					SetState(D_021);
				}
				RandHurtVoice();
				UI->curHP -= collider->atkDmg;
				UI->recoverHP -= collider->atkDmg / 2;
			}
		}
	}

	for (auto collider : boxColliders)
	{
		if (bodyCollider->IsBoxCollision(collider))  /// 박스 충돌을 했어
		{
			Vector3 fwd = Forward();
			Vector3 atkDir = -1 * collider->direction;
			if (collider->direction == Vector3(0, 0, 0))
				collider->direction = realPos->Pos() - collider->Pos();
			atkDir.y = 0;
			Vector3 reDir = -1 * atkDir;
			Vector3 rad = XMVector3AngleBetweenVectors(fwd, atkDir);

			if (collider->Active())
			{
  				if (curState >= L_400)
					return;

				if (curState == L_155 && RATIO < 0.36)
				{
					isEvaded = true;
					return;
				}
				if (curState == L_126 && RATIO < 0.8)
				{
					isEvaded = true;
					return;
				}

				evadeCheckCollider->SetActive(false);
				evadeCheckCollider->UpdateWorld();

				holdingSword = false;

				if (rad.x > XM_PIDIV2)
				{
					Rot().y = atan2(reDir.x, reDir.z);
					UpdateWorld();

					SetState(D_015);
				}
				else
				{
					Rot().y = atan2(atkDir.x, atkDir.z);
					UpdateWorld();

					SetState(D_021);
				}
				RandHurtVoice();
				UI->curHP -= collider->atkDmg;
				UI->recoverHP -= collider->atkDmg / 2;
			}
		}
	}
}

void Player::EvadeCheck()
{
	if (val == nullptr) return;

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

	if (isHitL155) // 앉아 발도 기인베기
	{
		TermAttackTimer += DELTA;

		if (TermAttackTimer > 0.4 && TermAttackTimer < 0.5)
		{
			if (!playOncePerTerm)
			{
				RandHitSounds();
				AttackWOCollision(17);
				circle[0]->active = true;
				playOncePerTerm = true;
			}
		}
		else if (TermAttackTimer > 0.55f && TermAttackTimer < 0.65f)
		{
			if (playOncePerTerm)
			{
				RandHitSounds();
				AttackWOCollision(17);
				circle[1]->active = true;
				playOncePerTerm = false;
			}
		}
		else if (TermAttackTimer > 0.7f && TermAttackTimer < 0.8f)
		{
			if (!playOncePerTerm)
			{
				RandHitSounds();
				AttackWOCollision(17);
				circle[2]->active = true;
				playOncePerTerm = true;
			}
		}
		else if (TermAttackTimer > 0.8f)
		{
			isHitL155 = false;
			FOR(3) circle[i]->active = false;
			playOncePerTerm = false;
			TermAttackTimer = 0.0;
		}
	}


	if (isHitL133)
	{
		TermAttackTimer2 += DELTA;
		int dmg = 0;
		if (UI->cotingLevel == 2) dmg = 28;
		else if (UI->cotingLevel == 1) dmg = 17.5f;
		else if (UI->cotingLevel == 0) dmg = 10.5f;


		if (TermAttackTimer2 > 0.6 && TermAttackTimer2 < 0.65)
		{
			if (!playOncePerTerm2)
			{
				RandHitSounds();
				AttackWOCollision(dmg);
				playOncePerTerm2 = true;
			}
		}
		else if (TermAttackTimer2 > 0.70f && TermAttackTimer2 < 0.75f)
		{
			if (playOncePerTerm2)
			{
				RandHitSounds();
				AttackWOCollision(dmg);
				playOncePerTerm2 = false;
			}
		}
		else if (TermAttackTimer2 > 0.80f && TermAttackTimer2 < 0.85f)
		{
			if (!playOncePerTerm2)
			{
				RandHitSounds();
				AttackWOCollision(dmg);
				playOncePerTerm2 = true;
			}
		}
		if (TermAttackTimer2 > 0.9 && TermAttackTimer2 < 0.95)
		{
			if (playOncePerTerm2)
			{
				RandHitSounds();
				AttackWOCollision(dmg);
				playOncePerTerm2 = false;
			}
		}
		else if (TermAttackTimer2 > 1.0f && TermAttackTimer2 < 1.05f)
		{
			if (!playOncePerTerm2)
			{
				RandHitSounds();
				AttackWOCollision(dmg);
				playOncePerTerm2 = true;
			}
		}
		else if (TermAttackTimer2 > 1.1f && TermAttackTimer2 < 1.15f)
		{
			if (playOncePerTerm2)
			{
				RandHitSounds();
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
				RandHitSounds();
				AttackWOCollision(19);
				playOncePerTerm2 = true;
			}
		}
		else if (TermAttackTimer2 > 0.2f && TermAttackTimer2 < 0.25f)
		{
			if (playOncePerTerm2)
			{
				RandHitSounds();
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
	randVoice = rand() % 5;
	if (curState <R_001 || curState >R_602) // 가루크 탑승때는 필요없음
		isSetState = true;


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

	ReadClip("L_126");
	ReadClip("L_127");

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

	ReadClip("R_001");
	ReadClip("R_013");
	ReadClip("R_024");
	ReadClip("R_031");
	ReadClip("R_041");
	ReadClip("R_104");
	ReadClip("R_142");
	ReadClip("R_143");
	ReadClip("R_144");
	ReadClip("R_400");
	ReadClip("R_401");
	ReadClip("R_402");
	ReadClip("R_600");
	ReadClip("R_601");
	ReadClip("R_602");

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

	ReadClip("W_005");
	ReadClip("W_006");
	ReadClip("W_007");
	ReadClip("W_009");
	ReadClip("W_010");
	ReadClip("W_020");
	ReadClip("W_062");
	ReadClip("W_063");
	ReadClip("F_072");
	ReadClip("F_073");

	ReadClip("T_019");
	ReadClip("T_020");
	ReadClip("T_050");
	ReadClip("T_051");
	ReadClip("T_052");

	ReadClip("E_092");
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
	if (K_LMB && !ItemManager::Get()->useBlueBox)		SetState(L_101);
	else if (KEY_DP('F'))  callGaruk = true;
	else if (UI->IsAbleBugSkill() && K_LBUG)	SetState(W_005);	// 사선 밧줄벌레 이동
	else if (KEY_DP(VK_SPACE))	Roll();


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
	if (K_LMB && !ItemManager::Get()->useBlueBox)			SetState(L_101);
	else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);
	else if (KEY_DP(VK_SPACE))	Roll();
	else if (UI->IsAbleBugSkill() && K_LBUG)	SetState(W_005);	// 사선 밧줄벌레 이동
	else if (KEY_DP('F'))  callGaruk = true;

	if (RATIO > 0.97)
	{
		SetState(S_011);
	}
}

void Player::S008() // 서서 납도
{
	PLAY;

	if (RATIO > 0.6)
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
	UI->staminaActive = false;

	Rotate();
	RandBreath();
	if (KEY_DP(VK_LSHIFT))
		SetState(S_122);

	if (!K_MOVE)
	{
		SetState(S_014);
	}

	// 101 내디뎌 베기
	if (K_LMB)		SetState(L_101);
	else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);
	else if (K_SPACE)	Roll();
	else if (UI->IsAbleBugSkill() && K_LBUG)	SetState(W_005);	// 사선 밧줄벌레 이동
	else if (KEY_DP('F'))  callGaruk = true;

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
	else if (KEY_DP('F'))  callGaruk = true;



	if (RATIO > 0.96)
	{
		SetState(S_001);
	}
}

void Player::S017()
{

}

void Player::S018() // 납도상태 구르기
{
	PLAY;
	if (RATIO < 0.1)
	{
		switch (randVoice)
		{
		case 0: Sounds::Get()->Play("roll1", 2.f); break;
		case 1: Sounds::Get()->Play("roll2", 2.f); break;
		case 2: Sounds::Get()->Play("roll3", 2.f); break;
		case 3: Sounds::Get()->Play("roll2", 2.f); break;
		case 4: Sounds::Get()->Play("roll3", 2.f); break;
		default: break;
		}
	}
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
		else if (KEY_DOWN('F')) callGaruk = true;

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
	if (RATIO < 0.1)
		Sounds::Get()->Play("exhausted", 2.f);
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
	RandBreath();
	UI->curStamina -= 0.05f;

	if (UIManager::Get()->curStamina < 0.1f)
		SetState(S_118);

	if (KEY_UP(VK_LSHIFT))
		SetState(S_011);	

	if (!K_MOVE)	
		SetState(S_014);	

	if (KEY_DOWN('F')) callGaruk = true;
	else if (UI->IsAbleBugSkill() && K_LBUG)	SetState(W_005);	// 사선 밧줄벌레 이동

	if (K_LMB)		SetState(L_101);
	else if (K_SPACE)	
		Roll();	

	if (RATIO > 0.95)
		Loop();
}

void Player::L001() // 발도상태 대기
{
	PLAY;
	if (K_MOVE)
		SetState(L_005);

	else if (KEY_PRESS(VK_LSHIFT))		SetState(S_008); // 납도	
	else if (K_LMB && !ItemManager::Get()->useBlueBox)		SetState(L_101);	// 101 내디뎌 베기	
	else if (K_RMB)		SetState(L_104);	// 104 찌르기	
	else if (K_LMBRMB)	SetState(L_103);	// 103 베어내리기
	else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);	// 106 기인 베기	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
	else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
	else if (K_SPACE)	Roll();				// 010 구르기

	if (KEY_DOWN('V'))
		SetState(L_128);
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
	RandBreath();

	if (KEY_PRESS(VK_LSHIFT))		SetState(L_009); // 납도	
	else if (K_LMB)		SetState(L_101);	// 101 내디뎌 베기	
	else if (K_RMB)		SetState(L_104);	// 104 찌르기	
	else if (K_LMBRMB)	SetState(L_103);	// 103 베어내리기
	else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);	// 106 기인 베기	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
	else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
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
	else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);	// 106 기인 베기	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
	else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
	else if (K_SPACE)	Roll();				// 010 구르기

	Rotate();

	if (!K_MOVE)
		SetState(L_008);


	if (RATIO > 0.96)
	{
		if (K_MOVE)
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
	else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);	// 106 기인 베기	
	else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
	else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
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
	if (RATIO < 0.1)
	{
		switch (randVoice)
		{
		case 0: Sounds::Get()->Play("roll1", 2.f); break;
		case 1: Sounds::Get()->Play("roll2", 2.f); break;
		case 2: Sounds::Get()->Play("roll3", 2.f); break;
		case 3: Sounds::Get()->Play("roll2", 2.f); break;
		case 4: Sounds::Get()->Play("roll3", 2.f); break;
		default: break;
		}
	}
	if (RATIO < 0.40)
		bodyCollider->SetActive(false);
	else
		bodyCollider->SetActive(true);

	// 줌 정상화
	{
		if (RATIO > 0 && RATIO < 0.9)
			CAM->Zoom(400, 5);
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
			CAM->Zoom(400, 5);
	}

	if (!K_MOVE)
		SetState(L_008);


	if (RATIO > 0.28)
	{
		if (KEY_PRESS(VK_LSHIFT))		SetState(L_009); // 납도	
		else if (K_LMB)		SetState(L_101);	// 101 내디뎌 베기	
		else if (K_RMB)		SetState(L_104);	// 104 찌르기	
		else if (K_LMBRMB)	SetState(L_103);	// 103 베어내리기
		else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);	// 106 기인 베기	
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
		else if (K_SPACE)	Roll();				// 010 구르기
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
		isEvaded = false;
	}
	if (RATIO > 0.3 && RATIO < 0.35)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.34 && RATIO < 0.35)
		RandVoice();

	if (RATIO < 0.3)
	{
		LimitRotate(15);
	}


	// 줌 정상화 (앉아 기인 회전 베기에서 넘어온 경우)
	{
		if (RATIO > 0 && RATIO < 0.45)
			CAM->Zoom(400, 5);
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

		if (K_LMB)				SetState(L_102);	// 세로베기		
		else if (K_RMB)				SetState(L_104);	// 찌르기
		else if (K_LMBRMB)			SetState(L_103);	// 베어내리기
		else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);	// 기인베기1		
		else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
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
		if (K_LMB || K_RMB)	SetState(L_104);	// 찌르기
		else if (K_LMBRMB)			SetState(L_103);	// 베어내리기
		else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);	// 기인베기1		
		else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
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
		isEvaded = false;
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
		if (K_RMB)				SetState(L_104);	// 찌르기
		else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_110);	// 기인내디뎌베기		
		else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
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
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
		isEvaded = false;
	}

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
		if (K_LMB || K_RMB)	SetState(L_105);	// 베어올리기
		else if (K_LMBRMB)			SetState(L_103);	// 베어내리기
		else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);	// 기인베기1		
		else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
		else if (K_SPACE)			Roll();

	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L105() // 베어 올리기
{
	PLAY;
	if (INIT)
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
		if (K_LMB)			SetState(L_102);	// 세로베기		
		else if (K_RMB)			SetState(L_104);	// 찌르기		
		else if (K_LMBRMB)		SetState(L_103);	// 베어내리기		
		else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106);	// 기인베기1		
		else if (K_CTRLRMB)		SetState(L_147);	// 간파 베기
		else if (K_CTRLSPACE)	SetState(L_151);	// 특수 납도
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
		else if (K_SPACE)		Roll();
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L106() // 기인 베기 1
{
	if (INIT)
	{
		spiritParticle->Play({ realPos->Pos().x, realPos->Pos().y + 100, realPos->Pos().z }, 0);
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		PlayClip(curState);
		initForward = Forward();
	}
	
	if (!playOncePerMotion)
	{
		UI->MinusSpiritGauge();
		playOncePerMotion = true;
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

		if (K_RMB)			SetState(L_104);	// 찌르기		
		else if (K_LMBRMB)		SetState(L_103);	// 베어내리기		
		else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_107);	// 기인 베기2		
		else if (K_CTRLRMB)		SetState(L_147);	// 간파 베기		
		else if (K_CTRLSPACE)	SetState(L_151);	// 특수 납도		
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
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
		spiritParticle->Play({ realPos->Pos().x, realPos->Pos().y + 100, realPos->Pos().z }, 0);
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
	}

	if (!playOncePerMotion)
	{
		UI->MinusSpiritGauge();
		playOncePerMotion = true;
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
			if (K_LMB || K_RMB)	SetState(L_105);	// 베어올리기
			else if (K_LMBRMB)			SetState(L_103);	// 베어내리기		
			else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_108);	// 기인 베기3		
			else if (K_CTRLRMB)			SetState(L_147);	// 간파 베기
			else if (K_CTRLSPACE)		SetState(L_151);	// 특수 납도		
			else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
			else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
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
		spiritParticle->Play({ realPos->Pos().x, realPos->Pos().y + 100, realPos->Pos().z }, 0);
		PlayClip(curState);
		initForward = Forward();
	}

	if (!playOncePerMotion)
	{
		UI->MinusSpiritGauge();
		playOncePerMotion = true;
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
			CAM->Zoom(400, 5);
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
				circle[3]->active = true;
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
		if (K_RMB || K_LMB)	SetState(L_104);  // 찌르기		
		else if (K_LMBRMB)			SetState(L_103);  // 베어내리기		
		else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_109);  // 기인 큰회전베기
		else if (K_CTRLRMB)			SetState(L_147);  // 간파 베기
		else if (K_CTRLSPACE)		SetState(L_151);  // 특수 납도		
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
		else if (K_SPACE)			Roll();			  // 구르기		
		circle[3]->active = false;
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L109() // 기인 큰회전베기
{
	PLAY;
	if (INIT)
	{
		spSuccessParticle->Play(Pos(), 0);
		spiritParticle->Play({ realPos->Pos().x, realPos->Pos().y + 100, realPos->Pos().z }, 0);
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		isEvaded = false;
	}

	if (!playOncePerMotion)
	{
		UI->MinusSpiritGauge();
		playOncePerMotion = true;
	}

	if (RATIO > 0.2 && RATIO < 0.21)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.1 && RATIO < 0.15)
		RandVoice();
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
			circle[0]->active = true;
		}
		else
			EndEffect();
	}

	if (RATIO > 0.30) // 특납 연계 가능 타이밍 언제?
	{
		circle[0]->active = false;
		if (K_CTRLSPACE)	SetState(L_151);	// 특수 납도
		else if (KEY_DOWN(VK_XBUTTON1)) SetState(L_101);
	}

	// 줌 정상화
	{
		if (RATIO > 0.47 && RATIO < 0.84)
			CAM->Zoom(400, 5);
	}

	if (RATIO > 0.96)
		SetState(S_001);
}

void Player::L110() // 기인 내디뎌베기
{
	PLAY;
	if (INIT)
	{
		spiritParticle->Play({ realPos->Pos().x, realPos->Pos().y + 100, realPos->Pos().z }, 0);
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
	}

	if (!playOncePerMotion)
	{
		UI->MinusSpiritGauge();
		playOncePerMotion = true;
	}

	if (RATIO > 0.3 && RATIO < 0.31)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.3)
		RandVoice();

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
		else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_108);	// 기인베기3
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
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

void Player::L119()
{
	PLAY;
	if (RATIO > 0.001 && RATIO < 0.002)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.3)
		RandVoice();



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

void Player::L122() // 날라차기 착지
{
	PLAY;

	//if (!playOncePerMotion)
	//{
	//	Pos().y = 0.0f;
	//	UpdateWorld();
	//	playOncePerMotion = true;
	//}

	if (RATIO > 0.2 && RATIO < 0.3)
		RandVoice();
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
	{
		playOncePerMotion = false;
		ReturnIdle();
	}
}

void Player::L126() // 수월의 자세
{
	PLAY;

	if (RATIO < 0.2)
		LimitRotate(180, 50);
	if(RATIO<0.1)
	Sounds::Get()->Play("suwolstart",0.5f);

	if (RATIO > 0.01 && RATIO < 0.8)
	{
		suwol->effect = true;
		if (isEvaded)
		{
			SetState(L_127);
			isEvaded = false;
		}

	}

	if (RATIO > 0.8)
	{
		suwol->effect = false;
	}

	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L127() // 수월의 자세 카운터
{
	PLAY;

	if (RATIO < 0.1)
		Sounds::Get()->Play("suwolattack", 0.5f);
	if (RATIO > 0.10)
	{
		suwol->effect = false;
		if (!playOncePerMotion)
		{
			slice->active = true; // 이펙트 켜주고
			playOncePerMotion = true;
		}
		if (RATIO < 0.27)
		{
			switch (UI->cotingLevel)
			{
			case 0:		Attack(80);		break;
			case 1:		Attack(80);		break;
			case 2:		Attack(120);	break;
			case 3:		Attack(200);	break;
			}
		}
	}

	if (RATIO > 0.27)
	{
		if (K_SPACE) Roll();
	}
	if (RATIO > 0.69)
	{
		if (K_CTRL)			SetState(L_108);
		else if (K_LMB || K_RMB)   SetState(L_105);
	}


	if (RATIO > 0.96)
		ReturnIdle();
}

void Player::L128()	// 날라차기 시작
{
	PLAY;

	wireBugParticle->Play(GetTranslationByNode(108), GetRotationByNode(129));
	if (!playOncePerMotion)
	{
		UI->UseBugSkill();
		Sounds::Get()->Play("wirebug", 3.5f);
		isEvaded = false;
		playerWireBug->SetActive(true);
		playOncePerMotion = true;
		if (keyboardRot != 0.0f)
			Rot().y = keyboardRot;
	}


	if (RATIO > 0.5 && !playOncePerMotion2)
	{
		Vector3 pos = GetTranslationByNode(leftHandNode);
		playerWireBug->SetMove(pos, true, Back() * 1000 + Up() * 400);
		playOncePerMotion2 = true;
	}


	// 줌 정상화 (앉아 기인 회전 베기에서 넘어온 경우)
	{
		if (RATIO > 0 && RATIO < 0.9)
			CAM->Zoom(400, 5);
	}


	if (RATIO > 0.96)
	{
		playOncePerMotion = false;
		playOncePerMotion2 = false;
		SetState(L_130);
	}
}

void Player::L130()	// 날라차기 체공중 
{
	PLAY;

	// 체공중
	{
		if (RATIO > 0.05)
		{
			if (Jump(900, 2))
				// 공격판정 프레임
			{
				if (Attack(2, true, 3))
				{
					if (K_CTRL && UI->GetCotingLevel() > 0)
					{
						UI->MinusCotingLevel();
						playerWireBug->SetActive(false);
						playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
						SetState(L_133);  // 투구깨기
					}
					else
					{
						playerWireBug->SetActive(false);
						playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
						SetState(L_136);  // 낙하찌르기
					}
				}

				if (RATIO > 0.96)
				{
					SetState(L_131);
				}
			}
			else
			{
				SetState(L_122);
			}
		}

	}
	if (RATIO > 0.25)
		playerWireBug->SetStop();

	if (RATIO > 0.5)
	{
		playerWireBug->SetActive(false);
		playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
	}
}

void Player::L131() // 체공 루프
{
	PLAY;
	// 체공중
	{
		if (Jump(900, 2))
			// 공격판정 프레임
		{
			if (Attack(2, true, 3))
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
			SetState(L_122);
		}
	}
}

void Player::L132()
{

}

void Player::L133()	// 투구깨기
{
	PLAY;
	if (INIT)
	{
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_25", .5f);
		Sounds::Get()->Play("helmbreaker", 0.5f);
		if (isInitVoice == false)
		{
			RandSpecialVoice();
			isInitVoice = true;
		}
	}

	if (RATIO > 0.4 && RATIO < 0.44)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);

	if (RATIO < 0.35)
		LimitRotate(180);

	// 체공중
	{
		if (RATIO < 0.38) // 줌아웃
			CAM->Zoom(750, 5);

		// 공격판정 타이밍
		if (RATIO > 0.38)
		{
			if (Attack(40))
			{
				isHitL133 = true;
			}
		}


		if (RATIO > 0.38 && realPos->Pos().y < height)
		{
			Pos().y = height;
			tuguAtk->active = true;
			jumpVelocity = originJumpVelocity;
			playOncePerMotion = false;
			isJump = false;
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
	isInitVoice = false;
	EndEffect();
	CAM->Zoom(400, 5);
	{
		if (RATIO > 0.23)
		{
			if (K_LMB || K_RMB)		SetState(L_104);	// 찌르기
			else if (K_CTRLSPACE)	SetState(L_151);	// 특수납도
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
	if (INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);

	if (RATIO > 0.2 && RATIO < 0.3)
		RandVoice();
	if (RATIO > 0.5 && RATIO < 0.54)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);

	// 체공중
	{
		if (RATIO > 0.55)
		{
			if (Attack(19))
				isHitL136 = true;
		}

		if (realPos->Pos().y < height)
		{
			EndEffect();
			Pos().y = height;
			jumpVelocity = originJumpVelocity;
			isJump = false;
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
		UI->curSpiritGauge = 0;
	}
	if (RATIO < 0.1)
		spStartParticle->Play(Pos(), 0);
	if (RATIO > 0.2 && RATIO < 0.3)
		RandVoice();
	UIManager::Get()->staminaActive = false;
	// 줌아웃 && 회피 판정 프레임
	{
		if (RATIO > 0 && RATIO < 0.30)
		{
			CAM->Zoom(650);
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
			evadeCheckCollider->SetActive(false);
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
			CAM->Zoom(400);
	}

	if (RATIO > 0.56) // 캔슬 가능 타이밍
	{
		if (K_LMB)			SetState(L_101);    // 세로베기		
		else if (K_RMB)			SetState(L_104);	// 찌르기		
		else if (K_LMBRMB)		SetState(L_103);	// 베어내리기		
		else if (K_CTRLSPACE)	SetState(L_151);	// 특수 납도
		else if (K_CTRL && isEvaded)	SetState(L_109);	// 기인큰회전베기
		else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
		else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
		else if (K_SPACE)		Roll();				// 구르기
	}

	if (RATIO > 0.96)
	{
		isEvaded = false;
		ReturnIdle();
	}
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
		isEvaded = false;
	}
	//if (RATIO > 0.2 && RATIO < 0.3)
	//	RandVoice();

	if (RATIO > 0.5 && RATIO < 0.6)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_9", .5f);

	if (RATIO > 0.56 && RATIO < 0.57)
		spAtkParticle->Play(haloCollider->Pos() + Right() * 1.0f, { 0,1,0 });

	if (RATIO < 0.2)
		LimitRotate(180, 15);


	// 줌 정상화 (기인 큰회전 베기에서 넘어온 경우)
	{
		if (RATIO > 0 && RATIO < 0.45)
			CAM->Zoom(400, 5);
	}

	// 캔슬 가능 프레임
	{
		if (RATIO > 0.72)
		{
			if (K_LMB)		SetState(L_154); // 앉아발도베기					
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

	if (K_LMB)		SetState(L_154); // 앉아발도베기					
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
	if (INIT)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_5", .5f);
	if (RATIO > 0.01 && RATIO < 0.05)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.17 && RATIO < 0.18)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	if (RATIO > 0.2 && RATIO < 0.3)
		RandVoice();

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
			if (K_LMB)			SetState(L_102); // 세로베기
			else if (K_RMB)			SetState(L_104); // 찌르기
			else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_106); // 기인 베기 1		
			else if (K_CTRLRMB)		SetState(L_147); // 간파 베기
			else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
			else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
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
		//Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_8", .5f);
	}
	if (RATIO > 0.11 && RATIO < 0.15)
		Sounds::Get()->Play("pl_wp_l_swd_com_media.bnk.2_7", .5f);
	// 줌아웃 && 회피 판정 프레임
	{
		if (RATIO > 0.1 && RATIO < 0.18)
			CAM->Zoom(450);
	}

	if (RATIO < 0.1)
	{
		spStartParticle->Play(Pos(), 0);
		LimitRotate(15);
	}

	static bool isHit = false;	// hit 하고 바로 3번 공격 들어가면 어색하니까 넣어주는 bool 

	// 공격판정 프레임 
	{
		if (RATIO > 0.1 && RATIO < 0.36)
		{
			holdingSword = false;
			if (Attack(35))
			{
				isHit = true;
				CAM->SetLockOnTarget(damages.back().pos);
			}
		}
		else
			EndEffect();
	}

	// 카운터 성공 시 추가 공격 프레임
	{
		if (isHit && (RATIO > 0.385 && RATIO < 0.39))
		{
			spSuccessParticle->Play(Pos(), 0);
			if (isHitL155 == false)
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
			CAM->SetLockOnTarget(Vector3(0, 0, 0));
			isEvaded = false; // 만약 앞에서 true로 남아있는 경우 보험용

			if (K_LMB)			SetState(L_101); // 내디뎌베기
			else if (K_CTRL && UI->curSpiritGauge >= 10)	SetState(L_108); // 기인 베기 3		
			else if (K_CTRLSPACE)	SetState(L_151); // 특수 납도
			else if (UI->IsAbleBugSkill() && K_LBUG)		SetState(L_128);	// 날라차기
			else if (UI->IsAbleBugSkill() && K_RBUG)		SetState(L_126);	// 수월의자세
			else if (K_SPACE)		Roll();			 // 구르기
		}
	}

	// 줌 정상화
	{
		if (RATIO > 0.40 && RATIO < 0.85)
			CAM->Zoom(400, 5);
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

void Player::R001()  // 탑승 후 대기 idle
{
	PLAY;

	if (K_MOVE)				SetState(R_013);
	if (K_SPACE)			SetState(R_104);
	if (KEY_DOWN('E'))
	{
		if (ItemManager::Get()->tag == "Whetstone")
			SetState(R_600);
		else if (cure || Lcure)
			SetState(R_400);
	}
	else if (UI->useNumberBar || UI->useSelectBar)
	{
		if (UI->useQuickSlot3 || UI->useNumberSlot3)
			SetState(R_600);
		else if (cure || Lcure)
			SetState(R_400);
	}
}

void Player::R013() // 쉬프트 안누르고 뛰기 루프, 근데 포지션이랑 로테이션 다 가루크에서 받아오니까 루프안해도 됨
{
	PLAY;

	if (!K_MOVE)		SetState(R_024);
	if (K_SPACE)		SetState(R_104);
	if (KEY_DOWN('E'))
	{
		if (ItemManager::Get()->tag == "Whetstone")
			SetState(R_600); // 숫돌
		else if (cure || Lcure)
			SetState(R_400); // 물약
	}
	else if (UI->useNumberBar || UI->useSelectBar)
	{
		if (UI->useQuickSlot3 || UI->useNumberSlot3)
			SetState(R_600);
		else if (cure || Lcure)
			SetState(R_400);
	}
}

void Player::R024() // 뛰다가 멈춤
{
	PLAY;



	if (K_MOVE && RATIO > 0.5)
		SetState(R_013);

	if (RATIO > 0.96)
		SetState(R_001);
}

void Player::R031() // 탑승
{
	PLAY;
	if (INIT)
	{
		switch (randVoice)
		{
		case 0: Sounds::Get()->Play("riding1", 2.5f); break;
		case 1: Sounds::Get()->Play("riding2", 2.5f); break;
		case 2: Sounds::Get()->Play("riding1", 2.5f); break;
		case 3: Sounds::Get()->Play("riding2", 2.5f); break;
		case 4: Sounds::Get()->Play("riding1", 2.5f); break;
		default: break;
		}
	}
	if (RATIO > 0.43)
	{
		if (K_MOVE)
		{
			SetState(R_013);
		}
	}



	if (RATIO > 0.96)
	{
		if (K_MOVE)
			SetState(R_013);
		else
			SetState(R_001);
	}
}

void Player::R041() // 뒤돌아 탑승
{
}

void Player::R104() // 달리다가 내리기
{
	PLAY;

	if (RATIO > 0.46)
	{
		EndRide();

		if (K_MOVE)
			SetState(S_005);
		else
			SetState(S_001);
	}

}

void Player::R142() // 포효 리액션
{
}

void Player::R143() // 포효 리액션 loop
{
}

void Player::R144() // 리액션 마무리
{
}

void Player::R400() //물약 먹기 시작
{
	PLAY;
	if (RATIO > 0.96)
		SetState(R_401);
}

void Player::R401() // 물약 빠는중
{
	PLAY;
	if (RATIO < 0.1)
		Sounds::Get()->Play("eatting", 2.3f);
	if (RATIO > 0.96)
		SetState(R_402);
}

void Player::R402() // 물약 다먹은
{
	PLAY;
	if (RATIO < 0.1f)
	{
		Sounds::Get()->Play("health_potion", 0.3f);
		potionParticle->Play(Pos() + Back() * 10, { 0,0,0 });
	}

	if (RATIO > 0.96)
	{
		if (K_MOVE)
			SetState(R_013);
		else
			SetState(R_001);

	}
}

void Player::R600() // 숫돌질
{
	PLAY;
	Vector3 r = GetTranslationByNode(rightHandNode) - GetTranslationByNode(145);
	r.GetNormalized();
	sutdol->SetPos(GetTranslationByNode(rightHandNode));

	if (RATIO < 0.8 && RATIO > 0.79)
	{
		sutdol->Play(GetTranslationByNode(rightHandNode), r);
		Sounds::Get()->Play("wheatstone1", 0.3f);
	}

	if (RATIO > 0.96)
		SetState(R_601);
}

void Player::R601() // 숫돌질
{
	PLAY;
	Vector3 r = GetTranslationByNode(rightHandNode) - GetTranslationByNode(145);
	r.GetNormalized();
	sutdol->SetPos(GetTranslationByNode(rightHandNode));

	if (RATIO < 0.35 && RATIO > 0.31)
	{
		sutdol->Play(GetTranslationByNode(rightHandNode), r);
		Sounds::Get()->Play("wheatstone1", 0.3f);
	}


	if (RATIO > 0.96)
		SetState(R_602);
}

void Player::R602() // 숫돌 마무리
{
	PLAY;
	Vector3 r = GetTranslationByNode(rightHandNode) - GetTranslationByNode(145);
	r.GetNormalized();
	sutdol->SetPos(GetTranslationByNode(rightHandNode));

	if (RATIO < 0.1 && RATIO > 0.09)
	{
		sutdol->Play(GetTranslationByNode(rightHandNode), r);
		Sounds::Get()->Play("wheatstone1", 0.3f);
	}
	if (RATIO > 0.59)
		sutdol->SetPos(longSword->GlobalPos() + longSword->Back() * 120.0f);
	if (RATIO < 0.6 && RATIO>0.59)
	{
		sutdol->PlayHalo(longSword->GlobalPos() + longSword->Back() * 120.0f);
		Sounds::Get()->Play("wheatstone2", 0.3f);
		UI->SharpeningStone();
	}
	if (RATIO > 0.96)
	{
		if (K_MOVE)
			SetState(R_013);
		else
			SetState(R_001);

	}
}

void Player::L400()
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();

	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::L403()
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::L451()
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
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
	//if (INIT)
	//	RandHurtVoice();
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
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		ReturnIdle();
	}
}

void Player::D001()  // 소경직
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		ReturnIdle2();
	}
}

void Player::D004() // 뒤에서 맞고 앞으로 소경직
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		ReturnIdle2();
	}
}

void Player::D007() // 누운 상태에서 일어나기 시작
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		SetState(L_453);
	}
}

void Player::D011()  // 7의 반대
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		SetState(L_451);
	}
}

void Player::D015() // 쳐맞고 덤블링 날라가기
{
	PLAY;

	if (!playOncePerMotion)
	{
		jumpVelocity = 2.0f;
		playOncePerMotion = true;
	}
	//if (INIT)
	//	RandHurtVoice();
	if (Jump(300))
	{
		Pos() += Back() * temp4 * DELTA;

		if (UI->IsAbleBugSkill() && K_LBUG)
		{
			playOncePerMotion = false;

			Vector3 camRot = CAM->Rot();
			camRot.y += XM_PI;
			Rot().y = camRot.y;
			SetState(W_009);
		}
	}
	else
	{
		playOncePerMotion = false;
		SetState(D_016);
	}
}

void Player::D016()  //덤블링하고 착지하며 두손으로 땅짚은 상태
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		SetState(L_451);
	}
}

void Player::D021() // 앞보고 앞으로 날라가기
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
	if (Jump(300))
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
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		SetState(L_453);
	}
}

void Player::D026()
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		SetState(D_007);
	}
}

void Player::D029()
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
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
	//if (INIT)
	//	RandHurtVoice();
	if (RATIO > 0.96)
	{
		SetState(D_007);
	}
}

void Player::D032()
{
	PLAY;
	//if (INIT)
	//	RandHurtVoice();
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
	//if (INIT)
	//	RandHurtVoice();
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

void Player::W005() // 사선으로 쏘는 밧줄벌레 전 동작
{
	PLAY;

	if (!playOncePerMotion)
	{
		//UI->UseBugSkill();
		Sounds::Get()->Play("wirebug", 3.5f);
		playerWireBug->SetActive(true);
		playOncePerMotion = true;
	}

	if (RATIO > 0.5 && !playOncePerMotion2)
	{
		Vector3 pos = GetTranslationByNode(leftHandNode);
		playerWireBug->SetMove(pos, true, Back() * 2000 + Up() * 800);
		playOncePerMotion2 = true;
	}

	if (RATIO > 0.96)
	{
		playerWireBug->SetStop();
		playOncePerMotion = false;
		playOncePerMotion2 = false;
		SetState(W_006);
	}
}

void Player::W006() // W005에서 이어지는 체공중 동작
{
	PLAY;

	if (RATIO > 0.25)
	{
		playerWireBug->SetActive(false);
		playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
	}

	if (Jump(1200, 1.5))
	{
		if (RATIO > 0.1 && UI->IsAbleBugSkill() && K_LBUG)
		{
			if (keyboardRot != 0.0f)
				Rot().y = keyboardRot;
			SetState(W_009);
		}

		else if (RATIO > 0.1 && UI->IsAbleBugSkill() && K_SPACE)
		{
			if (keyboardRot != 0.0f)
				Rot().y = keyboardRot;
			SetState(W_020);
		}

		if (RATIO > 0.96)
		{
			if (KEY_DP('W'))
			{
				SetState(F_073);
				playerWireBug->SetActive(false);
				playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());				
			}
			else
			{
				SetState(F_072);
				playerWireBug->SetActive(false);
				playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
			}
		}
	}
	else
	{
		if (KEY_DP('W'))
		{
			SetState(F_073);
			playerWireBug->SetActive(false);
			playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
		}
		else
		{
			SetState(F_072);
			playerWireBug->SetActive(false);
			playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
		}
	}
}

void Player::W007() // 낙하모션 Loop
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle2();
	}
}

void Player::W009() // 공중에서 전방으로 밧줄벌레 발사
{
	PLAY;

	Pos() -= Forward() * 500 * DELTA;

	if (!playOncePerMotion)
	{
		//UI->UseBugSkill();
		Sounds::Get()->Play("wirebug", 3.5f);
		playerWireBug->SetActive(true);
		playOncePerMotion = true;
	}

	if (!playOncePerMotion2)
	{
		Vector3 pos = GetTranslationByNode(leftHandNode);
		playerWireBug->SetMove(pos, true, Back() * 1600 + Up() * 100);
		playOncePerMotion2 = true;
	}

	if (RATIO > 0.96)
	{
		playOncePerMotion = false;
		playOncePerMotion2 = false;
		playerWireBug->SetStop();
		SetState(W_020);
	}
}

void Player::W010() // 사선 밧줄벌레 발사 착지 후 달리기
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(W_010);
	}
}

void Player::W020() // 밧줄벌레 발사 후 공중 체공중 구르기 눌렀을 때
{
	PLAY;

	if (!playOncePerMotion)
	{
		jumpVelocity = 6.0f;
		playOncePerMotion = true;
	}

	if (Jump(1400, 1.5))
	{
		if (RATIO > 0.96)
		{
			if (K_MOVE)
			{
				SetState(F_073);
				playerWireBug->SetActive(false);
				playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
			}
			else
			{
				SetState(F_072);
				playerWireBug->SetActive(false);
				playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
			}
		}
	}
	else
	{
		if (K_MOVE)
		{
			SetState(F_073);
			playerWireBug->SetActive(false);
			playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
		}
		else
		{
			SetState(F_072);
			playerWireBug->SetActive(false);
			playerWireBug->SetMove(Vector3::Zero(), false, Vector3::Zero());
		}
	}
}

void Player::W062() // 공중에서 매달려있기 시작
{
	PLAY;

	if (!playOncePerMotion)
	{
		playerWireBug->SetActive(true);
		playOncePerMotion = true;
	}

	if (RATIO > 0.96)
	{
		SetState(W_063);
	}
}

void Player::W063() // W062 루프
{
	PLAY;

	if (RATIO > 0.96)
	{
		SetState(W_007);
	}
}

void Player::F072() // 착지 후 제자리
{
	PLAY;

	if (RATIO > 0.96)
	{
		ReturnIdle2();
	}
}

void Player::F073() // 착지 후 앞으로 이동
{
	PLAY;

	Rotate();

	if (RATIO > 0.96)
	{
		SetState(S_011);
	}
}

void Player::T019() // 맵 입장
{
	PLAY;

	if (RATIO > 0.03 && RATIO < 0.13)
		Sounds::Get()->Play("mapchangestart", 1.0f);

	if (RATIO > 0.96)
	{
		//ReturnIdle2(); 입장, 도착 따로 하려면 이거로 쓰고
		SetState(T_020); // 합쳐서 쓰려면 그대로 쓰면 됨
	}
}

void Player::T020() // 맵 도착
{
	PLAY;

	if (RATIO > 0.05 && RATIO < 0.15)
		Sounds::Get()->Play("mapchangeend", 1.0f);

	if (RATIO > 0.96)
	{
		ReturnIdle2();
	}
}

void Player::T050() // 갈무리 시작
{
	PLAY;

	if (RATIO > 0.083 && RATIO < 0.183)
		Sounds::Get()->Play("capturing", 0.2f);

	if (RATIO > 0.226 && RATIO < 0.326)
		Sounds::Get()->Play("capturing2", 3.0f);


	if (RATIO > 0.96)
	{
		UI->captureIcon1 = true;
		SetState(T_051);
	}
}

void Player::T051() // 갈무리 중간
{
	PLAY;

	if (RATIO > 0.043 && RATIO < 0.143)
		Sounds::Get()->Play("capturing", 0.2f);

	if (RATIO > 0.191 && RATIO < 0.291)
		Sounds::Get()->Play("capturing2", 3.0f);

	if (RATIO > 0.96)
	{
		UI->captureIcon2 = true;
		SetState(T_052);
	}
}

void Player::T052() // 갈무리 끝
{
	PLAY;

	if (RATIO > 0.001 && RATIO < 0.101)
		Sounds::Get()->Play("capturing", 0.2f);

	if (RATIO > 0.139 && RATIO < 0.239)
		Sounds::Get()->Play("capturing2", 3.0f);


	if (RATIO > 0.96)
	{
		UI->captureIcon3 = true;
		isCaptured = true;
		isCaptureUIActive = false;
		ReturnIdle2();
	}
}

void Player::E092()
{
	PLAY;

	if (RATIO > 0.05 && RATIO < 0.15)
		Sounds::Get()->Play("queststart", 2.0f);

	if (RATIO > 0.96)
	{
		UI->isRender = true;
		ReturnIdle2();
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
	return (curState >= S_001 && curState <= R_602) || curState >= D_001;
}

void Player::StatusRender()
{
	vector<string> strStatus;

	//	strStatus.push_back("L_001 발도 상태 대기");
	//	strStatus.push_back("L_002 발도");
	//	strStatus.push_back("L_003 서서납도");
	//	strStatus.push_back("L_004 발도상태 걷기");
	//	strStatus.push_back("L_005 발도상태 걷기 시작");
	//	strStatus.push_back("L_006 발도상태 좌로 걷기 시작");
	//	strStatus.push_back("L_007 발도상태 우로 걷기 시작");
	//	strStatus.push_back("L_008 멈춤");
	//	strStatus.push_back("L_009 걸으면서 납도 ");
	//	strStatus.push_back("L_010 앞구르기");
	//	strStatus.push_back("L_011 왼쪽구르기");
	//	strStatus.push_back("L_012 오른쪽구르기");
	//	strStatus.push_back("L_013 뒤구르기");
	//	strStatus.push_back("L_014 구른후걷기");
	//	strStatus.push_back("L_015 구른후뒤걷기");
	//	strStatus.push_back("L_071 낮은높이언덕파쿠르");
	//	strStatus.push_back("L_072 중간높이언덕파쿠르");
	//	strStatus.push_back("L_073 높은높이언덕파쿠르");
	//	strStatus.push_back("L_077 ?");
	//	strStatus.push_back("L_078 ?");
	//	strStatus.push_back("L_079 ?");
	//	strStatus.push_back("L_101 내디뎌베기");
	//	strStatus.push_back("L_102 세로베기");
	//	strStatus.push_back("L_103 베어내리기");
	//	strStatus.push_back("L_104 찌르기");
	//	strStatus.push_back("L_105 베어올리기");
	//	strStatus.push_back("L_106 기인베기1");
	//	strStatus.push_back("L_107 기인베기2");
	//	strStatus.push_back("L_108 기인베기3");
	//	strStatus.push_back("L_109 기인큰회전베기");
	//	strStatus.push_back("L_110 기인내디뎌베기");
	//	strStatus.push_back("L_111 일자베기");
	//
	//	strStatus.push_back("S_003 납도 달리기");
	//	strStatus.push_back("S_008 제자리 납도");
	//	strStatus.push_back("S_009 걸으면서 납도");
	//
	//	string fps = "Status : " + strStatus.at((UINT)curState);
	//	Font::Get()->RenderText(fps, { 150, WIN_HEIGHT - 30 });
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

			if (d.isWeakness)
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

			if (d.isWeakness)
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

bool Player::Jump(float moveSpeed, float jumpSpeed)
{
	jumpVelocity -= 9.8f * jumpSpeed * DELTA;
	Pos() -= Forward() * moveSpeed * DELTA;
	Pos().y += jumpVelocity;

	if (realPos->Pos().y >= height || jumpVelocity > 0) // 상승 중일때나 y 값이 헤이트 이상이라면
	{
		isJump = true;
		return true;
	}
	else
	{
		{
			isJump = false;
			Pos().y = height;
			jumpVelocity = originJumpVelocity;
			return false;
		}
	}
}

void Player::GroundCheck()
{

	if (terrain == nullptr)
	{
		height = 0.0f;
		return;
	}


	Vector3 pos;
	terrain->ComputePicking(pos, realPos->Pos() + Vector3::Up() * 400, Vector3::Down());
	height = pos.y;

	if (!isJump)
		Pos().y = height;
}

void Player::RandVoice()
{
	switch (randVoice)
	{
	case 0:		Sounds::Get()->Play("attack1", 2.5f);		break;
	case 1:		Sounds::Get()->Play("attack2", 2.5f);		break;
	case 2:		Sounds::Get()->Play("attack3", 2.5f);		break;
	case 3:		Sounds::Get()->Play("attack4", 2.5f);		break;
	case 4:		Sounds::Get()->Play("attack5", 2.5f);		break;
	default:
		break;
	}
}

void Player::RandSpecialVoice()
{
	randVoice = rand() % 4;
	switch (randVoice)
	{
	case 0:		Sounds::Get()->Play("special1", 2.1f);		break;
	case 1:		Sounds::Get()->Play("special2", 2.1f);		break;
	case 2:		Sounds::Get()->Play("special3", 2.1f);		break;
	case 3:		Sounds::Get()->Play("special4", 2.1f);		break;
	default:
		break;
	}
}

void Player::RandHurtVoice()
{
	// 현재 상태가 대경직이 아니라면
	randVoice = rand() % 3;
	if (curState != L_451 && curState != L_453 && curState != D_015 && curState != D_016 && curState != D_021 &&
		curState != D_022 && curState != D_026 && curState != D_029 && curState != D_031 && curState != D_032)
	{
		switch (randVoice)
		{
		case 0:		Sounds::Get()->Play("hurt1", 2.5f);		break;
		case 1:		Sounds::Get()->Play("hurt2", 2.5f);		break;
		case 2:		Sounds::Get()->Play("hurt3", 2.5f);		break;
		case 3:		Sounds::Get()->Play("igonan1", .09f);	break;
		default:
			break;
		}
	}
	else // 대경직이라면
	{
		randVoice = rand() % 2;
		switch (randVoice)
		{
		case 0:		Sounds::Get()->Play("big_hurt1", 2.5f);		break;
		case 1:		Sounds::Get()->Play("big_hurt2", 2.5f);		break;
		case 2:		Sounds::Get()->Play("igonan2", .09f);		break;
		default:
			break;
		}
	}
}

void Player::RandBreath()
{
	// 달리다 일정 시간마다 체크해서 걸리면 사운드가 랜덤으로 나오는 식
	breathCount += DELTA;
	if (breathCount > 1.5) // 달리는 상태를 유지하는 동안 1.5초마다 체크한다.
	{
		randVoice = rand() % 6;
		switch (randVoice)
		{
		case 0:		Sounds::Get()->Play("breath", 1.5f);		break;
		case 1:		Sounds::Get()->Play("breath2", 1.5f);		break;
		case 2:		Sounds::Get()->Play("breath3", 1.5f);		break;
		case 3:		Sounds::Get()->Play("", 1.5f);		break;
		case 4:		Sounds::Get()->Play("", 1.5f);		break;
		case 5:		Sounds::Get()->Play("", 1.5f);		break;
		default:
			break;
		}
		breathCount = 0;
	}
}

void Player::GetWireBug()
{
	if (wireBug == nullptr || !(wireBug->Active()))
		return;

	Vector3 playerPos = realPos->Pos();
	playerPos.y = 0;

	Vector3 wireBugPos = wireBug->Pos();
	wireBugPos.y = 0;

	float distance = (playerPos - wireBugPos).Length();

	wireBug->UpdateUI();

	if (distance <= 150)
	{
		wireBug->SetWireBugPickUpUIActive(true);
		
		if (!soundOncePerUI)
		{
			Sounds::Get()->Play("uisound", 1.0f);
			soundOncePerUI = true;
		}

		if (KEY_PRESS('G')) // 키 변경 가능
		{
			UI->GetWildBug();
			Sounds::Get()->Play("getWildBug", 1.0f);
			wireBug->SetWireBugPickUpUIActive(false);
			wireBug->SetActive(false);
		}
	}
	else
	{
		wireBug->SetWireBugPickUpUIActive(false);
		soundOncePerUI = false;
	}
}

void Player::RandHitSounds()
{
	int i = rand() % 3;
	switch (i)
	{
	case 0:		Sounds::Get()->Play("hit_pl_media.bnk.2_14", 1.1f);		break;
	case 1:		Sounds::Get()->Play("hit_pl_media.bnk.2_20", 1.1f);		break;
	case 2:		Sounds::Get()->Play("hit_pl_media.bnk.2_35", 1.1f);		break;
	default:
		break;
	}
}

void Player::Capture()
{
	if (val == nullptr || !(val->GetIsDead()) || isCaptured)
		return;

	UpdateCaptureUI();

	Contact contact;

	auto colliders = val->GetCollider();
	UINT count = 0;

	for (auto collider : colliders)
	{
		if (collider == colliders[Valphalk::ROAR])
			continue;

		if (tmpCollider->IsCapsuleCollision(collider, &contact))
			count++;
	}

	if (count > 0)
	{
		isCaptureUIActive = true;

		if (!soundOncePerUI)
		{
			Sounds::Get()->Play("uisound", 1.0f);
			soundOncePerUI = true;
		}

		if (KEY_PRESS('G')) // 키 변경 가능
			SetState(T_050);
	}
	else
	{
		isCaptureUIActive = false;
		soundOncePerUI = false;
	}
}

void Player::UpdateCaptureUI()
{
	UIPos = realPos->Pos() + Vector3::Up() * 200;

	if (!CAM->ContainPoint(UIPos))
	{
		isCaptureUIActive = false;
		return;
	}

	captureUI->Pos() = CAM->WorldToScreen(UIPos);

	captureUI->UpdateWorld();
}

void Player::NearMapChangeArea()
{
	if (mapChanged)
		return;

	Vector3 playerPos = realPos->Pos();
	playerPos.y = 0;

	Vector3 mapChangeAreaPos = { 0,0,100 };// 여기서 맵 이동지점 정하기
	mapChangeAreaPos.y = 0;

	float distance = (playerPos - mapChangeAreaPos).Length();

	UIPos2 = mapChangeAreaPos + Vector3::Up() * 200;

	if (!CAM->ContainPoint(UIPos2))
	{
		isMapChangeUIActive = false;
		return;
	}

	mapChangeUI->Pos() = CAM->WorldToScreen(UIPos2);

	mapChangeUI->UpdateWorld();

	if (distance <= 150)
	{
		isMapChangeUIActive = true;

		if (!soundOncePerUI2)
		{
			Sounds::Get()->Play("uisound", 1.0f);
			soundOncePerUI2 = true;
		}

		if (KEY_PRESS('G')) // 키 변경 가능
		{
			isMapChangeUIActive = false;
			mapChanged = true;
			SetState(T_019);
		}
	}
	else
	{
		isMapChangeUIActive = false;
		soundOncePerUI2 = false;
	}
}
