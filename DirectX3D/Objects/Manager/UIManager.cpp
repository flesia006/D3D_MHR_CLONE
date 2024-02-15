#include "Framework.h"

UIManager::UIManager()
{
	clockFrame = new Quad(L"Textures/UI/ClockFrame.png");
	clockFrame->Pos() = { 120,960,0 };
	clockFrame->Scale() *= 1.5f;
	clockFrame->UpdateWorld();

	durability = new Quad(L"Textures/UI/Durability_magenta.png");
	durability->Pos() = { 300,900,0 };
	durability->Scale() *= 1.5f;
	durability->UpdateWorld();

	durability_back = new Quad(L"Textures/UI/Durability_Gauge2.png");
	durability_back->Pos() = { 303,900,0 };
	durability_back->Scale() *= 1.5f;

	hpBar = new Quad(L"Textures/UI/HpBar_noColor1.png");
	hpBar->Pos() = { 540,975,0 };
	hpBar->Scale() *= 1.5f;

	idBar = new Quad(L"Textures/UI/IDBar.png");
	idBar->Pos() = { 330,1020,0 };
	idBar->Scale() *= 1.5f;
	idBar->UpdateWorld();

	itemSlot = new Quad(L"Textures/UI/ItemSlot.png");
	itemSlot->Pos() = { 1740,180,0 };
	itemSlot->Scale() *= 1.5f;
	itemSlot->UpdateWorld();

	lsGauge = new Quad(L"Textures/UI/LSGauge.png");
	lsGauge->Pos() = { 510,900,0 };
	lsGauge->Scale() *= 1.5f;
	lsGauge->UpdateWorld();

	quickSlot = new Quad(L"Textures/UI/ActionSlide.png");
	quickSlot->Pos() = { 1500,180,0 };
	quickSlot->Scale() *= 1.5f;
	quickSlot->UpdateWorld();

	slingerBug = new Quad(L"Textures/UI/SlingerBug.png");
	slingerBug->Scale() *= 1.5f;

	slingerBug2 = new Quad(L"Textures/UI/SlingerBug.png");
	slingerBug2->Scale() *= 1.5f;

	slingerBug3 = new Quad(L"Textures/UI/SlingerBug.png");
	slingerBug3->Scale() *= 1.5f;
	slingerBug3->SetActive(false);

	staminarBar = new Quad(L"Textures/UI/StaminaBar_noColor.png");
	staminarBar->Pos() = { 540,945,0 };
	staminarBar->Scale() *= 1.5f;

	monsterIcon = new Quad(L"Textures/UI/monsterIcon.png");
	monsterIcon->Pos() = { 1830,990,0 };
	monsterIcon->Scale() *= 0.45f;
	monsterIcon->UpdateWorld();

	iconFrame = new Quad(L"Textures/UI/frame2.png");
	iconFrame->Pos() = { 1830,990,0 };
	iconFrame->Scale() *= 2.4f;
	iconFrame->SetActive(false);

	hpBarEdge = new Quad(L"Textures/UI/BarEdge.png");
	hpBarEdge->Pos() = { 885,975,0 };
	hpBarEdge->Scale() *= 1.5f;
	hpBarEdge->UpdateWorld();

	staminarBarEdge = new Quad(L"Textures/UI/BarEdge2.png");
	staminarBarEdge->Pos() = { 885,945,0 };
	staminarBarEdge->Scale() *= 1.5f;
	staminarBarEdge->UpdateWorld();

	clockHand = new Quad(L"Textures/UI/clockhand.png");
	clockHand->Pos() = { 129,963,0 };
	clockHand->Scale() *= 1.5f;

	clockHand2 = new Quad(L"Textures/UI/clockhand2.png");
	clockHand2->Pos() = { 129,963,0 };
	clockHand2->Scale() *= 1.5f;
	clockHand2->Rot().z += XM_PIDIV2 * 2 / 3;
	clockHand2->UpdateWorld();

	blackCircle = new Quad(L"Textures/UI/blackCircle.png");
	blackCircle->SetActive(false);
	blackCircle2 = new Quad(L"Textures/UI/blackCircle.png");
	blackCircle2->SetActive(false);
	blackCircle3 = new Quad(L"Textures/UI/blackCircle.png");
	blackCircle3->SetActive(false);

	blackHalfCircle = new Quad(L"Textures/UI/blackHalfCircle.png");
	blackHalfCircle->SetActive(false);
	blackHalfCircle2 = new Quad(L"Textures/UI/blackHalfCircle.png");
	blackHalfCircle2->SetActive(false);
	blackHalfCircle3 = new Quad(L"Textures/UI/blackHalfCircle.png");
	blackHalfCircle3->SetActive(false);

	orangeLeftHalfCircle = new Quad(L"Textures/UI/orangeHalfCircle.png");
	orangeLeftHalfCircle->SetActive(false);
	orangeLeftHalfCircle2 = new Quad(L"Textures/UI/orangeHalfCircle.png");
	orangeLeftHalfCircle2->SetActive(false);
	orangeLeftHalfCircle3 = new Quad(L"Textures/UI/orangeHalfCircle.png");
	orangeLeftHalfCircle3->SetActive(false);

	orangeRightHalfCircle = new Quad(L"Textures/UI/orangeHalfCircle2.png");
	orangeRightHalfCircle->SetActive(false);
	orangeRightHalfCircle2 = new Quad(L"Textures/UI/orangeHalfCircle2.png");
	orangeRightHalfCircle2->SetActive(false);
	orangeRightHalfCircle3 = new Quad(L"Textures/UI/orangeHalfCircle2.png");
	orangeRightHalfCircle3->SetActive(false);

	// ������ UI �߰�
	qickSlot_Back = new Quad(L"Textures/UI/QickSlot_Back.png");
	qickSlot_Back->Pos() = { 820, 170, 0 };
	qickSlot_Back->Scale() *= 0.3f;
	qickSlot_Back->UpdateWorld();

	qickSlot_Select = new Quad(L"Textures/UI/QickSlot_Select.png");
	qickSlot_Select->Pos() = { 820, 170, 0 };
	qickSlot_Select->Scale() *= 0.3f;
	
	FOR(8)
	{
		Quad* quad = new Quad(L"Textures/UI/SelectBox.png");
		selectBoxs.push_back(quad);
	}

	//ĳ���Ϳ� UI �߰�
	hp = new ProgressBar(
		L"Textures/Color/Hp.png",
		L"Textures/UI/HpBar_noColor1.png"
	);
	recover = new ProgressBar(
		L"Textures/Color/Damaged.png",
		L"Textures/Color/Black.png"
	);
	stamina = new ProgressBar(
		L"Textures/Color/Staminar.png",
		L"Textures/UI/StaminaBar_noColor.png"
	);

	durability_gauge = new ProgressBar(
		L"Textures/Color/Durability.png",
		L"Textures/UI/StaminaBar_noColor.png"
	);
	lsGauge2 = new ProgressBar(
		L"Textures/UI/LSGauge2.png",
		L"Textures/UI/nonebg.png"
	);
	lsCoting = new ProgressBar(
		L"Textures/UI/LSCoting_none.png",
		L"Textures/UI/LSCoting_none.png"
	);

	// hp bar ui
	hp->Scale() = { 2.625f,0.03f,0 };
	hp->Pos() = hpBar->Pos();
	hp->Pos().x -= 0.1f;
	curHP = maxHP;
	recover->Scale() = hp->Scale();
	recover->Pos() = hp->Pos();

	// stamina bar ui
	stamina->Scale() = { 2.625f,0.03f,0 };
	stamina->Pos() = staminarBar->Pos();
	stamina->Pos().x -= 0.1f;
	curStamina = maxStamina;

	//durability_gauge ui
	durability_gauge->Scale() = { 0.45f,0.03f,0 };
	durability_gauge->Pos() = durability_back->Pos();
	curDurability = maxDurability;

	//���ΰ����� UI
	lsGauge2->Scale() = { 1.5f,1.35f,0 };
	lsGauge2->Pos() = lsGauge->Pos();
	lsGauge2->Pos().x += 13.0f;

	//���� UI
	lsCoting->Pos() = { 510,900,0 };
	lsCoting->Scale() *= 1.5f;
}

