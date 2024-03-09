#pragma once
class Sample : public ModelAnimator
{
private:
	enum State
	{
		IDLE, WALK, DIGIN, DIGOUT, G_0022,
		G_0040, G_0084, G_0126, G_0127
	};

	enum Mode
	{
		RIDING,
		FOLLOWING,
		FIGHTING
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
	void SetFight() { mode = FIGHTING; }
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

	void Rotate(float rotateSpeed = 2.5f);   // ������ �� �޸��� �������
	void LimitRotate(float limit);   // ���ݸ��  15 , 180
	void RealRotate(float rad);

	float GetRadBtwTrgt();

	// Riding
	void Idle_R(); // G_0001
	void G0040_R(); // �ٱ� ����
	void G0084_R(); // �ٴٰ� ����

	// Follow
	void Idle_F(); // G_0001
	void Walk_F(); // G_0010
	void G0022_F(); // �ȱ� ����
	void G0040_F(); // �ٱ� ����
	void G0084_F(); // �ٴٰ� ����
	void G0126_F(); // �������� �� ����
	void G0127_F(); // ���������� �� ����

	void DigIn(); // motlist 01 �� �ʹݺ�
	void DigOut();// motlist 01 �� �ʹݺ�




	void Loop() { GetClip(curState)->ResetPlayTime(); isLoop = true; }

	void SetState(State state);



private:
	State curState = IDLE;
	State preState = IDLE;
	Mode mode = FOLLOWING;

	Transform* realPos = nullptr;
	Transform* camTrgt = nullptr;
	Transform* target;
	TerrainEditor* terrain;

private:

	bool isRiding = false;
	bool isFighting = false;
	bool playOncePerMotion = false;
	const float unitRad = 0.01744444f;

	const float rot135 = 2.36f;
	const float rot45 = 0.785f;
	float keyboardRot = 0.0f;
	float sumRot = 0.0f;
	float initRotY = 0.0f;
	float lengToTrgt = 0.0f;
	bool isSetState = false;
	bool  isLoop = false;

	float radBtwTarget = 0.0f;
	float radDifference = 0.0f;
};