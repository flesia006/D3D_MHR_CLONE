#pragma once

class Particle;
class Trail;
class Sample;
class Valphalk;
class DummyValphalk;
class WireBug;
class PlayerWireBug;
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

		L_113, L_114, L_115, L_116, L_119, L_122, L_126, L_127,
		L_128, L_130, L_131, L_132, L_133,
		L_134, L_135, L_136, L_137, L_138,

		L_147, L_151, L_152, L_153, L_154,
		L_155, L_156,
		S_001, S_003, S_005, S_008, S_009, S_011,
		S_014, S_017, S_018, S_019, S_020, S_026, S_029,
		S_038, S_118, S_119, S_120, S_122,

		// 가루크 모션들
		R_001, R_013, R_024, R_031, R_041, R_104,
		R_142, R_143, R_144, R_400, R_401, R_402,
		R_600, R_601, R_602,

		// 발도 피격모션
		L_400, L_403, L_451, L_453, L_455,
		// 납도 피격모션
		D_001, D_004, D_007, D_011, D_015,
		D_016, D_021, D_022, D_026, D_029,
		D_030, D_031, D_032, D_033, D_045,
		D_046, D_066, D_078, D_079, D_080,

		// 납도 밧줄벌레 액션
		W_005, W_006, W_007, W_009, W_010,
		W_020, W_062, W_063, F_072, F_073,

		// 맵 입장, 도착 및 갈무리 모션
		T_019, T_020, T_050, T_051, T_052,

		// 시작 모션(팔짱)
		E_092
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
	void SetGaruk(Transform* Garuk) { garuk = Garuk; }
	void SetDog(Sample* dog) { this->dog = dog; }
	void SetTerrain(TerrainEditor* terrain) { this->terrain = terrain; }

	CapsuleCollider* getCollider() { return tmpCollider; }
	CapsuleCollider* getSwordCollider() { return swordCollider; }
	Transform* GetRealPos() { return realPos; }

	void SetValphalk(Valphalk* val) { this->val = val; }
	void SetValphalk(DummyValphalk* val) { this->dumVal = val; }
	void SetWireBug(WireBug* wireBug) { this->wireBug = wireBug; }
	bool GetInBattleMap() { return inBattleMap; }

private:
	void Control();
	void Move();
	void ReadyRide(); // 가루크 답승 대기
	void Ride();
	void EndRide();
	void ResetPlayTime();
	void EffectUpdates();

	void UpdateWorlds();
	void Potion();
	void SharpeningStone();
	void UseBlueBox();

	void Rotate(float rotateSpeed = 5.0f);   // 앞으로 쭉 달리는 루프모션
	void LimitRotate(float limit, float rotSpeed = 5.0f);   // 공격모션  15 , 180
	void RealRotate(float rad);

	bool Attack(float power, bool push = true, UINT useOtherCollider = 0); // TODO : 데미지 계산 넣어야함
	bool AttackDummy(float power, bool push = true, UINT useOtherCollider = 0); // TODO : 데미지 계산 넣어야함
	void AttackWOCollision(float power = 0); // 충돌검사를 안하는 공격

	void HurtCheck();
	void EvadeCheck();

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

	bool Jump(float moveSpeed, float jumpSpeed = 0.6f);
	void GroundCheck();

	void RandVoice();
	void RandSpecialVoice();
	void RandHurtVoice();
	void RandBreath();
	void GetWireBug();
	void RandHitSounds();

	void Capture();
	void UpdateCaptureUI();

	void NearMapChangeArea();

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
	void Loop() { GetClip(curState)->ResetPlayTime(); }

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

	void L126();
	void L127();

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


	void R001();
	void R013();
	void R024();
	void R031();
	void R041();
	void R104();
	void R142();
	void R143();
	void R144();
	void R400();
	void R401();
	void R402();
	void R600();
	void R601();
	void R602();

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

	void W005();
	void W006();
	void W007();
	void W009();
	void W010();
	void W020();
	void W062();
	void W063();
	void F072();
	void F073();

	void T019();
	void T020();
	void T050();
	void T051();
	void T052();

	void E092();

