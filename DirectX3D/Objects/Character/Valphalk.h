#pragma once

class Valphalk : public ModelAnimator
{
public:
	enum State
	{
		E_0003,	E_0007,	E_0043,	E_0044,	E_0045,
		E_0055, E_0059, E_0060, E_0061, E_0071, 
		E_0097,	E_0098,	E_0099,	E_0146,	
		E_0147,	E_0151,	E_0152,	E_0153,	E_0164,
		E_0165,	E_0166,	E_0171,	E_0172,	E_0173,
		E_0178,	E_0179,	E_0180,	E_0186,	E_0187,	E_0188,
		E_1151, E_1155, E_1163, E_1164,		//습격		
		E_2001, E_2002, E_2003,				// 공격및 피격자세
		E_2013, E_2015, E_2017, E_2019, E_2020, E_2022,
		E_2027, E_2032, E_2033,
		E_2038, E_2040, E_2041, E_2042, E_2044, E_2045,
		E_2054, E_2056, E_2079,
		E_2091, E_2092, E_2093, E_2103, // 날개 휘둘
		E_2106, E_2107, E_2108,	E_2118, E_2121, 
		E_2129, E_2130, E_2131, E_2133, E_2134, E_2141,	 // 앞다리 찍으면서 날개 덮기
		E_2144, E_2145, E_2146,
		E_2151, E_2152, E_2153,
		E_2173, E_2174, E_2175, E_2185,
		E_2188, E_2189, E_2190, E_2192, E_2193, E_2200,
		E_2210, E_2211,  E_2253, E_2265, E_2267,
		E_2270, E_2271, E_2272, E_2274, E_2275, E_2276, E_2277, E_2278,
		E_2280, E_2286, E_2288, E_2290,
		E_2354, E_2356, E_2359, E_2361, E_2367, E_2368,
		E_2371, E_2372, E_2373, E_2374, E_2375, E_2376,
		E_2403,
		E_3001, E_3023,
		/* 앉아서 포효 자세 */
		E_4013,
		/*서서 포효 자세*/
		E_22005
	};

	enum Type // 어디가 색이 변할건지 
	{
		// 예를 든거임
		TypeA, // 이건 머리만 빨간색
		TypeB, // 이건 날개 빨간색
		TypeC // 이건 둘다 빨간색
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
		TAIL		// 끝 지점
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
		S_TRANSFORM,
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
		HB_LASERBLAST,
		FINDROAR,
		ANGERROAR,
		STORM,
		ENERGYBULLET,
		HUPGI,
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

	//ColliderName GetName() { return colliderName; }
	float damage = 0.1f;

private:
	// 패턴 함수
	void S_LegAtk();
	void S_StabAtk();
	void S_BackWingAtk();
	void S_SRush();
	void S_JetRush();
	void S_Transform();
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
	void HB_LaserBlast();
	void FindRoar();
	void AngerRoar();
	
	void Storm();
	void EnergyBullets();	
	void ForwardBoom();
	void FullBurst();
	void Hupgi();

	Vector3 GetPlayerPos();

private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	void SetState(State state, float rad = 0);
	void SetType(Type type);

	void Patrol();
	void Fight();

	void ChooseNextPattern();

	void PlayPattern();
	void Move();
	void UpdateUI(); //캐릭터 UI가 있으면 이후 업데이트
	float GetRadBtwTrgt();
	void RotateToTarget(float ratio1, float ratio2); // 
	void SetColliderAttack(ColliderName name, float ratio);
	int SetRadAndMirror(bool needMirror);


	// 모션 함수

	void E0003();
	void E0007();
	void E0043();
	void E0044();
	void E0045();
	void E0055();
	void E0059();
	void E0060();
	void E0061();
	void E0071();
	void E0097();
	void E0098();
	void E0099();
	void E0146();
	void E0147();
	void E0151();
	void E0152();
	void E0153();
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
	void E2002();
	void E2003();
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
	void E2041();
	void E2042();
	void E2044();
	void E2045();
	void E2054();
	void E2056();

	void E2091();
	void E2092(float degree = 0);
	void E2093(float degree = 0);
	void E2103(float degree = 0);

	void E2079();
	void E2106();
	void E2107();
	void E2108();
	void E2118();
	void E2121();

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
	void E2173();
	void E2174();
	void E2175();
	void E2185();
	void E2188();
	void E2189();
	void E2190();
	void E2192();
	void E2193();
	void E2200();
	void E2210();
	void E2211();
	void E2253();
	void E2265();
	void E2267();
	void E2270();
	void E2271();
	void E2272();
	void E2274();
	void E2275();
	void E2276();
	void E2277();
	void E2278();
	void E2280();
	void E2286();
	void E2288();
	void E2290();
	void E2354();
	void E2356();
	void E2359();
	void E2361();
	void E2367();
	void E2368();
	void E2371();
	void E2372();
	void E2373();
	void E2374();
	void E2375();
	void E2376();
	void E2403();

	void E3001();
	void E3023();
	void E4013();
	void E22005();

	void ColliderAdd();
	void ColliderNodePos();

private: // 이벤트 혹은 함수에서 조건이 필요할거 같을때
	bool LookatPlayer = false;
	bool OtherPlay = false;
	int Count = 0;

private:
	vector<Transform*> transforms;
	vector<CapsuleCollider*> colliders;

	vector<BoxCollider*> wings;
	vector<Transform*> Wingtransforms;

	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Transform* target;
	Vector3 initForward = Vector3::Zero();
	Transform* head = nullptr;
	CapsuleCollider* realPos = nullptr;

	// 샘플 무조건 바뀜
	//float speed = 50; //속력 : 기본 스탯
	//float maxHP = 100;
	//float curHP = 100;

	Vector3 velocity; //속력 : 실제 움직임

	Pattern curPattern = B_SWINGATK;
	State curState = E_0043; //= 기본 스테이트;
	State preState = curState;
	Type curType; //= 기본 타입;

	UINT sequence = 0;


	//스테이트 혹은 움직임에 따른 이벤트 지정
	vector<map<float, Event>> totalEvents;
	vector<map<float, Event>::iterator> eventIters;


	/////////////////////////////////////
	// 공격 콜라이더 (투사체, 폭발 등)	
	vector<SphereCollider*> bullets;
	CapsuleCollider* forwardBoom;
	BoxCollider* fullBurst;

	Vector3 fullBurstScale;
	Vector3 fullBurstPos;
	Vector3 fullBurstRot;

	float rotSpeed = 5.0f;
	int ranPatrol = 0;
	float patrolTime = 0;
	float bulletTime = 0;
	float stormTime = 0;

	//ColliderName colliderName;
	// 파티클 부분
	bool encounter = false;
	bool fight = false;
	bool fight2 = false;
	bool combo = false;

	bool playOncePerPattern = false;

	float radBtwTarget = 0.0f;
	float initialRad = 0.0f;

	const float rot135 = 2.36f;
	const float rot45 = 0.785f;

	float radDifference = 0.0f;
};