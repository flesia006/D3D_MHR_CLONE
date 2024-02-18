#pragma once

class Garuk : public ModelAnimator
{
private:
    //주요 멤버 데이터
    enum State
    {
        G_001, G_010,G_022,G_024
    };

public:
    //호출용 함수
    Garuk();
    ~Garuk();

    void Update();
    void Render();
    void GUIRender();

    void SetTarget(Transform* target) { this->target = target; }

    // 캐릭터와 배경, 길찾기 클래스를 상호 연결하는 함수
    //void SetTerrain(Terrain* terrain) { this->terrain = terrain; }
    //void SetAStar(AStar* aStar) { this->aStar = aStar; }
    //void Control(Transform* transform);
    Transform* GetTransform() { return transform; }

private:
    //멤버 함수
    void Control();
    void Move();
    void Rotate();

    void SetState(State state); // 상태 설정 함수 : FSM식 개발의 핵심
    //void SetPath();

    void G001();
    void G010();
    void G022();
    void G024();
    
private:
    //멤버 변수
    State curState = G_001; //현재 상태 + 기본값

    float curHP = 100;
    float maxHP = 100;
    float moveSpeed = 100;
    float rotSpeed = 10;

    Vector3 velocity;

    Vector3 initForward = Vector3::Zero();

    Transform* transform;
    Transform* target;
    //길 찾기용 데이터
    //Vector3 destPos; //목적지
    //vector<Vector3> path; //경로

    //Terrain* terrain; // 지형 (배경)
    //AStar* aStar;     // 길 찾는 알고리즘

};