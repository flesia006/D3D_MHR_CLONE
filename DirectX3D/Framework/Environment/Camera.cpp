#include "Framework.h"

Camera::Camera()
{
    tag = "Camera";

    viewBuffer = new ViewBuffer();
    viewBuffer->SetVS(1);


    camSphere = new SphereCollider(distance);
    camSphere->SetParent(this);
    camSphere->UpdateWorld();

    prevMousePos = mousePos;

    sight.dir = Vector3::Forward();
    sightRot = new Transform();
}

Camera::~Camera()
{
    delete viewBuffer;
}

void Camera::Update()
{
    projection = Environment::Get()->GetProjection();
    Frustum();

    if (sightRot->Rot().y < -3.14)
        sightRot->Rot().y += XM_2PI;

    if (sightRot->Rot().y > 3.14)
        sightRot->Rot().y -= XM_2PI;

    if (target == nullptr && target1 == nullptr && target == nullptr)
        mode = FREE;

    switch (mode)
    {
    case Camera::BASIC:     ThirdPresonViewMode();          break;
    case Camera::OPENING:   OpeningCAM();                   break;
    case Camera::DEAD:      DeadCAM();                      break;
    case Camera::FREE:      FreeMode();                     break;
    }


    if (KEY_DP(VK_F4))        mode = FREE;
    if (KEY_DP(VK_F5))        mode = BASIC;
    if (KEY_DP(VK_F6))        SetOpeningCAM();


    UpdateWorld();
}

void Camera::GUIRender()
{
    if (ImGui::TreeNode("CameraOption"))
    {
        ImGui::DragFloat("MoveSpeed", &moveSpeed);
        ImGui::DragFloat("RotSpeed", &rotSpeed);

        if (target && ImGui::TreeNode("TargetOption"))
        {
            ImGui::DragFloat("Distance", &distance, 0.1f);
            ImGui::DragFloat("Height", &height, 0.1f);
            ImGui::DragFloat3("FocusOffset", (float*)&focusOffset, 0.1f);

            float degree = XMConvertToDegrees(rotY);
            ImGui::DragFloat("RotY", &degree, 0.1f);
            rotY = XMConvertToRadians(degree);

            ImGui::DragFloat("MoveDamping", &moveDamping, 0.1f);
            ImGui::DragFloat("RotDamping", &rotDamping, 0.1f);

            ImGui::Checkbox("LookAtTargetX", &isLookAtTargetX);
            ImGui::Checkbox("LookAtTargetY", &isLookAtTargetY);

            ImGui::InputText("File", file, 128);

            if (ImGui::Button("Save"))
                TargetOptionSave(file);
            ImGui::SameLine();
            if (ImGui::Button("Load"))
                TargetOptionLoad(file);

            ImGui::TreePop();
        }

        Transform::GUIRender();

        ImGui::TreePop();
    }
}

void Camera::SetView()
{
    view = XMMatrixInverse(nullptr, world);
    viewBuffer->Set(view, world);

    viewBuffer->SetVS(1);
    viewBuffer->SetPS(1);
    viewBuffer->SetHS(1);
    viewBuffer->SetDS(1);
}

void Camera::SetOpeningCAM()
{
    mode = OPENING;
    distance = 120.0f;
    height = -30;
    sightRot->Rot().x = -0.1;
    sightRot->Rot().y = 0.6;
    sightRot->UpdateWorld();

    CAM->Rot() = sightRot->Rot();
    CAM->Pos() = target->GlobalPos() + sightRot->Back() * distance * 1.6;
    CAM->Pos().y += height;
}


void Camera::OpeningCAM()
{
    timer += DELTA;
    if (timer < 1.5f)
    {

    }
    else if (timer < 6.0f)
    {
        sightRot->Rot().x = Lerp(sightRot->Rot().x, 0.2, 1.5 * DELTA);
        sightRot->Rot().y = Lerp(sightRot->Rot().y, XM_PI, 1.5 * DELTA);
        distance = Lerp(distance, 400, 2 * DELTA);
        height = Lerp(height, 0, 1 * DELTA);

        sightRot->UpdateWorld();

        CAM->Rot() = sightRot->Rot();
        CAM->Pos() = target->GlobalPos() + sightRot->Back() * distance * 1.6;
        CAM->Pos().y += height;
    }
    else
    {

        distance = 400.0f;
        height = 0.0f;
        timer = 0.0f;
        mode = BASIC;
    }

}

