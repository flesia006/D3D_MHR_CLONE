#pragma once

class Valphalk : public ModelAnimator
{
public:
	enum State
	{
		E_0003, E_0007, E_0043, E_0044, E_0045,
		E_0055, E_0059, E_0060, E_0061, E_0071,
		E_0097, E_0098, E_0099, E_0146,
		E_0147, E_0151, E_0152, E_0153, E_0164,
		E_0165, E_0166, E_0171, E_0172, E_0173,
		E_0178, E_0179, E_0180, E_0186, E_0187, E_0188,
		E_1151, E_1155, E_1163, E_1164,		//습격		
		E_2001, E_2002, E_2003,				// 공격및 피격자세
		E_2013, E_2015, E_2017, E_2019, E_2020, E_2022,
		E_2027, E_2032, E_2033,
		E_2038, E_2040, E_2041, E_2042, E_2044, E_2045,
		E_2054, E_2056, E_2079, E_2082,
		E_2091, E_2092, E_2093, E_2103, // 날개 휘둘
		E_2106, E_2107, E_2108, E_2118, E_2121, E_2124,
		E_2129, E_2130, E_2131, E_2133, E_2134, E_2141,	 // 앞다리 찍으면서 날개 덮기
		E_2144, E_2145, E_2146, E_2145a,
		E_2151, E_2152, E_2153, E_2171,
		E_2173, E_2174, E_2175, E_2185,
		E_2188, E_2189, E_2190, E_2192, E_2193, E_2200, E_2200fix,
		E_2210, E_2211, E_2253, E_2265, E_2267,
		E_2270, E_2271, E_2272, E_2274, E_2275, E_2276, E_2277, E_2278,
		E_2280, E_2281, E_2282, E_2286, E_2288, E_2290,
		E_2354, E_2356, E_2359, E_2361, E_2367, E_2368,
		E_2371, E_2372, E_2373, E_2374, E_2375, E_2376,
		E_2381, E_2382, E_2383,
		E_2403,
		E_3001, E_3006, E_3015, E_3016, E_3017, E_3023,
		E_3101, E_3106, E_3114, E_3118,
		/* 앉아서 포효 자세 */
		E_4001, E_4013,
		E_4071, E_4073, E_4074,
		/*서서 포효 자세*/
		E_22005
	};

	enum ColliderName // 콜리더의 내용
	{
		// 머리부분
		HEAD,
		// 목 부분
		NECK,
		// 가슴 부분
		CHEST,
		// 몸통부분
		BODY,
		// 왼쪽 날개
		LWING,
		LWING_RADIUS, // 날개 연결 관절
		// 오른쪽 날개
		RWING,
		RWING_RADIUS, // 날개 연결 관절
		// 왼쪽 다리 (앞)
		LLEG1,
		LLEG1_FOOT, // 발바닥
		// 왼쪽 다리 (뒤)
		LLEG2,
		LLEG2_FOOT,
		// 오른쪽 다리 (앞)
		RLEG1,
		RLEG1_FOOT, // 발바닥
		// 오른쪽 다리 (뒤)
		RLEG2,
		RLEG2_FOOT,
		// 꼬리
		TAIL_START, // 시작 부분
		TAIL_1,		// 1/4 지점
		TAIL_2,		// 1/2 지점
		TAIL,		// 끝 지점

		ROAR		// 포효 충돌체
	};
	enum WingName
	{
		// 왼쪽 날개
		LWING1,
		// 오른쪽 날개
		RWING1
	};
	//UINT Index = 18;