UIManager::~UIManager()
{
	delete clockFrame;
	delete durability;
	delete durability_back;
	delete hpBar;
	delete idBar;
	delete itemSlot;
	delete lsCoting;
	delete lsGauge;
	delete lsGauge2;
	delete quickSlot;
	delete slingerBug;
	delete slingerBug2;
	delete slingerBug3;
	delete staminarBar;
	delete hp;
	delete recover;
	delete stamina;
	delete durability_gauge;
	delete monsterIcon;
	delete iconFrame;
	delete hpBarEdge;
	delete staminarBarEdge;
	delete clockHand;
	delete clockHand2;
	delete blackCircle;
	delete blackCircle2;
	delete blackCircle3;
	delete blackHalfCircle;
	delete blackHalfCircle2;
	delete blackHalfCircle3;
	delete orangeLeftHalfCircle;
	delete orangeLeftHalfCircle2;
	delete orangeLeftHalfCircle3;
	delete orangeRightHalfCircle;
	delete orangeRightHalfCircle2;
	delete orangeRightHalfCircle3;
	delete qickSlot_Back;
	delete qickSlot_Select;
}

void UIManager::Update()
{
	QickSlotBar();

	stamina->UpdateWorld();
	recover->UpdateWorld();
	hp->UpdateWorld();
	durability_back->UpdateWorld();
	hpBar->UpdateWorld();
	lsCoting->UpdateWorld();
	lsGauge2->UpdateWorld();
	slingerBug->UpdateWorld();
	slingerBug2->UpdateWorld();
	slingerBug3->UpdateWorld();
	staminarBar->UpdateWorld();
	durability_gauge->UpdateWorld();
	iconFrame->UpdateWorld();
	clockHand->UpdateWorld();
	blackCircle->UpdateWorld();
	blackCircle2->UpdateWorld();
	blackCircle3->UpdateWorld();
	blackHalfCircle->UpdateWorld();
	blackHalfCircle2->UpdateWorld();
	blackHalfCircle3->UpdateWorld();
	orangeLeftHalfCircle->UpdateWorld();
	orangeLeftHalfCircle2->UpdateWorld();
	orangeLeftHalfCircle3->UpdateWorld();
	orangeRightHalfCircle->UpdateWorld();
	orangeRightHalfCircle2->UpdateWorld();
	orangeRightHalfCircle3->UpdateWorld();
	qickSlot_Select->UpdateWorld();

	//hp, stamina �κ�
	hp->SetAmount(curHP / maxHP);
	recover->SetAmount(recoverHP / maxHP);
	stamina->SetAmount(curStamina / maxStamina);
	if (curHP < recoverHP)
		curHP += 0.1f * DELTA;
	
	if(staminaActive == false)
		curStamina += 2.5f * DELTA;

	if (curHP > recoverHP)
		recoverHP = curHP;

	//������ �κ�
	durability_gauge->SetAmount(curDurability / maxDurability);

	if (curDurability <= 80.0f && curDurability > 60.0f)
		durability->SetTexture(L"Textures/UI/Durability_magenta.png");
	else if (curDurability < 60.0f && curDurability > 40.0f)
		durability->SetTexture(L"Textures/UI/Durability_white.png");
	else if (curDurability < 40.0f && curDurability > 20.0f)
		durability->SetTexture(L"Textures/UI/Durability_blue.png");
	else if (curDurability < 20.0f && curDurability > 0.0f)
		durability->SetTexture(L"Textures/UI/Durability_green.png");

	////////////////////////////////
	//�������� 0 ���Ϸ� �������� �ʴ´�.
	if (curDurability <= 0.0f)
		curDurability = 0;

	if (curDurability < 0.0f)
		SharpeningStone();
	////////////////////////////////

	//���ΰ����� �κ�
	lsGauge2->SetAmount(curSpiritGauge / maxSpiritGauge);
	
	if (curSpiritGauge > 0.0f)
		curSpiritGauge -= 0.1f * DELTA;
	if (curSpiritGauge <= 0)
		curSpiritGauge = 0;

	if (isBonus)
	{
		bonusTime += 0.1f * DELTA;
		curSpiritGauge += 0.2f * DELTA;
	}

	if (bonusTime > limitTime)
	{
		bonusTime = 0.0f;
		isBonus = false;
		lsGauge2->SetTexture(L"Textures/UI/LSGauge2.png");
	}

	if (bonus154 == true)
	{
		bonusTime += DELTA;
		if (bonusTime < limitTime)
		{
			lsGauge2->SetTexture(L"Textures/UI/LSGauge2_blue.png");
			curSpiritGauge += 2.f * DELTA;			
		}
		else
		{
			lsGauge2->SetTexture(L"Textures/UI/LSGauge2.png");
			bonus154 = false;
		}
	}

	////////////////////////////////
	//���ΰ����� ���û�Ȳ, ���� �ʿ�
	//if (curGauge < 100.0f)
	//	curGauge += 0.2f;

	//if (curGauge > 100.0f)
	//{
	//	curGauge = 0.0f;
	//	curCoting = 100.0f;

	//	if (cotingLevel < 3)
	//		cotingLevel += 1 * DELTA;
	//}

	//if (KEY_PRESS('W'))
	//	GaugeBonus();

	if (cotingLevel <= 3 && cotingLevel > 0) // ���÷����� 1�̻��̶�� ������ �ֱ��� ����
	{
		curCoting -= .3f * DELTA;
	}
	////////////////////////////////

	//���� �κ�
	lsCoting->SetAmount(curCoting / maxCoting);

	if (cotingLevel == 0)
		lsCoting->SetTexture(L"Textures/UI/LSCoting_none.png");
	if (cotingLevel == 1)
		lsCoting->SetTexture(L"Textures/UI/LSCoting_white.png");			
	if (cotingLevel == 2)
		lsCoting->SetTexture(L"Textures/UI/LSCoting_yellow.png");			
	if (cotingLevel == 3)
		lsCoting->SetTexture(L"Textures/UI/LSCoting_red.png");			

	if (curCoting <= 0.0f) // �������� 100�� �����ʰ� 0�� �����ʰ�
		curCoting = 0;
	if (curCoting >= 100.0f)
		curCoting = 100;

	//Ÿ�� ������ ���� ��Ȳ, ���� ���� �ʿ�
	TargetMonster();

	//�ð�ٴ� �κ� : ��ǥ : 5�д� 30�� ���ư��� �ؾ���
	//���� ������ ������ ���ư��°� �����ִ� ����
	if (clockHand->Rot().z > -XM_PIDIV2 * 10 / 3)
		clockHand->Rot().z -= XM_PIDIV2 * 1 / 720;

	//���ٹ��� ��Ÿ�� �κ� - ȸ���ӵ��� ����, ���� �ʿ�
	if (bugCount == 2)
	{
		slingerBug->Pos() = { 997.5,180,0 };
		slingerBug2->Pos() = { 922.5,180,0 };

	}
	else if (bugCount == 3)
	{
		slingerBug->Pos() = { 960,180,0 };
		slingerBug2->Pos() = { 885,180,0 };

		slingerBug3->SetActive(true);
		slingerBug3->Pos() = { 1035,180,0 };
	}

	blackCircle->Pos() = slingerBug->Pos();
	blackHalfCircle->Pos() = slingerBug->Pos();
	orangeLeftHalfCircle->Pos() = slingerBug->Pos();
	orangeRightHalfCircle->Pos() = slingerBug->Pos();

	blackCircle2->Pos() = slingerBug2->Pos();
	blackHalfCircle2->Pos() = slingerBug2->Pos();
	orangeLeftHalfCircle2->Pos() = slingerBug2->Pos();
	orangeRightHalfCircle2->Pos() = slingerBug2->Pos();

	blackCircle3->Pos() = slingerBug3->Pos();
	blackHalfCircle3->Pos() = slingerBug3->Pos();
	orangeLeftHalfCircle3->Pos() = slingerBug3->Pos();
	orangeRightHalfCircle3->Pos() = slingerBug3->Pos();

	if (KEY_DOWN(VK_LBUTTON) && !isCoolTime1)
		isCoolTime1 = true;
	else if (KEY_DOWN(VK_LBUTTON) && isCoolTime1 && !isCoolTime2)
		isCoolTime2 = true;
	else if (KEY_DOWN(VK_LBUTTON) && bugCount == 3 && isCoolTime1 && isCoolTime2 && !isCoolTime3)
		isCoolTime3 = true;

	if (isCoolTime1)
	{
		slingerBug->SetActive(false);
		blackCircle->SetActive(true);
		blackHalfCircle->SetActive(true);
		orangeLeftHalfCircle->SetActive(true);
		orangeRightHalfCircle->SetActive(true);
	}

	if (isCoolTime2)
	{
		slingerBug2->SetActive(false);
		blackCircle2->SetActive(true);
		blackHalfCircle2->SetActive(true);
		orangeLeftHalfCircle2->SetActive(true);
		orangeRightHalfCircle2->SetActive(true);
	}

	if (isCoolTime3)
	{
		slingerBug3->SetActive(false);
		blackCircle3->SetActive(true);
		blackHalfCircle3->SetActive(true);
		orangeLeftHalfCircle3->SetActive(true);
		orangeRightHalfCircle3->SetActive(true);
	}

	/////////////////////////
	//���� ��Ȳ
	if (orangeLeftHalfCircle->Active())
		orangeLeftHalfCircle->Rot().z += XM_PIDIV2 * 1 / 360; // ��Ÿ�� ȸ���ӵ� �κ�

	if (orangeLeftHalfCircle2->Active())
		orangeLeftHalfCircle2->Rot().z += XM_PIDIV2 * 1 / 360; // ��Ÿ�� ȸ���ӵ� �κ�

	if (orangeLeftHalfCircle3->Active())
		orangeLeftHalfCircle3->Rot().z += XM_PIDIV2 * 1 / 360; // ��Ÿ�� ȸ���ӵ� �κ�

	if (KEY_DOWN(VK_RBUTTON))
		GetWildBug();
	/////////////////////////

	if (orangeLeftHalfCircle->Rot().z > XM_2PI)
	{
		orangeLeftHalfCircle->Rot().z -= XM_2PI;
		isCoolTime1 = false;

		slingerBug->SetActive(true);
		blackCircle->SetActive(false);
		blackHalfCircle->SetActive(false);
		orangeLeftHalfCircle->SetActive(false);
		orangeRightHalfCircle->SetActive(false);
	}

	if (orangeLeftHalfCircle2->Rot().z > XM_2PI)
	{
		orangeLeftHalfCircle2->Rot().z -= XM_2PI;
		isCoolTime2 = false;

		slingerBug2->SetActive(true);
		blackCircle2->SetActive(false);
		blackHalfCircle2->SetActive(false);
		orangeLeftHalfCircle2->SetActive(false);
		orangeRightHalfCircle2->SetActive(false);
	}

	if (orangeLeftHalfCircle3->Rot().z > XM_2PI)
	{
		orangeLeftHalfCircle3->Rot().z -= XM_2PI;
		isCoolTime3 = false;

		slingerBug3->SetActive(true);
		blackCircle3->SetActive(false);
		blackHalfCircle3->SetActive(false);
		orangeLeftHalfCircle3->SetActive(false);
		orangeRightHalfCircle3->SetActive(false);
	}
}