void Camera::SetDeadCAM(Transform* target, Transform* target2)
{
    this->target1 = target;
    mode = DEAD;
    distance = 400.0f;    
    sightRot->Rot().x = 0.5;
    sightRot->Rot().y = target->Rot().y;
    sightRot->UpdateWorld();

    if (target2 != nullptr)
        this->target2 = target2;

    CAM->Rot() = sightRot->Rot();
    CAM->Pos() = target->GlobalPos() + sightRot->Back() * distance * 1.6;
    CAM->Pos().y += height;
}

void Camera::DeadCAM()
{
    timer += DELTA;
    if(timer < 4)
    {
        sightRot->Rot().x = 0.5f;
        sightRot->Rot().y = Lerp(sightRot->Rot().y, sightRot->Rot().y + XM_PI, 0.1 * DELTA);      
    }
    else if (timer < 8)
    {
        if (!once)
        {
            sightRot->Rot().y -= XM_PIDIV4;
            distance = 1000.0f;
            target1 = target2;
            once = true;
        }
        sightRot->Rot().x = 1.0f;
        sightRot->Rot().y = Lerp(sightRot->Rot().y, sightRot->Rot().y + XM_PI, 0.1 * DELTA);

    }
    else if (timer < 12)
    {
        if (once)
        {
            sightRot->Rot().x = 1.2;
            sightRot->Rot().y -= XM_PI;
            once = false;
        }
        sightRot->Rot().x = Lerp(sightRot->Rot().x, 1.4, 1 * DELTA);        
    }
    else
    {
        timer = 0.0f;
        distance = 400.0f;
        target1 = nullptr;
        target2 = nullptr;
        mode = BASIC;
        return;
    }
    sightRot->UpdateWorld();
    CAM->Rot() = sightRot->Rot();
    CAM->Pos() = target1->GlobalPos() + sightRot->Back() * distance * 1.6;
}

Vector3 Camera::ScreenToWorld(Vector3 screenPos)
{
    return XMVector3TransformCoord(screenPos, world);
}

Vector3 Camera::WorldToScreen(Vector3 worldPos)
{
    Vector3 screenPos;

    screenPos = XMVector3TransformCoord(worldPos, view);
    screenPos = XMVector3TransformCoord(screenPos, projection);
    //NDC : -1 ~ 1

    screenPos = (screenPos + Vector3::One()) * 0.5f;//0~1

    screenPos.x *= WIN_WIDTH;
    screenPos.y *= WIN_HEIGHT;

    return screenPos;
}

Ray Camera::ScreenPointToRay(Vector3 screenPoint)
{
    Vector3 screenSize(WIN_WIDTH, WIN_HEIGHT, 1.0f);

    Vector2 point;
    point.x = (screenPoint.x / screenSize.x) * 2.0f - 1.0f;
    point.y = (screenPoint.y / screenSize.y) * 2.0f - 1.0f;

    Float4x4 temp;
    XMStoreFloat4x4(&temp, projection);

    screenPoint.x = point.x / temp._11;
    screenPoint.y = point.y / temp._22;
    screenPoint.z = 1.0f;

    screenPoint = XMVector3TransformNormal(screenPoint, world);

    Ray ray;
    ray.pos = Pos();
    ray.dir = screenPoint.GetNormalized();

    return ray;
}

void Camera::LookAtTarget()
{
    rotMatrix = XMMatrixRotationY(target->Rot().y + rotY);

    Vector3 forward = XMVector3TransformNormal(Vector3::Forward(), rotMatrix);

    Pos() = target->GlobalPos() + forward * -distance;
    Pos().y += height;

    Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
    Vector3 targetPos = target->GlobalPos() + offset;

    Vector3 dir = (targetPos - Pos()).GetNormalized();
    forward = Vector3(dir.x, 0.0f, dir.z).GetNormalized();

    Rot().x = acos(Dot(forward, dir));
    Rot().y = atan2(dir.x, dir.z);
}
void Camera::FreeMode()
{
    Vector3 delta = mousePos - prevMousePos;
    prevMousePos = mousePos;

    if (KEY_PRESS(VK_RBUTTON))
    {
        if (KEY_PRESS('W'))
            Pos() += Forward() * moveSpeed * DELTA;
        if (KEY_PRESS('S'))
            Pos() += Back() * moveSpeed * DELTA;
        if (KEY_PRESS('A'))
            Pos() += Left() * moveSpeed * DELTA;
        if (KEY_PRESS('D'))
            Pos() += Right() * moveSpeed * DELTA;
        if (KEY_PRESS('E'))
            Pos() += Down() * moveSpeed * DELTA;
        if (KEY_PRESS('Q'))
            Pos() += Up() * moveSpeed * DELTA;

        if (KEY_PRESS('Z'))
            Pos() += Forward() * 500 * DELTA;
        if (KEY_PRESS('C'))
            Pos() += Right() * 500 * DELTA;

        Rot().x -= delta.y * rotSpeed * DELTA;
        Rot().y += delta.x * rotSpeed * DELTA;
    }
}

