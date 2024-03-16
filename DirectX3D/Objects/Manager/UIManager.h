#pragma once
class UIManager : public Singleton<UIManager>
{
private:
    friend class Singleton;

public:
    UIManager();
    ~UIManager();

    void Update();
    void PostRender();
    void GUIRender();
    void Hit(float damage);
    void HealthPotion();
    void LargeHealthPotion();
    void Running();
    void Roll();
    void ReduceDurability();
    void SharpeningStone();
    void GaugeBonus();
    void TargetMonster();
    void GetWildBug();
        
    float MinusDurability() { return curDurability -= 0.2f; } // 내구도 깎는 함수
    float GetDurabilityLevelCoefft()                            // 내구도 공격력 보정치를 반환        
    {
        if      (curDurability <= 80.0f && curDurability > 60.0f)        return 1.5f;
        else if (curDurability <= 60.0f && curDurability > 40.0f)        return 1.32f;
        else if (curDurability <= 40.0f && curDurability > 20.0f)        return 1.2f;
        else if (curDurability <= 20.0f && curDurability >= 0.0f)        return 1.05f;
    }

    float GetSpritGauge() { return curSpiritGauge; }
    void PlusSpritGauge();   //{ return curSpiritGauge += 15; }
    void DoublePlusSpritGauge(); //{ return curSpiritGauge += 25; }
    void MinusSpiritGauge(); //{ return curSpiritGauge -= 10; }

    float GetCotingLevel() { return cotingLevel; }
    float PlusCotingLevel()  {  
        cotingLevel++; // 코팅레벨++
        if (cotingLevel > 3) cotingLevel = 3;
        curCoting = maxCoting;
        return cotingLevel;
    }    
    float MinusCotingLevel() {
        cotingLevel--; // 코팅레벨--
        if (cotingLevel <= 0) cotingLevel = 0;
        curCoting = maxCoting;
        return cotingLevel;
    }

    float GetCotingLevelCoefft()
    {
        if      (cotingLevel == 0)            return 1.0f;
        else if (cotingLevel == 1)            return 1.05f;
        else if (cotingLevel == 2)            return 1.1f;
        else if (cotingLevel == 3)            return 1.2f;
    }
    void Bonus154True() { bonus154 = true;}

    bool IsAbleBugSkill();
    void UseBugSkill();

    float SetMaxCoting() { return curCoting = maxCoting; }
    float SetMaxGauge() { return curSpiritGauge = maxSpiritGauge; }
    float curStamina = 100;//임시로 public에 올려둠
    bool staminaActive = false;

    // 발파 상태 아이콘 관련 내용
    bool specialMove = false;
    bool specialMove2 = false;
    bool partDestruct = false;
    bool partDestruct2 = false;
    bool valDeath = false;

    void UIAlphaOn();
    void StartUIAlphaOn();

private:
    // 퀵 슬롯 관한 내용
    //=====================
    void QuickSlot(); // 퀵 슬롯 어떤 식으로 랜더 할지 내용
    void QuickSlotBar(); // 퀵 슬롯 에서 가리키는 내용 함수
    void DragInvenItem();
    void DragSlot(); // 드래그 슬롯 내용
    void DragSlotBar(); // 드래그 슬롯 내용
    void NumberSlot(); // 넘버 슬롯 내용
    void NumberSlotBar(); // 넘버 슬롯 내용
    //=====================
    // 발파 상태 아이콘 관령 내용
    void StateIcon();

private:
    Quad* clockFrame;
    Quad* durability;
    Quad* durability_back;
    Quad* hpBar;
    Quad* idBar;
    Quad* itemSlot;
    Quad* lsGauge;
    Quad* quickSlot;
    Quad* slingerBug;
    Quad* slingerBug2;
    Quad* slingerBug3;
    Quad* staminarBar;
    Quad* monsterIcon;
    Quad* iconFrame;
    Quad* hpBarEdge;
    Quad* staminarBarEdge;
    Quad* clockHand;
    Quad* clockHand2;
    // 퀵슬롯 추가 부분
    Quad* quickSlot_Back;
    Quad* quickSlot_Select;
    Quad* quickSlot_Button;
    vector<Quad*> selectBoxs;
    vector<Quad*> selectBoxFrames;
    // 드래그 슬롯 추가 부분
    Quad* dragSlotBox;
    Quad* dragSlot_ButtonUp;
    Quad* dragSlot_ButtonWheel;
    Quad* dragSlot_ButtonDown;
    Quad* dragSlot_KeyButton;
    // 넘버 슬롯 추가 부분
    vector<Quad*> numberBoxs;
    vector<Quad*> numberBoxFrames;
    // 슬롯 안에 아이템 이름
    vector<Quad*> slotNames;

    Quad* blackCircle;
    Quad* blackHalfCircle;
    Quad* orangeLeftHalfCircle;
    Quad* orangeRightHalfCircle;
    Quad* blackCircle2;
    Quad* blackHalfCircle2;
    Quad* orangeLeftHalfCircle2;
    Quad* orangeRightHalfCircle2;
    Quad* blackCircle3;
    Quad* blackHalfCircle3;
    Quad* orangeLeftHalfCircle3;
    Quad* orangeRightHalfCircle3;

