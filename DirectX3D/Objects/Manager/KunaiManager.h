#pragma once

class KunaiManager : public Singleton<KunaiManager>
{
private:
    friend class Singleton;
    UINT SIZE = 30; // ���� ���� ���� ����

public:

    KunaiManager();
    ~KunaiManager();

    void Update();
    void Render();
    void PostRender();

    void Throw(Vector3 pos, Vector3 dir); // ���� ���̿��� ���� �Լ��� �����ϱ� ���� �Ű��Լ�
                                          // ĳ���ʹ� �� �Լ��� ����, �� �Լ��� ��¥ ���̸� ������

    bool IsCollision(Collider* collider);
    void SetEnemy(Valphalk* enemy) 
    { for (Kunai* kunai : kunaies) 
        kunai->SetEnemy(enemy); }

private:

    //������ ���� �����ؼ� �����ϱ� ����...
    ModelInstancing* kunaiInstancing; // ������ ���� ��� �� �ν��Ͻ̸����� ���
                                      // (����ü�� �ִϸ��̼��� �ִ� ����� ModelAnimationInstancing Ŭ������ �ʿ��� ��)

    vector<Kunai*> kunaies; // ���� ������ �� Ŭ����
    Valphalk* enemy;
};

