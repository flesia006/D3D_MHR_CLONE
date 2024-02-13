#pragma once

class Particle;
class Trail;
class Player : public ModelAnimator
{
private:
	enum State
	{
		L_001, L_002, L_003, L_004, L_005,
		L_006, L_007, L_008, L_009, L_010,
		L_011, L_012, L_013, L_014, L_015,
		L_071, L_072, L_073, L_077, L_078,
		L_079, L_101, L_102, L_103, L_104,
		L_105, L_106, L_107, L_108, L_109,
		L_110, L_111, L_112, L_113, L_114,
		L_115, /*L_116, L_117, L_118, L_119,
		L_120, L_121, L_122, L_123,*/ 
		L_147, L_151, L_152, L_153, L_154,
		L_155, L_156,


		S_001, S_003, S_005, S_008, S_009,
		S_014, S_017, S_018, S_026, S_029,
		S_038, S_118, S_119, S_120
	};

	enum Rotation
	{
		북, 북동, 동, 남동, 남, 남서, 서, 북서
	};


public:
	Player();
	~Player();


	void Update();
	void PreRender();
	void Render();
	void GUIRender();
	void PostRender();


	SphereCollider* getCollider() { return tmpCollider; }

private:
	void Control();
	void Move();
	void ResetPlayTime();

	void UpdateWorlds();
	void Potion();

	void Rotate();
	void Attack(float power = 0); // TODO : 데미지 계산 넣어야함
	void SetAnimation();
	void Roll();

	void SetState(State state);	
	void EndEffect();

	void SetIdle() { SetState((State)1); }

	void MotionRotate(float degree);

	bool State_S();

private:
	void ReadClips();
	void RecordLastPos();
	void ReturnIdle()
	{
		GetClip(L_001)->ResetPlayTime();
		SetState(L_001);

	}
	void ReturnIdle2()
	{
		GetClip(S_001)->ResetPlayTime();
		SetState(S_001);
	}
	void S001();
	void S003();
	void S005();
	void S008();
	void S009();
	void S014();
	void S017();
	void S018();
	void S026();
	void S029();
	void S038();
	void S118();
	void S119();
	void S120();


	void L001();
	void L002();
	void L003();
	void L004();
	void L005();
	void L006();
	void L007();
	void L008();
	void L009();
	void L010();

	void L101();
	void L102();
	void L103();
	void L104();
	void L105();
	void L106();
	void L107();
	void L108();
	void L109();
	void L110();


	void L147();
	void L151();
	void L152();
	void L153();
	void L154();
	void L155();
	void L156();


	void LRunning();
private:
	Transform* mainHand = nullptr;
	Transform* backSwd = nullptr;

	Transform* realPos = nullptr;
	Transform* backPos = nullptr;
	Transform* forwardPos = nullptr;

	Transform* head = nullptr;

	Transform* swordStart = nullptr;
	Transform* swordEnd = nullptr;
	
	Vector3 lastSwordEnd = {0, 0, 0};
	Vector3 swordSwingDir;

	SphereCollider* tmpCollider = nullptr;
	SphereCollider* tmpCollider2 = nullptr;
	SphereCollider* tmpCollider3 = nullptr;
	CapsuleCollider* swordCollider = nullptr;

	Model* longSword = nullptr;
	Model* kalzip = nullptr;

	Shadow* shadow;
	LightBuffer::Light* light;
	Trail* trail;
	HitParticle* hitParticle;

	State curState = L_101;
	State preState = L_101;

	float moveSpeed = 400;
	float rotSpeed = 10.0f;
	float deceleration = 5;

	const float motionSpeed = 1.5f;

	Vector3 velocity = Vector3::Zero();
	Vector3 targetPos = Vector3::Zero();
	Vector3 prevMousePos = Vector3();
	Vector3 prevPos = Vector3();
	


	bool isTarget = true;

	POINT clientCenterPos = { WIN_WIDTH / 2, WIN_HEIGHT >> 1 };

	Quad* crosshair = nullptr;

	int kunaiIndex = 0;
	int node = 197;

	const int lefeHandNode = 108;
	const int rightHandNode = 150;
	const int backSwdNode = 190;

	float rotation = -1.5;
	float camRot;
	float rad;
	float effectTimer = 0.0f;
	float L152Timer = 0.0f;
	int temp = 175;

	int loopApply = 334;

	float time = 0;

	bool cure = false;
	bool Lcure = false;

	bool attackOnlyOncePerMotion = false;
	bool renderEffect = false;
	bool holdingSword = false;

	Vector3 initForward = Vector3::Zero();

};

