#pragma once

class Valphalk : public ModelAnimator
{
public:
	enum State
	{
		E_0003,
		E_0007,

		// 플레이어 발견 전에 걸으면서 돌아다니기
		E_0043 /* 앞으로 걷기 */, E_0044 /* 왼쪽 보고 걷기 */, E_0045 /* 뒤로 돌고 걷기 */,

		// 플레이어 발견 후
		E_0097 /* 앞으로 포효 준비*/, E_0098 /* 왼쪽으로 포효 준비 */, E_0099, /* 뒤로 돌아서 포효 준비 */
		// 공격및 피격자세
		E_2038,E_2040,E_2054,
		E_3001,E_3023,
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
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	void SetState(State state);
	void SetType(Type type);

	void Patrol();
	void Fight();

	void Move();
	void UpdateUI(); //캐릭터 UI가 있으면 이후 업데이트

	void E0003();
	void E0007();
	void E0043();
	void E0044();
	void E0045();
	void E0097();
	void E0098();
	void E0099();
	void E2038();
	void E2040();
	void E2054();
	void E3001();
	void E3023();
	void E4013();
	void E22005();

	void ColliderAdd();
	void ColliderNodePos();

private: // 이벤트 혹은 함수에서 조건이 필요할거 같을때
	bool LookatPlayer = false;
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

	State curState = E_0043; //= 기본 스테이트;
	Type curType; //= 기본 타입;

	//스테이트 혹은 움직임에 따른 이벤트 지정
	vector<map<float, Event>> totalEvents;
	vector<map<float, Event>::iterator> eventIters;

	int ranPatrol = 0;
	float patrolTime = 0;
	//ColliderName colliderName;
	// 파티클 부분
	bool encounter = false;
	bool fight = false;
	bool fight2 = false;
	bool combo = false;
};