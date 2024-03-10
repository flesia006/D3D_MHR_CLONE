#pragma once
class Valphalk;
class Kunai
{
    // ����ü�� �ʿ��� ������

private:
    float LIFE_SPAN = 5.0f; // life span : ������ ���� �ֱ�.
                            // ���α׷��ֿ����� ������ ��ü�� ���� �ð��� ���Ѵ� (�ֱⰡ ������ ����)

    struct Damage
    {
        Vector3 pos = {};
        int damage = 0;
        int hitPart = 9;
        bool isWeakness = false;
        float timer = 0.0f;
    };

public:
    Kunai(Transform* transform);
    ~Kunai();

    void Update();
    void Render();
    void PostRender();

    void Throw(Vector3 pos, Vector3 dir);

    CapsuleCollider* GetCollider() { return collider; }
    Transform* GetTransform() { return transform; }

    void SetEnemy(Valphalk* enemy) { val = enemy; }

private:
    void Attack();

private:
    // �� ������ ���� : �ܺο��� �����
    vector<Damage> damages;

    Transform* transform;
    CapsuleCollider* collider;

    Valphalk* val;

    //����ӵ�
    float speed = 4000.0f;
    const float temp = -2.364f;  // �ؽ�Ʈ ���� �� ��ġ
    const float temp2 = -6.038f; // �ؽ�Ʈ ���� �� ��ġ
    const float temp3 = 14.067f; // �ؽ�Ʈ ���� �� ��ġ

    //���� ������ �Ⱓ
    float time = 0;

    float atkCoolDown = 0.0f;
    float coolDown = 0.15f;
    //����
    Vector3 direction;
};