void Camera::FollowMode()
{
    destRot = Lerp(destRot, target->Rot().y, rotDamping * DELTA);
    rotMatrix = XMMatrixRotationY(destRot + rotY);

    Vector3 forward = XMVector3TransformNormal(Vector3::Forward(), rotMatrix);

    destPos = target->GlobalPos() + forward * -distance;
    destPos.y += height;

    Pos() = Lerp(Pos(), destPos, moveDamping * DELTA);

    Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
    Vector3 targetPos = target->GlobalPos() + offset;

    Vector3 dir = (targetPos - Pos()).GetNormalized();
    forward = Vector3(dir.x, 0.0f, dir.z).GetNormalized();

    if (isLookAtTargetX)
    {
        Rot().x = acos(Dot(forward, dir));
    }
    if (isLookAtTargetY)
    {
        Rot().y = atan2(dir.x, dir.z);
    }
}

void Camera::ThirdPresonViewMode()
{
    if (freeCam == true)
    {
        FreeMode();
        return;
    }
    if (freeCam == false)
    {
        //Vector3 delta = mousePos - prevMousePos;
        //prevMousePos = mousePos;
        if (lockOnTarget == Vector3(0, 0, 0))
        {
            if (!KEY_PRESS('X') && !ItemManager::Get()->useBlueBox)
            {
                Vector3 delta = mousePos - prevMousePos;
                prevMousePos = mousePos;
        
                sightRot->Rot().x -= delta.y * rotSpeed * DELTA;
                sightRot->Rot().x = Clamp(-XM_PIDIV2 + 0.5f, XM_PIDIV2 - 0.01f, sightRot->Rot().x);
                sightRot->Rot().y += delta.x * rotSpeed * DELTA;
                sightRot->UpdateWorld();
        
                CAM->Rot() = sightRot->Rot();
            }
            CAM->Pos() = target->GlobalPos() + sightRot->Back() * distance * 1.6;
        }
        else
        {
            Vector3 trgtToTrgt;
            trgtToTrgt.x = (lockOnTarget.x - target->GlobalPos().x);
            trgtToTrgt.y = 0;
            trgtToTrgt.z = (lockOnTarget.z - target->GlobalPos().z);
            trgtToTrgt = trgtToTrgt.GetNormalized();
        
            sightRot->Rot().x = -0.1f;
            //sightRot->Rot().x = Clamp(-XM_PIDIV2 + 0.5f, XM_PIDIV2 - 0.01f, sightRot->Rot().x);
            sightRot->Rot().y = atan2(trgtToTrgt.x, trgtToTrgt.z);
            sightRot->UpdateWorld();
        
            CAM->Rot() = Lerp(Rot(), sightRot->Rot(), 10 * DELTA);
            CAM->Pos() = target->GlobalPos() + Back() * distance * 1.6;
        }
    }

    // 만약 카메라가 지면을 파고든다? (TODO : Terrain 만들면 그에 맞게 수정)

    // 1. 광선(뒤통수의 시선) 만들기
    sight.dir = sightRot->Back();
    sight.pos = target->GlobalPos();

    // 2. 땅과 contact 받아오기
    if (terrain != nullptr)
    {
        Vector3 pos = {};
        bool hitGround = false;
        if (sightRot->Rot().x < -0.4f)
        {
            hitGround = terrain->ComputePicking(pos, sight.pos, sight.dir);
            if ((target->GlobalPos() - pos).Length() > distance || !hitGround)
                return;
            CAM->Pos() = pos - sight.dir.Back() * 20;
        }
    }
}