private:
	Transform* mainHand = nullptr;
	Transform* backSwd = nullptr;

	Transform* realPos = nullptr;
	Transform* backPos = nullptr;
	Transform* forwardPos = nullptr;

	Transform* head = nullptr;
	Transform* center = nullptr;

	Transform* swordStart = nullptr;
	Transform* swordEnd = nullptr;

	Transform* garuk;

	Transform* playerWireBugHead = nullptr;
	Transform* playerWireBugTail = nullptr;

	Vector3 lastSwordEnd = { 0, 0, 0 };
	Vector3 swordSwingDir;

	CapsuleCollider* tmpCollider = nullptr;
	CapsuleCollider* tmpCollider2 = nullptr;
	CapsuleCollider* tmpCollider3 = nullptr;
	CapsuleCollider* swordCollider = nullptr;

	CapsuleCollider* bodyCollider = nullptr;
	CapsuleCollider* evadeCheckCollider = nullptr;

	Sample* dog = nullptr;
	TerrainEditor* terrain = nullptr;
	Valphalk* val = nullptr;
	DummyValphalk* dumVal = nullptr;

	Model* longSword = nullptr;
	Model* kalzip = nullptr;

	Shadow* shadow;
	LightBuffer::Light* light;
	Trail* trail;
	Trail* wireBugTrail;
	UINT lastParticleIndex = 0;
	UINT lastHitPart = 0;
	Vector3 lastSwordDir;

	State curState = E_092;
	State preState = E_092;

	float moveSpeed = 4000 * DELTA;
	float rotSpeed = 5.0f;
	float deceleration = 5;
	float keyboardRot = 0.0f;

	const float motionSpeed = 1.5f;

	Vector3 velocity = Vector3::Zero();
	float height = 0.0f;
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

	const int leftHandNode = 108;
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

	float jumpVelocity = 9.0f;
	const float originJumpVelocity = jumpVelocity;
	float gravityMult = 0.6f;

	int loopApply = 334;

	float time = 0;

	bool cure = false;
	bool Lcure = false;

	bool attackOnlyOncePerMotion = false;
	bool isDoubleStrikeMotion = false;
	bool playOncePerMotion = false;
	bool playOncePerMotion2 = false;
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
	bool isRiding = false;
	bool callGaruk = false;
	bool rideCAM = false;
	bool isJump = false;
	bool isInitVoice = false;

	WireBug* wireBug = nullptr; // 필드에서 주울 밧줄벌레
	PlayerWireBug* playerWireBug; // 밧줄벌레 기술 사용시 나오는 벌레

	int randVoice = 0;
	float breathCount = 0;

	Vector3 wireBugDir = Vector3::Zero();

	Quad* captureUI;
	Vector3 UIPos;
	bool isCaptureUIActive = false;
	bool isCaptured = false;
	bool soundOncePerUI = false;

	Quad* mapChangeUI;
	Vector3 UIPos2;
	bool isMapChangeUIActive = false;
	bool soundOncePerUI2 = false;
	bool mapChanged = false;
	bool inBattleMap = false;
	bool isFirstRender = false;
	///////////////////////////////////////////
	// Particle
	vector<HitParticle*> hitParticle;
	HitBoomParticle* hitBoomParticle;
	CriticalParticle* criticalParticle;
	Sp_atk_ready_Particle* spAtkParticle;
	Sp_atk_start* spStartParticle;
	Sp_atk_success* spSuccessParticle;
	PotionParticle* potionParticle;
	SpiritFlame* spiritParticle;
	Wire_Bug* wireBugParticle;
	Sutdol* sutdol;
	Transform* haloTransform = nullptr;
	CapsuleCollider* haloCollider = nullptr;
	Suwol* suwol = nullptr;
	vector<CircleEft*> circle;
	SliceEft* slice = nullptr;
	headBreakAtk* tuguAtk = nullptr;
	UseBug* usebug;
	bool isbugeffect = false;
	float bugtime = 0;
};

