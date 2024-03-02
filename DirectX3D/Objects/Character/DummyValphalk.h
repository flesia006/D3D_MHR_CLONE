#pragma once
class DummyValphalk : public ModelAnimator
{
public:
	enum State
	{
		E_0003,
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


public:
	DummyValphalk();
	~DummyValphalk();

	void Update();
	void PreRender();
	void Render();
	void GUIRender();
	void ColliderAdd();
	void ColliderNodePos();

	vector<CapsuleCollider*> GetCollider() { return colliders; }


private:
	vector<Transform*> transforms;
	vector<CapsuleCollider*> colliders;

	vector<BoxCollider*> wings;
	vector<Transform*> Wingtransforms;

};

