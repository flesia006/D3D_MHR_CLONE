#pragma once
class Valphalk : public ModelAnimator
{
public:
	enum State
	{
		// �ִϸ��̼� Ŭ������ ���°ſ� ���� �ٲ���
		// ���� ���
		STUN
	};

	enum Type // ��� ���� ���Ұ��� 
	{
		// ���� �����
		TypeA, // �̰� �Ӹ��� ������
		TypeB, // �̰� ���� ������
		TypeC // �̰� �Ѵ� ������
	};

	enum ColliderName // �ݸ����� ����
	{
		// �Ӹ��κ�
		HEAD,

		// ����κ�
		BODY,

		// ���� ����
		LWING,

		// ������ ����
		RWING,

		// ���� �ٸ� (��)
		LLEG1,

		// ���� �ٸ� (��)
		LLEG2,

		// ������ �ٸ� (��)
		RLEG1,

		// ������ �ٸ� (��)
		RLEG2,

		// ����
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

	void Hit(); // �¾����� ������ ��ǵ�
	void Spawn(Vector3 pos); // ������ġ
	void SetTarget(Transform* target); // Ÿ�� ����

	//Transform* GetTransform(int index) { return transforms[index]; }
	vector<CapsuleCollider*> GetCollider() { return colliders; }

	//ColliderName GetName() { return colliderName; }
	float damage = 0.1f;

private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	// ��ȯ �Ǵ� �̺�Ʈ�� �ε� ���� �� ��
	//===============

	//===============

	void SetState(State state);
	void SetType(Type type);

	void Move();
	void UpdateUI(); //ĳ���� UI�� ������ ���� ������Ʈ

private:
	//vector<Transform*> transforms;
	vector<CapsuleCollider*> colliders;

	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Transform* target;

	// ���� ������ �ٲ�
	//float speed = 50; //�ӷ� : �⺻ ����
	//float maxHP = 100;
	//float curHP = 100;

	Vector3 velocity; //�ӷ� : ���� ������

	State curState = STUN; //= �⺻ ������Ʈ;
	Type curType; //= �⺻ Ÿ��;

	//������Ʈ Ȥ�� �����ӿ� ���� �̺�Ʈ ����
	vector<map<float, Event>> totalEvent;
	vector<map<float, Event>::iterator> eventIters;

	//ColliderName colliderName;

	// ��ƼŬ �κ�

};