    // 아이템 아이콘 추가 ( 이건 퀵 슬롯에 있는것들 )
    Quad* rideGarukIcon;
    //===================
    Quad* potionIcon_Q;
    Quad* greatepotionIcon_Q;
    Quad* whetstoneIcon_Q;
    //=================== ( 아래는 다른 슬롯 쪽)
    Quad* potionIcon_D;
    Quad* greatepotionIcon_D;
    Quad* whetstoneIcon_D;
    vector<Quad*>inItDragItem_D;
    //===================
    Quad* potionIcon_N;
    Quad* greatepotionIcon_N;
    Quad* whetstoneIcon_N;
    //===================
    vector<Quad*> itemNumber_Q;
    vector<Quad*> itemNumber_D;
    vector<Quad*> itemNumber_N;
    vector<Quad*> itemKeyNumber_N;
    //===================
    
    //액터의 UI
    ProgressBar* hp;
    Vector3 hpPos; //체력바의 위치를 수치화한 것 (진짜 위치를 위한 중간계산용)
    ProgressBar* recover;

    // 스태미너 UI
    ProgressBar* stamina;
    Vector3 staminaPos; //체력바의 위치를 수치화한 것 (진짜 위치를 위한 중간계산용)
    ProgressBar* staminaRecover;

    //예리도 UI
    ProgressBar* durability_gauge;

    //기인게이지 UI
    ProgressBar* lsGauge2;

    //코팅 UI
    ProgressBar* lsCoting;

    // 발파 상태 UI
    Quad* valphalkStateIcon1;
    Quad* valphalkStateIcon2;
    Quad* valphalkStateIcon3;

    // 퀘스트 클리어
    Quad* questClearUI;
    // 퀘스트 시작
    Quad* questStartUI;

    // 갈무리 아이콘
    Quad* materialIcon1;
    Quad* materialIcon2;
    Quad* materialIcon3;

public:
    UINT cotingLevel = 0;
    UINT bugCount = 2;    

    float curHP = 100;
    float maxHP = 100;

    float recoverHP = 100;
    float maxStamina = 100;
    float recoverStamina = 100;
    float curDurability = 80;
    float maxDurability = 80;


    bool isBonus = false;

    float curSpiritGauge = 0;
    float maxSpiritGauge = 100;
    float bonusTime = 0.f;
    float limitTime = 32.f;
    bool bonus154 = false;


    float curCoting = 100;
    float maxCoting = 100;



    bool isCoolTime1 = false;
    bool isCoolTime2 = false;
    bool isCoolTime3 = false;

    bool getWildBug = false;

    const float wildBugDurationLimit = 180.0f;
    float wildBugDuration = 0.0f;
    
    // 퀵 슬롯 실행 할때 유무 확인 하기
    // 일단 8칸 이라 8개 만들건데 바뀔수 있음
    bool useQuickSlot1 = false;
    bool useQuickSlot2 = false;
    bool useQuickSlot3 = false;
    bool useQuickSlot4 = false;
    bool useQuickSlot5 = false;
    bool useQuickSlot6 = false;
    bool useQuickSlot7 = false;
    bool useQuickSlot8 = false;
    // 아래 이건 특정 키를 누르면 Bar가 활성화됨
    bool useSelectBar = false;
    Vector3 MousePos;

    int havePotion = 10; // 애는 20이 10개
    int haveGPotion = 0; // 애는 10이 10개

    // 드래그 슬롯 실행 할때 유무 확인 하기
    bool useDragBar = false;
    bool useDragSlot1 = true;
    bool useDragSlot2 = false;
    bool useDragSlot3 = false;

    float dragTimer = 0.0f;
    // 넘버 슬롯 실행 할때 유뮤 확인 하기
    bool useNumberBar = false;
    float timer = 0.0f;

    bool useNumberSlot1 = false;
    bool useNumberSlot2 = false;
    bool useNumberSlot3 = false;
    bool useNumberSlot4 = false;
    bool useNumberSlot5 = false;
    bool useNumberSlot6 = false;
    bool useNumberSlot7 = false;
    bool useNumberSlot8 = false;

    int DragCout = 0;

    // 발파 상태 내용
    float stateIconTimer = 0.0f;
    float stateIconTimer2 = 0.0f;
    float stateIconTimer3 = 0.0f;

    bool isRender = false;
    float clearUITimer = 0.0f;
    UINT clearCount = 0;
    float startUITimer = 0.0f;
    float waitTimer = 0.0f;
    UINT startCount = 0;

    // 갈무리 아이콘 시간 체크용
    bool captureIcon1 = false;
    bool captureIcon2 = false;
    bool captureIcon3 = false;

    float capturingTimer1 = 0.0f;
    float capturingTimer2 = 0.0f;
    float capturingTimer3 = 0.0f;

    UINT randNum1 = rand() % 3;
    UINT randNum2 = rand() % 3;
    UINT randNum3 = rand() % 3;
};

