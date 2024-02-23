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
		E_0146, // �����ڼ� ��ȯ
		//����
		E_1151, E_1155, E_1163, E_1164,
		// ���ݹ� �ǰ��ڼ�
		E_2001, E_2002, E_2003,
		E_2013, E_2015, E_2017, E_2019,// E_2020, E_2022,
		//E_2027, E_2032,
		E_2038, E_2040, //E_2041, E_2042, E_2044, E_2045,
		E_2054, //E_2056,
		E_2091, E_2092, E_2093, E_2103, // ���� �ֵ�
		//E_2106, E_2107, E_2108,
		//E_2118, E_2121, 
		E_2129, E_2130, E_2131, E_2133, E_2134, E_2141,	 // �մٸ� �����鼭 ���� ����
		E_2151, E_2152, E_2153,
		//E_2173, E_2174, E_2175,
		//E_2185, E_2188, E_2189, E_2190, E_2192, E_2193, E_2200,
		E_2210, E_2211,
		E_3001, E_3023,
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


	enum Pattern
	{
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

	void Hit(); // �¾����� ������ ��ǵ�
	void Spawn(Vector3 pos); // ������ġ
	void SetTarget(Transform* target) { this->target = target; } // Ÿ�� ����

	Transform* GetTransform(int index) { return transforms[index]; }
	vector<CapsuleCollider*> GetCollider() { return colliders; }

	//ColliderName GetName() { return colliderName; }
	float damage = 0.1f;

private:
	// ���� �Լ�
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
	void Hupgi();


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
	void UpdateUI(); //ĳ���� UI�� ������ ���� ������Ʈ
	float GetRadBtwTrgt();
	void RotateToTarget(float ratio1, float ratio2); // 
	void SetColliderAttack(ColliderName name, float ratio);


	// ��� �Լ�

	void E0003();
	void E0007();
	void E0043();
	void E0044();
	void E0045();
	void E0097();
	void E0098();
	void E0099();
	void E0146();
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
	void E2038();
	void E2040();
	void E2041();
	void E2042();
	void E2044();
	void E2045();
	void E2054();
	void E2056();

	void E2091();
	void E2092();
	void E2093();
	void E2103();

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

	Pattern curPattern = B_WINGATK;
	State curState = E_0043; //= �⺻ ������Ʈ;
	Type curType; //= �⺻ Ÿ��;

	UINT sequence = 0;


	//������Ʈ Ȥ�� �����ӿ� ���� �̺�Ʈ ����
	vector<map<float, Event>> totalEvents;
	vector<map<float, Event>::iterator> eventIters;

	Vector3 realFwd;
	float realRot;

	int ranPatrol = 0;
	float patrolTime = 0;
	float stormTime = 0;

	//ColliderName colliderName;
	// ��ƼŬ �κ�
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