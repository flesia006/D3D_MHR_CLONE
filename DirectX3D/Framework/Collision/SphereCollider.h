#pragma once

class SphereCollider : public Collider
{
public:
    SphereCollider(float radius = 1.0f, UINT stackCount = 8, UINT sliceCount = 16);
    ~SphereCollider() = default;
        
    virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact) override;

    virtual bool IsBoxCollision(BoxCollider* collider) override;
    virtual bool IsSphereCollision(SphereCollider* collider) override;
    virtual bool IsCapsuleCollision(CapsuleCollider* collider) override;

    void Update();

    float Radius() { return radius * max(GlobalScale().x, max(GlobalScale().y, GlobalScale().z)); }

    bool isAttack = false;

    float atkDmg = 10.0f;
    Vector3 lastPos = {};
    Vector3 curPos = {};
    Vector3 direction = {};
private:
    virtual void MakeMesh() override;

private:
    float radius;

    UINT stackCount, sliceCount;
};