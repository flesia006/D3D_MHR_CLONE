#pragma once

class CapsuleCollider : public Collider
{
public:
    CapsuleCollider(float radius = 1.0f, float height = 2.0f,
        UINT stackCount = 8, UINT sliceCount = 16);
    ~CapsuleCollider() = default;

    virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact) override;
    virtual bool IsBoxCollision(BoxCollider* collider) override;
    virtual bool IsSphereCollision(SphereCollider* collider) override;
    virtual bool IsCapsuleCollision(CapsuleCollider* collider) override;

    bool IsSphereCollision(SphereCollider* collider, Contact* contact);
    bool IsCapsuleCollision(CapsuleCollider* collider, Contact* contact);

    float Radius() { return radius * max(GlobalScale().x, max(GlobalScale().y, GlobalScale().z)); }
    float Height() { return height * GlobalScale().y; }

    Vector3 GetHitPointPos() { return  hitPoint->GlobalPos(); }

    void Update();
    void GUIRender();

    int part = 0;
    float partHp = 0.0f;
    bool isAttack = false;

    float atkDmg = 10.0f;
    UINT atkStrength = 2;  // 1 : 소경직을 유발,  2: 넘어짐을 유발, 3: 뭔가 더 대단한걸 유발 (아직 모르겠다)
    Vector3 lastPos = {};
    Vector3 curPos = {};
    Vector3 direction = {};

private:
    virtual void MakeMesh() override;

private:

    Transform* hitPoint;
    float radius, height;
    UINT stackCount, sliceCount;
};