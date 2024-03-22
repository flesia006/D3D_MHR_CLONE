#pragma once

class Sample : public ModelAnimator
{
private:
	enum State
	{
		IDLE, WALK, DIGIN, DIGOUT, G_0022,
		G_0040, G_0084, G_0126, G_0127,
		BATTLEIDLE, FIRE, BACKSTEP, FWDSTEP, TURNLEFT, TURNBACK,
	};

	enum Mode
	{
		RIDING,
		FOLLOWING,
		BATTLE
	};

public:
	Sample();
	~Sample();

	void Update();

	void Render();
	void PostRender();
	void GUIRender();

	void SetTarget(Transform* target) { this->target = target; }
	void SetEnemy(Valphalk* target);

	Transform* GetRealPos() { return realPos; }
	void SetRotPos(Vector3 rot, Vector3 pos)
	{
		SetState(G_0040);
		Pos().x = pos.x;
		Pos().z = pos.z;
		Rot() = rot;
	}

	void SetRide() { mode = RIDING; }
	void SetFollow() { mode = FOLLOWING; SetState(G_0084); }
	void SetFight() { mode = BATTLE; SetState(BATTLEIDLE); }
	void SetTerrain(TerrainEditor* terrain) { this->terrain = terrain; }

	bool isCallDog = false;
	bool readyToRide = false;
private:
	void UpdateWorlds();
	void Control();
	void Follow();
	void Battle();
	void ResetPlayTime();
	void GroundCheck();

	void Rotate(float rotateSpeed = 2.5f);   // æ’¿∏∑Œ ¬ﬂ ¥ﬁ∏Æ¥¬ ∑Á«¡∏º«
	void LimitRotate(float limit);   // ∞¯∞›∏º«  15 , 180
	void RealRotate(float rad);

	void SetRad();
	void RotateToEnemy(float ratio1, float ratio2); // 
	void LimitRotateToEnemy(float ratio1, float ratio2, float limit); // 

	float GetRadBtwTrgt();
	float GetRadBtwEnemy();

	// Riding
	void Idle_R(); // G_0001
	void G0040_R(); // ∂Ÿ±‚ Ω√¿€
	void G0084_R(); // ∂Ÿ¥Ÿ∞° ∏ÿ√„

	// Follow
	void Idle_F(); // G_0001
	void Walk_F(); // G_0010
	void G0022_F(); // ∞»±‚ ∑Á«¡
	void G0040_F(); // ∂Ÿ±‚ Ω√¿€
	void G0084_F(); // ∂Ÿ¥Ÿ∞° ∏ÿ√„
	void G0126_F(); // øﬁ¬ ¿∏∑Œ ∏ˆ µπ∑¡
	void G0127_F(); // ø¿∏•¬ ¿∏∑Œ ∏ˆ µπ∑¡

	void DigIn(); // motlist 01 ¿« √ π›∫Œ
	void DigOut();// motlist 01 ¿« √ π›∫Œ

	// Battle
	void Idle_B();
	void G0040_B();
	void G0084_B();
	void Fire_B();
	void FwdStep_B();
	void BackStep_B();
	void TurnLeft_B();
	void TurnBack_B();



	void Loop() { GetClip(curState)->ResetPlayTime(); isLoop = true; }
	void SetState(State state);



private:
	State curState = IDLE;
	State preState = IDLE;
	Mode mode = FOLLOWING;

	Transform* realPos = nullptr;
	Transform* camTrgt = nullptr;
	Transform* target;
	Valphalk* enemy;
	Transform* waist;

	Model* bowGun;
	Model* arrow;

	TerrainEditor* terrain;

private:

	bool isRiding = false;
	bool isFighting = false;
	bool playOncePerMotion = false;
	bool isSetState = false;
	bool isLoop = false;

	const float unitRad = 0.01744444f;
	const float rot135 = 2.36f;
	const float rot45 = 0.785f;

	float keyboardRot = 0.0f;
	float sumRot = 0.0f;
	float initRotY = 0.0f;
	float initialRad = 0.0f;   // π∫∞° π∫∞°¿Œµ• µ—¥Ÿ « ø‰«‘..;;
	float lengToTrgt = 0.0f;
	float lengToEnemy = 0.0f;
	float radBtwTarget = 0.0f;
	float radBtwEnemy = 0.0f;
	float radDifference = 0.0f;

	const int waistNode = 3;
	Garuk_Fire* fireParticle;
};