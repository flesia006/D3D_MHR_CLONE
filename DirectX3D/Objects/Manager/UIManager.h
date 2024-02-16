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

    // 퀵 슬롯 관한 내용
    //=====================
    void QuickSlot(); // 퀵 슬롯 어떤 식으로 랜더 할지 내용
    void QuickSlotBar(); // 퀵 슬롯 에서 가리키는 내용 함수
    //=====================

    float MinusDurability() { return curDurability -= 0.2f; } // 내구도 깎는 함수
    float GetDurabilityLevelCoefft()                            // 내구도 공격력 보정치를 반환        
    {
        if      (curDurability <= 80.0f && curDurability > 60.0f)        return 1.5f;
        else if (curDurability <= 60.0f && curDurability > 40.0f)        return 1.32f;
        else if (curDurability <= 40.0f && curDurability > 20.0f)        return 1.2f;
        else if (curDurability <= 20.0f && curDurability >= 0.0f)        return 1.05f;
    }

    float PlusSpritGauge()   { return curSpiritGauge += 15; }   // 기인게이지 늘리는 함수
    float MinusSpiritGauge() { return curSpiritGauge -= 10; }   // 기인게이지 깎는 함수
    float PlusCotingLevel()  {  
        cotingLevel++; // 코팅레벨++
        if (cotingLevel > 3) cotingLevel = 3;
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
    float SetMaxCoting() { return curCoting = maxCoting; }
    float curStamina = 100;//임시로 public에 올려둠
    bool staminaActive = false;

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
    Quad* quickSlot_Back;
    Quad* quickSlot_Select;
    vector<Quad*> selectBoxs;
    vector<Quad*> selectBoxFrames;

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

    //액터의 UI
    ProgressBar* hp;
    Vector3 hpPos; //체력바의 위치를 수치화한 것 (진짜 위치를 위한 중간계산용)
    ProgressBar* recover;

    float curHP = 100;
    float maxHP = 100;

    float recoverHP = 100;

    // 스태미너 UI
    ProgressBar* stamina;
    Vector3 staminaPos; //체력바의 위치를 수치화한 것 (진짜 위치를 위한 중간계산용)
    ProgressBar* staminaRecover;

    float maxStamina = 100;

    float recoverStamina = 100;

    //예리도 UI
    ProgressBar* durability_gauge;

    float curDurability = 80;
    float maxDurability = 80;

    //기인게이지 UI
    ProgressBar* lsGauge2;

    bool isBonus = false;

    float curSpiritGauge = 0;
    float maxSpiritGauge = 100;
    float bonusTime = 0.f;
    float limitTime = 32.f;
    bool bonus154 = false;

    //코팅 UI
    ProgressBar* lsCoting;

    float curCoting = 100;
    float maxCoting = 100;

    UINT cotingLevel = 0;

    //밧줄벌레 쿨타임 부분
    UINT bugCount = 2;

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
};

