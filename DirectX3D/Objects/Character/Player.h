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
		L_110, 

		L_113, L_114, L_115, L_116, L_119, L_122,
		L_128, L_130, L_131, L_132, L_133, 
		L_134, L_135, L_136, L_137, L_138,	

		L_147, L_151, L_152, L_153, L_154,
		L_155, L_156,
		S_001, S_003, S_005, S_008, S_009,
		S_014, S_017, S_018, S_026, S_029,
		S_038, S_118, S_119, S_120
	};

	enum Rotation
	{
		��, �ϵ�, ��, ����, ��, ����, ��, �ϼ�
	};

	struct Damage
	{
		Vector3 pos = {};
		int damage = 0;
		int hitPart = 9;
		bool isWeakness = false;
		float timer = 0.0f;
	};


public:
	Player();
	~Player();


	void Update();
	void PreRender();
	void Render();
	void GUIRender();
	void PostRender();

	CapsuleCollider* getCollider() { return tmpCollider; }

private:
	void Control();
	void Move();
	void ResetPlayTime();

	void UpdateWorlds();
	void Potion();

	void Rotate();
	bool Attack(float power, bool push = true, UINT useOtherCollider = 0); // TODO : ������ ��� �־����
	void AttackWOCollision(float power = 0); // �浹�˻縦 ���ϴ� ����
	bool CollisionCheck();
	void SetAnimation();
	void Roll();
	void TermAttackUpdate();

	void SetState(State state);	
	void EndEffect();

	void SetIdle() { SetState((State)1); }

	void MotionRotate(float degree);

	bool State_S();

	void StatusRender();
	void DamageRender();

	bool Jump(float moveSpeed);
	void GroundCheck();

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
	void Loop() {GetClip(curState)->ResetPlayTime();}

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
	void L014();

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

	void L113();
	void L114();
	void L115();
	void L116();
	void L119();
	void L122();
	void L128();
	void L130();
	void L131();
	void L132();
	void L133();
	void L134();
	void L135();
	void L136();
	void L137();
	void L138();

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

	CapsuleCollider* tmpCollider = nullptr;
	CapsuleCollider* tmpCollider2 = nullptr;
	CapsuleCollider* tmpCollider3 = nullptr;
	CapsuleCollider* swordCollider = nullptr;

	Model* longSword = nullptr;
	Model* kalzip = nullptr;

	Shadow* shadow;
	LightBuffer::Light* light;
	Trail* trail;
	vector<HitParticle*> hitParticle;
	UINT lastParticleIndex = 0;
	UINT lastHitPart = 0;
	Vector3 lastSwordDir;

	State curState = L_101;
	State preState = L_101;

	float moveSpeed = 4000 * DELTA;
	float rotSpeed = 5.0f;
	float deceleration = 5;

	const float motionSpeed = 1.5f;

	Vector3 velocity = Vector3::Zero();
	Vector3 targetPos = Vector3::Zero();
	Vector3 prevMousePos = Vector3();
	Vector3 prevPos = Vector3();

	bool isTarget = true;
	bool isHitL155 = false;
	bool isHitL133 = false;
	bool isHitL136 = false;
	float TermAttackTimer = 0.0f;
	float TermAttackTimer2 = 0.0f;
	float TermAttackTimer3 = 0.0f;

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

	const float temp = -2.364f;  // �ؽ�Ʈ ���� �� ��ġ
	const float temp2 = -6.038f; // �ؽ�Ʈ ���� �� ��ġ
	const float temp3 = 14.067f; // �ؽ�Ʈ ���� �� ��ġ

	float jumpVelocity = 2.8f;
	const float originJumpVelocity = jumpVelocity;
	float gravityMult = 0.6f;

	int loopApply = 334;

	float time = 0;

	bool cure = false;
	bool Lcure = false;

	bool attackOnlyOncePerMotion = false;
	bool isDoubleStrikeMotion = false;
	bool playOncePerMotion = false;
	bool playOncePerTerm = false;
	bool playOncePerTerm2 = false;

	bool renderEffect = false;
	bool holdingSword = false;

	Vector3 initForward = Vector3::Zero();

	vector<Damage> damages;
};

