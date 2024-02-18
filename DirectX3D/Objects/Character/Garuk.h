#pragma once

class Garuk : public ModelAnimator
{
private:
    //�ֿ� ��� ������
    enum State
    {
        G_001, G_010,G_022,G_024
    };

public:
    //ȣ��� �Լ�
    Garuk();
    ~Garuk();

    void Update();
    void Render();
    void GUIRender();

    void SetTarget(Transform* target) { this->target = target; }

    // ĳ���Ϳ� ���, ��ã�� Ŭ������ ��ȣ �����ϴ� �Լ�
    //void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
    //void SetAStar(AStar* aStar) { this->aStar = aStar; }
    //void Control(Transform* transform);
    Transform* GetTransform() { return transform; }

private:
    //��� �Լ�
    void Control();
    void Move();
    void Rotate();

    void SetState(State state); // ���� ���� �Լ� : FSM�� ������ �ٽ�
    //void SetPath();

    void G001();
    void G010();
    void G022();
    void G024();
    
private:
    //��� ����
    State curState = G_001; //���� ���� + �⺻��

    float curHP = 100;
    float maxHP = 100;
    float moveSpeed = 100;
    float rotSpeed = 10;

    Vector3 velocity;

    Vector3 initForward = Vector3::Zero();

    Transform* transform;
    Transform* target;
    //�� ã��� ������
    //Vector3 destPos; //������
    //vector<Vector3> path; //���

    //Terrain* terrain; // ���� (���)
    //AStar* aStar;     // �� ã�� �˰���

};