void UIManager::PostRender()
{
	recover->Render();
	hp->Render();
	stamina->Render();
	clockFrame->Render();
	durability->Render();
	durability_back->Render();
	hpBar->Render();
	idBar->Render();
	itemSlot->Render();
	lsCoting->Render();
	lsGauge->Render();
	lsGauge2->Render();
	quickSlot->Render();
	slingerBug->Render();
	slingerBug2->Render();
	slingerBug3->Render();
	staminarBar->Render();
	durability_gauge->Render();
	monsterIcon->Render();
	iconFrame->Render();
	hpBarEdge->Render();
	staminarBarEdge->Render();
	clockHand->Render();
	clockHand2->Render();

	blackCircle->Render();
	orangeLeftHalfCircle->Render();
	if (orangeLeftHalfCircle->Rot().z < XM_PI)
		blackHalfCircle->Render();
	if (orangeLeftHalfCircle->Rot().z > XM_PI)
		orangeRightHalfCircle->Render();

	blackCircle2->Render();
	orangeLeftHalfCircle2->Render();
	if (orangeLeftHalfCircle2->Rot().z < XM_PI)
		blackHalfCircle2->Render();
	if (orangeLeftHalfCircle2->Rot().z > XM_PI)
		orangeRightHalfCircle2->Render();

	blackCircle3->Render();
	orangeLeftHalfCircle3->Render();
	if (orangeLeftHalfCircle3->Rot().z < XM_PI)
		blackHalfCircle3->Render();
	if (orangeLeftHalfCircle3->Rot().z > XM_PI)
		orangeRightHalfCircle3->Render();
	qickSlot_Back->Render();
	qickSlot_Select->Render();
}

