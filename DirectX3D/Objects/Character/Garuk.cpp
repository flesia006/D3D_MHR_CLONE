#include "Framework.h"

Garuk::Garuk() : ModelAnimator("Garuk")
{
    ReadClip("G_001", 1);
    ReadClip("G_010", 1);
    ReadClip("G_022", 1);
    ReadClip("G_024",1);
    PlayClip(G_001); // ���� ���¿� ���� ���� 1ȸ ȣ��
    
}

Garuk::~Garuk()
{
}

void Garuk::Update()
{
    //ĳ���� ���� 3�� ȣ��
    Control();
    Move();
    Rotate();
    velocity = target->GlobalPos() - GlobalPos();

    ModelAnimator::Update();

    switch(curState)
    {
        case G_001:
            G001();
            break;
        case G_010:
            G010();
            break;
        case G_022:
            G022();
            break;
        case G_024:
            G024();
            break;
        default:
            break;
    }
}

void Garuk::Render()
{
    ModelAnimator::Render();
}

void Garuk::GUIRender()
{
    ModelAnimator::GUIRender();
    //for (CapsuleCollider* capsulCollider : colliders)
    //{
    //	capsulCollider->GUIRender();
    //}
    
    ImGui::SliderFloat3("garukpos", (float*)&Pos(), 0, 100);
    
}

//void Garuk::Control()
//{
    //if (KEY_DOWN(VK_LBUTTON))
    //{
    //    destPos = terrain->Pick(); // ���� �������� �������� ã�Ƴ���

    //    if (aStar->IsCollisionObstacle(GlobalPos(), destPos)) //�����Ÿ��� ��ֹ��� ���̸�
    //    {
    //        SetPath(); // ��ֹ��� ��ġ(��λ� ��� ��ֹ�����) ã�Ƴ� ���� �ش� �κ��� ���ư��� ��� ��� ����
    //    }
    //    else //��ֹ��� ������
    //    {
    //        path.clear(); //��δ� ���ǹ��ϴϱ� �� ���ְ�
    //        path.push_back(destPos); //���� ������ �ϳ��� ����� = �������� Move() �Լ��� �����ϸ�
    //    }
    //}
//}
//void Garuk::Control(Transform* transform)
//{
//    destPos = transform->Pos(); // ������ ã��
//                                  // �ͷ��� ������ ���� ����� ��ǻƮ��ŷ����
//
//    if (aStar->IsCollisionObstacle(GlobalPos(), destPos)) // �߰��� ��ֹ��� ������
//    {
//        SetPath(); // ��ü���� ��� ��� ����
//    }
//    else //��ֹ��� ���� ���
//    {
//        path.clear(); //3D���� ��ֹ��� ���µ� ���� ��ã�⸦ �� �ʿ� ����
//        path.push_back(destPos); // ���� �� ���� ��� ���Ϳ� ����ֱ�
//                                 // -> �׷��� ����� Move()�� �������� ã�ư� ��
//    }
//}

void Garuk::Control()
{
}

void Garuk::Move()
{
    if (velocity.Length() < 300) return; // �ӵ��� ������ ��� �� �߰�����(���⼭�� "������ �Ÿ�")�� �ʹ� ��� ����

    // �Ÿ��� �����̻� �־����� ���� ����
    if (velocity.Length() >= 300 && curState != G_022)
    {
        moveSpeed = 100;
        SetState(G_010);
    }

    //else if(velocity.Length() >= 400) // �Ÿ��� �ʹ� �ָ�
    //{
    //    moveSpeed = 300;   
    //    SetState(G_022);
    //}

    // ��ġ ���� �� ȸ�� ����ϱ�
    Pos() += velocity.GetNormalized() * moveSpeed * DELTA;
    Rot().y = atan2(velocity.x, velocity.z) + XM_PI; // �ӷº��Ϳ� ���� ȸ���� + �𵨿� ���� �������
}

void Garuk::Rotate()
{
    if (curState == G_001) return; //�̵� ���� �ƴ� ���� ȸ�� ����

    Vector3 forward = Forward(); //���� �� ������
    Vector3 cross = Cross(forward, velocity); //�� �հ� ���� �� �擇���� ���� ����

    if (INIT) // �̵��߿��� ��� ������ȯ�Ͽ� �ε�ε� ���°� ����
    {
        if (cross.y < 0) //�� ��꿡 ���� ������ ���̸� = ���� ���������� �������� ���� ���̴�
            Rot().y += rotSpeed * DELTA; // ���� ȸ��
        else if (cross.y > 0) //���� �ݴ�
            Rot().y -= rotSpeed * DELTA; //������ ȸ��
    }
}

void Garuk::SetState(State state) //ȣ���� �̰� �ϳ��θ�
{
    if (state == curState) return;
    
    curState = state; //���¸� �������ְ�
    PlayClip(state);  //����� ���¿� ���� �ִϸ��̼� ���
}

void Garuk::G001() // ���
{
    PLAY;
}

void Garuk::G010() // �ȱ� ����
{
    PLAY;
    if (RATIO > 0.98)    
        SetState(G_022);    
}

void Garuk::G022() // �ȴ���
{
    if (velocity.Length() < 400 && curState != G_024)
    {
        PLAY;
        moveSpeed = 300;
        SetState(G_024);
    }
    else moveSpeed = 100;
}

void Garuk::G024() // �ȱ� ����
{
    PLAY;
    if (RATIO > 0.98)
        SetState(G_001);
}