	enum Pattern
	{
		IDLE,
		S_LEGATK,
		S_STABATK,
		S_BACKWINGATK,
		S_SRUSH,
		S_JETRUSH,
		S_BITE,
		S_TRANSFORM,
		S_RUNANDBITE,
		S_RUNTOTRGT,
		B_SWINGATK,
		B_WINGATK,
		B_DOWNBLAST,
		B_FWDBLAST,
		B_ENERGYBLAST,
		B_DUMBLING,
		B_TRANSFORM,
		HS_FLYBLAST,
		HS_FLYFALLATK,
		HS_FLYWINGBLAST,
		HB_WINGATK,
		FINDROAR,
		ANGERROAR,
		STORM,
		ENERGYBULLET,
		HUPGI,
		FULLBURST,
		SIDESTEP,
		B_SIDESTEP,
		FORWARDBOOM,
		S_DEAD,
		S_SMALLSTAGGER,
		S_HUGESTAGGER,
		B_DEAD,
		B_SMALLSTAGGER,
		B_HUGESTAGGER,
		PATROL
	};


public:
	Valphalk();
	~Valphalk();

	void Update();
	void PreRender();
	void Render();
	void GUIRender();
	void PostRender();

	void Hit(); // 맞았을때 나오는 모션들
	void Spawn(Vector3 pos); // 스폰위치
	void SetTarget(Transform* target) { this->target = target; } // 타겟 설정

	Transform* GetTransform(int index) { return transforms[index]; }
	vector<CapsuleCollider*> GetCollider() { return colliders; }
	vector<SphereCollider*> GetSphereCollider() { return sphereColliders; }
	vector<BoxCollider*> GetBoxCollider() { return boxColliders; }
	Transform* GetRealPos() { return realPos; }

	void minusCurHP(int damage) { curHP -= damage; }
	void minusHeadHP(int damage) { colliders[HEAD]->partHp -= damage; }
	void minusChestHP(int damage) { colliders[CHEST]->partHp -= damage; }
	void minusLLegHP(int damage) { colliders[LLEG1]->partHp -= damage; }
	void minusRLegHP(int damage) { colliders[RLEG1]->partHp -= damage; }
	void minusTailHP(int damage) { colliders[TAIL]->partHp -= damage; }
	bool GetIsHupgi() { return isHupGi; }

	//ColliderName GetName() { return colliderName; }
	float damage = 0.1f;

private:
	// 패턴 함수
	void S_LegAtk();
	void S_StabAtk();
	void S_BackWingAtk();
	void S_SRush();
	void S_JetRush();
	void S_Bite();
	void S_Transform();
	void S_RunAndBite();
	void B_SwingAtk();
	void B_WingAtk();
	void B_DownBlast();
	void B_FwdBlast();
	void B_EnergyBlast();
	void B_Dumbling();
	void B_Trnasform();
	void HS_FlyBlast();
	void HS_FlyFallAtk();
	void HS_FlyWingBlast();
	void HB_WingAtk();
	void AngerRoar();

	void Storm();
	void EnergyBullets();
	void ForwardBoom();
	void FullBurst();
	void Hupgi();
	void Sidestep();
	void B_Sidestep();
	void S_Dead();
	void S_SmallStagger();
	void S_HugeStagger();
	void B_Dead();
	void B_SmallStagger();
	void B_HugeStagger();
	void Patrol();
	Vector3 GetPlayerPos();

	void Jet();

private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	void SetState(State state, float rad = 0);

	void DeathCheck();

	void ChooseNextPattern();
	void ConditionCheck();
	void PartDestroyCheck();

	void PlayPattern();
	void PushPlayer();
	void UpdateUI(); //캐릭터 UI가 있으면 이후 업데이트
	float GetRadBtwTrgt();
	void RotateToTarget(float ratio1, float ratio2); // 
	void SetColliderAttack(ColliderName name, float ratio, float dmg = 10.0f, UINT atkStrength = 2);
	int  SetRadAndMirror(bool needMirror);
	void Loop() { GetClip(curState)->ResetPlayTime(); Pos() = realPos->Pos(); }

	void FlameOn();
	void FlameOff();
	// 모션 함수

