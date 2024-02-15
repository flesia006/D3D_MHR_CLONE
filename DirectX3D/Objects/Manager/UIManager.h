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
    void TargetMonster();

    float MinusDurability() { return curDurability -= 0.2f; } // ������ ��� �Լ�
    float GetDurabilityLevelCoefft()                            // ������ ���ݷ� ����ġ�� ��ȯ        
    {
        if      (curDurability <= 80.0f && curDurability > 60.0f)        return 1.5f;
        else if (curDurability <= 60.0f && curDurability > 40.0f)        return 1.32f;
        else if (curDurability <= 40.0f && curDurability > 20.0f)        return 1.2f;
        else if (curDurability <= 20.0f && curDurability >= 0.0f)        return 1.05f;
    }

    float PlusSpritGauge()   { return curSpiritGauge += 15; }   // ���ΰ����� �ø��� �Լ�
    float MinusSpiritGauge() { return curSpiritGauge -= 10; }   // ���ΰ����� ��� �Լ�
    float PlusCotingLevel()  {  
        cotingLevel++; // ���÷���++
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
    float curStamina = 100;//�ӽ÷� public�� �÷���
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
    Quad* staminarBar;
    Quad* monsterIcon;
    Quad* iconFrame;
    Quad* hpBarEdge;
    Quad* staminarBarEdge;
    Quad* clockHand;
    Quad* clockHand2;

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

    float curSpiritGauge = 0;
    float maxSpiritGauge = 100;
    float bonusTime = 0.f;
    float limitTime = 32.f;
    bool bonus154 = false;

    //���� UI
    ProgressBar* lsCoting;

    float curCoting = 100;
    float maxCoting = 100;

    UINT cotingLevel = 0;

    
};

