#pragma once

class Valphalk : public ModelAnimator
{
public:
	enum State
	{
		E_0003,
		E_0007,

		// �÷��̾� �߰� ���� �����鼭 ���ƴٴϱ�
		E_0043 /* ������ �ȱ� */, E_0044 /* ���� ���� �ȱ� */, E_0045 /* �ڷ� ���� �ȱ� */,

		// �÷��̾� �߰� ��
		E_0097 /* ������ ��ȿ �غ�*/, E_0098 /* �������� ��ȿ �غ� */, E_0099, /* �ڷ� ���Ƽ� ��ȿ �غ� */
		// ���ݹ� �ǰ��ڼ�
		E_2038,E_2040,E_2054,
		E_3001,E_3023,
		/* �ɾƼ� ��ȿ �ڼ� */
		E_4013,
		/*���� ��ȿ �ڼ�*/
		E_22005 
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
		// �� �κ�
		NECK,
		// ���� �κ�
		CHEST,
		// ����κ�
		BODY,		
		// ���� ����
		LWING,
		LWING_RADIUS, // ���� ���� ����
		// ������ ����
		RWING,
		RWING_RADIUS, // ���� ���� ����
		// ���� �ٸ� (��)
		LLEG1,
		LLEG1_FOOT, // �߹ٴ�
		// ���� �ٸ� (��)
		LLEG2,
		LLEG2_FOOT,
		// ������ �ٸ� (��)
		RLEG1,
		RLEG1_FOOT, // �߹ٴ�
		// ������ �ٸ� (��)
		RLEG2,
		RLEG2_FOOT,
		// ����
		TAIL_START, // ���� �κ�
		TAIL_1,		// 1/4 ����
		TAIL_2,		// 1/2 ����
		TAIL		// �� ����
	};
	enum WingName
	{
		// ���� ����
		LWING1,
		// ������ ����
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

	void Hit(); // �¾����� ������ ��ǵ�
	void Spawn(Vector3 pos); // ������ġ
	void SetTarget(Transform* target) { this->target = target; } // Ÿ�� ����

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
	void UpdateUI(); //ĳ���� UI�� ������ ���� ������Ʈ

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

private: // �̺�Ʈ Ȥ�� �Լ����� ������ �ʿ��Ұ� ������
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

	// ���� ������ �ٲ�
	//float speed = 50; //�ӷ� : �⺻ ����
	//float maxHP = 100;
	//float curHP = 100;

	Vector3 velocity; //�ӷ� : ���� ������

	State curState = E_0043; //= �⺻ ������Ʈ;
	Type curType; //= �⺻ Ÿ��;

	//������Ʈ Ȥ�� �����ӿ� ���� �̺�Ʈ ����
	vector<map<float, Event>> totalEvents;
	vector<map<float, Event>::iterator> eventIters;

	int ranPatrol = 0;
	float patrolTime = 0;
	//ColliderName colliderName;
	// ��ƼŬ �κ�
	bool encounter = false;
	bool fight = false;
	bool fight2 = false;
	bool combo = false;
};