	void E0003();
	void E0007();
	void E0043();
	void E0044(float degree);
	void E0045(float degree);
	void E0055();
	void E0059();
	void E0060(float degree = 0);
	void E0061(float degree = 0);
	void E0071();
	void E0097();
	void E0098(float degree = 0);
	void E0099(float degree = 0);
	void E0146();
	void E0147();
	void E0151();
	void E0152(float degree = 0);
	void E0153(float degree = 0);
	void E0164();
	void E0165();
	void E0166();
	void E0171();
	void E0172();
	void E0173();
	void E0178();
	void E0179();
	void E0180();
	void E0186();
	void E0187();
	void E0188();
	void E1151();
	void E1155();
	void E1163();
	void E1164();
	void E2001();
	void E2002(float degree = 0);
	void E2003(float degree = 0);
	void E2013();
	void E2015();
	void E2017();
	void E2019();
	void E2020();
	void E2022();
	void E2027();
	void E2032();
	void E2033();
	void E2038();
	void E2040();
	void E2041(float degree = 0);
	void E2042(float degree = 0);
	void E2044(float degree = 0);
	void E2045(float degree = 0);
	void E2054();
	void E2056();
	void E2091();
	void E2092(float degree = 0);
	void E2093(float degree = 0);
	void E2103(float degree = 0);

	void E2079();
	void E2106();
	void E2107(float degree = 0);
	void E2108(float degree = 0);
	void E2118();
	void E2121();

	void E2124(Vector3 destVec);

	void E2129();
	void E2130();
	void E2131();
	void E2133();
	void E2134();
	void E2141();

	void E2151();
	void E2152();
	void E2153();

	void E2144();
	void E2145();
	void E2146();
	void E2145a();

	void E2171();

	void E2173();
	void E2174(float degree = 0);
	void E2175(float degree = 0);
	void E2185();
	void E2188();
	void E2189();
	void E2190();
	void E2192();
	void E2193();
	void E2200();
	void E2210();
	void E2211(float degree = 0);
	void E2253(Vector3 destVec = 0);

	void E2265();
	void E2267();
	void E2270();
	void E2271();
	void E2272();
	void E2274();
	void E2275();

	void EX2265();
	void EX2267();
	void EX2270(float degree = 0);
	void EX2271(float degree = 0);
	void EX2272(float degree = 0);
	void EX2274(float degree = 0);
	void EX2275(float degree = 0);
	void EX2276();
	void EX2277(float y = 0);
	void EX2278();

	void E2276();
	void E2277();
	void E2278();
	void E2280();
	void E2281(float degree = 0);
	void E2282(float degree = 0);
	void E2286();
	void E2288();
	void E2290();
	void E2354(float degree = 0);
	void E2356(float degree = 0);
	void E2359(float degree = 0);
	void E2361();
	void E2367();
	void E2368();

	void E2371();
	void E2372();
	void E2373();

	void EX2371();
	void EX2372(float degree = 0);
	void EX2373(float degree = 0);

	void E2374();
	void E2375();
	void E2376();

	void EX2374();
	void EX2375();
	void EX2376();

	void E2381();
	void E2382();
	void E2383();
	void E2082();

	void E2403();

	void E3001();
	void E3006();
	void E3015();
	void E3016();
	void E3017();
	void E3023();
	void E3101();
	void E3106();
	void E3114();
	void E3118();

	
	void E4001();
	void E4013();
	void E4071();
	void E4073(float timer, float checkHp);
	void E4074();


	void E22005();

	void ColliderAdd();
	void ColliderNodePos();

private: // 이벤트 혹은 함수에서 조건이 필요할거 같을때
	bool LookatPlayer = false;
	bool OtherPlay = false;
	bool OtherPlay2 = false;
	int Count = 0;
	float timer = 0.0f;
	int randX[6], randZ[6];
	bool isStorm = false;

private:
	vector<Transform*> transforms;
	vector<CapsuleCollider*> colliders;

	vector<BoxCollider*> wings;
	vector<Transform*> Wingtransforms;

	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Transform* target;
	Vector3 initPos = Vector3::Zero();
	Vector3 vecToTagt = Vector3::Zero();
	Vector3 initForward = Vector3::Zero();
	Transform* head = nullptr;
	CapsuleCollider* realPos = nullptr;
	Transform* realPosition = nullptr;
	CapsuleCollider* tempCollider = nullptr;

