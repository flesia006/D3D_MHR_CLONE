#pragma once
class Valphalk : public ModelAnimator
{
public:
	enum State
	{
		// 애니메이션 클립들이 들어가는거에 따라서 바뀔예정
		// 예를 들면
		STUN, E_2005 /*서서 포효 자세*/, E_4013 /* 앉아서 포효 자세 */
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

		// 몸통부분
		BODY,

		// 왼쪽 날개
		LWING,

		// 오른쪽 날개
		RWING,

		// 왼쪽 다리 (앞)
		LLEG1,

		// 왼쪽 다리 (뒤)
		LLEG2,

		// 오른쪽 다리 (앞)
		RLEG1,

		// 오른쪽 다리 (뒤)
		RLEG2,

		// 꼬리
		TAIL
	};

	UINT Index = 9;

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

	//Transform* GetTransform(int index) { return transforms[index]; }
	vector<CapsuleCollider*> GetCollider() { return colliders; }

	//ColliderName GetName() { return colliderName; }
	float damage = 0.1f;

private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	// 전환 되는 이벤트들 인데 아직 잘 모름
	//===============
	void EndRoar(); // 포효 끝
	//===============

	// 이벤트 실행 될때 내용인데 위에 전환이랑 합칠수도
	//===============
	void StartRoar(); // 포효 시작
	//===============

	void SetState(State state);
	void SetType(Type type);

	void Move();
	void UpdateUI(); //캐릭터 UI가 있으면 이후 업데이트

	void E4013();

private: // 이벤트 혹은 함수에서 조건이 필요할거 같을때
	bool LookatPlayer = false;
	int Count = 0;

private:
	//vector<Transform*> transforms;
	vector<CapsuleCollider*> colliders;

	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Transform* target;
	Vector3 initForward = Vector3::Zero();

	// 샘플 무조건 바뀜
	//float speed = 50; //속력 : 기본 스탯
	//float maxHP = 100;
	//float curHP = 100;

	Vector3 velocity; //속력 : 실제 움직임

	State curState = STUN; //= 기본 스테이트;
	Type curType; //= 기본 타입;

	//스테이트 혹은 움직임에 따른 이벤트 지정
	vector<map<float, Event>> totalEvents;
	vector<map<float, Event>::iterator> eventIters;

	//ColliderName colliderName;

	// 파티클 부분
};