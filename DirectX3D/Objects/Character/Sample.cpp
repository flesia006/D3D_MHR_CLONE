#include "Framework.h"
#include "Sample.h"

Sample::Sample() : ModelAnimator("Sample")
{
	ReadClip("IDLE");
	ReadClip("WorK");
	ReadClip("DIGIN");
	ReadClip("DIGOUT");
	ReadClip("G_0022");
	ReadClip("G_0040");
	ReadClip("G_0084");
	ReadClip("G_0126");
	ReadClip("G_0127");

	ReadClip("BATTLEIDLE");
	ReadClip("FIRE");
	ReadClip("BACKSTEP");
	ReadClip("FWDSTEP");
	ReadClip("TURNLEFT");
	ReadClip("TURNBACK");


	realPos = new Transform();
	waist = new Transform();

	bowGun = new Model("bowGun");
	arrow = new Model("arrow");
	bowGun->SetParent(waist);

	fireParticle = new Garuk_Fire();	
}

Sample::~Sample()
{
	delete realPos;
	delete waist;
	delete bowGun;
	delete fireParticle;
}

void Sample::Update()
{
	UpdateWorlds();

	if (KEY_DP('3'))
		SetFight();
	switch (mode)
	{
	case Sample::RIDING:		Control();		break;
	case Sample::FOLLOWING:		Follow();		break;
	case Sample::BATTLE:		Battle();		break;
	}

	ModelAnimator::Update();
	ResetPlayTime();
	GroundCheck();
	fireParticle->Update();
}

void Sample::Render()
{

	ModelAnimator::Render();

	if (mode == BATTLE)
	{
		bowGun->Render();
	}

	

	if (isSetState)
	{
		Pos() = realPos->Pos();
		isSetState = false;
		isLoop = false;
	}
	if (isLoop)
	{
		Pos() = realPos->Pos();
		isLoop = false;

	}

	fireParticle->Render();
}

void Sample::GUIRender()
{
//	ModelAnimator::GUIRender();
//	Vector3 realpos = realPos->Pos();
//	Vector3 pos = Pos();
//
//	ImGui::DragFloat3("realPos", (float*)&realpos);
//	ImGui::DragFloat3("Pos", (float*)&pos);
//	ImGui::DragFloat("lengToTrgt", &lengToTrgt);
//	ImGui::DragFloat("radbtw", &radBtwEnemy);
//	
//	bowGun->GUIRender();	
	arrow->GUIRender();
}

void Sample::UpdateWorlds()
{
	Vector3 camRot = CAM->Rot();
	camRot.y += XM_PI;

	if (KEY_DP('W') && KEY_DP('D'))		keyboardRot = camRot.y + XM_PIDIV4;
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

	if (Rot().y < -3.14)			Rot().y += XM_2PI;
	if (Rot().y > 3.14)				Rot().y -= XM_2PI;

	GetRadBtwTrgt();
	GetRadBtwEnemy();
	if(target != nullptr)
		lengToTrgt = (target->GlobalPos() - realPos->Pos()).Length();
	if(enemy != nullptr)
		lengToEnemy = (enemy->GlobalPos() - realPos->Pos()).Length();
	realPos->Pos() = GetTranslationByNode(1);
	realPos->Rot() = Rot();
	realPos->UpdateWorld();

	waist->SetWorld(GetTransformByNode(waistNode));	
	bowGun->UpdateWorld();
}

void Sample::Control()
{
	switch (curState)
	{
	case Sample::IDLE:		Idle_R();	break;
	case Sample::G_0040:	G0040_R();	break;
	case Sample::G_0084:	G0084_R();	break;
	}
}

void Sample::Follow()
{


	switch (curState)
	{
	case Sample::IDLE:		Idle_F(); 	break;
	case Sample::WALK:		Walk_F(); 	break;
	case Sample::G_0022:	G0022_F();	break;
	case Sample::G_0040:	G0040_F();	break;
	case Sample::G_0084:	G0084_F();	break;
	case Sample::G_0126:	G0126_F();	break;
	case Sample::G_0127:	G0127_F();	break;
	}
}

void Sample::Battle()
{
	switch (curState)
	{
	case Sample::BATTLEIDLE:	Idle_B();		break;
	case Sample::G_0040:		G0040_B();		break;
	case Sample::G_0084:		G0084_B();		break;
	case Sample::FIRE:			Fire_B();		break;
	case Sample::FWDSTEP:		FwdStep_B();	break;
	case Sample::BACKSTEP:		BackStep_B();	break;
	case Sample::TURNLEFT:		TurnLeft_B();	break;
	case Sample::TURNBACK:		TurnBack_B();	break;
	}
}

void Sample::ResetPlayTime()
{
	if (preState != curState)
		GetClip(preState)->ResetPlayTime();
}

void Sample::GroundCheck()
{
	if (terrain == nullptr)
	{
		if (realPos->Pos().y < 0)
			Pos().y = 0;
		return;
	}


	Vector3 pos1;
	terrain->ComputePicking(pos1, realPos->Pos() + Vector3::Up() * 400, Vector3::Down());


	Pos().y = pos1.y;

}