void UIManager::GUIRender()
{
	qickSlot_Back->GUIRender();
	qickSlot_Select->GUIRender();
}

void UIManager::Hit(float damage)
{
	curHP = curHP - damage;
	hp->SetAmount(curHP / maxHP);

	recoverHP = recoverHP - damage / 2;
	recover->SetAmount(recoverHP / maxHP);
}

void UIManager::HealthPotion()
{
	curHP += 20.0f * DELTA;
}

void UIManager::LargeHealthPotion()
{
	curHP += 30.f * DELTA;
}

void UIManager::Running()
{
	curStamina -= 3.2f * DELTA;
}

void UIManager::Roll()
{
	curStamina -= 15.f;
}

void UIManager::ReduceDurability()
{
	curDurability -= 0.1f * DELTA;
}

void UIManager::SharpeningStone()
{
	curDurability = maxDurability;
}

void UIManager::GaugeBonus()
{
	if (!isBonus)
	{
		isBonus = true;
		lsGauge2->SetTexture(L"Textures/UI/LSGauge2_blue.png");
	}
}

void UIManager::TargetMonster()
{
	if (KEY_DOWN('G'))
	{
		if (iconFrame->Active() == false)
			iconFrame->SetActive(true);
		else if (iconFrame->Active() == true)
			iconFrame->SetActive(false);
	}
}

void UIManager::GetWildBug()
{
	bugCount++;
}

void UIManager::QickSlotBar()
{

}
