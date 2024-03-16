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
        
    float MinusDurability() { return curDurability -= 0.2f; } // ������ ��� �Լ�
    float GetDurabilityLevelCoefft()                            // ������ ���ݷ� ����ġ�� ��ȯ        
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
        cotingLevel++; // ���÷���++
        if (cotingLevel > 3) cotingLevel = 3;
        curCoting = maxCoting;
        return cotingLevel;
    }    
    float MinusCotingLevel() {
        cotingLevel--; // ���÷���--
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
    float curStamina = 100;//�ӽ÷� public�� �÷���
    bool staminaActive = false;

    // ���� ���� ������ ���� ����
    bool specialMove = false;
    bool specialMove2 = false;
    bool partDestruct = false;
    bool partDestruct2 = false;
    bool valDeath = false;

    void UIAlphaOn();
    void StartUIAlphaOn();

private:
    // �� ���� ���� ����
    //=====================
    void QuickSlot(); // �� ���� � ������ ���� ���� ����
    void QuickSlotBar(); // �� ���� ���� ����Ű�� ���� �Լ�
    void DragInvenItem();
    void DragSlot(); // �巡�� ���� ����
    void DragSlotBar(); // �巡�� ���� ����
    void NumberSlot(); // �ѹ� ���� ����
    void NumberSlotBar(); // �ѹ� ���� ����
    //=====================
    // ���� ���� ������ ���� ����
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
    // ������ �߰� �κ�
    Quad* quickSlot_Back;
    Quad* quickSlot_Select;
    Quad* quickSlot_Button;
    vector<Quad*> selectBoxs;
    vector<Quad*> selectBoxFrames;
    // �巡�� ���� �߰� �κ�
    Quad* dragSlotBox;
    Quad* dragSlot_ButtonUp;
    Quad* dragSlot_ButtonWheel;
    Quad* dragSlot_ButtonDown;
    Quad* dragSlot_KeyButton;
    // �ѹ� ���� �߰� �κ�
    vector<Quad*> numberBoxs;
    vector<Quad*> numberBoxFrames;
    // ���� �ȿ� ������ �̸�
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

    // ������ ������ �߰� ( �̰� �� ���Կ� �ִ°͵� )
    Quad* rideGarukIcon;
    //===================
    Quad* potionIcon_Q;
    Quad* greatepotionIcon_Q;
    Quad* whetstoneIcon_Q;
    //=================== ( �Ʒ��� �ٸ� ���� ��)
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
    
    //������ UI
    ProgressBar* hp;
    Vector3 hpPos; //ü�¹��� ��ġ�� ��ġȭ�� �� (��¥ ��ġ�� ���� �߰�����)
    ProgressBar* recover;

    // ���¹̳� UI
    ProgressBar* stamina;
    Vector3 staminaPos; //ü�¹��� ��ġ�� ��ġȭ�� �� (��¥ ��ġ�� ���� �߰�����)
    ProgressBar* staminaRecover;

    //������ UI
    ProgressBar* durability_gauge;

    //���ΰ����� UI
    ProgressBar* lsGauge2;

    //���� UI
    ProgressBar* lsCoting;

    // ���� ���� UI
    Quad* valphalkStateIcon1;
    Quad* valphalkStateIcon2;
    Quad* valphalkStateIcon3;

    // ����Ʈ Ŭ����
    Quad* questClearUI;
    // ����Ʈ ����
    Quad* questStartUI;

    // ������ ������
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
    
    // �� ���� ���� �Ҷ� ���� Ȯ�� �ϱ�
    // �ϴ� 8ĭ �̶� 8�� ����ǵ� �ٲ�� ����
    bool useQuickSlot1 = false;
    bool useQuickSlot2 = false;
    bool useQuickSlot3 = false;
    bool useQuickSlot4 = false;
    bool useQuickSlot5 = false;
    bool useQuickSlot6 = false;
    bool useQuickSlot7 = false;
    bool useQuickSlot8 = false;
    // �Ʒ� �̰� Ư�� Ű�� ������ Bar�� Ȱ��ȭ��
    bool useSelectBar = false;
    Vector3 MousePos;

    int havePotion = 10; // �ִ� 20�� 10��
    int haveGPotion = 0; // �ִ� 10�� 10��

    // �巡�� ���� ���� �Ҷ� ���� Ȯ�� �ϱ�
    bool useDragBar = false;
    bool useDragSlot1 = true;
    bool useDragSlot2 = false;
    bool useDragSlot3 = false;

    float dragTimer = 0.0f;
    // �ѹ� ���� ���� �Ҷ� ���� Ȯ�� �ϱ�
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

    // ���� ���� ����
    float stateIconTimer = 0.0f;
    float stateIconTimer2 = 0.0f;
    float stateIconTimer3 = 0.0f;

    bool isRender = false;
    float clearUITimer = 0.0f;
    UINT clearCount = 0;
    float startUITimer = 0.0f;
    float waitTimer = 0.0f;
    UINT startCount = 0;

    // ������ ������ �ð� üũ��
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

