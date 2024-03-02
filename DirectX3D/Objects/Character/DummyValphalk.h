#pragma once
class DummyValphalk : public ModelAnimator
{
public:
	enum State
	{
		E_0003,
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

