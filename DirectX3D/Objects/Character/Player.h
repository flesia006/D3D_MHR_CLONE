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
		L_115, L_116, L_117, L_118, L_119,
		L_120, L_121, L_122, L_123, S_003,
		S_008, S_009
	};

	enum Rotation
	{
		북, 북동, 동, 남동, 남, 남서, 서, 북서
	};


public:
	Player();
	~Player();


	void Update();
	void UpdateWorlds();
	void PreRender();
	void Render();
	void GUIRender();
	void PostRender();


private:
	void Control();
	void Move();
	void ResetPlayTime();

	void Rotate();
	void Attack(); // TODO :  인자로 모션 배율 넣기
	void SetAnimation();
	void Roll();

	void SetState(State state);
	void Throw();
	void EndThrow();

	void SetIdle() { SetState((State)1); }

	void MotionRotate(float degree);

private:
	void ReadClips();
	void RecordLastPos();
	void ReturnIdle()
	{
		Pos() = realPos->Pos();
		GetClip(L_001)->ResetPlayTime();
		SetState(L_001);
	}
	void S003();
	void S008();
	void S009();

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

	void LRunning();
private:
	Transform* mainHand = nullptr;
	Transform* root = nullptr;
	Transform* realPos = nullptr;
	Transform* lastPos = nullptr;
	Transform* head = nullptr;
	Transform* back = nullptr;

	Transform* swordStart = nullptr;
	Transform* swordEnd = nullptr;

	SphereCollider* tmpCollider = nullptr;
	CapsuleCollider* swordCollider = nullptr;

	Model* longSword = nullptr;

	Shadow* shadow;
	Particle* particle;
	LightBuffer::Light* light;
	Trail* trail;

	State curState = L_101;
	State preState = L_101;

	float moveSpeed = 500;
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
	float rotation = -1.5;

	float camRot;
	float rad;

	int loopApply = 334;



};