void Sample::Rotate(float rotateSpeed)
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

void Sample::LimitRotate(float limit)
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
			sumRot += 5 * DELTA;
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

void Sample::RealRotate(float rad)
{
	Rot().y += rad;
	Pos().x = ((Pos().x - realPos->Pos().x) * cos(-rad) - (Pos().z - realPos->Pos().z) * sin(-rad)) + realPos->Pos().x;
	Pos().z = ((Pos().x - realPos->Pos().x) * sin(-rad) + (Pos().z - realPos->Pos().z) * cos(-rad)) + realPos->Pos().z;

}

void Sample::SetRad()
{
	if (radBtwEnemy > -rot135 && radBtwEnemy <= -rot45) // 왼쪽 90도
	{
		radDifference = radBtwEnemy + XM_PIDIV2;
	}
	else if (radBtwEnemy > -XM_PI && radBtwEnemy <= -rot135) // 왼뒤쪽 45도
	{
		radDifference = radBtwEnemy + XM_PI;
	}
	else if (radBtwEnemy > rot45 && radBtwEnemy <= rot135) // 오른쪽 90도
	{
		radDifference = radBtwEnemy - XM_PIDIV2;
		Scale().x *= -1;
	}
	else if (radBtwEnemy > rot135 && radBtwEnemy <= XM_PI) // 오른뒤쪽 45도
	{
		radDifference = radBtwEnemy - XM_PI;
		Scale().x *= -1;
	}
	initialRad = Rot().y;
}

void Sample::RotateToEnemy(float ratio1, float ratio2)
{
	float curRatio = RATIO;
	curRatio = Clamp(ratio1, ratio2, curRatio);

	float rad = ((curRatio - ratio1) / (ratio2 - ratio1)) * radDifference;

	Rot().y = initialRad + rad;
}

void Sample::LimitRotateToEnemy(float ratio1, float ratio2, float limit)
{
	float curRatio = RATIO;
	curRatio = Clamp(ratio1, ratio2, curRatio);

	float rad = ((curRatio - ratio1) / (ratio2 - ratio1)) * radBtwEnemy;
	sumRot += rad;
	if (abs(sumRot) < unitRad * limit)
	{
		RealRotate(rad);
	}
}

float Sample::GetRadBtwTrgt()
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

float Sample::GetRadBtwEnemy()
{
	UpdateWorld();
	Vector3 fwd = Forward();
	Vector3 VtoP = (realPos->Pos() - enemy->GlobalPos()).GetNormalized();
	Vector3 rad = XMVector3AngleBetweenVectors(fwd, VtoP);
	Vector3 cross = Cross(fwd, VtoP);
	radBtwEnemy = rad.x;
	if (Cross(fwd, VtoP).y < 0)
		radBtwEnemy *= -1;

	return radBtwEnemy;
}

void Sample::Idle_R()
{
	PLAY;

	if (K_MOVE)
		SetState(G_0040);
}

void Sample::Walk_F()
{
	PLAY;


	//RealRotate();

}

void Sample::DigIn()
{
	PLAY;


	if (RATIO > 0.96)
	{
		SetState(DIGOUT);
	}
}

void Sample::DigOut()
{
	PLAY;


	if (RATIO > 0.96)
	{
		SetState(IDLE);
	}
}

void Sample::Idle_B()
{
	// 혹시라도 잘못 배틀 모드에 들어온 경우 일단 팔로우 모드로
	if (enemy == nullptr)
		SetFollow();

	PLAY;

	if (RATIO > 0.5)
	{
		if (abs(radBtwEnemy) > rot45)
		{
			if (abs(radBtwEnemy) > rot135)
				SetState(TURNBACK);
			else
				SetState(TURNLEFT);
		}
	}

	//공격 가능한 범위라면
	if (RATIO >= 0.96)
	{
		if (lengToEnemy < 700)			SetState(BACKSTEP);
		else if (lengToEnemy < 1400)	SetState(FIRE);
		else if (lengToEnemy > 1900)	SetState(G_0040);
		else							SetState(FWDSTEP);
	}
}

void Sample::G0040_B()
{
	PLAY;

	if (radBtwEnemy < -unitRad)
		RealRotate(-2.5 * DELTA);
	else if (radBtwEnemy > unitRad)
		RealRotate(2.5 * DELTA);

	if (lengToEnemy < 700)
		SetState(G_0084);


	if (RATIO > 0.96)
		Loop();
}

void Sample::G0084_B()
{
	PLAY;


	if (RATIO > 0.96)
	{
		if (lengToEnemy < 700)			SetState(BACKSTEP);
		else if (lengToEnemy < 1400)	SetState(FIRE);
		else if (lengToEnemy > 1900)	SetState(G_0040);
		else							SetState(FWDSTEP);
	}
}