void Camera::Frustum()
{
    Float4x4 VP;
    XMStoreFloat4x4(&VP, view * projection);

    //Left
    a = VP._14 + VP._11;
    b = VP._24 + VP._21;
    c = VP._34 + VP._31;
    d = VP._44 + VP._41;
    planes[0] = XMVectorSet(a, b, c, d);

    //Right
    a = VP._14 - VP._11;
    b = VP._24 - VP._21;
    c = VP._34 - VP._31;
    d = VP._44 - VP._41;
    planes[1] = XMVectorSet(a, b, c, d);

    //Bottom
    a = VP._14 + VP._12;
    b = VP._24 + VP._22;
    c = VP._34 + VP._32;
    d = VP._44 + VP._42;
    planes[2] = XMVectorSet(a, b, c, d);

    //Top
    a = VP._14 - VP._12;
    b = VP._24 - VP._22;
    c = VP._34 - VP._32;
    d = VP._44 - VP._42;
    planes[3] = XMVectorSet(a, b, c, d);

    //Near
    a = VP._14 + VP._13;
    b = VP._24 + VP._23;
    c = VP._34 + VP._33;
    d = VP._44 + VP._43;
    planes[4] = XMVectorSet(a, b, c, d);

    //Far
    a = VP._14 - VP._13;
    b = VP._24 - VP._23;
    c = VP._34 - VP._33;
    d = VP._44 - VP._43;
    planes[5] = XMVectorSet(a, b, c, d);

    FOR(6)
        planes[i] = XMPlaneNormalize(planes[i]);
}

void Camera::TargetOptionSave(string file)
{
    string path = "TextData/Camera/" + file + ".cam";

    BinaryWriter* writer = new BinaryWriter(path);

    writer->Float(distance);
    writer->Float(height);
    writer->Float(moveDamping);
    writer->Float(rotDamping);
    writer->Float(rotY);
    writer->Vector(focusOffset);
    writer->Bool(isLookAtTargetX);
    writer->Bool(isLookAtTargetY);

    delete writer;
}

void Camera::TargetOptionLoad(string file)
{
    string path = "TextData/Camera/" + file + ".cam";

    BinaryReader* reader = new BinaryReader(path);

    distance = reader->Float();
    height = reader->Float();
    moveDamping = reader->Float();
    rotDamping = reader->Float();
    rotY = reader->Float();
    focusOffset = reader->Vector();
    isLookAtTargetX = reader->Bool();
    isLookAtTargetY = reader->Bool();

    delete reader;
}

bool Camera::ContainPoint(Vector3 point)
{
    FOR(6)
    {
        Vector3 dot = XMPlaneDotCoord(planes[i], point);

        if (dot.x < 0.0f)
            return false;
    }

    return true;
}

bool Camera::ContainSphere(Vector3 center, float radius)
{
    Vector3 edge;
    Vector3 dot;

    FOR(6)
    {
        //1
        edge.x = center.x - radius;
        edge.y = center.y - radius;
        edge.z = center.z - radius;
        dot = XMPlaneDotCoord(planes[i], edge);
        if (dot.x > 0.0f)
            continue;

        //2
        edge.x = center.x + radius;
        edge.y = center.y - radius;
        edge.z = center.z - radius;
        dot = XMPlaneDotCoord(planes[i], edge);
        if (dot.x > 0.0f)
            continue;

        //3
        edge.x = center.x - radius;
        edge.y = center.y + radius;
        edge.z = center.z - radius;
        dot = XMPlaneDotCoord(planes[i], edge);
        if (dot.x > 0.0f)
            continue;

        //4
        edge.x = center.x - radius;
        edge.y = center.y - radius;
        edge.z = center.z + radius;
        dot = XMPlaneDotCoord(planes[i], edge);
        if (dot.x > 0.0f)
            continue;

        //5
        edge.x = center.x + radius;
        edge.y = center.y + radius;
        edge.z = center.z - radius;
        dot = XMPlaneDotCoord(planes[i], edge);
        if (dot.x > 0.0f)
            continue;

        //6
        edge.x = center.x + radius;
        edge.y = center.y - radius;
        edge.z = center.z + radius;
        dot = XMPlaneDotCoord(planes[i], edge);
        if (dot.x > 0.0f)
            continue;

        //7
        edge.x = center.x - radius;
        edge.y = center.y + radius;
        edge.z = center.z + radius;
        dot = XMPlaneDotCoord(planes[i], edge);
        if (dot.x > 0.0f)
            continue;

        //8
        edge.x = center.x + radius;
        edge.y = center.y + radius;
        edge.z = center.z + radius;
        dot = XMPlaneDotCoord(planes[i], edge);
        if (dot.x > 0.0f)
            continue;

        return false;
    }

    return true;
}
