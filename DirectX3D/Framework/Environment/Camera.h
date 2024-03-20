#pragma once
class TerrainEditor;
class Camera : public Transform
{
private:
    enum CAMmode
    {
        BASIC,
        OPENING,
        DEAD,
        FREE
    };

public:
    Camera();
    ~Camera();

    void Update();
    void GUIRender();

    void SetView();

    void SetTarget(Transform* target) { this->target = target; }
    void SetLockOnTarget(Vector3 target) { this->lockOnTarget = target; }
    void SetTerrain(TerrainEditor* terrain) { this->terrain = terrain; }

    void SetOpeningCAM();
    void SetDeadCAM(Transform* target, Transform* target2 = nullptr);

    void OpeningCAM();
    void DeadCAM();

    Vector3 ScreenToWorld(Vector3 screenPos);
    Vector3 WorldToScreen(Vector3 worldPos);

    Ray ScreenPointToRay(Vector3 screenPoint);

    void LookAtTarget();

    void TargetOptionSave(string file);
    void TargetOptionLoad(string file);

    bool ContainPoint(Vector3 point);
    bool ContainSphere(Vector3 center, float radius);

    ViewBuffer* GetViewBuffer() { return viewBuffer; }

    void Zoom(float dist, float damping = 15.0f)
        // 카메라 거리랑 줌인 줌아웃 되는 속도를 인자로. 속도 너무 느리게 넣으면 
        // 목표 거리까리 도달하지 않으니 주의
    {
        distance = Lerp(distance, dist, damping * DELTA);
    }
    bool isFreeCamTrue() { return freeCam = true; }
    bool isFreeCamFalse() { return freeCam = false; }

    Transform* sightRot;
    bool shakeCAM = false;

private:
    void FreeMode();
    void FollowMode();

    void ThirdPresonViewMode();

    void Frustum();
private:
    ViewBuffer* viewBuffer;
    Matrix view;
    Matrix projection;

    Vector3 planes[6];
    float a, b, c, d;

    float moveSpeed = 5000.0f;
    float rotSpeed = 2.0f;


    Vector3 prevMousePos;

    Transform* target = nullptr;
    Transform* target1 = nullptr;
    Transform* target2 = nullptr;
    Vector3 lockOnTarget;

    float distance = 400.0f;
    float height = 100.0f;
    float moveDamping = 5.0f;
    float rotDamping = 1.0f;

    float rotY = 0;

    float destRot = 0.0f;
    Vector3 destPos;
    Vector3 focusOffset;

    bool isLookAtTargetX = true;
    bool isLookAtTargetY = true;

    bool playOpening = false;
    bool playDeadScene = false;
    bool once = false;
    bool freeCam = false;

    bool lateInitialize = false;

    Matrix rotMatrix;

    char file[128] = {};

    SphereCollider* camSphere = nullptr;
    BoxCollider* ground = nullptr;
    Ray sight;
    TerrainEditor* terrain = nullptr;

    CAMmode mode = BASIC;
    float timer = 0.0f;
    float shakeTimer = 0.0f;
    UINT count = 0;
};