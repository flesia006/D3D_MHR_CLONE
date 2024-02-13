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

    float getcurStamina() { return curStamina; }

private:
    Quad* clockFrame;
    Quad* durability;
    Quad* durability_gauge;
    Quad* hpBar;
    Quad* idBar;
    Quad* itemSlot;
    Quad* lsCoting;
    Quad* lsCoting2;
    Quad* lsGauge;
    Quad* lsGauge2;
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

public:
    float curStamina = 100;
    float maxStamina = 100;

    float recoverStamina = 100;

};

