#pragma once
class Valphalk;
class Kunai
{
    // 투사체에 필요한 데이터

private:
    float LIFE_SPAN = 5.0f; // life span : 원문은 생애 주기.
                            // 프로그래밍에서는 생성된 객체의 지속 시간을 말한다 (주기가 끝나면 삭제)

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
    // 모델 변수는 없음 : 외부에서 만들기
    vector<Damage> damages;

    Transform* transform;
    CapsuleCollider* collider;

    Valphalk* val;

    //진행속도
    float speed = 4000.0f;
    const float temp = -2.364f;  // 텍스트 띄우기 용 수치
    const float temp2 = -6.038f; // 텍스트 띄우기 용 수치
    const float temp3 = 14.067f; // 텍스트 띄우기 용 수치

    //현재 생성된 기간
    float time = 0;

    float atkCoolDown = 0.0f;
    float coolDown = 0.15f;
    //방향
    Vector3 direction;
};