void Sample::Fire_B()
{
	PLAY;

	if (RATIO < 0.25)
	{
		LimitRotateToEnemy(0, 0.3, 45);
		fireParticle->Play({ Pos().x,Pos().y + 150,Pos().z }, Back() * 300);
	}

	if (RATIO > 0.291f)
	{
		if (!playOncePerMotion)
		{
			KunaiManager::Get()->Throw(bowGun->GlobalPos(), ((enemy->GlobalPos() + Vector3::Up() * 200) - bowGun->GlobalPos()).GetNormalized());
			playOncePerMotion = true;
		}
	}

	if (RATIO > 0.96)
	{
		playOncePerMotion = false;
		if (lengToEnemy < 700)			SetState(BACKSTEP);
		else if (lengToEnemy < 1400)	Loop();
		else if (lengToEnemy > 1900)	SetState(G_0040);
		else							SetState(FWDSTEP);
	}
}

void Sample::FwdStep_B()
{
	PLAY;

	if (RATIO > 0.093 && RATIO < 0.73)
		LimitRotateToEnemy(0.093, 0.8, 90);

	if (RATIO > 0.96)
	{
		if (lengToEnemy < 700)			SetState(BACKSTEP);
		else if (lengToEnemy < 1400)	SetState(FIRE);
		else if (lengToEnemy > 1900)	SetState(G_0040);
		else							Loop();
	}
}

void Sample::BackStep_B()
{
	PLAY;

	if (RATIO > 0.093 && RATIO < 0.73)
		LimitRotateToEnemy(0.093, 0.8, 90);

	if (RATIO > 0.96)
	{
		if (lengToEnemy < 700)			Loop();
		else if (lengToEnemy < 1400)	SetState(FIRE);
		else if (lengToEnemy > 1900)	SetState(G_0040);
		else							SetState(FWDSTEP);
	}
}

void Sample::TurnLeft_B()
{
	PLAY;

	if (!playOncePerMotion)
	{
		SetRad();
		playOncePerMotion = true;
	}

	if (RATIO > 0.19 && RATIO < 0.65)
		RotateToEnemy(0.19, 0.7);

	if (RATIO > 0.96)
	{
		if (lengToEnemy < 700)			SetState(BACKSTEP);
		else if (lengToEnemy < 1400)	SetState(FIRE);
		else if (lengToEnemy > 1900)	SetState(G_0040);
		else							SetState(FWDSTEP);
	}
}

void Sample::TurnBack_B()
{
	PLAY;

	if (!playOncePerMotion)
	{
		SetRad();
		playOncePerMotion = true;
	}

	if (RATIO > 0.19 && RATIO < 0.65)
		RotateToEnemy(0.19, 0.7);

	if (RATIO > 0.96)
	{
		if (lengToEnemy < 700)			SetState(BACKSTEP);
		else if (lengToEnemy < 1400)		SetState(FIRE);
		else if (lengToEnemy > 1900)	SetState(G_0040);
		else							SetState(FWDSTEP);
	}
}

void Sample::G0040_R() // 달리기 루프
{

	PLAY;

	Rotate();

	if (!K_MOVE && RATIO < 0.96)
		SetState(G_0084);


	if (RATIO > 0.96)
	{
		Loop();
	}
}

void Sample::G0084_R()
{
	PLAY;

	if (K_MOVE && RATIO > 0.4 && RATIO < 0.95)
		SetState(G_0040);

	if (RATIO > 0.96)
	{
		SetState(IDLE);
	}
}

void Sample::Idle_F()
{
	PLAY;

	if (isCallDog)
		SetState(G_0040);

	if (lengToTrgt > 200)
	{
		SetState(G_0022);
	}

	if (RATIO > 0.96)
		Loop();
}

void Sample::G0022_F()
{
	PLAY;

	// 1. 거리가 더 멀어져서 달려야 함
	// 2. 거리가 충분히 가까워져서 걸어도 됨

	if (radBtwTarget < 0)
		RealRotate(-2 * DELTA);
	else
		RealRotate(2 * DELTA);

	if (isCallDog)
		SetState(G_0040);

	if (lengToTrgt > 700)
	{
		SetState(G_0040);
	}
	else if (lengToTrgt < 150)
	{
		SetState(IDLE);
	}

	if (RATIO > 0.96)
		Loop();
}

void Sample::G0040_F()
{
	PLAY;

	// 1. 거리가 더 멀어져서 달려야 함

	if (radBtwTarget < -1)
		RealRotate(-3 * DELTA);
	else if(radBtwTarget > 1)
		RealRotate(3 * DELTA);

	if (!isCallDog)
	{
		if (lengToTrgt < 400)
		{
			SetState(G_0022);
		}
	}

	if (isCallDog)
	{
		if (lengToTrgt < 70)
			readyToRide = true;
	}


	if (RATIO > 0.96)
		Loop();
}

void Sample::G0084_F()
{
	PLAY;

	if (RATIO > 0.96)
		SetState(IDLE);
}

void Sample::G0126_F()
{
	PLAY;

	if (RATIO > 0.96)
		SetState(IDLE);
}

void Sample::G0127_F()
{
	PLAY;

	if (RATIO > 0.96)
		SetState(IDLE);
}


void Sample::SetState(State state)
{
	if (curState == state)
		return;

	Scale().x = 1;

	isSetState = true;
	isLoop = false;
	sumRot = 0.0f;
	preState = curState;
	curState = state;
	playOncePerMotion = false;
}
