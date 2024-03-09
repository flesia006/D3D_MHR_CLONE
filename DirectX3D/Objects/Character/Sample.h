#pragma once
class Sample : public ModelAnimator
{
private:
	enum State
	{
		IDLE, WALK, DIGIN, DIGOUT, G_0022,
		G_0040, G_0084, G_0126, G_0127, 
		FIRE, BACKSTEP, FWDSTEP, TURNLEFT, TURNBACk,
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
	void GUIRender();

	void SetTarget(Transform* target) { this->target = target; }
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
	void SetFight() { mode = BATTLE; }
	void SetTerrain(TerrainEditor* terrain) { this->terrain = terrain; }

	bool isCallDog = false;
	bool readyToRide = false;
private:
	void UpdateWorlds();
	void Control();
	void Follow();
	void Fight();
	void ResetPlayTime();
	void GroundCheck();

	void Rotate(float rotateSpeed = 2.5f);   // ¾ÕÀ¸·Î Âß ´Þ¸®´Â ·çÇÁ¸ð¼Ç
	void LimitRotate(float limit);   // °ø°Ý¸ð¼Ç  15 , 180
	void RealRotate(float rad);

	float GetRadBtwTrgt();

	// Riding
	void Idle_R(); // G_0001
	void G0040_R(); // ¶Ù±â ½ÃÀÛ
	void G0084_R(); // ¶Ù´Ù°¡ ¸ØÃã

	// Follow
	void Idle_F(); // G_0001
	void Walk_F(); // G_0010
	void G0022_F(); // °È±â ·çÇÁ
	void G0040_F(); // ¶Ù±â ½ÃÀÛ
	void G0084_F(); // ¶Ù´Ù°¡ ¸ØÃã
	void G0126_F(); // ¿ÞÂÊÀ¸·Î ¸ö µ¹·Á
	void G0127_F(); // ¿À¸¥ÂÊÀ¸·Î ¸ö µ¹·Á

	void DigIn(); // motlist 01 ÀÇ ÃÊ¹ÝºÎ
	void DigOut();// motlist 01 ÀÇ ÃÊ¹ÝºÎ

	// Battle
	void G0040_B();
	void G0084_B();
	void Fire_B();
	void FwdStep_B();
	void BackStep_B();



	void Loop() { GetClip(curState)->ResetPlayTime(); isLoop = true; }
	void SetState(State state);



private:
	State curState = IDLE;
	State preState = IDLE;
	Mode mode = FOLLOWING;

	Transform* realPos = nullptr;
	Transform* camTrgt = nullptr;
	Transform* target;
	Transform* enemy;

	TerrainEditor*  terrain;

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
	float lengToTrgt = 0.0f;
	float radBtwTarget = 0.0f;
	float radDifference = 0.0f;
};