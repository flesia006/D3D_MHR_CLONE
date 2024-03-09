#pragma once

class Particle;
class Trail;
class Valphalk;
class WireBug;
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
		S_001, S_003, S_005, S_008, S_009, S_011,
		S_014, S_017, S_018, S_019, S_020, S_026, S_029,
		S_038, S_118, S_119, S_120, S_122,

		// 발도 피격모션
		L_400, L_403, L_451, L_453, L_455,
		// 납도 피격모션
		D_001, D_004, D_007, D_011, D_015,
		D_016, D_021, D_022, D_026, D_029,
		D_030, D_031, D_032, D_033, D_045,
		D_046, D_066, D_078, D_079, D_080
	};

	enum Rotation
	{
		북, 북동, 동, 남동, 남, 남서, 서, 북서
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
	CapsuleCollider* getSwordCollider() { return swordCollider; }
	Transform* GetRealPos() { return realPos; }

	void SetValphalk(Valphalk* val) { this->val = val; }
	void SetWireBug(WireBug* wireBug) { this->wireBug = wireBug; }

private:
	void Control();
	void Move();
	void ResetPlayTime();

	void UpdateWorlds();
	void Potion();

	void Rotate(float rotateSpeed = 5.0f);   // 앞으로 쭉 달리는 루프모션
	void LimitRotate(float limit);   // 공격모션  15 , 180
	void RealRotate(float rad);

	bool Attack(float power, bool push = true, UINT useOtherCollider = 0); // TODO : 데미지 계산 넣어야함
	bool AttackDummy(float power, bool push = true, UINT useOtherCollider = 0); // TODO : 데미지 계산 넣어야함
	void AttackWOCollision(float power = 0); // 충돌검사를 안하는 공격

	void HurtCheck();
	void EvadeCheck();

	bool CollisionCheck();
	void SetAnimation();
	void Roll();
	void TermAttackUpdate();

	bool DeathCheck();

	void SetState(State state);	
	void EndEffect();

	void SetIdle() { SetState((State)1); }

	void MotionRotate(float degree);

	bool State_S();

	void StatusRender();
	void DamageRender();

	bool Jump(float moveSpeed);
	void GroundCheck();

	void GetWireBug();

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
	void S011();
	void S014();
	void S017();
	void S018();
	void S019();
	void S020();
	void S026();
	void S029();
	void S038();
	void S118();
	void S119();
	void S120();
	void S122();


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

	void L400();
	void L403();
	void L451();
	void L453();
	void L455();

	void D001();
	void D004();
	void D007();
	void D011();
	void D015();
	void D016();
	void D021();
	void D022();
	void D026();
	void D029();
	void D030();
	void D031();
	void D032();
	void D033();
	void D045();
	void D046();
	void D066();
	void D078();
	void D079();
	void D080();

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

	CapsuleCollider* bodyCollider = nullptr;
	CapsuleCollider* evadeCheckCollider = nullptr;

	Model* longSword = nullptr;
	Model* kalzip = nullptr;

	Shadow* shadow;
	LightBuffer::Light* light;
	Trail* trail;
	UINT lastParticleIndex = 0;
	UINT lastHitPart = 0;
	Vector3 lastSwordDir;

	State curState = L_101;
	State preState = L_101;

	float moveSpeed = 4000 * DELTA;
	float rotSpeed = 5.0f;
	float deceleration = 5;
	float keyboardRot = 0.0f;

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

	const float temp = -2.364f;  // 텍스트 띄우기 용 수치
	const float temp2 = -6.038f; // 텍스트 띄우기 용 수치
	const float temp3 = 14.067f; // 텍스트 띄우기 용 수치
	float temp4 = -580.0f;

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
	float initRotY = 0.0f;
	float sumRot = 0.0f;
	const float unitRad = 0.01744444f;

	bool isSetState = false;

	vector<Damage> damages;

	bool isEvaded = false; // 회피했는지 여부

	Valphalk* val = nullptr;
	
	WireBug* wireBug = nullptr;

	///////////////////////////////////////////
	// Particle
	vector<HitParticle*> hitParticle;
	HitBoomParticle* hitBoomParticle;
	CriticalParticle* criticalParticle;
	Sp_atk_ready_Particle* spAtkParticle;
	PotionParticle* potionParticle;

	Transform* haloTransform = nullptr;
	CapsuleCollider* haloCollider = nullptr;

};

