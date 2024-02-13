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

    //������ UI
    ProgressBar* hp;
    Vector3 hpPos; //ü�¹��� ��ġ�� ��ġȭ�� �� (��¥ ��ġ�� ���� �߰�����)
    ProgressBar* recover;

    float curHP = 100;
    float maxHP = 100;

    float recoverHP = 100;

    // ���¹̳� UI
    ProgressBar* stamina;
    Vector3 staminaPos; //ü�¹��� ��ġ�� ��ġȭ�� �� (��¥ ��ġ�� ���� �߰�����)
    ProgressBar* staminaRecover;

public:
    float curStamina = 100;
    float maxStamina = 100;

    float recoverStamina = 100;

};

