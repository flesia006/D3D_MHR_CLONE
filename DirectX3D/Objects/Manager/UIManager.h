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

    float curStamina = 100;//�ӽ÷� public�� �÷���

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

    float maxStamina = 100;

    float recoverStamina = 100;

    //������ UI
    ProgressBar* durability_gauge;

    float curDurability = 80;
    float maxDurability = 80;

    //���ΰ����� UI
    ProgressBar* lsGauge2;

    bool isBonus = false;

    float curGauge = 0;
    float maxGauge = 100;
    float bonusTime = 0;
    float limitTime = 50;

    //���� UI
    ProgressBar* lsCoting;

    float curCoting = 100;
    float maxCoting = 100;

    UINT cotingLevel = 0;
};

