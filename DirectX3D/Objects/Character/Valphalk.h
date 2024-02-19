#pragma once
class Valphalk : public ModelAnimator
{
public:
	enum State
	{
		// �ִϸ��̼� Ŭ������ ���°ſ� ���� �ٲ���
		// ���� ���
		STUN, E_2005 /*���� ��ȿ �ڼ�*/, E_4013 /* �ɾƼ� ��ȿ �ڼ� */
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
	void SetTarget(Transform* target) { this->target = target; } // Ÿ�� ����

	//Transform* GetTransform(int index) { return transforms[index]; }
	vector<CapsuleCollider*> GetCollider() { return colliders; }

	//ColliderName GetName() { return colliderName; }
	float damage = 0.1f;

private:
	void SetEvent(int clip, Event event, float timeRatio);
	void ExecuteEvent();

	// ��ȯ �Ǵ� �̺�Ʈ�� �ε� ���� �� ��
	//===============
	void EndRoar(); // ��ȿ ��
	//===============

	// �̺�Ʈ ���� �ɶ� �����ε� ���� ��ȯ�̶� ��ĥ����
	//===============
	void StartRoar(); // ��ȿ ����
	//===============

	void SetState(State state);
	void SetType(Type type);

	void Move();
	void UpdateUI(); //ĳ���� UI�� ������ ���� ������Ʈ

	void E4013();

private: // �̺�Ʈ Ȥ�� �Լ����� ������ �ʿ��Ұ� ������
	bool LookatPlayer = false;
	int Count = 0;

private:
	//vector<Transform*> transforms;
	vector<CapsuleCollider*> colliders;

	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Transform* target;
	Vector3 initForward = Vector3::Zero();

	// ���� ������ �ٲ�
	//float speed = 50; //�ӷ� : �⺻ ����
	//float maxHP = 100;
	//float curHP = 100;

	Vector3 velocity; //�ӷ� : ���� ������

	State curState = STUN; //= �⺻ ������Ʈ;
	Type curType; //= �⺻ Ÿ��;

	//������Ʈ Ȥ�� �����ӿ� ���� �̺�Ʈ ����
	vector<map<float, Event>> totalEvents;
	vector<map<float, Event>::iterator> eventIters;

	//ColliderName colliderName;

	// ��ƼŬ �κ�
};