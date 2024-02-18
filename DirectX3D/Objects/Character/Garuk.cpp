#include "Framework.h"

Garuk::Garuk() : ModelAnimator("Garuk")
{
    ReadClip("G_001", 1);
    ReadClip("G_010", 1);
    ReadClip("G_022", 1);
    ReadClip("G_024",1);
    PlayClip(G_001); // 현재 상태에 따른 동작 1회 호출
    
}

Garuk::~Garuk()
{
}

void Garuk::Update()
{
    //캐릭터 조종 3종 호출
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
    //    destPos = terrain->Pick(); // 최종 목적지를 지형에서 찾아내고

    //    if (aStar->IsCollisionObstacle(GlobalPos(), destPos)) //직선거리에 장애물이 보이면
    //    {
    //        SetPath(); // 장애물의 위치(경로상 어디가 장애물인지) 찾아낸 다음 해당 부분을 돌아가는 경로 계속 내기
    //    }
    //    else //장애물이 없으면
    //    {
    //        path.clear(); //경로는 무의미하니까 다 없애고
    //        path.push_back(destPos); //최종 목적지 하나만 남기기 = 그쪽으로 Move() 함수를 수행하면
    //    }
    //}
//}
//void Garuk::Control(Transform* transform)
//{
//    destPos = transform->Pos(); // 목적지 찾기
//                                  // 터레인 에디터 쓰는 사람은 컴퓨트픽킹으로
//
//    if (aStar->IsCollisionObstacle(GlobalPos(), destPos)) // 중간에 장애물이 있으면
//    {
//        SetPath(); // 구체적인 경로 내어서 가기
//    }
//    else //장애물이 없는 경우
//    {
//        path.clear(); //3D에서 장애물도 없는데 굳이 길찾기를 쓸 필요 없음
//        path.push_back(destPos); // 가야 할 곳만 경로 벡터에 집어넣기
//                                 // -> 그러면 여우는 Move()로 목적지를 찾아갈 것
//    }
//}

void Garuk::Control()
{
}

void Garuk::Move()
{
    if (velocity.Length() < 300) return; // 속도에 영향을 줘야 할 중간변수(여기서는 "대상과의 거리")가 너무 적어도 종료

    // 거리가 일정이상 멀어지면 추적 시작
    if (velocity.Length() >= 300 && curState != G_022)
    {
        moveSpeed = 100;
        SetState(G_010);
    }

    //else if(velocity.Length() >= 400) // 거리가 너무 멀면
    //{
    //    moveSpeed = 300;   
    //    SetState(G_022);
    //}

    // 위치 갱신 및 회전 계산하기
    Pos() += velocity.GetNormalized() * moveSpeed * DELTA;
    Rot().y = atan2(velocity.x, velocity.z) + XM_PI; // 속력벡터에 의한 회전값 + 모델에 의한 보정계수
}

void Garuk::Rotate()
{
    if (curState == G_001) return; //이동 중이 아닐 때는 회전 안함

    Vector3 forward = Forward(); //모델의 앞 따오기
    Vector3 cross = Cross(forward, velocity); //내 앞과 가야 할 방뱡에서 나온 법선

    if (INIT) // 이동중에도 계속 방향전환하여 부들부들 떠는거 방지
    {
        if (cross.y < 0) //위 계산에 의한 법선이 밑이면 = 내가 목적지보다 오른쪽을 보는 중이다
            Rot().y += rotSpeed * DELTA; // 왼쪽 회전
        else if (cross.y > 0) //위와 반대
            Rot().y -= rotSpeed * DELTA; //오른쪽 회전
    }
}

void Garuk::SetState(State state) //호출은 이거 하나로만
{
    if (state == curState) return;
    
    curState = state; //상태를 변경해주고
    PlayClip(state);  //변경된 상태에 따른 애니메이션 재생
}

void Garuk::G001() // 대기
{
    PLAY;
}

void Garuk::G010() // 걷기 시작
{
    PLAY;
    if (RATIO > 0.98)    
        SetState(G_022);    
}

void Garuk::G022() // 걷는중
{
    if (velocity.Length() < 400 && curState != G_024)
    {
        PLAY;
        moveSpeed = 300;
        SetState(G_024);
    }
    else moveSpeed = 100;
}

void Garuk::G024() // 걷기 멈춤
{
    PLAY;
    if (RATIO > 0.98)
        SetState(G_001);
}
