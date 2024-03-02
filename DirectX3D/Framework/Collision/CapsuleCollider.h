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

private:
    virtual void MakeMesh() override;

private:

    Transform* hitPoint;
    float radius, height;
    UINT stackCount, sliceCount;
};