	// 샘플 무조건 바뀜
	//float speed = 50; //속력 : 기본 스탯
	//float maxHP = 5000;
	//float curHP = 5000;

	Vector3 velocity; //속력 : 실제 움직임

	Pattern curPattern = PATROL;
	State curState = E_0003; //= 기본 스테이트;
	State preState = curState;

	UINT sequence = 0;


	//스테이트 혹은 움직임에 따른 이벤트 지정
	vector<map<float, Event>> totalEvents;
	vector<map<float, Event>::iterator> eventIters;


	/////////////////////////////////////
	// 공격 콜라이더 (투사체, 폭발 등)	
	vector<SphereCollider*> bullets;
	BoxCollider* forwardBoom;
	BoxCollider* fullBurst;
	BoxCollider* effectBox1;
	BoxCollider* effectBox2;
	BoxCollider* effectBox3;
	SphereCollider* effectSphere1;
	SphereCollider* effectSphere2;
	Vector3 forwardBoomPosInit = { 0,-300,-1000 };
	Vector3 explosionPos = {};
	Vector3 explosionPos2 = {};
	//공격 충돌체 보관용 벡터
	vector<SphereCollider*> sphereColliders;
	vector<BoxCollider*> boxColliders;

	Vector3 fullBurstScale;
	Vector3 fullBurstPos;
	Vector3 fullBurstRot;
	Vector3 fullBurstFireScale;

	float rotSpeed = 5.0f;
	int ranPatrol = 0;
	float patrolTime = 0;
	float bulletTime = 0;
	float stormTime = 0;

	//ColliderName colliderName;
	// 파티클 부분
//	bool encounter = false;
//	bool fight = false;
//	bool fight2 = false;
	bool combo = false;

	bool isSlashMode = true;
	bool isHupGi = false;
	bool renderJet = false;
	bool renderJetRight = false;
	bool renderFullBurst = false;

	bool  isFindTrgt = false;
	float roarAfterTimer = 0.0f;  // 인식 포효 이후부터 타이머 시작
	float hupGiTimer = 0.0f;	  //  2분 지나면 끝
	bool  needHupGi = false;

	bool angerRoar90 = false;
	bool angerRoar40 = false;
	float angerTimer = 0.0f;
	bool isAnger = false;

	bool ult50 = false;

	bool angerRoar90Threshold = false;
	bool angerRoar40Threshold = false;
	bool ult50Threshold = false;

	bool playOncePerPattern = false;

	float radBtwTarget = 0.0f;
	float initialRad = 0.0f;
	float initRotY = 0.0f;


	const float rot135 = 2.36f;
	const float rot45 = 0.785f;

	float radDifference = 0.0f;
	float playRatioForE0071 = 0.0f;

	int whichPat = 0;

	bool isReverse = false;
	bool isStagger = false;

public:
	float maxHP = 25000;
	float curHP = 25000;
	float checkHp; // 흡기때 쓸거
	float yDifference = 0.0f;

	// 파티클
private:
	vector<Val_Jet_Particle*> jetParticle;
	vector<Val_fire*> fireParticle;
	float timer2 = 0;
	Transform* jetpos;
	Transform* jetposend;
	Vector3 jetpos1_1, jetpos2_1, jetpos3_1, jetpos4_1, jetpos5_1, jetpos6_1;
	Vector3 jetpos1_2, jetpos2_2, jetpos3_2, jetpos4_2, jetpos5_2, jetpos6_2;
	Vector3 jetpos1, jetpos2, jetpos3, jetpos4, jetpos5, jetpos6;

	vector<HupgiFire*> hupgiFire;
	vector<Explosion*> explosionParticle;
	ParticleSystem2* hupgiCharge;
	//StormEffect* stormEffect;
	//Vector3 jetpos2;

	vector<Transform*> zetPos;
	vector<ValZet*> valZets;
	FullBurstParticle* fullburstParticle;
	FullBurstParticle2* fullburstParticle2;
};