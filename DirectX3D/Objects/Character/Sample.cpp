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

	realPos = new Transform();
}

Sample::~Sample()
{

}

void Sample::Update()
{
	UpdateWorlds();

	switch (mode)
	{
	case Sample::RIDING:		Control();		break;
	case Sample::FOLLOWING:		Follow();		break;
	case Sample::BATTLE:		Fight();		break;
	}


	ModelAnimator::Update();
	ResetPlayTime();
	GroundCheck();
}

void Sample::Render()
{

	ModelAnimator::Render();

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
}

void Sample::GUIRender()
{
	ModelAnimator::GUIRender();
	Vector3 realpos = realPos->Pos();
	Vector3 pos = Pos();

	ImGui::DragFloat3("realPos", (float*)&realpos);
	ImGui::DragFloat3("Pos", (float*)&pos);
	ImGui::DragFloat("lengToTrgt", &lengToTrgt);

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
	lengToTrgt = (target->GlobalPos() - realPos->Pos()).Length();
	realPos->Pos() = GetTranslationByNode(1);
	realPos->Rot() = Rot();
	realPos->UpdateWorld();
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

void Sample::Fight()
{
	switch (curState)
	{
	case Sample::IDLE:		Idle_F(); 	break;
	case Sample::G_0040:	G0040_F();	break;
	case Sample::G_0084:	G0084_F();	break;
	case Sample::G_0126:	G0126_F();	break;
	case Sample::G_0127:	G0127_F();	break;
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

	if (radBtwTarget < 0)
		RealRotate(-2 * DELTA);
	else
		RealRotate(2 * DELTA);

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


	isSetState = true;
	isLoop = false;
	sumRot = 0.0f;
	preState = curState;
	curState = state;
	playOncePerMotion = false;
}
