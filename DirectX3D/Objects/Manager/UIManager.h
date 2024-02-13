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
    void Hit(float damage);
    void HealthPotion();
    void LargeHealthPotion();
    void Running();
    void Roll();
    void ReduceDurability();
    void SharpeningStone();
    void GaugeBonus();

    float curStamina = 100;//임시로 public에 올려둠

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
    Quad* staminarBar;

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

    float curGauge = 0;
    float maxGauge = 100;
    float bonusTime = 0;
    float limitTime = 50;

    //코팅 UI
    ProgressBar* lsCoting;

    float curCoting = 100;
    float maxCoting = 100;

    UINT cotingLevel = 0;
};

